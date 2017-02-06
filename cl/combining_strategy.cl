__kernel void set_results(
		__global char * resultVector,
		unsigned int nextResultIndex,
		__global bool * firstPlayerHasWon) {
	if (get_global_id(0) == 0) 
	{
		resultVector[nextResultIndex] = *firstPlayerHasWon;
		resultVector[nextResultIndex + 1] = !*firstPlayerHasWon;
	}
}
