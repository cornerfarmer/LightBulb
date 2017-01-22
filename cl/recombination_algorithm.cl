__kernel void recombineWeightsWithAverage( 
          __global float * W1, 
          unsigned int W1_row_start, unsigned int W1_col_start, 
          unsigned int W1_row_inc, unsigned int W1_col_inc, 
          unsigned int W1_row_size, unsigned int W1_col_size, 
          unsigned int W1_internal_rows, unsigned int W1_internal_cols,
          __global const float * W2, 
          unsigned int W2_row_start, unsigned int W2_col_start, 
          unsigned int W2_row_inc, unsigned int W2_col_inc, 
          unsigned int W2_row_size, unsigned int W2_col_size, 
          unsigned int W2_internal_rows, unsigned int W2_internal_cols) 
{ 
	unsigned int row_gid = get_global_id(0) / get_local_size(0);
	unsigned int col_gid = get_global_id(0) % get_local_size(0);
	for (unsigned int row = row_gid; row < W1_row_size && row < W2_row_size; row += get_num_groups(0))
	{
		for (unsigned int col = col_gid; col < W1_col_size && col < W2_col_size; col+=get_local_size(0))
		{
			W1[(row * W1_row_inc + W1_row_start) * W1_internal_cols + col * W1_col_inc + W1_col_start] += W2[(row * W2_row_inc + W2_row_start) * W2_internal_cols + col * W2_col_inc + W2_col_start];
			W1[(row * W1_row_inc + W1_row_start) * W1_internal_cols + col * W1_col_inc + W1_col_start] /= 2;
		}
	}
} 


__kernel void recombineMutationStrengthWithAverage( 
          __global float * v1, 
          unsigned int v1_start, unsigned int v1_inc, unsigned int v1_size, 
          __global const float * v2, 
          unsigned int v2_start, unsigned int v2_inc, unsigned int v2_size) 
{ 
	for (unsigned int i = get_global_id(0); i < v1_size && i < v2_size; i += get_global_size(0)) 
	{
		v1[i*v1_inc+v1_start] += v2[i*v2_inc+v2_start]; 
		v1[i*v1_inc+v1_start] /= 2;
	}
} 
