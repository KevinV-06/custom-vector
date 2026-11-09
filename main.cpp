// custom-vector.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include "vector.h"

int main() {
	Vector<int> v;
	std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << ", empty: " << std::boolalpha << v.empty() << "\n";

	v.reserve(10);
	std::cout << "after reserve(10): size: " << v.size() << ", capacity: " << v.capacity() << "\n";
	v.reserve(5);
	std::cout << "after reserve(5): capacity: " << v.capacity() << "\n";

	Vector<int> nums;
	for (int i = 0; i < 10; ++i) {
		nums.push_back(i * 10);
		std::cout << "size: " << nums.size() << ", capacity: " << nums.capacity() << "\n";
	}

	for (std::size_t i = 0; i < nums.size(); ++i) {
		std::cout << nums[i] << " ";
	}
	std::cout << "\n";

	nums[0] = 999;
	std::cout << "after nums[0] = 999: " << nums[0] << "\n";

	Vector<std::string> words;
	std::string hello = "hello";
	words.push_back(hello);
	words.push_back(std::string("world"));
	std::cout << words[0] << " " << words[1] << "\n";
	std::cout << "hello is still: " << hello << "\n";

	std::string moved = "moved string";
	words.push_back(std::move(moved));
	std::cout << words[2] << "\n";

	Vector<std::string> alias;
	alias.push_back("a string long enough to be stored on the heap");
	alias.push_back(alias[0]);
	std::cout << alias[0] << "\n" << alias[1] << "\n";
}