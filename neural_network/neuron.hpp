#pragma once

template <typename T>
struct Neuron {

    Neuron() :

        weight{ 0 }

    {}

    Neuron(T w) :

        weight{ w }

    {}

    T weight;

    friend Neuron<T> operator*(const Neuron<T>& left, const Neuron<T>& right) {

        return Neuron<T>{ left.weight* right.weight };

    }

    Neuron<T>& operator+=(const Neuron<T>& right) {

        this->weight += right.weight;

        return *this;

    }

};