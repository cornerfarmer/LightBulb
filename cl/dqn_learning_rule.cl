__kernel void determine_action(
	__global const char * last_boolean_output,
	__global int * actions,
	uint size,
	uint index) {
	for (unsigned int i = get_global_id(0); i < size; i += get_global_size(0))
	{
		if (last_boolean_output[i])
			actions[index] = i;
	}
}

__kernel void set_teaching_input(
	__global const float * output,
	__global float * values,
	__global char * enabled,
	__global const float * rewards,
	__global const int * actions,
	__global const char * isTerminalStates,
	uint size,
	uint index,
	float discountFactor) {
	int inputIndex = actions[index];
	for (unsigned int i = get_global_id(0); i < size; i += get_global_size(0))
	{
		if (i != inputIndex) 
		{
			enabled[i] = 0;
		} 
		else 
		{
			enabled[i] = 1;
			values[i] = rewards[index];

			if (!isTerminalStates[index]) {
				int bestOutput = 0;
				for (unsigned int j = 1; j < size; j++)
				{
					if (output[bestOutput] <= output[j])
						bestOutput = j;
				}
				values[i] += discountFactor * output[bestOutput];
			}
		}
	}
}