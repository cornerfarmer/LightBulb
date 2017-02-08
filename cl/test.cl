__kernel void test1(
	unsigned int t1,
	unsigned int t2,
	unsigned int t3,
	unsigned int t4,
	unsigned int t5,
	unsigned int t6
		) {

}


__kernel void test2(
	unsigned int t1
		) {

}

__kernel void test3(
	__global float* v,
	__global float* sum
		) {
	for (uint i = 0; i < 1024; i++)
		*sum += v[i];
}


__kernel void testSum(
	__global float* v,
	unsigned int size,
	__global float* sum
	) {

	float sum2 = 0;
	for (uint i = get_global_id(0); i < size; i+=get_global_size(0))
		sum2 += v[i];
	*sum += sum2;

}


