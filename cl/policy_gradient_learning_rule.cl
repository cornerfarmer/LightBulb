__kernel void get_error_vector(
	__global float * errorVector,
	__global const char * last_boolean_output,
	__global const float * output,
	uint size) {
	for (unsigned int i = get_global_id(0); i < size; i += get_global_size(0))
	{
		errorVector[i] = last_boolean_output[i] - output[i];
	}
}


__kernel void compute_rewards(
	__global float * rewardRecord,
	__global const char * isTerminalStateRecord,
	__global const int * recordStart,
	__global const int * nextRecordIndex,
	__global int * lastRelevantIndex,
	uint buffer_size
) {
	if (get_global_id(0) == 0)
	{
		*lastRelevantIndex = -1;
		int i = *nextRecordIndex - 1;
		do
		{
			if (i < 0)
				i = buffer_size - 1;

			if (*lastRelevantIndex == -1 && isTerminalStateRecord[i])
				*lastRelevantIndex = i;
			if (*lastRelevantIndex != -1)
			{
				if (!isTerminalStateRecord[i])
					rewardRecord[i] = rewardRecord[(i + 1) % buffer_size] * 0.99f;
			}
			i--;
		} while (i != *recordStart - 1);
	}
}



__kernel void compute_gradients(
	__global float * gradient,
	unsigned int gradient_size1,
	unsigned int gradient_size2,
	unsigned int gradient_internal_size2,
	__global const float * gradientRecord,
	unsigned int gradientRecord_internal_size2,
	__global const float * rewardRecord,
	__global const int * recordStart,
	__global const int * nextRecordIndex,
	__global const int * lastRelevantIndex,
	uint buffer_size
) {
	unsigned int row_gid = get_global_id(0) / get_local_size(0);
	unsigned int col_gid = get_global_id(0) % get_local_size(0);
	for (unsigned int row = row_gid; row < gradient_size1; row += get_num_groups(0))
	{
		for (unsigned int col = col_gid; col < gradient_size2; col += get_local_size(0))
		{
			for (int i = *recordStart; i != (*lastRelevantIndex + 1) % buffer_size; i++, i %= buffer_size)
			{
				gradient[row * gradient_internal_size2 + col] += gradientRecord[(row + i * gradient_size1) * gradientRecord_internal_size2 + col] * rewardRecord[i];
			}
		}
	}
}


__kernel void compute_next_record_start(
	__global int * recordStart,
	__global const int * lastRelevantIndex,
	uint buffer_size
) {
	if (get_global_id(0) == 0)
	{
		*recordStart = (*lastRelevantIndex + 1) % buffer_size;
	}
}


__kernel void compute_next_record_index(
	__global int * nextRecordIndex,
	uint buffer_size
) {
	if (get_global_id(0) == 0)
	{
		*nextRecordIndex++;
		*nextRecordIndex %= buffer_size;
	}
}
