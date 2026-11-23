// custom-vector.cpp : Defines the entry point for the application.
//
#include <algorithm>
#include <iostream>
#include <string>
#include "vector.h"

int main() {
	Vector<int> it;
	for (int i = 5; i > 0; --i) {
		it.push_back(i * 10);
	}

	for (auto& x : it) {
		x += 1;
	}
	for (const auto& x : it) {
		std::cout << x << " ";
	}
	std::cout << "\n";

	const Vector<int>& view = it;
	for (auto p = view.begin(); p != view.end(); ++p) {
		std::cout << *p << " ";
	}
	std::cout << "\n";

	std::sort(it.begin(), it.end());
	for (int x : it) {
		std::cout << x << " ";
	}
	std::cout << "\n";

	std::cout << *it.cbegin() << " " << (it.cend() - it.cbegin()) << "\n";

	Vector<int> none;
	for (int x : none) {
		std::cout << x;
	}
	std::cout << "none ok\n";

	Vector<std::string> names;
	names.push_back("ada");
	names.push_back("grace");
	for (const auto& n : names) {
		std::cout << n << " ";
	}
	std::cout << "\n";
}