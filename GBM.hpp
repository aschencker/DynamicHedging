#ifndef GBM_HPP
#define GBM_HPP

#include <boost/numeric/ublas/vector.hpp>
#include <string>
namespace ublas = boost::numeric::ublas;

class GBM
{
private:
	double s0;
	double mu;
	double sigma;
public:
	//constructors
	GBM();
	GBM(double s, double m, double vol);
	GBM(const GBM& source);
	//destructor
	~GBM();

	//assignment oparator
	GBM& operator = (const GBM& source);

	//generated a path of length n of Geometric Browninan motion
	ublas::vector<double> Sample(int n) const;

	std::string ToString() const;

	//setters
	void S0(double s);
	void Mu(double m);
	void Sigma(double s);

	//getters
	double S0() const;
	double Mu() const;
	double Sigma() const;
};
#endif
