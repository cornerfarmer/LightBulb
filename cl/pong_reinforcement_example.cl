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

void reset(
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
		__global float* input,
	__global int* currentPlayer) {
	if (get_global_id(0) == 0) 
	{
		if (whoHasWon(ballPosX, ballRad, width) != 0 || *time >= *maxTime || *time == -1)
		{
			*time = 0;
			reset(ballPosX, ballPosY, ballVelX, ballVelY, ballRad, width, height, maxBallSpeed, minBallSpeed, paddle1Pos, paddle2Pos, rand1, rand2, rand3, rand4);
		}
		*currentPlayer = 1;

		input[0] = *ballPosX / *width;
		input[1] = *ballPosY / *height;
		input[2] = *ballVelX / *maxBallSpeed;
		input[3] = *ballVelY / *maxBallSpeed;
		input[4] = *paddle1Pos / (*height - *paddleHeight);
		input[5] = 0;
	}
}



void movePaddle(
	int dir,
	__global const int* currentPlayer,
	__global float* paddle1Pos,
	__global float* paddle2Pos,
	__global const int* paddleSpeed,
	__global const int* height,
	__global const int* paddleHeight
)
{
	if (*currentPlayer == 1)
	{
		if (dir == 1)
			*paddle1Pos += *paddleSpeed;
		else if (dir == -1)
			*paddle1Pos -= *paddleSpeed;
		*paddle1Pos = max(0.0f, min((float)(*height - *paddleHeight), *paddle1Pos));
	}
	else
	{
		if (dir == 1)
			*paddle2Pos += *paddleSpeed;
		else if (dir == -1)
			*paddle2Pos -= *paddleSpeed;
		*paddle2Pos = max(0.0f, min((float)(*height - *paddleHeight), *paddle2Pos));
	}
}

void executeCompareAI(
	__global const float* ballPosY,
	__global const int* paddleHeight,
	__global int* currentPlayer,
	__global float* paddle1Pos,
	__global float* paddle2Pos,
	__global const int* paddleSpeed,
	__global const int* height)
{
	if (*ballPosY > *paddle2Pos + *paddleHeight / 2)
		movePaddle(1, currentPlayer, paddle1Pos, paddle2Pos, paddleSpeed, height, paddleHeight);
	else
		movePaddle(-1, currentPlayer, paddle1Pos, paddle2Pos, paddleSpeed, height, paddleHeight);
}


void advanceBallWithoutCollision(
	float fac,
	__global float* ballPosX,
	__global float* ballPosY,
	__global const float* ballVelX,
	__global const float* ballVelY
)
{
	*ballPosX += *ballVelX * fac;
	*ballPosY += *ballVelY * fac;
}


void advanceBall(
	float fac,
	__global float* ballPosX,
	__global float* ballPosY,
	__global float* ballVelX,
	__global float* ballVelY,
	__global const int* ballRad,
	__global const int* width,
	__global const int* height,
	__global const int* maxBallSpeed,
	__global const float* paddle1Pos,
	__global const float* paddle2Pos,
	__global const float* speedIncreaseFac,
	__global const int* paddleHeight
)
{
	float nextBallPosX = *ballPosX + *ballVelX * fac;
	float nextBallPosY = *ballPosY + *ballVelY * fac;

	float colTimeX = 0, colTimeY = 0;

	if (nextBallPosY <= 0)
		colTimeY = *ballPosY / -*ballVelY;

	if (nextBallPosY + *ballRad >= *height)
		colTimeY = (*height - (*ballPosY + *ballRad)) / *ballVelY;

	if (nextBallPosX <= 0)
		colTimeX = *ballPosX / -*ballVelX;

	if (nextBallPosX + *ballRad >= *width)
		colTimeX = (*width - (*ballPosX + *ballRad)) / *ballVelX;


	if (colTimeX > 0 && (colTimeY == 0 || colTimeX <= colTimeY))
	{
		advanceBallWithoutCollision(colTimeX, ballPosX, ballPosY, ballVelX, ballVelY);
		if ((*ballVelX > 0 && *ballPosY + *ballRad >= *paddle1Pos && *ballPosY <= *paddle1Pos + *paddleHeight) ||
			(*ballVelX < 0 && *ballPosY + *ballRad >= *paddle2Pos && *ballPosY <= *paddle2Pos + *paddleHeight))
		{
			*ballVelX *= -1;
			//advanceBall(fac - colTimeX, ballPosX, ballPosY, ballVelX, ballVelY, ballRad, width, height, maxBallSpeed, paddle1Pos, paddle2Pos, speedIncreaseFac, paddleHeight);
			if (fabs(*ballVelX * *speedIncreaseFac) < *maxBallSpeed && fabs(*ballVelY * *speedIncreaseFac) < *maxBallSpeed) {
				*ballVelX *= *speedIncreaseFac;
				*ballVelY *= *speedIncreaseFac;
			}
		}
		else
		{
			advanceBallWithoutCollision(fac - colTimeX, ballPosX, ballPosY, ballVelX, ballVelY);
		}
	}
	else if (colTimeY > 0)
	{
		advanceBallWithoutCollision(colTimeY, ballPosX, ballPosY, ballVelX, ballVelY);
		*ballVelY *= -1;
		//advanceBall(fac - colTimeY, ballPosX, ballPosY, ballVelX, ballVelY, ballRad, width, height, maxBallSpeed, paddle1Pos, paddle2Pos, speedIncreaseFac, paddleHeight);
	}
	else
		advanceBallWithoutCollision(fac, ballPosX, ballPosY, ballVelX, ballVelY);
}



__kernel void interpret_nn_output(
	__global int* time,
	__global float* ballPosX,
	__global float* ballPosY,
	__global float* ballVelX,
	__global float* ballVelY,
	__global const int* ballRad,
	__global const int* width,
	__global const int* height,
	__global const int* maxBallSpeed,
	__global float* paddle1Pos,
	__global float* paddle2Pos,
	__global const float* paddleSpeed,
	__global const int* paddleHeight,
	__global const float* output,
	unsigned int output_size,
	__global int* currentPlayer,
	__global const float* speedIncreaseFac
) {
	if (get_global_id(0) == 0)
	{
		if (output[0])
			movePaddle(1, currentPlayer, paddle1Pos, paddle2Pos, paddleSpeed, height, paddleHeight);
		else if ((output_size > 1 && output[1]) || (output_size == 1 && !output[0]))
			movePaddle(-1, currentPlayer, paddle1Pos, paddle2Pos, paddleSpeed, height, paddleHeight);

		*currentPlayer = -1;
		executeCompareAI(ballPosY, paddleHeight, currentPlayer, paddle1Pos, paddle2Pos, paddleSpeed, height);
		advanceBall(1, ballPosX, ballPosY, ballVelX, ballVelY, ballRad, width, height, maxBallSpeed, paddle1Pos, paddle2Pos, speedIncreaseFac, paddleHeight);
		
		*time++;
		//*reward = whoHasWon();
	}
}
