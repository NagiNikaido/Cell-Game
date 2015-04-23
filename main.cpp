#include <bits/stdc++.h>
#include "board.hpp"
#include "cell.hpp"
#include "game_frame.hpp"

using namespace std;

void someTest(){
	Board a(20);
	Heap<int> b;

	a.init(10,6,-1,EllipseDec());
	a.printBoard();
	b.push(1);
	b.push(2);
	b.push(3);
	std::printf("%d\n",b.top());
	for(Heap<int> :: iterator p=b.begin();p!=b.end();p++)
		std::printf("%d ",*p);
	std::puts("");
	b.pop();
	std::printf("%d\n",b.top());
}

Framework Game;

int main()
{
	Game.mainLoop();
	return 0;
}
