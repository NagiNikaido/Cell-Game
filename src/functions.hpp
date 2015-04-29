#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

#include <bits/stdc++.h>

using namespace std;

template<typename _T> inline _T sqr(_T x){return x*x;}

inline double euclidDist(int x1,int y1,int x2,int y2){
	return std::sqrt(sqr(x1-x2)+sqr(y1-y2));
}
inline int manhattanDist(int x1,int y1,int x2,int y2){
	return std::abs(x1-x2)+std::abs(y1-y2);
}

class LinearDec_euclid{
public:
	inline double operator() (int x1,int y1,int x2,int y2,double p){
		//return int(std::floor(p/(1+euclidDist(x1,y1,x2,y2))+.5));
		return 1.*p/(1+euclidDist(x1,y1,x2,y2));
	}
};

class LinearDec_manhattan{
public:
	inline double operator() (int x1,int y1,int x2,int y2,double p){
		//return int(std::floor(p/(1+manhattanDist(x1,y1,x2,y2))+.5));
		return 1.*p/(1+manhattanDist(x1,y1,x2,y2));
	}
};

class EllipseDec{
public:
	inline double operator() (int x1,int y1,int x2,int y2,double p){
		double len=euclidDist(x1,y1,x2,y2);
		if(len>=1.05*p) return 0;
		//return int(std::floor(std::sqrt(sqr(p)-sqr(p)/sqr(1.05*p)*sqr(len)))+.5);
		return std::sqrt(sqr(p)-sqr(p)/sqr(1.05*p)*sqr(len));
	}
};

class Probability_Of_Death{
private:
	double ageLimit;
public:
	Probability_Of_Death(double _lim=0) : ageLimit(_lim){}
	inline double operator() (double cur_age){
	// naive version
		return cur_age>ageLimit ? 1 : 0;
	}
};

inline double Calc_Damage(double atk,double def){
	return atk/sqrt(def);
}

#endif
