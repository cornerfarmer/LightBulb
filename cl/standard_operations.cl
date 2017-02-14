__kernel void copy_vector_to_matrix_col(
	__global const float * vec,
	unsigned int vec_size,
	__global float * M,
	unsigned int M_internal_size2,
	unsigned int col)
{
	for (unsigned int i = get_global_id(0); i < vec_size; i += get_global_size(0))
	{
		M[i * M_internal_size2 + col] = vec[i];
	}
}

__kernel void copy_scalar_to_vector_elem(
	__global float * vec,
	__global const float * scalar,
	unsigned int element)
{
	if (get_global_id(0) == 0)
		vec[element] = *scalar;
}