// custom-vector.cpp : Defines the entry point for the application.
//
#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
	Vector<int> v;
	std::cout << "size: " << v.size() << "\n";
	std::cout << "capacity: " << v.capacity() << "\n";
	std::cout << "empty: " << v.empty() << "\n";
}
