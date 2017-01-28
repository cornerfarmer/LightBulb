__kernel void six_hump_camel_function(
		__global float * pos,
		__global float * value) {
	if (get_global_id(0) == 0) {
		*value = -1 * (4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4));
	}
}
