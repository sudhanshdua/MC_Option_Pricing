//	1-factor Monte Carlo option pricing with Explicit Euler
//
//	(c) Sudhansh Dua


// Header files
#include "OptionData.hpp"
#include "NormalGenerator.hpp"
#include "Range.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <boost/tuple/tuple.hpp>
using namespace std;


// Stochastic Differential Equation:		----------->		dS(t) = (r - D) * S(t) * dt + sig * S(t) * dW(t)
namespace SDE  
{
	OptionData* data;	

	double drift(double t, double St)
	{ // Drift term
		return ((data->r) - (data->D)) * St;	//	(r - D) * S(t)
	}

	double diffusion(double t, double St)
	{ // Diffusion term
		
		return data->sig * St;					//	(sig) * S(t)
	}
}


template <typename Type>
boost::tuple<Type, Type> SDSE(const vector<Type>& price, const Type& r, const Type& T)
{
	Type sum_price_squared = 0;			// Sum of square of option prices
	Type sum_price = 0;					// Sum of option prices

	for (size_t i = 0; i < price.size(); i++)
	{
		sum_price_squared += price[i] * price[i];
		sum_price += price[i];
	}

	size_t M = price.size();				// Total no. of simulations
	Type SD = sqrt((sum_price_squared - ((1.0 / M) * (sum_price * sum_price))) / (M - 1.0)) * exp(-1.0 * r * T); // Standard Deviation of discounted prices
	Type SE = SD / sqrt(M);

	return boost::make_tuple(SD, SE);
}

int main()
{
	cout << "1-factor Monte Carlo option price with Explicit Euler\n";

	//	Storing data for options in vectors
	typedef boost::tuple<double, double, double, double, double, double, string> Option_Parameters;		//	S, K, T, r, sig, D, type
	vector<Option_Parameters> Options;

	Options.push_back(boost::make_tuple(60, 65, 0.25, 0.08, 0.3, 0.0, "C"));			//	Option 1
	Options.push_back(boost::make_tuple(100, 100, 1.0, 0.00, 0.2, 0.0, "C"));			//	Option 2
	Options.push_back(boost::make_tuple(5, 10, 1.0, 0.12, 0.5, 0.0, "C"));				//	Option 3

	for (size_t i = 0; i < Options.size(); i++)
	{
		vector<double> Call_vector, Put_vector;									//	declaring two vectors to store the values of call and put options


		cout << "\n\nOption: " << i + 1 << endl;
		OptionData myOption;													//	Object to store the characteristics from the Options vector
		double S_0 = Options[i].get<0>();						
		myOption.K = Options[i].get<1>();
		myOption.T = Options[i].get<2>();
		myOption.r = Options[i].get<3>();
		myOption.sig = Options[i].get<4>();
		myOption.D = Options[i].get<5>();
		myOption.type = Options[i].get<6>();


		long N = 100;								//	No. of sub-intervals = 100 by default
		cout << "No. of sub-intervals in time (NT) : ";
		cin >> N;


		Range<double> range(0.0, myOption.T);		//	time interval range from t = 0 to t = T
		double S_old = S_0;							//	variable that will represent the spot price at previous time interval
		double S_new;								//	variable that will represent the spot ptice at the current time interval


		vector<double> St = range.mesh(N);


		long NSim = 10000;							//	No. of simulations = 10000 by default
		cout << "No. of Simulations (NSim) : ";
		cin >> NSim;


		double dt = myOption.T / double(N);			//	time period of the sub-interval
		

		double dW;									//	Random number (Wiener process)
		double call_price = 0.0;
		double put_price = 0.0;

		// NormalGenerator --> base class
		NormalGenerator* myNormal = new BoostNormal;	//	dynamic memory allocation + polymorphism


		using namespace SDE;
		SDE::data = &myOption;


		int count = 0;								//	No. of times S(t) hits origin

		// we atart from simulation number 1
		for (long i = 1; i <= NSim; ++i)
		{
			//	Calculating a path for rach iteration
			if ((i / 10000) * 10000 == i)
			{
				//	Outputs a message after every 10000th iteration
				cout << i << endl;
			}


			S_old = S_0;		//	condition for t = 0
			// from t = 1 to t = T
			for (unsigned long index = 1; index < St.size(); ++index)
			{

				//	Create a random number
				dW = myNormal->getNormal();

				//	Expilcit Euler (FDM)
				S_new = S_old + (dt * drift(St[index - 1], S_old)) + (sqrt(dt) * diffusion(St[index - 1], S_old) * dW);

				//	Moving forward
				S_old = S_new;

				//	Spurious values
				if (S_new <= 0.0)
				{
					count++;
				}
			}


			double tmp1 = myOption.payoff(S_new);		//	temporary variable storing the call payoff for every simulation
			Call_vector.push_back(tmp1);
			call_price += (tmp1) / double(NSim);		//	Calculation of mean call price for NSim


			// Changing to Put
			myOption.type = "P";
			double tmp2 = myOption.payoff(S_new);		//	temporary variable storing the put payoff for every simulation
			Put_vector.push_back(tmp2);
			put_price += (tmp2) / double(NSim);			//	Calculation of mean put price for NSim


			// Changing back to Call
			myOption.type = "C";
		}


		//	Discounting these mean call and put option prices
		call_price *= exp(-myOption.r * myOption.T);
		put_price *= exp(-myOption.r * myOption.T);


		delete myNormal;		//	de-allocating memory


		cout << "\nCall Option Price: " << call_price << ", " << endl;							
		cout << "Put Option Price: " << put_price << ", " << endl;								
		cout << "Number of times S hits origin: " << count << endl;


		//	Printing the SD and SE
		boost::tuple<double, double> Call_Stats = SDSE<double>(Call_vector, myOption.r, myOption.T);
		boost::tuple<double, double> Put_Stats = SDSE<double>(Put_vector, myOption.r, myOption.T);


		cout << "\nCall:" << " \tNT = " << N << " \tNSim = " << NSim << " \tStandard Deviation = " << Call_Stats.get<0>() << " \tStandard Error = " << Call_Stats.get<1>() << endl;
		cout << "Put:" << "\tNT = " << N << " \tNSim = " << NSim << " \tStandard Deviation = " << Put_Stats.get<0>() << " \tStandard Error = " << Put_Stats.get<1>();
		cout << "\n---------------------------------------------------------------------------------------------\n";
	}

}
