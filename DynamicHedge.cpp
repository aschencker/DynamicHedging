#include "DynamicHedge.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

//defualt constructor
DynamicHedge::DynamicHedge()
{
	
}

//parameter constructor
DynamicHedge::DynamicHedge(string frequency0, int contracts0, char LongOrShort,
						   char CallOrPut, double time, double spot,
						   double strike0, double drift, double vol,
						   double rf0): EuropeanOption(spot, strike0, rf0, time,
													   vol, 0, LongOrShort,
													   CallOrPut)
{
	//convert frequency to number of periods
	double period;
	frequency = frequency0;
	if(frequency == "1 minute")
	{
		period = 252 * 6.5 * 60;
	}
	else if(frequency == "5 minute")
	{
		period = 252 * 6.5 * 12;
	}
	else if(frequency == "10 minute")
	{
		period = 252 * 6.5 * 6;
	}
	else if(frequency == "15 minute")
	{
		period = 252 * 6.5 * 4;
	}
	else if(frequency == "30 minute")
	{
		period = 252 * 6.5 * 2;
	}
	else if(frequency == "hour")
	{
		period = 252 * 6.5;
	}
	else if(frequency ==  "day")
	{
		period = 252;
	}
	else if(frequency == "week")
	{
		period = 52;
	}

	//populate GBM
   	GBM::S0(spot);
    GBM::Mu(drift / period);
	GBM::Sigma(vol / sqrt(period));

	//number of periods in the dynamic hedge
	periods = (int)(period * time);
	contracts = contracts0;
}

//destructor
DynamicHedge::~DynamicHedge()
{
	
}

DynamicHedge& DynamicHedge::operator = (const DynamicHedge& source)
{
	if(this != &source)
	{
		GBM::operator = (source);
		EuropeanOption::operator = (source);
		frequency = source.frequency;
		periods = source.periods;
		contracts = source.contracts;
	}
	return *this;
}

//output: boost matrix of a sample dynamic hedge
ublas::matrix<double> DynamicHedge::Sample()
{
	ublas::vector<double> gbm = GBM::Sample(periods + 1);
	ublas::matrix<double> table(periods + 1, 8);
	double shareCount = 0;

	double time = EuropeanOption::Time();
	double years = EuropeanOption::Time();
	char CP = EuropeanOption::Type();
	char LS = EuropeanOption::Direction();
	double rf = EuropeanOption::Rf();
	double strike = EuropeanOption::Strike();

	for(int i = 0; i < periods+1; i++)
	{
		table(i, 0) = i; //period
		table(i, 1) = time; //time left on option
		table(i, 2) = gbm(i); //spot price
		EuropeanOption::Spot(gbm(i)); //update price
		if(i < periods)
		{
			table(i, 3) = abs(EuropeanOption::Price()); //option price
			table(i, 4) = EuropeanOption::Delta(); //option delta
		}else
		{
			//last period
   			table(i, 3) = abs(EuropeanOption::Payoff()); //option price
			if(table(i, 3) == 0)
			{
				table(i, 4) = 0; //option delta
			}
			else
			{
				//option delta
				switch(CP)
				{
				case 'c': case 'C':
					switch(LS)
					{
					case 'l': case 'L':
						table(i, 4) = 1;
						break;
					case 's': case 'S':
						table(i, 4) = -1;
						break;
					default:
						break;
  					}
					break;
				case 'p': case 'P':
					switch(LS)
					{
					case 'l': case 'L':
						table(i, 4) = -1;
						break;
					case 's': case 'S':
						table(i, 4) = 1;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
		}
		table(i, 5) = (-table(i, 4) * contracts) - shareCount; //shares bought sold
		shareCount = table(i, 5) + shareCount;
		table(i, 6) = -table(i, 5) * gbm(i); // inflow outflow from shares

		if(i == 0)
		{
			switch(EuropeanOption::Direction())
			{
			case 'L': case 'l':
				table(i, 7) = table(i, 6) - table(i, 3) * contracts; //balance long option
				break;
			case 's': case 'S':
				table(i, 7) = table(i, 6) + table(i, 3) * contracts; //balance short option
				break;
			default:
				break;
			}	
		}
		else
		{
			table(i, 7) = table(i - 1, 7) * exp(rf / ((double)periods / years))
				+ table(i, 6); //balance
		}
		if(i == periods)
		{
			if(table(i, 4) > 0)
			{
				table(i, 7) -= strike * contracts; //balance short itm option 
			}
			else if(table(i, 4) < 0)
			{
				table(i, 7) += strike * contracts; //balance long itm option
			}
		}

		time -= 1 / ((double)periods / years);
		EuropeanOption::Time(time); //update time
	}
	return table;
}

//frequency getter
string DynamicHedge::Frequency() const
{
	return frequency;
}

//periods getter
int DynamicHedge::Periods() const
{
	return periods;
}

//contracts getter
int DynamicHedge::Contracts() const
{
	return contracts;
}
