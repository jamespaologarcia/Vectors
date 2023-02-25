#pragma once
#include <sstream>
#include <iostream>
#include <initializer_list>

template<typename T>
class MyVector
{
private:
	int m_size;
	T* pItems;
	int m_capacity;
public:
	explicit MyVector(int size = 0);

	MyVector(const std::initializer_list<T>& list);

	MyVector(const MyVector<T>& v);

	~MyVector() {
		delete[] pItems;
		pItems = nullptr;
	};
	int size() const;
	T get(int index) const;
	void set(int index, T value);
	bool validateRange(int index) const;
	MyVector& operator=(MyVector<T>& v);
	//Overload the subscript operator ([]) to allow both reading and writing of elements in our	vector.
	T& operator[](int index);
	//ReadOnly
	T operator[](int index) const;
	int capacity() const { return m_capacity; }
	///
	

	/// <summary>
	///• Throw a std::length_error if newSize is less than 0 (with a description of the problem).
	///• Call reserve() to reserve memory for the new size.
	///• Iterate from the current size to the new sizeand set the values to zero.
	///• Set the current size to the new size.
	/// </summary>
	/// <param name="newCapacity"></param>
	void reserve(int newCapacity);
	/// <summary>
	/// • Throw a std::length_error if newSize is less than 0 (with a description of the problem).
	/// • Call reserve() to reserve memory for the new size.
	///	• Iterate from the current size to the new sizeand set the values to zero.
	///	• Set the current size to the new size.
	/// </summary>
	/// <param name="newSize"></param>
	void resize(int newSize);

	/// <summary>
	/// function to add a new element to a vector and dynamically increase the capacity by 2x
	/// </summary>
	/// <param name="value"></param>
	void push_back(T value);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	T pop_back();
};
//std::ostream& operator<<(std::ostream& out, const MyVector& v);

template<typename T>
MyVector<T>::MyVector(int size) : m_size{ size }, pItems{ nullptr }, m_capacity{ size } {
	if (m_size < 0) {
		throw std::length_error("Size cannot be less than 0");
	}
	if (size > 0) {
		pItems = new T[m_size];
	}
}
/// <summary>
/// https://y.yarn.co/e0311657-f54c-46d4-8813-9f21f63ca2ed_text.gif
/// </summary>+
/// 
/// 
/// <param name="v"></param>
template<typename T>
MyVector<T>::MyVector(const MyVector& v) : MyVector(v.size()) {

	for (int i{ 0 }; i < m_size; i++)
	{
		pItems[i] = v.pItems[i];
	}
}
//[Stage 2] Create a constructor that allows for initialization via a std::initializer_list.
template<typename T>
MyVector<T>::MyVector(const std::initializer_list<T>& list)
	: MyVector(list.size())
{
	int index{ 0 };
	for (T element : list)
	{
		pItems[index] = element;
		index++;
	}
}
template<typename T>
int MyVector<T>::size() const {
	return m_size;
}
template<typename T>
T MyVector<T>::get(int index) const {
	validateRange(index);
	return pItems[index];
}
template<typename T>
void MyVector<T>::set(int index, T value) {
	validateRange(index);
	pItems[index] = value;
}
template<typename T>
bool MyVector<T>::validateRange(int index) const {
	if (index < m_size && index >= 0) {
		return true;
	}
	else {
		throw std::out_of_range("Out of range");
	}

}
//Operators
template<typename T>
T& MyVector<T>::operator[](int index) {
	validateRange(index);
	return pItems[index];
}
template<typename T>
T MyVector<T>::operator[](int index) const {
	validateRange(index);
	return pItems[index];
}
/// <summary>
/// Creates a copy constructor to allow us to initialize a vector from another vector
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector& v) {
	if (&v == this) return *this;

	m_size = v.m_size;
	delete[] pItems;
	pItems = nullptr;

	if (v.m_size > 0)
	{
		pItems = new T[m_size];

		for (int i{ 0 }; i < m_size; i++)
		{
			pItems[i] = v.pItems[i];
		}

	}
	return *this;
}
template<typename T>
void MyVector<T>::reserve(int newCapacity) {
	if (newCapacity <= m_capacity) return;

	//ELSE
	//Dynamically allocate new memory for the desired capacity (space)
	T* newMemorySpace = new T[newCapacity];
	for (int i{ 0 }; i < m_capacity; i++)
	{
		//Copy over the existing elements into the newly allocated memory.
		newMemorySpace[i] = pItems[i];
	}
	//Copy over the existing elements into the newly allocated memory.
	m_capacity = newCapacity;
	//De-allocate the old memory (return it to the heap)
	delete[] pItems;
	//Update our pItems to point to the newly allocated memory.
	pItems = newMemorySpace;
}
template<typename T>
void MyVector<T>::resize(int newSize) {
	//Throw a std::length_error if newSize is less than 0 (with a description of the problem).
	if (newSize < 0) throw std::length_error("Size cannot be less than 0");
	//Call reserve() to reserve memory for the new size.
	reserve(newSize);
	//Iterate from the current size to the new sizeand set the values to zero.
	for (int i{ m_size }; i < newSize; i++)
	{
		pItems[i] = 0;
	}
	//Set the current size to the new size.
	m_size = newSize;

}
template<typename T>
void MyVector<T>::push_back(T value) {
	if (m_capacity == 0) reserve(8);
	//if size reaches the capacity, we double the capacity reserve.
	if (m_capacity == m_size) reserve(m_capacity * 2);
	//Adds in the value once we're sure that there's enough capacity to accommodate the new value. 
	pItems[m_size] = value;
	//Increase m_size
	m_size++;
}
template<typename T>
T MyVector<T>::pop_back() {
	if (m_size == 0) throw std::exception("The vector is empty");
	m_size--;
	return pItems[m_size];
}


/// <summary>
/// Overload the insertion (<<) operator to print out a vector containing 3 elements as follows:
// [1.1, 2.2, 3.3].The insertion operator can’t be written as a method, it must be a function(since
// the left hand side of the operation must be a std::ostream, and not an instance of the object we
// want to output.Since we have access to everything we need with the methods we have
// written for MyVector so far we don’t need to make it a friend. (Things get a bit tricky in stage 5
//	if we were to use a friend function, so let’s make it as simple as possible for now).Ensure the
//operator<< definition is in the.cpp file, otherwise your project will not link properly.
/// </summary>
/// <param name="out"></param>
/// <param name="v"></param>
/// <returns></returns>
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& v) {
	out << "[";
	for (int i{ 0 }; i < v.size(); i++)
	{
		out << v.get(i);
		if (i < v.size() - 1)
		{

			out << ",";
		}
	}
	out << "]";
	return out;
}

