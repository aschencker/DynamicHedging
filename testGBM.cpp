#include "GBM.hpp"
#include <iostream>
#include <fstream>

int main()
{
	int n = 252; //days in a year 
	GBM gbm(10, .25/n, .5/std::sqrt(n)); //init gbm
	ublas::vector<double> ts = gbm.Sample(n); //sample from gbm

	std::cout << gbm.ToString() << std::endl;

	//output gbm to a file
	std::ofstream file;
	file.open("testGBM.csv");
	for(int i = 0; i < n; i++)
	{
		file << ts(i) << std::endl;
	}
	file.close();
	return 0;
}
