#pragma once

#include <vector>
#include <stdexcept>
#include <random>

#include "layer.hpp"

template <typename T>
struct WeigthsMatrix {
public:

    WeigthsMatrix() :

        rowNumber_{ 0 },
        columnNumber_{ 0 }

    {}

    /// <summary>
    /// create matrix m * n
    /// </summary>
    WeigthsMatrix(size_t m, size_t n) :

        rowNumber_{ m },
        columnNumber_{ n }

    {

        weights_.resize(rowNumber_);
        for (auto& row : weights_) {

            row.resize(columnNumber_);

        }

    }

    size_t getRowNumber() const {

        return rowNumber_;

    }

    size_t getColumnNumber() const {

        return columnNumber_;

    }

    friend Layer<T> operator*(const Layer<T>& left, const WeigthsMatrix<T>& right) {

        if (left.size() != right.getRowNumber()) {

            throw std::invalid_argument("Number of left columns != Number of right rows");

        }

        size_t K{ left.size() };

        Layer<T> result{ right.getColumnNumber() };


        for (size_t j{ 0u }; j < result.size(); j++) {

            result.neurons[j] = 0;

            for (size_t k{ 0u }; k < K; k++) {

                result.neurons[j] += left.neurons[k] * right.weights_[k][j];

            }

        }

        return result;

    }

    friend const std::vector<T> operator*(const std::vector<T>& left, const WeigthsMatrix<T>& right) {

        return (Layer<T>(left) * right).neurons;

    }

    friend WeigthsMatrix<T> operator*(const WeigthsMatrix<T>& left, const WeigthsMatrix<T>& right) {

        if (left.getColumnNumber() != right.getRowNumber()) {

            throw std::invalid_argument("Number of left columns != Number of right rows");

        }
        size_t K{ left.getColumnNumber() };

        WeigthsMatrix<T> result{ left.getRowNumber(), right.getColumnNumber() };

        for (size_t i{ 0u }; i < result.getRowNumber(); i++) {

            for (size_t j{ 0u }; j < result.getColumnNumber(); j++) {

                result.weights_[i][j] = 0;

                for (size_t k{ 0u }; k < K; k++) {

                    result.weights_[i][j] += left.weights_[i][k] * right.weights_[k][j];

                }

            }

        }


        return result;

    }


    void randomFill() {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> distribution(static_cast<T>(-1), static_cast<T>(1));

        for (size_t i{ 0u }; i < this->getRowNumber(); i++) {

            for (size_t j{ 0u }; j < this->getColumnNumber(); j++) {

                this->weights_[i][j] = distribution(gen);

            }

        }

    }

    /// <summary>
    /// </summary>
    /// <returns> Memory size of dynamic parts in bites </returns>
    size_t getMemorySize() const {

        T a;
        return sizeof(a) * rowNumber_ * columnNumber_ * CHAR_BIT;

    }

    size_t getParametersNumber() const {

        return rowNumber_ * columnNumber_;

    }

    std::vector<std::vector<T>> weights_;

private:

    size_t rowNumber_;
    size_t columnNumber_;


};