#ifndef __GAME_FRAME_H__
#define __GAME_FRAME_H__

#include <bits/stdc++.h>
#include "board.hpp"
#include "cell.hpp"

using namespace std;

#include <unistd.h>

#if (defined(__WIN32__) || defined(_WIN32) || defined(__WIN64__) || defined(__WIN64))
#	include <windows.h>
#	define SLEEP(MICROSECONDS) Sleep(int(MICROSECONDS))
#   define CLS  system("cls")
#else
#	define SLEEP(MICROSECONDS) usleep(int(1000*(MICROSECONDS)))
#   define CLS  system("clear")
#endif

#define BROADCAST(...) printf( __VA_ARGS__ ),fprintf(logfile, __VA_ARGS__ )

class Framework{
private:
	int gameSize;
	double gameSpeed;
	int gameTime;
	int cellNum;
	std::vector<Cell> cellList;
	Board gameBoard;
	FILE *logfile;
public:
	Framework(){}
	void versionInfo(){
	}
	void welcomeInfo(){
		puts("*************************************");
		puts("*      Cell Game v0.1 - alpha       *");
		puts("*                                   *");
		puts("*                                   *");
		puts("*************************************");
		puts("");
		puts("A very naive version");
		puts("\"I'm just a molecule!\" --- by a Cell");
//		puts("\"... at the temperature of 0K.\" -- by another Cell");
		puts("\n");
	}
	void newGame(int size=20,double speed=0.5,int num=4){
		gameSize=size;
		gameSpeed=speed;
		gameTime=0;
		cellNum=num;
		cellList.clear();
		gameBoard.clear();
		gameBoard.newBoard(size);
		for(int i=0;i<num;i++) cellList.push_back(Cell(i,i,i));
	}
	void refresh(){
		CLS;
		BROADCAST("Time : %d\n",gameTime);
		gameBoard.printBoard();
		gameBoard.printBoard(logfile);
		for(int i=0;i<cellList.size();i++) cellList[i].printInfo(),puts("");
		for(int i=0;i<cellList.size();i++) cellList[i].printInfo(logfile),fprintf(logfile,"\n");
	}
	void moveLoop(){
		for(int flag=1;flag;){
			flag=0;
			for(int i=0;i<cellList.size();i++) if(cellList[i].canMov()){
				flag=1;refresh();
				BROADCAST("No.%03d Cell's turn.\n",cellList[i].id);
				///////
				
				vector<int> t;
				cellList[i].checkHunger();
				if(cellList[i].beKilled()){
					BROADCAST("No.%03d Cell died of hunger.\n",cellList[i].id);
					cellList.erase(cellList.begin()+i);
					i--;
				}
				else{
					int x=cellList[i].x,y=cellList[i].y;
					for(int j=0;j<4;j++){
						int tx=x+dx[j],ty=y+dy[j];
						if(tx<0 || ty<0 || tx>=gameSize || ty>=gameSize) t.push_back(-1);
						else{
							for(int k=0;k<cellList.size();k++) if(cellList[k].x==tx && cellList[k].y==ty)
								t.push_back(cellList[k].id);
							if(t.size()<=j) t.push_back(0);
						}
					}
					pair<int,int> action=cellList[i].makeMov(t);
					switch(action.first){
						case 1:{
							cellList[i].move(action.second);
							refresh();
							BROADCAST("No.%03d Cell move from (%d,%d) to (%d,%d).\n",cellList[i].id,x,y,cellList[i].x,cellList[i].y);
							break;
						}
						case 2:{
							int j;
							for(j=0;j<cellList.size();j++) if(cellList[j].id==action.second) break;
							double dt=cellList[j].getDamaged(cellList[i].makeDamage());
							refresh();
							BROADCAST("No.%03d Cell attacked No.%03d Cell, making %.3f points of damage.\n",cellList[i].id,action.second,dt);
							if(cellList[j].beKilled()){
								BROADCAST("No.%03d Cell was killed.\n",action.second);
								cellList.erase(cellList.begin()+j);
								if(j<=i) i--;
							}
							break;
						}
						case 3:{
							break;
						}
						case 4:{
							cellList[i].haveSomeFood(gameBoard[x][y]);
							refresh();
							BROADCAST("No.%03d Cell had some food.\n",cellList[i].id);
							break;
						}
					};
				}
				SLEEP(gameSpeed*1000);
			}
		}
		for(int i=0;i<cellList.size();i++){
			refresh();
			if(cellList[i].dead()){
				BROADCAST("No.%03d Cell passed away.\n",cellList[i].id);
				SLEEP(gameSpeed*1000);
				cellList.erase(cellList.begin()+i);
				i--;
			}
		}
	}
	void gameLoop(){
		for(;cellList.size();){
			++gameTime;
			for(int i=0;i<cellList.size();i++) cellList[i].incAge();
			refresh();
			moveLoop();
		}
		CLS;
		BROADCAST("Game over!\n");
	}
	void mainLoop(){
		char op[5];
		for(;;){
			CLS;
			welcomeInfo();
			puts("new - new game\n");
			puts("quit - quit game\n");
			scanf("%s",op);
			if(op[0]=='q') break;
			else if(op[0]=='n'){
				char buf[50];
				int size,num;
				double speed;
				time_t timer=time(0);
				
				printf("size = ");scanf("%d",&size);
				printf("speed = ");scanf("%lf",&speed);
				printf("num = ");scanf("%d",&num);
				
				sprintf(buf,"log/%s.log",asctime(localtime(&timer)));
				logfile=fopen(buf,"w");
				newGame(size,speed,num);
				gameLoop();
				fclose(logfile);
				SLEEP(1500);
			}
		}
		CLS;
	}
};

#endif
