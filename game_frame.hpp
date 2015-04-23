#ifndef __GAME_FRAME_H__
#define __GAME_FRAME_H__

#include <bits/stdc++.h>
#include "board.hpp"
#include "cell.hpp"

using std::printf;

#include <unistd.h>

#if (defined(__WIN32__) || defined(_WIN32) || defined(__WIN64__) || defined(__WIN64))
#	include <windows.h>
#	define SLEEP(MICROSECONDS) Sleep(int(MICROSECONDS))
#   define CLS  system("cls")
#else
#	define SLEEP(MICROSECONDS) usleep(int(1000*(MICROSECONDS)))
#   define CLS  system("clear")
#endif

class Framework{
private:
	int gameSize;
	double gameSpeed;
	int gameTime;
	int cellNum;
	std::vector<Cell> cellList;
	Board gameBoard;
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
		puts("\"... at the temperature of 0K.\" -- by another Cell");
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
	void gameLoop(){
		for(;;){
			CLS;
			printf("Time : %d\n",++gameTime);
			gameBoard.printBoard();
			for(int i=0;i<cellList.size();i++) cellList[i].incAge();
			for(int i=0;i<cellList.size();i++) cellList[i].printInfo(),puts("");
			SLEEP(gameSpeed*1000);
		}
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
				int size;
				double speed;
				int num;
				printf("size = ");scanf("%d",&size);
				printf("speed = ");scanf("%lf",&speed);
				printf("num = ");scanf("%d",&num);
				
				newGame(size,speed,num);
				gameLoop();
			}
		}
		CLS;
	}
};

#endif
