__kernel void element_prod(
    __global float * vec1, 
    unsigned int start1, 
    unsigned int inc1, 
    unsigned int size1, 
    __global const float * vec2, 
    unsigned int start2, 
    unsigned int inc2, 
    __global const float * vec3, 
   unsigned int start3, 
   unsigned int inc3) 
{ 
  for (unsigned int i = get_global_id(0); i < size1; i += get_global_size(0)) 
    vec1[i*inc1+start1] = vec2[i*inc2+start2] * vec3[i*inc3+start3]; 
}

__kernel void outer_prod( 
  __global float * A, 
  unsigned int A_start1, unsigned int A_start2, 
  unsigned int A_inc1,   unsigned int A_inc2, 
  unsigned int A_size1,  unsigned int A_size2, 
  unsigned int A_internal_size1,  unsigned int A_internal_size2, 
  __global const float * vec1, 
  unsigned int start1, 
  unsigned int inc1, 
  unsigned int size1, 
  __global const float * vec2, 
  unsigned int start2, 
  unsigned int inc2, 
  unsigned int size2) 
{ 
  unsigned int row_gid = get_global_id(0) / get_local_size(0); 
  unsigned int col_gid = get_global_id(0) % get_local_size(0); 
  for (unsigned int row = row_gid; row < A_size1; row += get_num_groups(0)) 
  { 
    float tmp = vec1[row * inc1 + start1];
	for (unsigned int col = col_gid; col < A_size2; col += get_local_size(0)) 
      A[(row * A_inc1 + A_start1) * A_internal_size2 + col * A_inc2 + A_start2] -= tmp * vec2[col * inc2 + start2]; 
  } 
} 

__kernel void vec_mul( 
          __global const float * A, 
          unsigned int A_row_start, unsigned int A_col_start, 
          unsigned int A_row_inc, unsigned int A_col_inc, 
          unsigned int A_row_size, unsigned int A_col_size, 
          unsigned int A_internal_rows, unsigned int A_internal_cols, 
          __global const float * v, 
          unsigned int v_start, unsigned int v_inc, unsigned int v_size, 
          __global float * result, 
          unsigned int result_start, unsigned int result_inc, unsigned int result_size, 
          __local float * work) 
{ 
  unsigned int row_gid = get_global_id(0) / get_local_size(0); 
  unsigned int col_gid = get_global_id(0) % get_local_size(0); 
  unsigned int lid = get_local_id(0); 
  for (unsigned int row = row_gid; row < A_row_size; row += get_num_groups(0)) 
  { 
    float dot_prod = 0; 
    for (unsigned int col = col_gid; col < A_col_size; col+=get_local_size(0)) 
      dot_prod += A[(row * A_row_inc + A_row_start) * A_internal_cols + col * A_col_inc + A_col_start] * v[v_start + v_inc * col]; 
    work[lid] = dot_prod; 
    for(unsigned int stride=get_local_size(0)/2 ; stride>0 ; stride>>=1){ 
      barrier(CLK_LOCAL_MEM_FENCE); 
      if(lid < stride) 
        work[lid] += work[lid+stride]; 
    } 
    if(lid == 0) 
      result[row * result_inc + result_start] = work[0]; 
  } 
} 


__kernel void backpropagate_last(
    __global const float * errorVec, 
    unsigned int startErr, 
    unsigned int incErr, 
    unsigned int sizeErr, 
    __global const float * derivVec, 
    unsigned int startDeriv, 
    unsigned int incDeriv, 
	unsigned int sizeDeriv,
    __global const float * actVec, 
   unsigned int startAct, 
   unsigned int incAct, 
   unsigned int sizeAct,
    __global float * deltaVec, 
   unsigned int startDelta, 
   unsigned int incDelta, 
   unsigned int sizeDelta,
   __global float * G, 
   unsigned int G_start1, unsigned int G_start2, 
   unsigned int G_inc1,   unsigned int G_inc2, 
   unsigned int G_size1,  unsigned int G_size2, 
   unsigned int G_internal_size1,  unsigned int G_internal_size2) 
{ 
  for (unsigned int i = get_global_id(0); i < sizeDelta; i += get_global_size(0)) 
    deltaVec[i*incDelta+startDelta] = derivVec[i*incDeriv+startDeriv] * errorVec[i*incErr+startErr]; 

  barrier(CLK_GLOBAL_MEM_FENCE);

  unsigned int row_gid = get_global_id(0) / get_local_size(0); 
  unsigned int col_gid = get_global_id(0) % get_local_size(0); 
  for (unsigned int row = row_gid; row < G_size1; row += get_num_groups(0)) 
  { 
    float tmp = deltaVec[row * incDelta + startDelta];
    for (unsigned int col = col_gid; col < G_size2; col += get_local_size(0)) 
        G[(row * G_inc1 + G_start1) * G_internal_size1 + col * G_inc2 + G_start2] -= tmp * actVec[col * incAct + startAct]; 
  } 
}





