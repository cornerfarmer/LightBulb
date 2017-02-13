
__kernel void rms_prop_learning_rate(
	__global float * prevSquaredGradient,
	unsigned int prevSquaredGradient_internal_size2,
	__global float * prevDeltaWeights,
	unsigned int prevDeltaWeights_internal_size2,
	__global float * prevGradient,
	unsigned int prevGradient_internal_size2,
	__global float * weights,
	unsigned int weights_internal_size2,
	__global float * gradient,
	unsigned int gradient_internal_size2,
	unsigned int size1,
	unsigned int size2,
	float gradientMomentum,
	float deltaWeightsMomentum,
	float squaredGradientMomentum,
	float learningRate,
	float minSquaredGradient)
{ 
  unsigned int row_gid = get_global_id(0) / get_local_size(0);
  unsigned int col_gid = get_global_id(0) % get_local_size(0);
  for (unsigned int row = row_gid; row < size1; row += get_num_groups(0)) 
  {
	  for (unsigned int col = col_gid; col < size2; col += get_local_size(0)) 
	  {
		  prevGradient[row * prevGradient_internal_size2 + col] = gradientMomentum * prevGradient[row * prevGradient_internal_size2 + col] + (1 - gradientMomentum) * gradient[row * gradient_internal_size2 + col];
		  prevSquaredGradient[row * prevSquaredGradient_internal_size2 + col] = squaredGradientMomentum * prevSquaredGradient[row * prevSquaredGradient_internal_size2 + col] + (1 - squaredGradientMomentum) * gradient[row * gradient_internal_size2 + col] * gradient[row * gradient_internal_size2 + col];
		  prevDeltaWeights[row * prevDeltaWeights_internal_size2 + col] = deltaWeightsMomentum * prevDeltaWeights[row * prevDeltaWeights_internal_size2 + col] - learningRate * gradient[row * gradient_internal_size2 + col] / sqrt(prevSquaredGradient[row * prevSquaredGradient_internal_size2 + col] - prevGradient[row * prevGradient_internal_size2 + col] * prevGradient[row * prevGradient_internal_size2 + col] + minSquaredGradient);
		  weights[row * weights_internal_size2 + col] += prevDeltaWeights[row * prevDeltaWeights_internal_size2 + col];
	  }
  }

}
