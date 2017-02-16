__kernel void set_boolean_output_rand(
		__global char * last_boolean_output,
		uint size,
		uint rand) {
	for (unsigned int i = get_global_id(0); i < size; i += get_global_size(0))
		last_boolean_output[i] = (i == rand);
}


__kernel void set_boolean_output_best(
	__global char * last_boolean_output,
	__global const float * last_output,
	uint size) {
	int bestOutput = 0;
	for (unsigned int i = 1; i < size; i++)
	{
		if (last_output[bestOutput] <= last_output[i])
			bestOutput = i;
	}
	for (unsigned int i = 0; i < size; i++)
		last_boolean_output[i] = (i == bestOutput);
}