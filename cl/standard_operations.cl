__kernel void copy_matrix_to_tensor_area(
	__global const float * M,
	unsigned int M_size1,
	unsigned int M_size2,
	unsigned int M_internal_size2,
	__global float * T,
	unsigned int T_internal_size2,
	unsigned int area)
{
	unsigned int row_gid = get_global_id(0) / get_local_size(0);
	unsigned int col_gid = get_global_id(0) % get_local_size(0);
	for (unsigned int row = row_gid; row < M_size1; row += get_num_groups(0))
	{
		for (unsigned int col = col_gid; col < M_size2; col += get_local_size(0))
		{
			T[(row + area * M_size1) * T_internal_size2 + col] = M[row * M_internal_size2 + col];
		}
	}
}

__kernel void copy_matrix_to_tensor_area_scalar(
	__global const float * M,
	unsigned int M_size1,
	unsigned int M_size2,
	unsigned int M_internal_size2,
	__global float * T,
	unsigned int T_internal_size2,
	__global const int * area)
{
	unsigned int row_gid = get_global_id(0) / get_local_size(0);
	unsigned int col_gid = get_global_id(0) % get_local_size(0);
	for (unsigned int row = row_gid; row < M_size1; row += get_num_groups(0))
	{
		for (unsigned int col = col_gid; col < M_size2; col += get_local_size(0))
		{
			T[(row + *area * M_size1) * T_internal_size2 + col] = M[row * M_internal_size2 + col];
		}
	}
}


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

__kernel void copy_vector_to_matrix_col_scalar(
	__global const float * vec,
	unsigned int vec_size,
	__global float * M,
	unsigned int M_internal_size2,
	__global const int * col)
{
	for (unsigned int i = get_global_id(0); i < vec_size; i += get_global_size(0))
	{
		M[i * M_internal_size2 + *col] = vec[i];
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

__kernel void copy_scalar_to_vector_elem_scalar(
	__global float * vec,
	__global const float * scalar,
	__global const int * element)
{
	if (get_global_id(0) == 0)
		vec[*element] = *scalar;
}

__kernel void copy_scalar_to_vector_elem_char(
	__global char * vec,
	__global const char * scalar,
	unsigned int element)
{
	if (get_global_id(0) == 0)
		vec[element] = *scalar;
}

__kernel void copy_scalar_to_vector_elem_char_scalar(
	__global char * vec,
	__global const char * scalar,
	__global const int * element)
{
	if (get_global_id(0) == 0)
		vec[*element] = *scalar;
}



