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
	t1 = t1 + 5;
	t1 = t1 + 5;
	t1 = t1 + 5;
	t1 = t1 + 5;
	t1 = t1 + 5;
	t1 = t1 + 5;
}

__kernel void test3(
	__global float* v,
	__global float* sum
		) {
	for (uint i = 0; i < 1024; i++)
		*sum += v[i];
}


