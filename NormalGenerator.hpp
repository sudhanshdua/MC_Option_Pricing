//	NormalGenerator.hpp
// 
//	Using Boost libraries to create a random number generator


#ifndef NormalGenerator_HPP
#define NormalGenerator_HPP

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

class NormalGenerator
{
private:
	// No members as of yet!
	
public:
	virtual double getNormal() const = 0;
};

class BoostNormal : public NormalGenerator
{
private:
	boost::lagged_fibonacci607 rng;
	boost::normal_distribution<> normal;
	boost::variate_generator<boost::lagged_fibonacci607&, boost::normal_distribution<> >* myRandom;

public:
	BoostNormal();				// default constructor
	~BoostNormal();				// destructor

	double getNormal() const;
};

#endif