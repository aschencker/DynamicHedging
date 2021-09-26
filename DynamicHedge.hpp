#ifndef DynamicHedge_HPP
#define DynamicHedge_HPP

#include "EuropeanOption.hpp"
#include "GBM.hpp"
#include <string>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace ublas = boost::numeric::ublas;
using namespace std;

class DynamicHedge: public EuropeanOption, public GBM
{
private:
	string frequency;
	int periods;
	int contracts;
public:
	//constructors
	DynamicHedge();
	DynamicHedge(string frequency0, int contracts0, char CallOrPut,
				 char LongOrShort, double time, double spot, double strike,
				 double drift, double vol, double rf);
	DynamicHedge(const DynamicHedge& source);
	//destructor
	~DynamicHedge();

	//assignment operator
	DynamicHedge& operator = (const DynamicHedge& source);
	
	//generates a sample dynamic hedge 
	ublas::matrix<double> Sample();

	//getters
	string Frequency() const;
	int Periods() const;
	int Contracts() const;
};

#endif
