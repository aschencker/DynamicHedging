#include "EuropeanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <iostream>
#include <algorithm>

using namespace boost::math;

//default constructor
EuropeanOption::EuropeanOption()
{
	
}

//paramter constructor
EuropeanOption::EuropeanOption(double s0, double k0, double r0,
							   double t0, double sigma0, double q0,
							   char direction0, char type0): S(s0), K(k0), r(r0),
														     t(t0), sigma(sigma0),
														     q(q0),
														     direction(direction0),
														     type(type0)
{
	
}

//copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& source): S(source.S),
															  K(source.K),
															  r(source.r),
															  t(source.t),
															  sigma(source.sigma),
															  q(source.q),
															  direction(source.direction),
															  type(source.type)
															
{
	
}

EuropeanOption::~EuropeanOption()
{
	
}

//assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)
{
	if(this != &source)
	{
		S = source.S;
		K = source.K;
		r = source.r;
		t = source.t;
		sigma = source.sigma;
		q = source.q;
		direction = source.direction;
		type = source.type;
	}
	return *this;
}

//output: double represting d1 in Black-Scholes formula
double EuropeanOption::d1() const
{
	return (log(S / K) + (r - q + sigma * sigma / 2) * t) / (sigma * sqrt(t));
}

//output: double represting d2 in Black-Scholes formula    
double EuropeanOption::d2() const
{
	return d1() - sigma * sqrt(t);
}

//output: fair value of European call option
double EuropeanOption::CallPrice() const
{
	normal_distribution<> N(0.0,1.0);
	return S * exp(-q * t) * cdf(N, d1()) - K * exp(-r * t) * cdf(N, d2());
}

//output: fair value of European put option
double EuropeanOption::PutPrice() const
{
	normal_distribution<> N(0.0, 1.0);
	return K * exp(-r * t) * cdf(N, -d2()) - S * exp(-q * t) * cdf(N, -d1());
}

//output: first derivative of fair value of a call option
//        with respesct to the underlying assets price 
double EuropeanOption::CallDelta() const
{
	normal_distribution<> N(0.0, 1.0);
	return exp(-q * t) * cdf(N, d1());
}

//output: first derivative of fair value of a put option
//        with respect to the underlying assets price
double EuropeanOption::PutDelta() const
{
	normal_distribution<> N(0.0, 1.0);
	return -exp(-q * t) * cdf(N, -d1());
}

//output: first derivative of fair value of put and call options
//        with respect to the implied volatility
double EuropeanOption::CallPutVega() const
{
	normal_distribution<> N(0.0, 1.0);
	return (S * sqrt(t) * exp(-q * t) * pdf(N, d1()) / 100);
}

//output: first derivative of fair value of a call option
//        with respect to the time to option expiration
double EuropeanOption::CallTheta() const
{
	normal_distribution<> N(0.0, 1.0);
	double term1 = -exp(-q * t) * (S * pdf(N, d1()) * sigma) / (2 * sqrt(t));
	double term2 = r * K * exp(-r * t) * cdf(N, d2());
	double term3 = q * S * exp(-q * t) * cdf(N, d1());
	return (term1 - term2 + term3) / 252;
}

//output: first derivative of fair value of a put option
//        with repsect to the time to option expiration
double EuropeanOption::PutTheta() const
{
	normal_distribution<> N(0.0, 1.0);
	double term1 = -exp(-q * t) * (S * pdf(N, d1()) * sigma) / (2 * sqrt(t));
	double term2 = r * K * exp(-r * t) * cdf(N, -d2());
	double term3 = q * S * exp(-q * t) * cdf(N, -d1());
	return (term1 + term2 - term3) / 252;
}

//output: first derivative of fair value of a call option
//        with respect to the risk free rate
double EuropeanOption::CallRho() const
{
    normal_distribution<> N(0.0, 1.0);
	return K * t * exp(-r * t) * cdf(N, d2()) / 100;
}

//output: first derivative of fair value of a put option
//        with respect to the risk free rate
double EuropeanOption::PutRho() const
{
	normal_distribution<> N(0.0, 1.0);
	return -K * t * exp(-r * t) * cdf(N, -d2()) / 100;
}

//output: first derivative of fair value of a call option
//        with repect to the underlying assets dividend yield
double EuropeanOption::CallEpsilon() const
{
	normal_distribution<> N(0.0, 1.0);
	return -S * t * exp(-q * t) * cdf(N, d1()) / 100;
}

//output: first derivative of fair value of a put option
//        with respect to the underlying assets dividend yield
double EuropeanOption::PutEpsilon() const
{
	normal_distribution<> N(0.0, 1.0);
	return S * t * exp(-q * t) * cdf(N, -d1()) / 100;
}

//output: first derviative of fair value of a call option
//        with respect to the options strike price
double EuropeanOption::Callitm() const
{
	normal_distribution<> N(0.0, 1.0);
	return cdf(N, d2());
}

//output: first derivative of fair value of a put option
//        with repsect to the options strike price
double EuropeanOption::Putitm() const
{
	normal_distribution<> N(0.0, 1.0);
	return cdf(N, -d2());
}

//output: second derivative of fair value of a call or put option
//        with respect to the option underlying price
double EuropeanOption::CallPutGamma() const
{
	normal_distribution<> N(0.0, 1.0);
	return exp(-q * t) * pdf(N, d1()) / (S * sigma * sqrt(t));
}

