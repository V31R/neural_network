#pragma once

#include "pch.h"

#include "../../neural_network/neural_network/layer.hpp"


TEST(TestConstructorFloatLayer, SizeDefaultActivation) {

	float value{ 42.f };

	size_t size{ 1u };

	Layer<float> layer{ size };

	EXPECT_EQ(size, layer.size());

	layer.neurons[0] = value;

	EXPECT_FLOAT_EQ(value, layer.neurons[0]);

}

TEST(TestConstructorFloatLayer, DefaultActivationExist) {

	Layer<float> layer{};

	auto f = layer.getActivate();

	EXPECT_TRUE(static_cast<bool>(f));

}

TEST(TestConstructorFloatLayer, DefaultActivation) {

	float value{ 42.f };

	Layer<float> layer{ 1u };
	layer.neurons[0] = value;

	auto f = layer.getActivate();

	EXPECT_FLOAT_EQ(value, layer.getActivate()(layer.neurons[0]));

}

TEST(TestConstructorFloatLayer, ArrayDefaultActivation) {

	std::vector<float> values{ 42.f, 21.f, 31.5f };

	Layer<float> layer{ values };

	for (size_t i{ 0u }; i < values.size(); i++) {

		EXPECT_FLOAT_EQ(values[i], layer.neurons[i]);

	}

}