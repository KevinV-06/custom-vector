// custom-vector.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include "vector.h"

int main() {
	Vector<std::string> m1;
	m1.push_back("alpha");
	m1.push_back("beta");

	Vector<std::string> m2(std::move(m1));
	std::cout << "m2: " << m2.size() << " " << m2[0] << " " << m2[1] << "\n";
	std::cout << "m1 after move: size " << m1.size() << ", capacity " << m1.capacity() << "\n";

	Vector<std::string> m3;
	m3.push_back("old");
	m3 = std::move(m2);
	std::cout << "m3: " << m3.size() << " " << m3[0] << " " << m3[1] << "\n";
	std::cout << "m2 after move: size " << m2.size() << "\n";

	m3 = std::move(m3);
	std::cout << "m3 after self-move: " << m3.size() << " " << m3[0] << "\n";

	m1.push_back("reused");
	std::cout << "m1 reused: " << m1.size() << " " << m1[0] << "\n";

	Vector<Vector<int>> nested;
	Vector<int> inner;
	inner.push_back(1);
	inner.push_back(2);
	nested.push_back(inner);
	nested.push_back(std::move(inner));
	nested.push_back(Vector<int>());
	std::cout << "nested: " << nested.size() << " " << nested[0].size() << " " << nested[1][1] << "\n";
}