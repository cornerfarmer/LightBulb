#include "Performance/ViennaCLTests.hpp"
#include "Eigen/Dense"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

#define SIZE 1024
#define TESTING 1

void doViennaCLTest()
{
	/*LightBulb::FeedForwardNetworkTopologyOptions options;
	options.neuronsPerLayerCount.resize(3);
	options.neuronsPerLayerCount[0] = 2;
	options.neuronsPerLayerCount[1] = 1024;
	options.neuronsPerLayerCount[2] = 1;
	options.useBiasNeuron = false;
	options.descriptionFactory = new LightBulb::SameNeuronDescriptionFactory(new LightBulb::NeuronDescription(new LightBulb::WeightedSumFunction(), new LightBulb::FermiFunction()));

	LightBulb::NeuralNetwork neuralNetwork(new LightBulb::FeedForwardNetworkTopology(options));

	neuralNetwork.getNetworkTopology().getAllWeights()[0].getEigenValueForEditing().setRandom();

	neuralNetwork.getNetworkTopology().getAllWeights()[1].getEigenValueForEditing().setRandom();

	LightBulb::Vector<> input(options.neuronsPerLayerCount[0]);
	input.getEigenValueForEditing().setRandom();

	LightBulb::TopologicalOrder topologicalOrder;


	neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);

	clock_t begin = clock();
	for (int i = 0; i < 1000; i++)
		neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;


	neuralNetwork.getNetworkTopology().setCalculatorType(LightBulb::CT_GPU);
	neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
	viennacl::backend::finish();
	begin = clock();
	for (int i = 0; i < 1000; i++)
		neuralNetwork.calculateWithoutOutputCopy(input, topologicalOrder, false);
	viennacl::backend::finish();
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	return;*/
	LightBulb::WeightedSumFunction function;
	// 2 - 3 - 1 Network:
	std::vector<LightBulb::Vector<>> activations;
	activations.push_back(LightBulb::Vector<>(64));
	activations[0].getEigenValueForEditing().setRandom();
	activations.push_back(LightBulb::Vector<>(21));
	activations[1].getEigenValueForEditing().setRandom();
	activations.push_back(LightBulb::Vector<>(10));

	std::vector<LightBulb::Vector<>> netInputs(3);
	netInputs[0] = LightBulb::Vector<>(18);
	netInputs[1] = LightBulb::Vector<>(64);
	netInputs[2] = LightBulb::Vector<>(9);

	std::vector<LightBulb::Matrix<>> weights(2);
	weights[0] = LightBulb::Matrix<>(64, 64);
	weights[0].getEigenValueForEditing().setRandom();
	weights[1] = LightBulb::Matrix<>(9, 21);
	weights[1].getEigenValueForEditing().setRandom();


	clock_t begin = clock();
	for (int i = 0; i < 0; i++) {
		function.execute(1, activations, netInputs, weights);
	}
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	Eigen::VectorXf expect = netInputs[1].getEigenValue();
	function.setCalculatorType(LightBulb::CT_GPU);
	function.execute(1, activations, netInputs, weights);
	viennacl::backend::finish();

	auto& test5 = getKernel("test", "test2", "test.cl");
	begin = clock();
	for (int i = 0; i < 100; i++) {
		//function.execute(1, activations, netInputs, weights);
		viennacl::ocl::enqueue(test5(cl_uint(1))
		);
	}
	viennacl::backend::finish();
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	return;


	viennacl::matrix<float> testMatrix(SIZE, SIZE);

	auto& test1 = getKernel("test", "test1", "test.cl");
	begin = clock();
	for (int i = 0; i < 100000; i++) {
		viennacl::ocl::enqueue(test1(cl_uint(1),
			cl_uint(2),
			cl_uint(3),
			cl_uint(4),
			cl_uint(5),
			cl_uint(6))
		);
	}
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	auto& test2 = getKernel("test", "test2", "test.cl");
	begin = clock();
	for (int i = 0; i < 100000; i++) {
		viennacl::ocl::enqueue(test2(cl_uint(1))
		);
	}
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	auto& test3 = getKernel("test", "test3", "test.cl");
	begin = clock();
	for (int i = 0; i < 100000; i++) {
		viennacl::ocl::enqueue(test3(viennacl::traits::opencl_handle(testMatrix))
		);
	}
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	getchar();
	return;

	viennacl::matrix<float> m_W1(SIZE, SIZE);
	viennacl::matrix<float> m_W2(SIZE, SIZE);
	viennacl::matrix<float> m_W3(SIZE, SIZE);

	for (int i = 0; i < 100; i++) {
		m_W1 = viennacl::linalg::prod(m_W2, m_W3);
		std::cout << i << std::endl;
	}
	viennacl::backend::finish();



	LightBulb::Matrix<>A(1024, 1024);
	LightBulb::Matrix<> B(1024, 1024);
	LightBulb::Matrix<> C(1024, 1024);

	/*for (int r = 0; r < A.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < A.getEigenValue().cols(); c++)
		{
			A.getEigenValueForEditing()(r, c) = 0.5;
			B.getEigenValueForEditing()(r, c) = 0.25;
		}
	}*/

	for (int i = 0; i < 100; i++) {
		C.getViennaclValueForEditing() = viennacl::linalg::prod(A.getViennaclValue(), B.getViennaclValue());
		std::cout << i << std::endl;
	}
	std::cout << C.getEigenValue()(43, 12) << std::endl;

	viennacl::matrix<float> v_W1(SIZE, SIZE);
	viennacl::matrix<float> v_W2(2, SIZE);
	viennacl::vector<float> v_o1(SIZE);
	viennacl::vector<float> v_o2(2);
	viennacl::vector<float> v_i(SIZE);

	Eigen::MatrixXf e_W1(SIZE, SIZE);
	Eigen::MatrixXf e_W2(2, SIZE);
	Eigen::VectorXf e_o1(SIZE);
	Eigen::VectorXf e_o2(2);
	Eigen::VectorXf e_i(SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			e_W1(i, j) = (float)rand() / RAND_MAX;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			e_W2(i, j) = (float)rand() / RAND_MAX;
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		e_i(j) = (float)rand() / RAND_MAX;
	}

	viennacl::copy(e_W1, v_W1);
	viennacl::copy(e_W2, v_W2);
	viennacl::copy(e_i, v_i);

	v_o1 = viennacl::linalg::prod(v_W1, v_i);
	viennacl::backend::finish();

	begin = clock();

	for (int i = 0;; i++) {
		if (i%100==0)
		std::cout << i << std::endl;
		v_o1 = viennacl::linalg::prod(v_W1, v_i);
		v_o2 = viennacl::linalg::prod(v_W2, v_o1);
	}
	viennacl::backend::finish();
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;

	std::cout << time << ";" << (end - begin) << std::endl;
	std::cout << v_o2(0) << ", " << v_o2(1) << std::endl;


	begin = clock();

	for (int i = 0; i < 100; i++) {
		e_o1 = e_W1 * e_i;
		e_o2 = e_W2 * e_o1;
	}

	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;

	std::cout << time << ";" << (end - begin) << std::endl;
	std::cout << e_o2(0) << ", " << e_o2(1) << std::endl;
}
