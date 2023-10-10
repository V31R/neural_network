#pragma once

#include <vector>
#include <functional>

#include "neuron.hpp"


template <typename T>
T defaultActivation(T arg) {

    return arg;

}

template <typename T>
class Layer {

public:

    Layer(std::function<T(T)> activation = defaultActivation<T>) :

        activation_{ activation }

    {}

    Layer(size_t size, std::function<T(T)> activation = defaultActivation<T>):
    
       Layer{ activation }

    {

        neurons.resize(size);

    }

    Layer(const std::vector<T> & array, std::function<T(T)> activation = defaultActivation<T>) :

        Layer{ activation }

    {

        neurons.resize(array.size());
        for (size_t i{ 0u }; i < array.size(); i++) {

            neurons[i] = array[i];

        }

    }

    std::vector<T> activate(const std::vector<T>& resultAfterMultipication) const{

        std::vector<T> result{ resultAfterMultipication };
        for (size_t i{ 0u }; i < resultAfterMultipication.size(); i++) {

            result[i] = activation_(neurons[i] + resultAfterMultipication[i]);

        }

        return result;

    }
    

    size_t size() const {

        return neurons.size();

    }

    std::function<T(T)> getActivate() const {

        return activation_;

    }

    /// <summary>
    /// </summary>
    /// <returns> Memory size of dynamic parts in bites </returns>
    size_t getMemorySize() const {

        T a;
        return sizeof(a) * neurons.size() * CHAR_BIT;

    }

    size_t getParametersNumber() const {

        return neurons.size();

    }


    std::vector<T> neurons;

private:

    std::function<T(T)> activation_;

};