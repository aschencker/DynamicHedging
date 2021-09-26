#include "GBM.hpp"
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <cmath>
#include <iostream>

//default constructor
GBM::GBM()
{
	
}

//parameter constructor
GBM::GBM(double s, double m, double vol): s0(s), mu(m), sigma(vol)
{
	
}

//copy constructor
GBM::GBM(const GBM& source): s0(source.s0), mu(source.mu), sigma(source.sigma)
{
	
}

//destructors
GBM::~GBM()
{
	
}

//assignment operator
GBM& GBM::operator = (const GBM& source)
{
	if(this != &source)
	{
		s0 = source.s0;
		mu = source.mu;
		sigma = source.sigma;
	}
	return *this;
}

//output: path of length n of Geometric Browninan motion
ublas::vector<double> GBM::Sample(int n) const
{
	ublas::vector<double> out(n);
	out(0) = s0;

	boost::random::mt19937 rng;
	rng.seed(static_cast<boost::uint32_t> (std::time(0)));
	boost::random::normal_distribution<double> rnorm(0, 1);
	
	for(int i = 1; i < n; i++)
	{
		out(i) = out(i - 1) * std::exp(mu - (sigma * sigma / 2) + sigma * rnorm(rng));
	}
	return out;
}

//output: cout of GBM parameters
std::string GBM::ToString() const
{
	return "S0 = " + std::to_string(s0) + ", mu = " + std::to_string(mu)
		+ ", sigma = " + std::to_string(sigma);
}

//s0 setter
void GBM::S0(double s)
{
	s0 = s;
}

//mu setter
void GBM::Mu(double m)
{
	mu = m;
}

//sigma setter
void GBM::Sigma(double s)
{
	sigma = s;
}

//s0 getter
double GBM::S0() const
{
	return s0;
}

//mu getter
double GBM::Mu() const
{
	return mu;
}

//sigma getter
double GBM::Sigma() const
{
	return sigma;
}
