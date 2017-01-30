float distanceBetweenPositions(__global float * pos1, __global float * pos2)
{
	return sqrt(pow(pos1[0] - pos2[0], 2) + pow(pos1[1] - pos2[1], 2));
}

__kernel void calc_fitness(
		__global float * pos,
		unsigned int pos_size,
		__global float * consumers,
		__global float * fitness) {
	if (get_global_id(0) == 0) {
		*fitness = 0;
		for (unsigned int p = 0; p < pos_size; p += 2)
		{
			*fitness -= distanceBetweenPositions(pos + p, consumers + p * 2);
			*fitness -= distanceBetweenPositions(pos + p, consumers + (p + 1) * 2);
			if (p < pos_size - 2)
				*fitness -= distanceBetweenPositions(pos + p, pos + p + 2);
		}
	}
}
