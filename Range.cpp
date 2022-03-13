//	Implementing the class that is defined in the header file: "Range.hpp"
//
//	(c) Sudhansh Dua


#ifndef Range_CPP
#define Range_CPP


#include "Range.hpp"


// Constructors and Destructor
template <typename T>
Range<T>::Range()					
{ // Default constructor

	T def(0);
	hi = def;
	lo = def;
}


template <typename T>								
Range<T>::Range(const T& low1, const T& high1)
{ // Constructor that accepts arguments

	if (low1 < high1)
	{
		lo = low1;
		hi = high1;
	}
	else
	{
		lo = high1;
		hi = low1;
	}
}


template <typename T>								
Range<T>::Range(const Range<T>& range) : lo(range.lo), hi(range.hi)
{ //	 Copy constructor

}


template <typename T>
Range<T>::~Range()
{ // Destructor

}


// Modifier functions
template <typename T>
void Range<T>::low(const T& low1)
{
	lo = low1;
}

template <typename T>
void Range<T>::high(const T& high1)
{
	hi = high1;
}


// Getter functions
template <typename T>
T Range<T>::low() const
{
	return lo;
}

template <typename T>
T Range<T>::high() const
{
	return hi;
}

template <typename T>
T Range<T>::spread() const
{
	return hi - lo;
}


// Boolean functions
template <typename T>
bool Range<T>::left(const T& value)
{
	if (value < lo)
	{
		return true;
	}
	else
		return false;
}

template <typename T>
bool Range<T>::right(const T& value)
{
	if (value > hi)
	{
		return true;
	}
	else
		return false;
}

template <typename T>
bool Range<T>::inside(const T& value)
{
	if ((value >= lo) && (value <= hi))   // Closed interval
	{
		return true;
	}
	else
		return false;
}


// Assignment operator
template <typename T>
Range<T>& Range<T>::operator = (const Range<T>& range)
{
	if (this == &range)
	{
		return *this;
	}
	hi = range.hi;
	lo = range.lo;

	return *this;
}


template <typename T>
vector<T> Range<T>::mesh(long nSteps) const
{
	T step_size = (hi - lo) / T(nSteps);

	vector<T> result(nSteps + 1);

	T value = lo;

	for (int i = 0; i < nSteps + 1; i++)
	{
		result[i] = value;
		value += step_size;
	}

	return result;
}


#endif