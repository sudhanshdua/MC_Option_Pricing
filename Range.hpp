// Range.hpp : A template class that represents a closed interval [low, high]
// 
// (c) Sudhansh Dua

#ifndef Range_HPP
#define Range_HPP


#include <vector>
using namespace std;


template<typename T>
class Range
{
private:
	T lo;
	T hi;


public:
	// Constructors and Destructor
	Range();									// default constructor
	Range(const T& low1, const T& high1);		// constructor that accepts arguments
	Range(const Range<T>& range);				// copy constructor
	virtual ~Range();							// destructor


	// Modifier functions
	void low(const T& low1);					// sets a new low value in the range
	void high(const T& high1);					// sets a new high value in the range


	// Getter functions
	T low() const;								// gets the low value from a range
	T high() const;								// gets the high value from a range
	T spread() const;							// gets the high - low value from a range


	// Boolean functions
	bool left(const T& value);					// Is this value to the left of the range (i.e. less than the lower level) ?
	bool right(const T& value);					// Is this value to the right of the range (i.e. more than the higher level) ? 
	bool inside(const T& value);				// Is this value inside the range ?


	vector<T> mesh(long nSteps) const;			// creates a discrete mesh


	// Assignment operartor
	Range<T>& operator = (const Range<T>& range);


};


#ifndef Range_CPP
#include "Range.cpp"

#endif

#endif