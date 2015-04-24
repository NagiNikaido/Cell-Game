/*
a very naive version
"I'm just a molecule!" --- by a Cell
"... at the temperature of 0K." -- by another Cell
*/
#ifndef __CELL_HPP__
#define __CELL_HPP__

#include <bits/stdc++.h>
#include "functions.hpp"
#include "random.hpp"
#include "constants.hpp"
#include "ds/heap.hpp"

using namespace std;

class Cell{
private:	
	double sup_need_base,sup_need_atk,sup_need_def,sup_need_move,sup_need_gen,sup_cur,sup_bound;
	double hpLost_hunger,hpRec_hunger;
	double hp,hp_limit,atk,def,spe,sight,ageLimit,mov;
	int age;
	Probability_Of_Death probability_death;
	Randomizer rand;
//	Heap<Event> memo;
public:
	int id,x,y;
	Cell(){}
	Cell(int _id,int _x,int _y) : id(_id), x(_x), y(_y) {
		rand.setRandomSeed(std::time(0)+id+1);
		hp=hp_limit=rand.randomReal(HP_LOWER_BOUND,HP_UPPER_BOUND);
		atk=rand.randomReal(ATK_LOWER_BOUND,ATK_UPPER_BOUND);
		def=rand.randomReal(DEF_LOWER_BOUND,DEF_UPPER_BOUND);
		spe=rand.randomReal(SPE_LOWER_BOUND,SPE_UPPER_BOUND);
		sight=rand.randomReal(SIGHT_LOWER_BOUND,SIGHT_UPPER_BOUND);
		ageLimit=rand.randomReal(AGE_LIMIT_LOWER_BOUND,AGE_LIMIT_UPPER_BOUND);
		probability_death=Probability_Of_Death(ageLimit);
		sup_need_base=0.75*sight+0.4*spe;
		sup_need_atk=0.5*atk+0.23*def+0.4*spe;
		sup_need_def=0.23*atk+0.5*def+0.3*spe;
		sup_need_move=0.6*spe;
		sup_need_gen=sup_need_base*0.5;
		sup_bound=5*(sup_need_atk+sup_need_base);
		sup_cur=sup_bound;
		hpLost_hunger=rand.randomReal(0.05,0.1);
		hpRec_hunger=rand.randomReal(0.075,0.1);
		age=0;mov=0;
	}
/*
	Cell(int _id,int _x,int _y,double _sup_need_base,double _sup_need_atk,double _sup_need_def,double _sup_need_move,
			double _sup_need_gen,double _sup_cur,double _sup_bound,double _hp,double _atk,double _def,
			double _spe,double _sight,double _ageLimit,int _age)
			: id(_id), x(_x), y(_y), sup_need_base(_sup_need_base), sup_need_atk(_sup_need_atk), sup_need_def(_sup_need_def),
			  sup_need_move(_sup_need_move), sup_need_gen(_sup_need_gen), sup_cur(_sup_cur), sup_bound(_sup_bound),
			  hp(_hp), atk(_atk), def(_def), spe(_spe), sight(_sight), ageLimit(_ageLimit), age(_age)
			  {
				  rand.setRandomSeed(std::time(0)+id+1);
			  }
*/
//// currently *NOT IN USE*
	double getHp(){return hp;}
	double getAtk(){return atk;}
	double getDef(){return def;}
	double getSpe(){return spe;}
	double getSight(){return sight;}
	double getMov(){return mov;}
	bool beKilled(){return hp<=EPS;}
	void checkHunger(){
		if(sup_cur<=EPS) hp-=hpLost_hunger*hp_limit;
		else{
			hp=max(hp_limit,hpRec_hunger*hp_limit);
			sup_cur-=sup_need_base;
		}
	}
	bool dead(){
		double P=probability_death(age);
		double k=rand.randomReal(1,100);
		return k<=P*100;
	}
	
	double getDamaged(double t_atk){
		double a_atk=Calc_Damage(t_atk,def);
		hp-=a_atk;sup_cur=max(sup_cur-sup_need_def,0.);
		return a_atk;
	}
	double makeDamage(){
		sup_cur-=sup_need_atk;
		return atk;
	}
	
	void move(int dir){x+=dx[dir];y+=dy[dir];sup_cur-=sup_need_move;}

	double haveSomeFood(double sup){
		double dt=std::min(sup_bound-sup_cur,sup);
		sup_cur+=dt;
		return dt;
	}
	//"Sweet!" -- by a Cell

	void gen(){}
	//doing nothing at all.
	
	void incAge(){mov+=spe;age++;}
	double canMov(){return mov>=1;}
	pair<int,int> makeMov(vector<int> otherCells){
		mov-=1;
		
		vector<pair<int,int>> t;
		for(int i=0;i<4;i++) if(~otherCells[i]){
			if(otherCells[i]){
				if(sup_cur>=sup_need_atk) t.push_back(make_pair(2,otherCells[i]-1));
			}
			else{
				if(sup_cur>=sup_need_move) t.push_back(make_pair(1,i));
			}
		}
		t.push_back(make_pair(4,0));
		int pp=t.size();
		int k=rand.randomInt(0,pp*1000);
		return t[k/1000];
	}

	void printInfo(){
		printf("Cell No.%03d\n",id);
		printf("Pos : (%d,%d)\n",x,y);
		printf("Age : %d ",age);
		printf("Hp : %.3f/%.3f\n",hp,hp_limit);
		printf("SUP : %.3f/%.3f\n",sup_cur,sup_bound);
		printf("ATK : %.3f, DEF : %.3f\n",atk,def);
		printf("SPE : %.3f, SIGHT : %.3f\n",spe,sight);
	}
	void printInfo(FILE *fp){
		fprintf(fp,"Cell No.%03d\n",id);
		fprintf(fp,"Pos : (%d,%d)\n",x,y);
		fprintf(fp,"Age : %d ",age);
		fprintf(fp,"Hp : %.3f/%.3f\n",hp,hp_limit);
		fprintf(fp,"SUP : %.3f/%.3f\n",sup_cur,sup_bound);
		fprintf(fp,"ATK : %.3f, DEF : %.3f\n",atk,def);
		fprintf(fp,"SPE : %.3f, SIGHT : %.3f\n",spe,sight);
	}
};

#endif
