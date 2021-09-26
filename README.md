# DynamicHedge

This repository contains 3 classes. European Options, Geometric Brownian Motion, and 
Dynamic Heding. European Options supports pricing and greek computations. Geometric 
Brownian Motion supports simulating GBM with diffrent parameters. Dynamic Hedging 
uses European options and Geometric browian motion as base classes. Dynamic 
hedging supports simulating calls and puts, long or short, with diffrent rebalance frequencys, 
and supports european options and geometric browinian motion with diffrent parameters. This 
was just a fun project to do in C++.

To compile on a mac please have boost installed and use the following commands

clang++ -std=c++11 -stdlib=libc++ testDynamicHedge.cpp EuropeanOption.cpp GBM.cpp DynamicHedge.cpp
clang++ -std=c++11 -stdlib=libc++ testEuropeanOption.cpp EuropeanOption.cpp 
\newline clang++ -std=c++11 -stdlib=libc++ testGBM.cpp GBM.cpp
