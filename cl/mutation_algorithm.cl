__kernel void mutateWeights( 
          __global float * W1, 
          unsigned int W1_row_start, unsigned int W1_col_start, 
          unsigned int W1_row_inc, unsigned int W1_col_inc, 
          unsigned int W1_row_size, unsigned int W1_col_size, 
          unsigned int W1_internal_rows, unsigned int W1_internal_cols,
          __global float * mutationStrength, 
          unsigned int mutationStrength_start, unsigned int mutationStrength_inc, unsigned int mutationStrength_size,
		  unsigned int mutationStrengthIndexOffset,
		  __global float* randNumbers,
		  unsigned int randNumbersOffset) 
{ 
	unsigned int row_gid = get_global_id(0) / get_local_size(0);
	unsigned int col_gid = get_global_id(0) % get_local_size(0);
	for (unsigned int row = row_gid; row < W1_row_size; row += get_num_groups(0))
	{
		for (unsigned int col = col_gid; col < W1_col_size; col+=get_local_size(0))
		{
			W1[(row * W1_row_inc + W1_row_start) * W1_internal_cols + col * W1_col_inc + W1_col_start] += mutationStrength[(row * W1_col_size + col + mutationStrengthIndexOffset) * mutationStrength_inc + mutationStrength_start] * randNumbers[randNumbersOffset + row * W1_col_size + col];
		}
	}
} 


__kernel void mutateMutationStrength( 
          __global float * mutationStrength, 
          unsigned int mutationStrength_start, unsigned int mutationStrength_inc, unsigned int mutationStrength_size,
		  float mutationStrengthChangeSpeed, float mutationStrengthMax, float mutationStrengthMin, __global float* randNumbers) 
{ 
	for (unsigned int i = get_global_id(0); i < mutationStrength_size; i += get_global_size(0)) 
	{
		mutationStrength[i*mutationStrength_inc+mutationStrength_start] *= exp(mutationStrengthChangeSpeed * randNumbers[i]); 
		mutationStrength[i*mutationStrength_inc+mutationStrength_start] = (mutationStrength[i*mutationStrength_inc+mutationStrength_start] < 0 ? -1 : 1) * min(mutationStrengthMax, max(mutationStrengthMin, fabs(mutationStrength[i*mutationStrength_inc+mutationStrength_start])));
	}
} 
