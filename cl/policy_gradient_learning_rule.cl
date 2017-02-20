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
