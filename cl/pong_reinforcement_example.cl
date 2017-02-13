int whoHasWon(
		__global float* ballPosX,
		__global const int* ballRad,
		__global const int* width) {
	if (*ballPosX + *ballRad >= *width)
		return -1;
	else if (*ballPosX <= 0)
		return 1;
	else
		return 0;
}

int reset(
		__global float* ballPosX,
		__global float* ballPosY,
		__global float* ballVelX,
		__global float* ballVelY,
		__global const int* ballRad,
		__global const int* width,
		__global const int* height,
		__global const int* maxBallSpeed,
		__global const int* minBallSpeed,
		__global float* paddle1Pos,
		__global float* paddle2Pos,
		float rand1,
		float rand2,
		float rand3,
		float rand4) {
	*ballPosX = *width / 2;
	*ballPosY = *height / 2;

	*ballVelX = rand1 * (*maxBallSpeed - *minBallSpeed) / 8.0f + *minBallSpeed;
	if (rand2 > 0.5f)
		*ballVelX *= -1;
	*ballVelY = rand3 * (*maxBallSpeed - *minBallSpeed) / 8.0f + *minBallSpeed;
	if (rand4 > 0.5f)
		*ballVelY *= -1;

	*paddle1Pos = *height / 2;
	*paddle2Pos = *height / 2;
}


__kernel void get_nn_input(
		__global int* time,
		__global const int* maxTime,
		__global float* ballPosX,
		__global float* ballPosY,
		__global float* ballVelX,
		__global float* ballVelY,
		__global const int* ballRad,
		__global const int* width,
		__global const int* height,
		__global const int* maxBallSpeed,
		__global const int* minBallSpeed,
		__global float* paddle1Pos,
		__global float* paddle2Pos,
		__global const int* paddleHeight,
		float rand1,
		float rand2,
		float rand3,
		float rand4,
		__global float* input) {
	if (get_global_id(0) == 0) 
	{
		if (whoHasWon(ballPosX, ballRad, width) != 0 || *time >= *maxTime || *time == -1)
		{
			*time = 0;
			reset(ballPosX, ballPosY, ballVelX, ballVelY, ballRad, width, height, maxBallSpeed, minBallSpeed, paddle1Pos, paddle2Pos, rand1, rand2, rand3, rand4);
		}

		input[0] = *ballPosX / *width;
		input[1] = *ballPosY / *height;
		input[2] = *ballVelX / *maxBallSpeed;
		input[3] = *ballVelY / *maxBallSpeed;
		input[4] = *paddle1Pos / (*height - *paddleHeight);
		input[5] = 0;
	}
}
