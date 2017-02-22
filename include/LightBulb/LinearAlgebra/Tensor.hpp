#pragma once

#ifndef _TENSOR_H_
#define _TENSOR_H_

// Includes
#include <viennacl/matrix.hpp>
#include "AbstractLinearAlgebraObject.hpp"


namespace viennacl
{
	template<typename NumericT, typename F>
	void copy(std::vector<Eigen::Matrix<NumericT, -1, -1>> const & cpu_tensor,
		viennacl::matrix<NumericT, F> & vcl_tensor)
	{
		typedef typename viennacl::matrix<NumericT>::size_type      size_type;

		std::vector<NumericT> data(vcl_tensor.internal_size());
		for (size_type matrix = 0; matrix < cpu_tensor.size(); ++matrix)
		{
			for (size_type row = 0; row < cpu_tensor[matrix].rows(); ++row)
			{
				for (size_type column = 0; column < cpu_tensor[matrix].cols(); ++column)
					data[F::mem_index(matrix * cpu_tensor[matrix].rows() + row, column, vcl_tensor.internal_size1(), vcl_tensor.internal_size2())] = cpu_tensor[matrix]((int)row, (int)column);
			}
		}

		viennacl::backend::memory_write(vcl_tensor.handle(), 0, sizeof(NumericT) * data.size(), &(data[0]));
	}

	template<typename NumericT, typename F>
	void copy(const matrix<NumericT, F> & gpu_tensor,
		std::vector<Eigen::Matrix<NumericT, -1, -1>> & cpu_tensor)
	{
		typedef typename matrix<float, F>::size_type      size_type;

		if ((gpu_tensor.size1() > 0) && (gpu_tensor.size2() > 0))
		{
			std::vector<NumericT> temp_buffer(gpu_tensor.internal_size());
			viennacl::backend::memory_read(gpu_tensor.handle(), 0, sizeof(NumericT)*gpu_tensor.internal_size(), &(temp_buffer[0]));

			//now copy entries to cpu_matrix:
			for (size_type matrix = 0; matrix < cpu_tensor.size(); ++matrix)
			{
				for (size_type row = 0; row < cpu_tensor[matrix].rows(); ++row)
				{
					for (size_type column = 0; column < cpu_tensor[matrix].cols(); ++column)
						cpu_tensor[matrix]((int)row, (int)column) = temp_buffer[F::mem_index(matrix * cpu_tensor[matrix].rows() + row, column, gpu_tensor.internal_size1(), gpu_tensor.internal_size2())];
				}
			}
		}
	}
}

namespace LightBulb
{
	/**
	 * \brief Describes a three dimensional linear algebra data structure, also called tensor.
	 * \details Internally they are just stored as an array of matrices (cpu) and as one big matrix which contains all those smaller matrices (gpu).
	 * \tparam DataType The data type which should be stored in the data structure.
	 */
	template<typename DataType = float>
	class Tensor : public AbstractLinearAlgebraObject<std::vector<Eigen::Matrix<DataType, -1, -1>>, viennacl::matrix<DataType>>
	{
	private:
		/**
		 * \brief 
		 */
		mutable int viennaclMatrices;
	protected:
		void copyToEigen() const override
		{
			if (this->eigenValue.size() != viennaclMatrices || this->eigenValue.size() > 0 && (this->eigenValue[0].rows() != this->viennaclValue.size1() || this->eigenValue[0].cols() != this->viennaclValue.size2()))
				this->eigenValue.resize(viennaclMatrices, Eigen::Matrix<DataType, -1, -1>(this->viennaclValue.size1(), this->viennaclValue.size2()));

			viennacl::copy(this->viennaclValue, this->eigenValue);
		}
		void copyToViennaCl() const override
		{
			if (this->eigenValue.size() != viennaclMatrices || this->eigenValue.size() > 0 && (this->eigenValue[0].rows() != this->viennaclValue.size1() || this->eigenValue[0].cols() != this->viennaclValue.size2()))
			{
				viennaclMatrices = this->eigenValue.size();
				this->viennaclValue.resize(this->eigenValue[0].rows() * viennaclMatrices, this->eigenValue[0].cols());
			}

			if (this->eigenValue.size() != 0)
				viennacl::copy(this->eigenValue, this->viennaclValue);
		}
	public:
		/**
		 * \brief Creates a new tensor with a specific size.
		 * \param matrices The amount of matrices.
		 * \param rows The amount of rows.
		 * \param cols The amount of cols.
		 */
		Tensor(int matrices = 0, int rows = 0, int cols = 0)
		{
			viennaclMatrices = 0;
			if (matrices > 0 && rows > 0 && cols > 0) {
				this->eigenValue.resize(matrices, Eigen::Matrix<DataType, -1, -1>(rows, cols));
				this->eigenValueIsDirty = true;
			}
		}

		/*Tensor(const Eigen::Tensor<DataType, 3>& eigenTensor)
		{
			viennaclMatrices = 0;
			this->eigenValue = eigenTensor;
			this->eigenValueIsDirty = true;
		}*/

		/*Tensor(const Tensor& other)
			: AbstractLinearAlgebraObject<Eigen::Tensor<DataType, 3>, viennacl::matrix<DataType>>()
		{
			if (!((other.eigenValueIsDirty && other.eigenValue.size() == 0) || (other.viennaclValueIsDirty && other.viennaclValue.size1() == 0 && other.viennaclValue.size2() == 0) || (other.eigenValue.size() == 0 && other.viennaclValue.size1() == 0 && other.viennaclValue.size2() == 0)))
				copyAllFrom(other);
		}*/

	};

}



#endif