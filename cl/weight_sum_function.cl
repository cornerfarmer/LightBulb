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
      dot_prod += W[(row * W_row_inc + W_row_start) * W_internal_cols + col * W_col_inc + W_col_start] * actVec[startAct + incAct * col]; 
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