//output: second derivative of fair value of a call or put option
//        with respect to the implied volatility
double EuropeanOption::CallPutVomma() const
{
	normal_distribution<> N(0.0, 1.0);
	return CallPutVega() * d1() * d2() / sigma;
}

//output: derivative of vega w.r.t underlying stock price
//        also derivative of delta w.r.t implied volatility 
double EuropeanOption::CallPutVanna() const
{
	normal_distribution<> N(0.0, 1.0);
	return (CallPutVega() / S) * (1 - (d1() / (sigma * sqrt(t))));
}

//call: fair value or greek for call option as a double
//put: fair value or greek for put option as a double
//output: the correct fair value or greek accounting for
//        long vs short and put vs call
double EuropeanOption::nestedSwitch(double call, double put) const
{
	double output;
	switch(type)
	{
	case 'c': case 'C':
		switch(direction)
		{
		case 'l': case 'L':
			output = call;
			break;
		case 's': case 'S':
			output = -call;
			break;
		default:
			throw -1;
		}
		break;
	case 'p': case 'P':
		switch(direction)
		{
		case 'l': case 'L':
			output = put;
			break;
		case 's': case 'S':
			output = -put;
			break;
		default:
			throw -1;
		}
		break;
	default:
		throw -1;
	}
	return output;
}

//price in the for of an inflow/outflow for a call or put option long or short
double EuropeanOption::Price() const
{
	return nestedSwitch(-CallPrice(), -PutPrice());
}

//output: delta of a call or put option long or short
double EuropeanOption::Delta() const
{
	return nestedSwitch(CallDelta(), PutDelta());
}

//output: vega of a call or put option long or short
double EuropeanOption::Vega() const
{
	return nestedSwitch(CallPutVega(), CallPutVega()); 
}

//output: theta of a call or put option long or short
double EuropeanOption::Theta() const
{
	return nestedSwitch(CallTheta(), PutTheta());
}

//output: rho of a call or put option long or short
double EuropeanOption::Rho() const
{
	return nestedSwitch(CallRho(), PutRho());
}

//output: epsilon of a call or put option long or short
double EuropeanOption::Epsilon() const
{
	return nestedSwitch(CallEpsilon(), PutEpsilon());
}

//output: probabilty the option is profitable
double EuropeanOption::ITM() const
{
	double output;
   	switch(type)
	{
	case 'c': case 'C':
		switch(direction)
		{
		case 'l': case 'L':
			output = Callitm();
			break;
		case 's': case 'S':
			output = 1 - Callitm();
			break;
		default:
			throw -1;
		}
		break;
	case 'p': case 'P':
		switch(direction)
		{
		case 'l': case 'L':
			output = Putitm();
			break;
		case 's': case 'S':
			output = 1 - Putitm();
			break;
		default:
			throw -1;
		}
		break;
	default:
		throw -1;
	}
	return output;
}

//output: gamma of a call or put option long or short
double EuropeanOption::Gamma() const
{
	return nestedSwitch(CallPutGamma(), CallPutGamma());
}

//output: vomma of a call or put option long or short
double EuropeanOption::Vomma() const
{
	return nestedSwitch(CallPutVomma(), CallPutVomma());
}

//output: vanna of a call or put option long or short
double EuropeanOption::Vanna() const
{
	return nestedSwitch(CallPutVanna(), CallPutVanna());
}

//output: Payoff of the option if exersised
double EuropeanOption::Payoff() const
{
	double out;
	switch(type)
	{
	case 'c': case 'C':
		out = std::max(S-K, 0.0);
		break;
	case 'p': case 'P':
		out = std::max(K-S, 0.0);
		break;
	default:
		throw -1;
	}
	if((direction == 's') || (direction == 'S'))
	{
		out = -out;
	}
	return out;
}

//print all option parameters
std::string EuropeanOption::ToString() const
{
	return "S: " + std::to_string(S) + ", K: " + std::to_string(K) + ", r: "
		+ std::to_string(r) + ", t: " + std::to_string(t) + ", sigma: "
		+ std::to_string(sigma) + ", q: " + std::to_string(q) + ", Direction: "
		+ direction + ", type: " + type;
}

//Spot price setter
void EuropeanOption::Spot(double s)
{
	S = s;
}

//strike price setter
void EuropeanOption::Strike(double k)
{
	K = k;
}

//risk free rate setter
void EuropeanOption::Rf(double rn)
{
	r = rn;
}

//time setter
void EuropeanOption::Time(double tn)
{
	t = tn;
}

//volatility setter
void EuropeanOption::Sigma(double s)
{
	sigma = s;
}

//dividend setter
void EuropeanOption::Dividend(double div)
{
	q = div;
}

//Long or Short setter
void EuropeanOption::Direction(char d)
{
	direction = d;
}

//Call or put setter
void EuropeanOption::Type(char cp)
{
	type = cp;
}

//spot price getter 
double EuropeanOption::Spot() const
{
	return S;
}

//strike price getter
double EuropeanOption::Strike() const
{
	return K;
}

//risk free rate getter
double EuropeanOption::Rf() const
{
	return r;
}

//time to exp getter
double EuropeanOption::Time() const
{
	return t;
}

//volatility getter
double EuropeanOption::Sigma() const
{
	return sigma;
}

//dividend getter
double EuropeanOption::Dividend() const
{
	return q;
}

//Long or short getter
char EuropeanOption::Direction() const
{
	return direction;
}

//call or put getter
char EuropeanOption::Type() const
{
	return type;
}
