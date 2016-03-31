#pragma once

#ifndef _MATRIXIO_H_
#define _MATRIXIO_H_

// Libary includes
#include <EigenSrc/Dense>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace cereal
{
	template <class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	void serialize(Archive& archive, Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& matrix)
	{
		std::vector<std::vector<double>> vector(matrix.rows(), std::vector<double>(matrix.cols()));
		for (int i = 0; i < matrix.rows(); i++)
		{
			for (int j = 0; j < matrix.cols(); j++)
			{
				vector[i][j] = matrix(i, j);
			}
		}
		archive(vector);
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<Eigen::VectorXd>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<Eigen::VectorXd> & construct)
		{
			construct();
		}
	};
}

#endif