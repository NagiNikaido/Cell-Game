#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <bits/stdc++.h>

const int MOD = 1000000007;

class Randomizer{
private:
	int seed;

public:
	Randomizer() : seed(std::time(0)){}
	void setRandomSeed(int newSeed){seed=newSeed;}
	int randomInt(int l,int r){
		int res=seed=(((1u*seed*seed*13+seed*5)^seed)%MOD+MOD)%MOD;
		return res%(r-l+1)+l;
	}
	double randomReal(double l,double r){
		int t=randomInt(0,MOD-1);
		return l+(r-l)*t/MOD;
	}
};

#endif
