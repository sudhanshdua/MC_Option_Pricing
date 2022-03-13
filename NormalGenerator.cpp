//	Implementing the class that is defined in the header file: "NormalGenerator.hpp"

#ifndef NormalGenerator_CPP
#define NormalGenerator_CPP


#include "NormalGenerator.hpp"
#include <cmath>


// default constructor
BoostNormal::BoostNormal() : NormalGenerator()
{
	rng = boost::lagged_fibonacci607();				// random number generator
	normal = boost::normal_distribution<>(0, 1);
	myRandom = new boost::variate_generator<boost::lagged_fibonacci607&, boost::normal_distribution<> >(rng, normal);	// dynamic memory
}


// destructor
BoostNormal::~BoostNormal()
{
	delete myRandom;			// de-allocating memory
}


double BoostNormal::getNormal() const
{
	return (*myRandom)();
}


#endif