#include "DynamicHedge.hpp"
#include "EuropeanOption.hpp"
#include "GBM.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	char cp, ls;
	string frequency;
	int contracts;
	double t, strike, spot, mu, sigma, rf;

	cp = 'C'; //C or P
	ls = 'L'; //L or S
	frequency = "day"; //1 minute, 5 minute, 10 minute, 15 minute, 30 minute, hour, day, week
	contracts = 1; 
	t = 50.0/252.0;
	spot = 10;
	strike = 10;
	mu = 0;
	sigma = .3;
	rf = .1; 

	//init dynamic hedge
	DynamicHedge hedge(frequency, contracts, ls, cp, t, spot, strike, mu, sigma, rf);

	ublas::matrix<double> out = hedge.Sample(); //generate sample

	//output sample to file
	std::ofstream file;
	file.open("DynamicHedge.csv");
	file << "Call or Put: " << cp
		 << ", Long or Short: " << ls
		 << ", Rebalance Frequency: " << frequency
		 << ", Years: " << t
		 << ", S0: " << spot
		 << ", Strike: " << strike
		 << ", drift: " << mu
		 << ", volatility: " << sigma
		 << ", risk free rate: " << rf
		 << ", Number of options Contract: "<< contracts <<endl << endl;

	file << setprecision(6) << fixed
		 << "Period" << ","
		 << "Time Left" << ","
		 << "Spot Price" << ","
		 << "Option Value" << ","
		 << "Option Position Delta" << ","
		 << "Shares Bought/Sold" << ","
		 << "Inflow/Outflow from Shares" << ","
		 << "Balance" << endl;

	for(int i = 0; i < out.size1(); i++)
	{
		for(int j = 0; j < out.size2(); j++)
		{
			if(j < (out.size2() - 1))
			{
				file << out(i, j) << ",";
			}
			else
			{
				file << out(i, j) << endl;
			}
		}
	}

	file.close();
	return 0;
}
