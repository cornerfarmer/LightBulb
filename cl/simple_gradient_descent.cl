#define _START_ x
#define _INC_ y
#define _SIZE_ z


__kernel void simple_gradient_descent( 
  float learningRate,
  float weightDecayFac,
  __global float * W, 
  unsigned int W_start1, unsigned int W_start2, 
  unsigned int W_inc1,   unsigned int W_inc2, 
  unsigned int W_size1,  unsigned int W_size2, 
  unsigned int W_internal_size1,  unsigned int W_internal_size2,
  const __global float * G, 
  unsigned int G_start1, unsigned int G_start2, 
  unsigned int G_inc1,   unsigned int G_inc2, 
  unsigned int G_internal_size1,  unsigned int G_internal_size2) 
{ 
  unsigned int row_gid = get_global_id(0) / get_local_size(0);
  unsigned int col_gid = get_global_id(0) % get_local_size(0);
  for (unsigned int row = row_gid; row < W_size1; row += get_num_groups(0))
      for (unsigned int col = col_gid; col < W_size2; col += get_local_size(0))
        W[(row * W_inc1 + W_start1) * W_internal_size2 + (col * W_inc2 + W_start2)] -= learningRate * G[(row * G_inc1 + G_start1) * G_internal_size2 + (col * G_inc2 + G_start2)] + weightDecayFac * W[(row * W_inc1 + W_start1) * W_internal_size2 + (col * W_inc2 + W_start2)]; 
}


__kernel void simple_gradient_descent_with_momentum( 
  float learningRate,
  float weightDecayFac,
  float momentum,
  __global float * W, 
  unsigned int W_start1, unsigned int W_start2, 
  unsigned int W_inc1,   unsigned int W_inc2, 
  unsigned int W_size1,  unsigned int W_size2, 
  unsigned int W_internal_size1,  unsigned int W_internal_size2,
  __global float * M, 
  unsigned int M_start1, unsigned int M_start2, 
  unsigned int M_inc1,   unsigned int M_inc2, 
  unsigned int M_size1,  unsigned int M_size2, 
  unsigned int M_internal_size1,  unsigned int M_internal_size2,
  const __global float * G, 
  unsigned int G_start1, unsigned int G_start2, 
  unsigned int G_inc1,   unsigned int G_inc2, 
  unsigned int G_internal_size1,  unsigned int G_internal_size2) 
{ 
  unsigned int row_gid = get_global_id(0) / get_local_size(0);
  unsigned int col_gid = get_global_id(0) % get_local_size(0);
  for (unsigned int row = row_gid; row < W_size1; row += get_num_groups(0)) {
      for (unsigned int col = col_gid; col < W_size2; col += get_local_size(0)) {
        M[(row * W_inc1 + W_start1) * W_internal_size2 + (col * W_inc2 + W_start2)] = -learningRate * G[(row * G_inc1 + G_start1) * G_internal_size2 + (col * G_inc2 + G_start2)] - weightDecayFac * W[(row * W_inc1 + W_start1) * W_internal_size2 + (col * W_inc2 + W_start2)] + momentum * M[(row * M_inc1 + M_start1) * M_internal_size2 + (col * M_inc2 + M_start2)]; 
		W[(row * W_inc1 + W_start1) * W_internal_size2 + (col * W_inc2 + W_start2)] += M[(row * W_inc1 + W_start1) * W_internal_size2 + (col * W_inc2 + W_start2)];
      }
  }
}