// OptionData.hpp : Encapsulates all the option data
//
// (c) Sudhansh Dua


#ifndef OptionData_HPP
#define OptionData_HPP


#include <algorithm>		// for the max() function
using namespace std;
#include <string>


struct OptionData
{ // option data and behaviour

	double K = 100;
	double T = 1;
	double r = 0.03;
	double sig = 0.2;
	string type = "C";		// "C" - Call (default), "P" - Put
	double D = 0;			// constant dividend yield (= 0 by default)


	// Payoff function
	double payoff(double S)
	{
		if (type == "C")
		{ // Call payoff

			return max(S - K, 0.0);
		}
		else
		{ // Put payoff

			return max(K - S, 0.0);
		}

	}

};


#endif