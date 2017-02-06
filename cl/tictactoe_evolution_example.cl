__kernel void set_fields_from_output(
		__global float * output,
		__global float * fields,
		unsigned int fields_internal_size2,
		__global bool * illegalMove,
		int current_player) {
	if (get_global_id(0) == 0) 
	{
		for (unsigned int i = 0; i < 9; i++) 
		{
			if (output[i] > 0.5f)
			{
				int x = i / 3;
				int y = i % 3;
				if (fields[x * fields_internal_size2 + y] != 0)
					*illegalMove = true;
				else 
					fields[x * fields_internal_size2 + y] = current_player;
				return;
			}
		}
		*illegalMove = true;
	}
}

__kernel void reset_environment(
		__global float * fields,
		unsigned int fields_internal_size2,
		__global bool * illegalMove) {
	unsigned int row_gid = get_global_id(0) / get_local_size(0); 
	unsigned int col_gid = get_global_id(0) % get_local_size(0); 
	for (unsigned int row = row_gid; row < 3; row += get_num_groups(0)) 
	{ 
		for (unsigned int col = col_gid; col < 3; col += get_local_size(0)) 
			fields[row * fields_internal_size2 + col] = 0; 
	} 
	*illegalMove = false;
}

__kernel void get_sight(
		__global float * sight,
		__global float * fields,
		unsigned int fields_internal_size2,
		int current_player) {
	unsigned int row_gid = get_global_id(0) / get_local_size(0); 
	unsigned int col_gid = get_global_id(0) % get_local_size(0); 
	for (unsigned int row = row_gid; row < 3; row += get_num_groups(0)) 
	{ 
		for (unsigned int col = col_gid; col < 3; col += get_local_size(0)) 
		{
			int fieldValue = current_player * fields[row * fields_internal_size2 + col];
			if (fieldValue == 1)
				sight[(row * 3 + col) * 2] = 1;
			else
				sight[(row * 3 + col) * 2] = 0;

			if (fieldValue == -1)
				sight[(row * 3 + col) * 2 + 1] = 1;
			else
				sight[(row * 3 + col) * 2 + 1] = 0;
		}
	} 
}

__kernel void calc_who_has_won(
		__global int * whoHasWon,
		__global float * fields,
		unsigned int fields_internal_size2) {
	if (get_global_id(0) == 0) 
	{
		if (fields[0 * fields_internal_size2 + 0] != 0 && fields[0 * fields_internal_size2 + 0] == fields[0 * fields_internal_size2 + 1] && fields[0 * fields_internal_size2 + 1] == fields[0 * fields_internal_size2 + 2])
			*whoHasWon = fields[0 * fields_internal_size2 + 0];
		else if (fields[1 * fields_internal_size2 + 0] != 0 && fields[1 * fields_internal_size2 + 0] == fields[1 * fields_internal_size2 + 1] && fields[1 * fields_internal_size2 + 1] == fields[1 * fields_internal_size2 + 2])
			*whoHasWon = fields[1 * fields_internal_size2 + 0];
		else if (fields[2 * fields_internal_size2 + 0] != 0 && fields[2 * fields_internal_size2 + 0] == fields[2 * fields_internal_size2 + 1] && fields[2 * fields_internal_size2 + 1] == fields[2 * fields_internal_size2 + 2])
			*whoHasWon = fields[2 * fields_internal_size2 + 0];

		else if (fields[0 * fields_internal_size2 + 0] != 0 && fields[0 * fields_internal_size2 + 0] == fields[1 * fields_internal_size2 + 0] && fields[1 * fields_internal_size2 + 0] == fields[2 * fields_internal_size2 + 0])
			*whoHasWon = fields[0 * fields_internal_size2 + 0];
		else if (fields[0 * fields_internal_size2 + 1] != 0 && fields[0 * fields_internal_size2 + 1] == fields[1 * fields_internal_size2 + 1] && fields[1 * fields_internal_size2 + 1] == fields[2 * fields_internal_size2 + 1])
			*whoHasWon = fields[0 * fields_internal_size2 + 1];
		else if (fields[0 * fields_internal_size2 + 2] != 0 && fields[0 * fields_internal_size2 + 2] == fields[1 * fields_internal_size2 + 2] && fields[1 * fields_internal_size2 + 2] == fields[2 * fields_internal_size2 + 2])
			*whoHasWon = fields[0 * fields_internal_size2 + 2];

		else if (fields[0 * fields_internal_size2 + 0] != 0 && fields[0 * fields_internal_size2 + 0] == fields[1 * fields_internal_size2 + 1] && fields[1 * fields_internal_size2 + 1] == fields[2 * fields_internal_size2 + 2])
			*whoHasWon = fields[0 * fields_internal_size2 + 0];
		else if (fields[2 * fields_internal_size2 + 0] != 0 && fields[2 * fields_internal_size2 + 0] == fields[1 * fields_internal_size2 + 1] && fields[1 * fields_internal_size2 + 1] == fields[0 * fields_internal_size2 + 2])
			*whoHasWon = fields[2 * fields_internal_size2 + 0];
		else
			*whoHasWon = 0;
	}
}

__kernel void set_winner(
		__global bool * firstPlayerHasWon,
		__global int * whoHasWon,
		__global bool * illegalMove,
		int currentPlayer,
		char parasiteEnvironment) {
	if (get_global_id(0) == 0) 
	{
		if (*illegalMove)
		{
			if (currentPlayer == -1)
				*firstPlayerHasWon = false;
			else
				*firstPlayerHasWon = true;
		}
		else
		{
			if (*whoHasWon == 0) {
				if (parasiteEnvironment)
					*firstPlayerHasWon = false;
				else
					*firstPlayerHasWon = true;
			}
			else if (*whoHasWon == 1) {
				*firstPlayerHasWon = true;
			}
			else if (*whoHasWon == -1) {
				*firstPlayerHasWon = false;
			}
		}
	}
}