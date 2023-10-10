#pragma once
#include <vector>
#include "layer.hpp"
#include "weight_matrix.hpp"
#include <functional>
#include <random>

template <typename T>
class NeuralNetwork {
public:

	NeuralNetwork(size_t inputLayerSize, size_t outputLayerSize, const std::vector<size_t> & innerLayersSizes, std::function<T(T)> activation, bool random = true) {

		for (auto& layer : innerLayersSizes) {

			layers_.push_back(Layer<T>(layer, activation));

		}

		size_t currentLeftSize = inputLayerSize;

		for (auto& layer : layers_) {

			matrices_.push_back(WeigthsMatrix<T>(currentLeftSize, layer.size()));
			currentLeftSize = layer.size();

		}

		matrices_.push_back(WeigthsMatrix<T>(currentLeftSize, outputLayerSize));

		if (random) {

			fillWeights();

		}

	}

	std::vector<T> predict(const std::vector<T>& X) const{

		std::vector<T>  currentX{ X };

		size_t i{ 0u };
		for (i = 0u; i < layers_.size(); i++) {
			
			currentX = layers_[i].activate(currentX * matrices_[i]);

		}

		return currentX * matrices_.back();

	}

	void fillWeights() {

		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_real_distribution<T> distribution(static_cast<T>(- 1), static_cast<T>(1));

		for (size_t i{ 0u }; i < layers_.size();i++) {

			for (size_t j{ 0u }; j < layers_[i].size(); j++) {

				layers_[i].neurons[j] = distribution(gen);

			}

		}

		for (auto& matrix : matrices_) {

			matrix.randomFill();

		}

	}

	size_t getInputSize() const {

		return matrices_[0].getRowNumber();

	}

	/// <summary>
	/// </summary>
	/// <returns> Memory size of dynamic parts in bites </returns>
	size_t getMemorySize() const {

		size_t memory{ 0u };

		for (auto& layer : layers_) {

			memory += layer.getMemorySize();

		}

		for (auto& matrix : matrices_) {

			memory += matrix.getMemorySize();

		}

		return memory;

	}

	size_t getParametersNumber() const {

		size_t parameters{ 0u };

		for (auto& layer : layers_) {

			parameters += layer.getParametersNumber();

		}

		for (auto& matrix : matrices_) {

			parameters += matrix.getParametersNumber();

		}

		return parameters;

	}


private:

	std::vector<Layer<T>> layers_;
	std::vector<WeigthsMatrix<T>> matrices_;

};
