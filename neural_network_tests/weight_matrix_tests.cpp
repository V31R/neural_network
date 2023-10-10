#pragma once

#include "pch.h"

#include "../../neural_network/neural_network/layer.hpp"
#include "../../neural_network/neural_network/weight_matrix.hpp"

TEST(TestConstructorFloatMatrix, Default) {

	float value{ 42.f };

	size_t m{ 2u };
	size_t n{ 5u };

	WeigthsMatrix<float>  weigthsMatrix{ m, n };

	EXPECT_EQ(m, weigthsMatrix.getRowNumber());
	EXPECT_EQ(n, weigthsMatrix.getColumnNumber());

}


TEST(TestMultiplicationFloatMatrix, MatricesMultiplication) {

	float value{ 42.f };

	Layer<float> left{ 3u };

	left.neurons[0] = 1;
	left.neurons[1] = 2;
	left.neurons[2] = 3;

	WeigthsMatrix<float>  right{ 3u, 2u };

	right.weights_[0][0] = 1; right.weights_[0][1] = 2;
	right.weights_[1][0] = 3; right.weights_[1][1] = 4;
	right.weights_[2][0] = 5; right.weights_[2][1] = 6;

	Layer<float> trueResult{ 2 };

	trueResult.neurons[0] = 22;
	trueResult.neurons[1] = 28;

	auto result = left * right;

	for (size_t i{ 0u }; i < trueResult.size(); i++) {

		EXPECT_FLOAT_EQ(trueResult.neurons[i], result.neurons[i]);

	}

}

TEST(TestMultiplicationFloatMatrix, LayerAndMatrixMultiplication) {

	float value{ 42.f };

	WeigthsMatrix<float>  left{ 2u, 3u };
	WeigthsMatrix<float>  right{ 3u, 2u };

	left.weights_[0][0] = 1; left.weights_[0][1] = 2; left.weights_[0][2] = 3;
	left.weights_[1][0] = 4; left.weights_[1][1] = 5; left.weights_[1][2] = 6;

	right.weights_[0][0] = 1; right.weights_[0][1] = 2;
	right.weights_[1][0] = 3; right.weights_[1][1] = 4;
	right.weights_[2][0] = 5; right.weights_[2][1] = 6;


	WeigthsMatrix<float>  trueResult{ 2u, 2u };

	trueResult.weights_[0][0] = 22; trueResult.weights_[0][1] = 28;
	trueResult.weights_[1][0] = 49; trueResult.weights_[1][1] = 64;

	auto result = left * right;


	EXPECT_EQ(trueResult.getRowNumber(), result.getRowNumber());
	EXPECT_EQ(trueResult.getColumnNumber(), result.getColumnNumber());

	for (size_t i{ 0u }; i < trueResult.getRowNumber(); i++) {

		for (size_t j{ 0u }; j < trueResult.getColumnNumber(); j++) {

			EXPECT_FLOAT_EQ(trueResult.weights_[i][j], result.weights_[i][j]);

		}

	}

}