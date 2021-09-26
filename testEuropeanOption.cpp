#include "EuropeanOption.hpp"
#include <iostream>

using namespace std;

int main()
{
	//init an option of each type and direction
	EuropeanOption lc(10, 10, .1, 1, .1, 0, 'L', 'C');
	EuropeanOption sc(10, 10, .1, 1, .1, 0, 'S', 'C');
	EuropeanOption lp(10, 10, .1, 1, .1, 0, 'L', 'P');
	EuropeanOption sp(10, 10, .1, 1, .1, 0, 'S', 'P');

	//test all greeks
	cout << "Long Call: " << lc.ToString() << endl;
	cout << "Short Call: " << sc.ToString() << endl;
	cout << "Long Put: " << lp.ToString() << endl;
	cout << "Short Put: " << sp.ToString() << endl;
	cout << endl;
	
	cout << "Fair Value" << endl;
	cout << "Long Call outflow/inflow: " << lc.Price() << endl;
	cout << "Short Call outflow/inflow: " << sc.Price() << endl;
	cout << "Long Put outflow/inflow: " << lp.Price() << endl;
	cout << "Short Put outflow/inflow: " << sp.Price() << endl << endl;

	cout << "Delta" << endl;
	cout << "Long Call Delta: " << lc.Delta() << endl;
	cout << "Short Call Delta: " << sc.Delta() << endl;
	cout << "Long Put Delta: " << lp.Delta() << endl;
	cout << "Short Put Delta: " << sp.Delta() << endl << endl;

	cout << "Vega" << endl;
	cout << "Long Call Vega: " << lc.Vega() << endl;
	cout << "Short Call Vega: " << sc.Vega() << endl;
	cout << "Long Put Vega: " << lp.Vega() << endl;
	cout << "Short Put Vega: " << sp.Vega() << endl << endl;

	cout << "Theta" << endl;
	cout << "Long Call Theta: " << lc.Theta() << endl;
	cout << "Short Call Theta: " << sc.Theta() << endl;
	cout << "Long Put Theta: " << lp.Theta() << endl;
	cout << "Short Put Theta: " << sp.Theta() << endl << endl;

	cout << "Rho" << endl;
	cout << "Long Call Rho: " << lc.Rho() << endl;
	cout << "Short Call Rho: " << sc.Rho() << endl;
	cout << "Long Put Rho: " << lp.Rho() << endl;
	cout << "Short Put Rho: " << sp.Rho() << endl << endl;

   	cout << "Epsilon" << endl;
	cout << "Long Call Epsilon: " << lc.Epsilon() << endl;
	cout << "Short Call Epsilon: " << sc.Epsilon() << endl;
	cout << "Long Put Epsilon: " << lp.Epsilon() << endl;
	cout << "Short Put Epsilon: " << sp.Epsilon() << endl << endl;

   	cout << "ITM/OTM" << endl;
	cout << "Long Call ITM: " << lc.ITM() << endl;
	cout << "Short Call OTM: " << sc.ITM() << endl;
	cout << "Long Put ITM: " << lp.ITM() << endl;
	cout << "Short Put OTM: " << sp.ITM() << endl << endl;

	cout << "Gamma" << endl;
	cout << "Long Call Gamma: " << lc.Gamma() << endl;
	cout << "Short Call Gamma: " << sc.Gamma() << endl;
	cout << "Long Put Gamma: " << lp.Gamma() << endl;
	cout << "Short Put Gamma: " << sp.Gamma() << endl << endl;

	cout << "Vomma" << endl;
	cout << "Long Call Vomma: " << lc.Vomma() << endl;
	cout << "Short Call Vomma: " << sc.Vomma() << endl;
	cout << "Long Put Vomma: " << lp.Vomma() << endl;
	cout << "Short Put Vomma: " << sp.Vomma() << endl << endl;

	cout << "Vanna" << endl;
	cout << "Long Call Vanna: " << lc.Vanna() << endl;
	cout << "Short Call Vanna: " << sc.Vanna() << endl;
	cout << "Long Put Vanna: " << lp.Vanna() << endl;
	cout << "Short Put Vanna: " << sp.Vanna() << endl;
	return 0;
}
