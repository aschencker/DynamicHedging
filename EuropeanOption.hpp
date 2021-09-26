#ifndef EuropeanOption_HPP
#define EuropeanOption_HPP
#include <string>

class EuropeanOption
{
private:
	double S;
	double K;
	double r;
	double t;
	double sigma;
	double q;
	char direction; // l for long, s for short
	char type;  //c for call, p for put

	//used in fair value and greek computations
	double d1() const;
	double d2() const;

	//handles diffrences in fair value and greeks due to
	//long vs short and put vs call
	double nestedSwitch(double call, double put) const;

	//fair value
	double CallPrice() const;
	double PutPrice() const;

	//first order greeks
	double CallDelta() const;
	double PutDelta() const;
	double CallPutVega() const;
	double CallTheta() const;
	double PutTheta() const;
	double CallRho() const;
	double PutRho() const;
	double CallEpsilon() const;
	double PutEpsilon() const;

	double Callitm() const;
	double Putitm() const;

	//second order greeks
	double CallPutGamma() const;
	double CallPutVomma() const;
	double CallPutVanna() const;
public:
	//constructors
	EuropeanOption();
	EuropeanOption(double s0, double k0, double r0, double t0, double sigma0,
				   double q0, char direction0, char type0);
	EuropeanOption(const EuropeanOption& source);
	~EuropeanOption(); //destructor

	//assigment operator
	EuropeanOption& operator = (const EuropeanOption& source);

	//fair value
	double Price() const;

	//first order greeks
	double Delta() const;
	double Vega() const;
	double Theta() const;
	double Rho() const;
	double Epsilon() const;

	double ITM() const;

	//second order greeks
	double Gamma() const;
	double Vomma() const;
	double Vanna() const;

	//other
	double Payoff() const;
	std::string ToString() const;

	//setters
	void Spot(double s);
	void Strike(double k);
	void Rf(double rn);
	void Time(double tn);
	void Sigma(double vol);
	void Dividend(double div);
	void Direction(char d);
	void Type(char cp);

	//getters
	double Spot() const;
	double Strike() const;
	double Rf() const;
	double Time() const;
	double Sigma() const;
	double Dividend() const;
	char Direction() const;
	char Type() const;
};
#endif
