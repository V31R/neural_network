#include <cmath>

template<typename T>
T sigmoid(T x) {

	T alpha = 1;
	return static_cast<T>(1) / (1 + std::exp(static_cast<T>(-alpha) * x));

}