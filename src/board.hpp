#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <bits/stdc++.h>
#include "random.hpp"
#include "functions.hpp"
#include "constants.hpp"

using namespace std;

class Board{
private:
	double *pool,**sW;
	int N;
	Randomizer rand;

public:
	Board(){}
	Board(int _N) : N(_N), rand() {
		pool=new double[N*N];
		sW=new double*[N];
		for(int i=0;i<N;i++) sW[i]=pool+i*N;
	}
	~Board(){
		clear();
	}

	template <typename _T=EllipseDec>
	void init(int resourcePointNum=10,
			  int maxResourceAmount=6,
			  int randomSeed=-1,
			  _T generator=EllipseDec()){
		if(~randomSeed) rand.setRandomSeed(randomSeed);
		memset(pool,0,sizeof(double)*N*N);
		for(int i=0;i<resourcePointNum;i++){
			int x=rand.randomInt(0,N),y=rand.randomInt(0,N);
			double p=rand.randomReal(1,maxResourceAmount);
			for(int tx=0;tx<N;tx++)
				for(int ty=0;ty<N;ty++)
					sW[tx][ty]+=generator(x,y,tx,ty,p);
		}
	}
	void newBoard(int _N){
		clear();N=_N;
		pool=new double[N*N];
		sW=new double*[N];
		for(int i=0;i<N;i++) sW[i]=pool+i*N;
		init();
	}
	void printBoard(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				printf("%7.3f",sW[i][j]);
			puts("");
		}
	}
	void printBoard(FILE *fp){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				fprintf(fp,"%7.3f",sW[i][j]);
			fprintf(fp,"\n");
		}
	}
	void clear(){
		if(N) delete sW,delete pool,N=0;
	}
	
	inline double * operator [] (int x){
		return sW[x];
	}
};
#endif
