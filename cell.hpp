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

using std::printf;

class Cell{
private:	
	double sup_need_base,sup_need_atk,sup_need_def,sup_need_move,sup_need_gen,sup_cur,sup_bound;
	double hp,hpLimit,atk,def,spe,sight,ageLimit,mov;
	int age;
	Probability_Of_Death probability_death;
	Randomizer rand;
//	Heap<Event> memo;
public:
	int id,x,y;
	Cell(){}
	Cell(int _id,int _x,int _y) : id(_id), x(_x), y(_y) {
		rand.setRandomSeed(std::time(0)+id+1);
		hp=hpLimit=rand.randomReal(HP_LOWER_BOUND,HP_UPPER_BOUND);
		atk=rand.randomReal(ATK_LOWER_BOUND,ATK_UPPER_BOUND);
		def=rand.randomReal(DEF_LOWER_BOUND,DEF_UPPER_BOUND);
		spe=rand.randomReal(SPE_LOWER_BOUND,SPE_UPPER_BOUND);
		sight=rand.randomReal(SIGHT_LOWER_BOUND,SIGHT_UPPER_BOUND);
		ageLimit=rand.randomReal(AGE_LIMIT_LOWER_BOUND,AGE_LIMIT_UPPER_BOUND);
		sup_need_base=0.75*sight+0.4*spe;
		sup_need_atk=sup_need_base+0.5*atk+0.23*def+0.4*spe;
		sup_need_def=sup_need_base+0.23*atk+0.5*def+0.3*spe;
		sup_need_move=sup_need_base+0.6*spe;
		sup_need_gen=sup_need_base*1.5;
		sup_bound=5*sup_need_atk;
		sup_cur=sup_bound;
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
	bool dead(){
		double P=probability_death(age);
		double k=rand.randomReal(0,100);
		return k<=P*100;
	}

	double getDamaged(int cell_id,int px,int py,double t_atk){
		double a_atk=Calc_Damage(t_atk,def);
		hp-=a_atk;sup_cur-=sup_need_def;
		return a_atk;
	}
	double makeDamage(int cell_id,int px,int py,double a_atk){
		sup_cur-=sup_need_atk;
		return a_atk;
	}
	
	void move(int dir){x+=dx[dir];y+=dy[dir];}

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
	std::vector<double> makeMov(){
		mov-=1;
		std::vector<double> t;
		if(sup_cur<=sup_need_base*1.05){
			for(int i=0;i<6;i++) t.push_back(0);
			t.push_back(1);
		}
		else{
			for(int i=0;i<7;i++) t.push_back(1./7);
		}
		return t;
	}

	void printInfo(){
		printf("Cell No.%03d\n",id);
		printf("Pos : (%d,%d)\n",x,y);
		printf("Age : %d ",age);
		printf("Hp : %.3f/%.3f\n",hp,hpLimit);
		printf("SUP : %.3f/%.3f\n",sup_cur,sup_bound);
		printf("ATK : %.3f, DEF : %.3f\n",atk,def);
		printf("SPE : %.3f, SIGHT : %.3f\n",spe,sight);
	}
};

#endif
