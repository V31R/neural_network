// neural_network.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "neural_network.hpp"
#include "activation.hpp"
#include <functional>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <utility>

#include "libxl.h"

template<typename T>
std::vector<T> generateArray(size_t size) {

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<T> distribution(static_cast<T>(-1), static_cast<T>(1));


	std::vector<T>  result{};
	result.resize(size);

	for (size_t i{ 0u }; i < size; i++) {

		result[i] = distribution(gen);

	}
	
	return result;

}

template<typename T>
long long int iteration(const NeuralNetwork<T> & nn) {

	auto x = generateArray<T>(nn.getInputSize());

	auto start = std::chrono::high_resolution_clock::now();

	auto res = nn.predict(x);

	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

	return diff.count();

}


template<typename T>
std::pair<long long int,double> testNNiterations(size_t input, size_t output, const std::vector<size_t>& inner, size_t iterations, bool printIteration = true) {

	T a;

	std::function<float(float)> activation = sigmoid<float>;
	NeuralNetwork<T> nn(10u, 1u, inner, activation);
	std::cout << "Type: " << typeid(a).name() << ". NN parameters number: " << nn.getParametersNumber() 
		<< ". NN size: " << sizeof(nn) + nn.getMemorySize()/ CHAR_BIT << " bytes."  << std::endl;

	long long int sum{ 0 };

	for (size_t i{ 0u }; i < iterations; i++) {

		sum += iteration<T>(nn);
		if (printIteration) {
			std::cout << "Iteration: "<<i + 1 << ". Current mean time: " 
				<< std::setprecision(6) << sum / 1000. / (i + 1) << " seconds." << std::endl;
		}

	}
	if (printIteration) {

		std::cout << std::endl;

	}
	double time = sum / 1000. / iterations;

	std::cout << "Type: " << typeid(a).name() << ". Type size: " << sizeof(a) * CHAR_BIT << " bit. "
		<< "Mean time: " << std::setprecision(6) << time << " seconds." << std::endl;

	return { nn.getParametersNumber() , time };

}


template<typename T>
void testNN(size_t input, size_t output, size_t iterations) {

	std::wostringstream oss{};
	oss << typeid(T).name();
	std::wstring type{ oss.str() };

	libxl::Book* book = xlCreateBook();

	libxl::Font* textFont = book->addFont();
	textFont->setSize(11);
	textFont->setName(L"Calibri");

	// formats

	libxl::Format* textFormat = book->addFormat();
	textFormat->setFont(textFont);
	textFormat->setAlignH(libxl::ALIGNH_CENTER);

	libxl::Sheet* sheet = book->addSheet(type.c_str());
	sheet->writeStr(1, 0, L"Number of parameters", textFormat);
	sheet->writeStr(1, 1, L"Time, .sec", textFormat);

	size_t rowNumber{ 2u };
	std::vector<size_t> inner{ 1000, 1000, 1000, 1000 };
	for (size_t i{ 0 }; i < 10; i++) {

		for (size_t j{ 0u }; j < inner.size(); j++) {

			inner[j] += 1000;
			auto [number, time] = testNNiterations<T>(input, output, inner, iterations, false);
			sheet->writeNum(rowNumber, 0, number, textFormat);
			sheet->writeNum(rowNumber, 1, time, textFormat);
			rowNumber++;
			std::cout << std::endl;

		}

	}

	book->save((type + L".xls").c_str());
	book->release();

}

int main(){

	size_t iterations{ 30u };

	size_t input{ 100u }; 
	size_t output{ 1u };
	std::vector<size_t> inner{ 1000, 1000, 1000, 1000 };
	testNN<float>(input, output, iterations);
	testNN<double>(input, output, iterations);

	return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
