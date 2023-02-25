#ifndef TEST_SUITE_TEMPLATE_H
#define TEST_SUITE_TEMPLATE_H

#include "MyVector.h"
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "Cents.h"


// Uncomment each of these once you have finished the stage.  
// This will enable automated testing to try to help catch any problems.
#define STAGE_1_COMPLETE
#define STAGE_2_COMPLETE
#define STAGE_3_COMPLETE
#define STAGE_4_COMPLETE

// This class will allow us to do some automated testing on the first 4 stages
// of the MyVector class.  To enable testing add the following line to your main().
//     assert(TestSuiteTemplate::runTestSuite());
// You will need to uncomment the #define statements (above) when you have finished
// each stage. 
class TestSuiteTemplate {
public:

	static bool runTestSuite() {
		std::cout << "Running TestSuite ------------------------" << "\n";
		testStage1();
		testStage2();
		testStage3();
		testStage4();

		std::cout << "TestSuite complete -----------------------" << "\n";
		return true;
	}

	static bool testStage1() {
#ifdef STAGE_1_COMPLETE
		std::cout << " --- STAGE 1\n";
		std::cout << "testing constructor... ";
		// create an instance in a block, when the block goes out of scope vEmpty will
		// be destroyed via the destructor.  Ensure the destructor works correctly
		// Ensure the constructor didn't make an allocation call if size was 0.		
		{
			MyVector<Cents> vEmpty;
		}

		// ensure a constructor with a parameter works
		MyVector<Cents> v(3);
		std::cout << "success\n";

		// test the size function
		std::cout << "testing size()... ";
		assert(v.size() == 3);
		std::cout << "success\n";

		// test set functionality
		std::cout << "testing set()/get()... ";
		for (int i = 0; i < v.size(); i++) {
			v.set(i, i * 1);
		}

		// test get functionality
		assert(v.get(0) == 0);
		assert(v.get(1) == 1);
		assert(v.get(2) == 2);
		std::cout << "success\n";

		std::cout << "testing exceptions\n";

		std::cout << "testing exceptions\n";
		// test length_error for the constructor
		try {
			MyVector<Cents> vNegative(-2);
			assert(false && "expected an exception to be thrown here!");
		}
		catch (std::length_error& ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}
		catch (...)
		{
			assert(false);
		}

		// test out of range functionality
		try {
			v.set(-1, 5);
			assert(false);
		}
		catch (std::out_of_range ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}
		catch (...) {
			assert(false);
		}

		// test out of range functionality
		try {
			v.set(3, 5);
			assert(false);
		}
		catch (std::out_of_range ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}
		catch (...) {
			assert(false);
		}

		// ensure the size() function is const
		const MyVector<Cents> v2(3);
		v2.size();

		// ensure the get() function is const
		v2.get(0);

		std::cout << "success!\n";
		std::cout << " --- STAGE 1 passed.\n\n";
#endif
		return true;
	}

	static bool testStage2() {
#ifdef STAGE_2_COMPLETE
		std::cout << " --- STAGE 2\n";

		// test constructor with a std::initializer_list
		std::cout << "Test std::initializer_list...";
		MyVector<Cents> v{ 0, 1, 2 };

		// ensure values were set
		assert(v.get(0) == 0);
		assert(v.get(1) == 1);
		assert(v.get(2) == 2);
		std::cout << "success\n";

		// test this insertion operator
		std::cout << "Testing insertion operator...";
		std::cout << v << "\n";
		std::cout << "success\n";

		// test range exceptions
		std::cout << "Testing out of range...";
		try {
			v.get(4);
		}
		catch (std::out_of_range ex) {
			std::cout << "  expected Exception thrown: " << ex.what() << "\n";
		}
		catch (...)
		{
			assert(false);
		}
		std::cout << "success\n";

		// test the copy constructor
		std::cout << "Testing copy constructor...";
		MyVector<Cents> v2{ 5, 5, 5 };
		MyVector<Cents> v3 = v2;
		int itemCount = 0;
		// ensure elements were copied
		for (int i = 0; i < v3.size(); i++)
		{
			assert(v2.get(i) == v3.get(i));
			itemCount++;
		}
		// ensure size is the same.
		assert(itemCount == v2.size());
		assert(itemCount == v3.size());
		std::cout << "success\n";

		// test the assignment operator (going from small to large).
		std::cout << "Testing assignment...";
		MyVector<Cents> v4{ 5, 6, 7 };
		MyVector<Cents> v5{ 1, 2 };
		v5 = v4;
		// ensure elements were copied
		for (int i = 0; i < v4.size(); i++) {
			assert(v5.get(i) == v4.get(i));
		}
		// ensure size is as expected.
		assert(v5.size() == v4.size());
		assert(v5.size() == 3);

		// test assignment (going from large to small)
		MyVector<Cents> v6{ 5, 5, 5 };
		MyVector<Cents> v7(6);
		v7 = v6;

		// ensure elements were copied
		for (int i = 0; i < v6.size(); i++) {
			assert(v6.get(i) == v7.get(i));
		}
		// ensure size is as expected
		assert(v7.size() == v6.size());
		assert(v7.size() == 3);


		std::cout << "success\n";
		std::cout << " --- STAGE 2 passed.\n\n";
#endif
		return true;
	}