__kernel void backpropagate_inner(
    __global const float * errorVec, 
    unsigned int startErr, 
    unsigned int incErr, 
    unsigned int sizeErr, 
    __global const float * derivVec, 
    unsigned int startDeriv, 
    unsigned int incDeriv, 
	unsigned int sizeDeriv,
    __global const float * actVec, 
   unsigned int startAct, 
   unsigned int incAct, 
   unsigned int sizeAct,
    __global float * lastDeltaVec, 
   unsigned int startLastDelta, 
   unsigned int incLastDelta, 
   unsigned int sizeLastDelta,
    __global float * deltaVec, 
   unsigned int startDelta, 
   unsigned int incDelta, 
   unsigned int sizeDelta,
   __global const float * W, 
   unsigned int W_start1, unsigned int W_start2, 
   unsigned int W_inc1,   unsigned int W_inc2, 
   unsigned int W_size1,  unsigned int W_size2, 
   unsigned int W_internal_size1,  unsigned int W_internal_size2,
   __global float * G, 
   unsigned int G_start1, unsigned int G_start2, 
   unsigned int G_inc1,   unsigned int G_inc2, 
   unsigned int G_size1,  unsigned int G_size2, 
   unsigned int G_internal_size1,  unsigned int G_internal_size2) 
{ 

  unsigned int row_gid = get_global_id(0) / get_local_size(0); 
  unsigned int col_gid = get_global_id(0) % get_local_size(0); 
  unsigned int lid = get_local_id(0); 
  for (unsigned int row = row_gid; row < W_row_size; row += get_num_groups(0)) 
  { 
    float dot_prod = 0; 
    for (unsigned int col = col_gid; col < W_col_size; col+=get_local_size(0)) 
      dot_prod += W[(row * W_row_inc + W_row_start) * W_internal_cols + col * W_col_inc + W_col_start] * lastDeltaVec[startLastDelta + incLastDelta * col]; 
    work[lid] = dot_prod; 
    for(unsigned int stride=get_local_size(0)/2 ; stride>0 ; stride>>=1){ 
      barrier(CLK_LOCAL_MEM_FENCE); 
      if(lid < stride) 
        work[lid] += work[lid+stride]; 
    } 
    if(lid == 0) 
      errorVec[row * incErr + startErr] = work[0]; 
  } 

   barrier(CLK_GLOBAL_MEM_FENCE);

  for (unsigned int i = get_global_id(0); i < sizeDelta - 1; i += get_global_size(0)) 
    deltaVec[i*incDelta+startDelta] = derivVec[i*incDeriv+startDeriv] * errorVec[i*incErr+startErr]; 

  barrier(CLK_GLOBAL_MEM_FENCE);

  unsigned int row_gid = get_global_id(0) / get_local_size(0); 
  unsigned int col_gid = get_global_id(0) % get_local_size(0); 
  for (unsigned int row = row_gid; row < G_size1; row += get_num_groups(0)) 
  { 
    float tmp = deltaVec[row * incDelta + startDelta];
    for (unsigned int col = col_gid; col < G_size2; col += get_local_size(0)) 
        G[(row * G_inc1 + G_start1) * G_internal_size1 + col * G_inc2 + G_start2] -= tmp * actVec[col * incAct + startAct]; 
  } 
}

