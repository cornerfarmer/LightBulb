#define _START_ x
#define _INC_ y
#define _SIZE_ z

__kernel void calc_error_vector(
    __global float * errVec, 
    unsigned int startErr, 
    unsigned int incErr, 
    unsigned int sizeErr, 
    __global const float * teachingInpVec, 
    unsigned int startTeachingInp, 
    unsigned int incTeachingInp, 
    __global const float * outputVec, 
   unsigned int startOutputVec, 
   unsigned int incOutputVec) 
{ 
  for (unsigned int i = get_global_id(0); i < sizeErr; i += get_global_size(0)) 
    errVec[i*incErr+startErr] = teachingInpVec[i*incTeachingInp+startTeachingInp] - outputVec[i*incOutputVec+startOutputVec]; 
}

__kernel void calc_specific_error(
    __global float * errVec, 
    unsigned int startErr, 
    unsigned int incErr, 
    unsigned int sizeErr, 
    __global float * specificError) 
{ 
  for (unsigned int i = get_global_id(0); i < sizeErr; i += get_global_size(0)) 
    errVec[i*incErr+startErr] = pow(errVec[i*incErr+startErr], 2); 

  barrier(CLK_GLOBAL_MEM_FENCE);

  *specificError = 0;
  for (unsigned int i = 0; i < sizeErr; i++) 
    *specificError += errVec[i*incErr+startErr];
}
