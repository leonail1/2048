//
//  main.cpp
//  2048
//
//  Created by 林正刚 on 2022/11/15.
//
#include"class-fundamental.h"
#include"class-TransposeMove.h"
#include"class-DirectionVector.h"
#include <iostream>
#include"Parameter.h"
#include<stdlib.h>
#include <time.h>
using std::cout;
using std::endl;
using std::cin;
using arr=int[Map_size][Map_size];//arr代表一个指向二维数组的指针
int main(int argc, const char * argv[]) {
    srand((int)time(0));
    
    DirectionVector chess_board;//初始化地图
    
    
    arr& map=chess_board.ReturnMap();
    chess_board.Rand(map);
    while(!chess_board.Isover(map)&&chess_board.Iswin(map))
    {
        chess_board.Rand(map);
        chess_board.Generate(map);
        int dir=chess_board.GetUserInput();
        chess_board.Move(dir,chess_board.ReturnPos()[dir]);
    }
    
    return 0;
}


