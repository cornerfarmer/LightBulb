__kernel void execute( 
          __global const float * actVec, 
          unsigned int startAct, unsigned int incAct, unsigned int sizeAct, 
          __global float * netInputVec, 
          unsigned int startNetInput, unsigned int incNetInput, unsigned int sizeNetInput, 
          __global const float * W, 
          unsigned int W_row_start, unsigned int W_col_start, 
          unsigned int W_row_inc, unsigned int W_col_inc, 
          unsigned int W_row_size, unsigned int W_col_size, 
          unsigned int W_internal_rows, unsigned int W_internal_cols, 
          __local float * work) 
{ 
  unsigned int row_gid = get_global_id(0) / get_local_size(0); 
  unsigned int col_gid = get_global_id(0) % get_local_size(0); 
  unsigned int lid = get_local_id(0); 
  for (unsigned int row = row_gid; row < W_row_size; row += get_num_groups(0)) 
  { 
    float dot_prod = 0; 
    for (unsigned int col = col_gid; col < W_col_size; col+=get_local_size(0)) 
      dot_prod += W[(row * W_row_inc + W_row_start) * W_internal_cols + col * W_col_inc + W_col_start] * (col < sizeAct ? actVec[startAct + incAct * col] : 1); 
    work[lid] = dot_prod; 
    for(unsigned int stride=get_local_size(0)/2 ; stride>0 ; stride>>=1){ 
      barrier(CLK_LOCAL_MEM_FENCE); 
      if(lid < stride) 
        work[lid] += work[lid+stride]; 
    } 
    if(lid == 0) 
      netInputVec[row * incNetInput + startNetInput] = work[0]; 
  } 
} 


__kernel void execute1(
	__global const float * actVec,
	unsigned int startAct, unsigned int incAct, unsigned int sizeAct,
	__global float * netInputVec,
	unsigned int startNetInput, unsigned int incNetInput, unsigned int sizeNetInput,
	__global const float * W,
	unsigned int W_row_start, unsigned int W_col_start,
	unsigned int W_row_inc, unsigned int W_col_inc,
	unsigned int W_row_size, unsigned int W_col_size,
	unsigned int W_internal_rows, unsigned int W_internal_cols,
	__local float * work)
{
	float sum = 0.0f;
	int row = get_global_id(0); // row index
	for (int col = 0; col < W_col_size; col++)
	{
		sum += W[(row * W_row_inc + W_row_start) * W_internal_cols + col * W_col_inc + W_col_start] * actVec[startAct + incAct * col];
	}
	netInputVec[row] = sum;
}

#define ROW_DIM 0
#define COL_DIM 1
__kernel void execute2(
	__global const float * actVec,
	unsigned int startAct, unsigned int incAct, unsigned int sizeAct,
	__global float * netInputVec,
	unsigned int startNetInput, unsigned int incNetInput, unsigned int sizeNetInput,
	__global const float * W,
	unsigned int W_row_start, unsigned int W_col_start,
	unsigned int W_row_inc, unsigned int W_col_inc,
	unsigned int W_row_size, unsigned int W_col_size,
	unsigned int W_internal_rows, unsigned int W_internal_cols,
	__local float * work)
{
	 // Compute partial dot product
	float sum = (float)0;
	for (int col = get_global_id(COL_DIM); col<W_col_size; col += get_global_size(COL_DIM))
	{
		sum += W[(get_global_id(ROW_DIM) * W_row_inc + W_row_start) * W_internal_cols + col * W_col_inc + W_col_start] * actVec[startAct + incAct * col];
	}

	// Each thread stores its partial sum in WORK
	int rows = get_local_size(ROW_DIM); // rows in group
	int cols = get_local_size(COL_DIM); // initial cols in group
	int ii = get_local_id(ROW_DIM); // local row index in group, 0<=ii<rows
	int jj = get_local_id(COL_DIM); // block index in column, 0<=jj<cols
	work[ii + rows*jj] = sum;
	barrier(CLK_LOCAL_MEM_FENCE); // sync group

								  // Reduce sums in log2(cols) steps
	while (cols > 1)
	{
		cols >>= 1;
		if (jj < cols) work[ii + rows*jj] += work[ii + rows*(jj + cols)];
		barrier(CLK_LOCAL_MEM_FENCE); // sync group
	}

	// Write final result in Y
	if (jj == 0) netInputVec[get_global_id(ROW_DIM)] = work[ii];
}
