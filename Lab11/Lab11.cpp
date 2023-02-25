#include "TestSuiteTemplate.h"
#include "MyVector.h"
#define _CRTDBG_MAP_ALLOC // for detecting memory leaks
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
#include "Cents.h"
int main()
{
	// for detecting memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TestSuiteTemplate::runTestSuite();

	/*MyVector v1{1.5, 2.5};
	MyVector v2 = v1;
	MyVector v3(v1);
	v3.set(0, 9);
	std::cout << v1 << v2 << v3;*/


	//const MyVector constVec{ 1.1, 2.2 };
	//std::cout << constVec[0];
	//std::vector<Cents> v; // a vector for doing some tests with
	//int iterations = 20;
	//v.reserve(iterations);
	//std::cout << "adding items:\n";
	//for (int i = 0; i < iterations; i++) {
	//	// add an item to the vector
	//	v.push_back(0.0);
	//	// print out some stats
	//	std::cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << "\n";
	//}
	//std::cout << "removing items:\n";
	//for (int i = 0; i < iterations; i++) {
	//	// remove an item from the vector
	//	v.pop_back();
	//	// print out some stats
	//	std::cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << "\n";
	//}

	//MyVector v{ 1,2,3 };
	//std::cout << v;
	//v.resize(6);
	//std::cout << v;
	//v.resize(2);
	//std::cout << v;


	//MyVector<std::string> str{ "Hehe", "Hihi", "Hoho" };
	//std::cout << str;



}