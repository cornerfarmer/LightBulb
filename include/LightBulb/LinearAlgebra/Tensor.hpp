#pragma once

#ifndef _TENSOR_H_
#define _TENSOR_H_

// Includes
#include <unsupported/Eigen/CXX11/Tensor>
#include <viennacl/matrix.hpp>
#include "AbstractLinearAlgebraObject.hpp"


namespace viennacl
{
	template<typename NumericT, typename F>
	void copy(Eigen::Tensor<NumericT, 3> const & cpu_tensor,
		viennacl::matrix<NumericT, F> & vcl_tensor)
	{
		typedef typename viennacl::matrix<NumericT>::size_type      size_type;

		std::vector<NumericT> data(vcl_tensor.internal_size());
		for (size_type matrix = 0; matrix < cpu_tensor.dimension(0); ++matrix)
		{
			for (size_type row = 0; row < cpu_tensor.dimension(1); ++row)
			{
				for (size_type column = 0; column < cpu_tensor.dimension(2); ++column)
					data[F::mem_index(matrix * cpu_tensor.dimension(1) + row, column, vcl_tensor.internal_size1(), vcl_tensor.internal_size2())] = cpu_tensor((int)matrix, (int)row, (int)column);
			}
		}

		viennacl::backend::memory_write(vcl_tensor.handle(), 0, sizeof(NumericT) * data.size(), &(data[0]));
	}

	template<typename NumericT, typename F>
	void copy(const matrix<NumericT, F> & gpu_tensor,
		Eigen::Tensor<NumericT, 3> & cpu_tensor)
	{
		typedef typename matrix<float, F>::size_type      size_type;

		if ((gpu_tensor.size1() > 0) && (gpu_tensor.size2() > 0))
		{
			std::vector<NumericT> temp_buffer(gpu_tensor.internal_size());
			viennacl::backend::memory_read(gpu_tensor.handle(), 0, sizeof(NumericT)*gpu_tensor.internal_size(), &(temp_buffer[0]));

			//now copy entries to cpu_matrix:
			for (size_type matrix = 0; matrix < cpu_tensor.dimension(0); ++matrix)
			{
				for (size_type row = 0; row < cpu_tensor.dimension(1); ++row)
				{
					for (size_type column = 0; column < cpu_tensor.dimension(2); ++column)
						cpu_tensor((int)matrix, (int)row, (int)column) = temp_buffer[F::mem_index(matrix * cpu_tensor.dimension(1) + row, column, gpu_tensor.internal_size1(), gpu_tensor.internal_size2())];
				}
			}
		}
	}
}

namespace LightBulb
{
	// Forward declarations

	template<typename DataType = float>
	class Tensor : public AbstractLinearAlgebraObject<Eigen::Tensor<DataType, 3>, viennacl::matrix<DataType>>
	{
	private:
		mutable int viennaclMatrices;
	protected:
		void copyToEigen() const override
		{
			if (this->eigenValue.dimension(0) != viennaclMatrices || this->eigenValue.dimension(1) != this->viennaclValue.size1() || this->eigenValue.dimension(2) != this->viennaclValue.size2())
				this->eigenValue.resize((int)viennaclMatrices, (int)this->viennaclValue.size1(), (int)this->viennaclValue.size2());

			viennacl::copy(this->viennaclValue, this->eigenValue);
		}

		void copyToViennaCl() const override
		{
			if (this->eigenValue.dimension(0) != viennaclMatrices || this->eigenValue.dimension(1) != this->viennaclValue.size1() || this->eigenValue.dimension(2) != this->viennaclValue.size2())
			{
				viennaclMatrices = this->eigenValue.dimension(0);
				this->viennaclValue.resize(this->eigenValue.dimension(1) * viennaclMatrices, this->eigenValue.dimension(2));
			}

			if (this->eigenValue.size() != 0)
				viennacl::copy(this->eigenValue, this->viennaclValue);
		}

	public:
		Tensor(int matrices, int rows = 0, int cols = 0)
		{
			viennaclMatrices = 0;
			if (matrices > 0 && rows > 0 && cols > 0) {
				this->eigenValue = Eigen::Tensor<DataType, 3>(matrices, rows, cols);
				this->eigenValueIsDirty = true;
			}
		}

		Tensor(const Eigen::Tensor<DataType, 3>& eigenTensor)
		{
			viennaclMatrices = 0;
			this->eigenValue = eigenTensor;
			this->eigenValueIsDirty = true;
		}

		/*Tensor(const Tensor& other)
			: AbstractLinearAlgebraObject<Eigen::Tensor<DataType, 3>, viennacl::matrix<DataType>>()
		{
			if (!((other.eigenValueIsDirty && other.eigenValue.size() == 0) || (other.viennaclValueIsDirty && other.viennaclValue.size1() == 0 && other.viennaclValue.size2() == 0) || (other.eigenValue.size() == 0 && other.viennaclValue.size1() == 0 && other.viennaclValue.size2() == 0)))
				copyAllFrom(other);
		}*/

	};

}



#endif