	static bool testStage3() {
#ifdef STAGE_3_COMPLETE
		std::cout << " --- STAGE 3\n";
		MyVector<Cents> v{ 1, 2, 3 };

		// test subscript operator as a setter
		std::cout << "Testing subscript operator[] for set...";
		v[1] = 5;
		assert(v.get(1) == 5);
		std::cout << "success\n";

		// test subscript operator as a getter
		std::cout << "Testing subscript operator[] for get...";
		assert(v.get(1) == v[1]);
		assert(v.get(1) == 5);
		std::cout << "success\n";

		// test out of range exceptions
		std::cout << "Testing subscript operator[] for throwing errors...\n";
		try {
			v[-1];
		}
		catch (std::out_of_range& ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}
		catch (...) {
			assert(false);
		}

		try {
			v[3] = 5;
		}
		catch (std::out_of_range& ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}
		catch (...) {
			assert(false);
		}
		std::cout << "success\n";

		// test if the subscript operator works on a const array
		// this requires a secondary override to the [] operator labelled as const in 2 places
		const MyVector<Cents> v2{ 1, 3, 4 };
		v2[0];

		std::cout << " --- STAGE 3 passed.\n\n";
#endif
		return true;
	}


	static bool testStage4() {
#ifdef STAGE_4_COMPLETE
		std::cout << " --- STAGE 4\n";
		std::cout << "Testing reserve()...\n";
		MyVector<Cents> v1;
		assert(v1.size() <= v1.capacity());
		assert(v1.size() == 0);
		assert(v1.capacity() == 0);

		v1.reserve(3);
		assert(v1.capacity() == 3);
		// even if we reserve, we should be able to access the memory until we resize the vector
		try {
			v1[0] = 0;
		}
		catch (std::out_of_range& ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}

		// test if reserve() copied elements correctly 
		MyVector<Cents> v2{ 0,1,2 };
		v2.reserve(6);
		assert(v2.capacity() == 6);
		assert(v2[0] == 0 && v2[1] == 1 && v2[2] == 2);

		// would be nice if we could assert old memory has been released!
		std::cout << "success (but no guarantee of no memory leaks)\n";

		std::cout << "Testing resize()...\n";
		MyVector<Cents> v3;
		int size = 5;
		v3.resize(size);
		assert(v3.capacity() == size);

		for (int i = 0; i < size; i++) {
			v3[i] = i;
		}
		for (int i = 0; i < size; i++) {
			assert(v3[i] == i);
		}

		// check out of bounds after resize()
		try {
			v1[size] = 99;
		}
		catch (std::out_of_range& ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}

		// check that new vars have been initialized to 0 after resize
		MyVector<Cents> v4{ 1,2 };
		v4.resize(4);
		assert(v4[0] == 1);
		assert(v4[1] == 2);
		assert(v4[2] == 0);
		assert(v4[3] == 0);

		v4.resize(1);
		assert(v4.capacity() == 4);
		assert(v4.size() == 1);
		// check out of bounds after resize() downwards
		try {
			v1[1]; // try to access index 1 which should fail
		}
		catch (std::out_of_range& ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}

		// test push_back functionality
		std::cout << "Testing push_back()...\n";
		MyVector<Cents> v5;
		assert(v5.size() == 0);
		assert(v5.capacity() == 0);
		int trials = 20;
		for (int i = 0; i < trials; i++) {
			v5.push_back(i);
		}
		std::cout << "v5 should contain " << trials << " elements.\n";
		std::cout << v5 << "\n";
		std::cout << "v5 size:" << v5.size() << ", capacity:" << v5.capacity() << "\n";
		assert(v5.size() == trials);
		assert(v5.capacity() >= trials);

		// test if resize leaves capacity where it is
		std::cout << "resizing to 10\n";
		v5.resize(10);
		std::cout << v5 << "\n";
		std::cout << "v5 size:" << v5.size() << ", capacity:" << v5.capacity() << "\n";
		assert(v5.size() == 10);
		assert(v5.capacity() >= 10);

		// test pop_back
		MyVector<Cents> v6{ 0,1,2,3 };
		Cents d = v6.pop_back();
		assert(d == 3);
		assert(v6.size() == 3);
		assert(v6.capacity() >= 3);

		// tets pop_back on an empty vector
		v6.resize(0);
		try {
			v6.pop_back();
		}
		catch (std::exception ex) {
			std::cout << "  expected exception thrown: " << ex.what() << "\n";
		}
		catch (...) {
			assert(false);
		}
		std::cout << " --- STAGE 4 passed.\n\n";
#endif
		return true;
	}

};


#endif	// TESTSUITE_H
