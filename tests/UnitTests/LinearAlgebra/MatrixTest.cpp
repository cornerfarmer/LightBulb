#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "gtest/gtest.h"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"

using namespace LightBulb;

TEST(Matrix, basicCompute)
{
	Matrix<> A(1024, 1024);
	Matrix<> B(1024, 1024);
	Matrix<> C(1024, 1024);

	for (int r = 0; r < A.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < A.getEigenValue().cols(); c++)
		{
			A.getEigenValueForEditing()(r, c) = 0.5;
			B.getEigenValueForEditing()(r, c) = 0.25;
		}
	}

	C.getViennaclValueForEditing() = viennacl::linalg::prod(A.getViennaclValue(), B.getViennaclValue());

	for (int r = 0; r < C.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < C.getEigenValue().cols(); c++)
		{
			EXPECT_EQ(128, C.getEigenValue()(r, c));
		}
	}
}


TEST(Matrix, assignOperatorTest)
{
	Matrix<> A(1024, 1024);
	Matrix<> B(1024, 1024);

	for (int r = 0; r < A.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < A.getEigenValue().cols(); c++)
		{
			A.getEigenValueForEditing()(r, c) = 0.5;
		}
	}

	B.getViennaclValue();

	A = B;

	EXPECT_EQ(A, B);
}
//
//TEST(Matrix, performanceTest)
//{
//	viennacl::vector<float> testMatrix(1024);
//	viennacl::scalar<float> sum = 0;
//	testMatrix = viennacl::scalar_vector<float>(1024, 1);
//
//	auto& test1 = getKernel("test", "test1", "test.cl");
//	std::cout << test1.global_work_size(0) << "," << test1.global_work_size(1) << std::endl;
//	clock_t begin = clock();
//	for (int i = 0; i < 100000; i++) {
//		viennacl::ocl::enqueue(test1(cl_uint(1),
//			cl_uint(2),
//			cl_uint(3),
//			cl_uint(4),
//			cl_uint(5),
//			cl_uint(6))
//		);
//	}
//	clock_t end = clock();
//	double time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//	viennacl::backend::finish();
//
//
//	auto& test2 = getKernel("test", "test2", "test.cl");
//	test2.global_work_size(0, 1);
//	test2.local_work_size(0, 1);
//	viennacl::ocl::enqueue(test2(cl_uint(1))
//		);
//	begin = clock();
//	for (int i = 0; i < 1000000; i++) {
//		viennacl::ocl::enqueue(test2(cl_uint(1))
//		);
//	}
//	viennacl::backend::finish();
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//	viennacl::backend::finish();
//
//	auto& test3 = getKernel("test", "test3", "test.cl");
//	test3.global_work_size(1, 1);
//	begin = clock();
//	for (int i = 0; i < 100000; i++) {
//		//viennacl::ocl::enqueue(test3(viennacl::traits::opencl_handle(testMatrix), viennacl::traits::opencl_handle(sum))
//		testMatrix = viennacl::scalar_vector<float>(1024, 1);
//		//);
//	}
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//	viennacl::backend::finish();
//	std::cout << sum << std::endl;
//}
//
//TEST(Matrix, performanceTestWSum)
//{
//	WeightedSumFunction function;
//	// 2 - 3 - 1 Network:
//	std::vector<Vector<>> activations;
//	activations.push_back(Vector<>(128));
//	activations[0].getEigenValueForEditing().setRandom();
//	activations.push_back(Vector<>(129));
//	activations[1].getEigenValueForEditing().setRandom();
//	activations.push_back(Vector<>(10));
//
//	std::vector<Vector<>> netInputs(3);
//	netInputs[0] = Vector<>(18);
//	netInputs[1] = Vector<>(128);
//	netInputs[2] = Vector<>(9);
//
//	std::vector<Matrix<>> weights(2);
//	weights[0] = Matrix<>(128, 129);
//	weights[0].getEigenValueForEditing().setRandom();
//	weights[1] = Matrix<>(128, 129);
//	weights[1].getEigenValueForEditing().setRandom();
//
//	
//	for (int j = 0; j < 1000; j++)
//	{
//		clock_t begin = clock();
//		for (int i = 0; i < 100000; i++) {
//			netInputs[1].getEigenValueForEditing().noalias() = weights[1 - 1].getEigenValue().leftCols(128) * activations[1 - 1].getEigenValue();
//			netInputs[1].getEigenValueForEditing().noalias() += weights[1 - 1].getEigenValue().col(128);
//		}
//		clock_t end = clock();
//		double time = (double)(end - begin) / CLOCKS_PER_SEC;
//		std::cout << time << ";A" << (end - begin) << std::endl;
//
//		begin = clock();
//		for (int i = 0; i < 100000; i++) {
//			netInputs[1].getEigenValueForEditing().noalias() = weights[1].getEigenValue() * activations[1].getEigenValue();
//		}
//		end = clock();
//		time = (double)(end - begin) / CLOCKS_PER_SEC;
//		std::cout << time << ";B" << (end - begin) << std::endl;
//	}
//
//	Eigen::VectorXf expect = netInputs[1].getEigenValue();
//	function.setCalculatorType(CT_GPU);
//	function.execute(1, activations, netInputs, weights);
//	viennacl::backend::finish();
//
//	clock_t begin = clock();
//	for (int i = 0; i < 100000; i++) {
//		function.execute(1, activations, netInputs, weights);
//	}
//	viennacl::backend::finish();
//	clock_t end = clock();
//	double time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//
//	for (int i = 0; i < netInputs[1].getEigenValue().size(); i++)
//	{
//		EXPECT_NEAR(expect(i), netInputs[1].getEigenValue()(i), 0.0001);
//	}
//
//	netInputs[1].getViennaclValueForEditing() = viennacl::linalg::prod(weights[0].getViennaclValue(), activations[0].getViennaclValue());
//	viennacl::backend::finish();
//
//	begin = clock();
//	for (int i = 0; i < 100000; i++) {
//		netInputs[1].getViennaclValueForEditing() = viennacl::linalg::prod(weights[0].getViennaclValue(), activations[0].getViennaclValue());
//	}
//	viennacl::backend::finish();
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//}
//
//#define SIZE 1024
//TEST(Matrix, performanceTestComp)
//{
//	viennacl::matrix<float> v_W1(SIZE, SIZE);
//	viennacl::matrix<float> v_W2(2, SIZE);
//	viennacl::vector<float> v_o1(SIZE);
//	viennacl::vector<float> v_o2(2);
//	viennacl::vector<float> v_i(SIZE);
//
//	Eigen::MatrixXf e_W1(SIZE, SIZE);
//	Eigen::MatrixXf e_W2(2, SIZE);
//	Eigen::VectorXf e_o1(SIZE);
//	Eigen::VectorXf e_o2(2);
//	Eigen::VectorXf e_i(SIZE);
//
//	for (int i = 0; i < SIZE; i++)
//	{
//		for (int j = 0; j < SIZE; j++)
//		{
//			e_W1(i, j) = (float)rand() / RAND_MAX;
//		}
//	}
//
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < SIZE; j++)
//		{
//			e_W2(i, j) = (float)rand() / RAND_MAX;
//		}
//	}
//
//	for (int j = 0; j < SIZE; j++)
//	{
//		e_i(j) = (float)rand() / RAND_MAX;
//	}
//
//	viennacl::copy(e_W1, v_W1);
//	viennacl::copy(e_W2, v_W2);
//	viennacl::copy(e_i, v_i);
//
//	v_o1 = viennacl::linalg::prod(v_W1, v_i);
//	v_o2 = viennacl::linalg::prod(v_W2, v_o1);
//	viennacl::backend::finish();
//
//	clock_t begin = clock();
//
//	for (int i = 0; i < 10000; i++) {
//		v_o1 = viennacl::linalg::prod(v_W1, v_i);
//		v_o2 = viennacl::linalg::prod(v_W2, v_o1);
//	}
//	viennacl::backend::finish();
//	clock_t end = clock();
//	double time = (double)(end - begin) / CLOCKS_PER_SEC;
//
//	std::cout << time << ";" << (end - begin) << std::endl;
//	std::cout << v_o2(0) << ", " << v_o2(1) << std::endl;
//
//
//	begin = clock();
//
//	for (int i = 0; i < 10000; i++) {
//		e_o1 = e_W1 * e_i;
//		e_o2 = e_W2 * e_o1;
//	}
//
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//
//	std::cout << time << ";" << (end - begin) << std::endl;
//	std::cout << e_o2(0) << ", " << e_o2(1) << std::endl;
//}
//
//#define SIZE2 100000000
//
//TEST(Matrix, performanceSum)
//{
//	viennacl::vector<float> vienna(SIZE2);
//	viennacl::scalar<float> sum = 0;
//	Eigen::VectorXf eigen(SIZE2);
//
//	for (int j = 0; j < SIZE2; j++)
//	{
//		eigen(j) = (float)rand() / RAND_MAX;
//	}
//
//	auto& testSum = getKernel("test", "testSum", "test.cl");
//	//testSum.global_work_size(0, 1);
//	//testSum.local_work_size(0, 1);
//	std::cout << testSum.global_work_size(0) << "," << testSum.global_work_size(1) << std::endl;
//	std::cout << testSum.local_work_size(0) << "," << testSum.local_work_size(1) << std::endl;
//	viennacl::ocl::enqueue(testSum(
//		viennacl::traits::opencl_handle(vienna),
//		cl_uint(SIZE2),
//		viennacl::traits::opencl_handle(sum)
//	));
//	viennacl::backend::finish();
//
//	clock_t begin = clock();
//	viennacl::ocl::enqueue(testSum(
//		viennacl::traits::opencl_handle(vienna),
//		cl_uint(SIZE2),
//		viennacl::traits::opencl_handle(sum)
//	));
//	viennacl::backend::finish();
//	clock_t end = clock();
//	double time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//	std::cout << sum << std::endl;
//
//	float sumEigen = 0;
//
//	begin = clock();
//
//	for (int i = 0; i < SIZE2; i++) {
//		sumEigen += eigen(i);
//	}
//
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//
//	std::cout << time << ";" << (end - begin) << std::endl;
//	std::cout << sumEigen << std::endl;
//}
//
//
//TEST(Matrix, performanceNN)
//{
//	FeedForwardNetworkTopologyOptions options;
//	options.neuronsPerLayerCount.resize(3);
//	options.neuronsPerLayerCount[0] = 2;
//	options.neuronsPerLayerCount[1] = 8192;
//	options.neuronsPerLayerCount[2] = 1;
//	options.useBiasNeuron = false;
//	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction()));
//
//	NeuralNetwork neuralNetwork(new FeedForwardNetworkTopology(options));
//
//	neuralNetwork.getNetworkTopology().getAllWeights()[0].getEigenValueForEditing().setRandom();
//
//	neuralNetwork.getNetworkTopology().getAllWeights()[1].getEigenValueForEditing().setRandom();
//
//	Vector<> input(options.neuronsPerLayerCount[0]);
//	input.getEigenValueForEditing().setRandom();
//
//	TopologicalOrder topologicalOrder;
//
//
//	neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
//
//	clock_t begin = clock();
//	for (int i = 0; i < 100000; i++)
//		neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
//	clock_t end = clock();
//	double time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//	
//
//	neuralNetwork.getNetworkTopology().setCalculatorType(CT_GPU);
//	neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
//	viennacl::backend::finish();
//	begin = clock();
//	for (int i = 0; i < 100000; i++)
//		neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
//	viennacl::backend::finish();
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//}
//
//
//
//TEST(Matrix, performanceFermi)
//{
//	FermiFunction fermiFunction;
//	std::vector<Vector<>> activation;
//	std::vector<Vector<>> netInput;
//	netInput.push_back(Vector<>(128));
//	activation.push_back(Vector<>(128));
//
//	netInput[0].getEigenValueForEditing().setRandom();
//
//
//	fermiFunction.execute(0, activation, netInput);
//
//	clock_t begin = clock();
//	for (int i = 0; i < 100000; i++)
//		fermiFunction.execute(0, activation, netInput);
//	clock_t end = clock();
//	double time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//
//	fermiFunction.setCalculatorType(CT_GPU);
//	fermiFunction.execute(0, activation, netInput);
//	viennacl::backend::finish();
//	begin = clock();
//	for (int i = 0; i < 100000; i++)
//		fermiFunction.execute(0, activation, netInput);
//	viennacl::backend::finish();
//	end = clock();
//	time = (double)(end - begin) / CLOCKS_PER_SEC;
//	std::cout << time << ";" << (end - begin) << std::endl;
//
//}
//
//TEST(Matrix, memoryTest)
//{
//	for (int i = 0; i < 100000; i++)
//		(new Vector<>(1000000))->getViennaclValue();
//}