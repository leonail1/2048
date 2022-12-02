//  基类
//  class-fundamental.h
//  2048
//
//  Created by 林正刚 on 2022/11/17.
//
#include"Parameter.h"
#ifndef class_fundamental_h
#define class_fundamental_h
using arr=int[Map_size][Map_size];
using arr1=int[Map_size];

class Fundamental{
public:
    Fundamental();
    void Initlize(int(&MAP)[Map_size][Map_size]);//初始化
    bool Isover(int (&MAP)[Map_size][Map_size]);//判断游戏是否结束，结束返回1
    bool Iswin(int(&MAP)[Map_size][Map_size]);//判断是否赢，并询问是否继续
    void Rand(int(&MAP)[Map_size][Map_size]);//地图随机生成2或者4，4概率较小
    double rand021();//返回0-1之间的随机数
    double randA2B(int start,int end);//返回start到end之间的随机整数
    void Generate(int(&MAP)[Map_size][Map_size]);//在屏幕上显示地图
    int GetUserInput();//接受用户输入并转化成宏定义的数字
    void HelpMessage();//帮助信息
    void Print(int cnt);//打印函数，打印第cnt个数
    void PrintMap();//打印整个地图
    virtual void Move(int direction,int position)=0;
    virtual void Combine(int direction,int position)=0;
    virtual void Gather(int direction,int position)=0;
    arr& ReturnMap();//返回MAP地图
    arr1& ReturnPos();//返回POS数组
protected:
    int MAP[Map_size][Map_size];
    int POS[4]={0,Map_size-1,0,Map_size-1};//把up，down转为position
};

Fundamental::Fundamental(void){
    Initlize(MAP);
}

void Fundamental::Initlize(int(&MAP)[Map_size][Map_size]){
    cerr<<"------------Initlize Finish!------------"<<endl;
    for(int i=0;i<Map_size;i++)
    {
        for(int j=0;j<Map_size;j++)
        {
            MAP[i][j]=0;
        }
    }
}

bool Fundamental::Isover(int (&MAP)[Map_size][Map_size]){
    for(int i=0;i<Map_size;i++)
    {
        for(int j=0;j<Map_size;j++)
        {
            if(MAP[i][j]==0)return 0;//没结束
        }
    }
    cout<<"Game end!";
    return 1;
}

bool Fundamental::Iswin(int(&MAP)[Map_size][Map_size]){
    for(int i=0;i<Map_size;i++)
    {
        for(int j=0;j<Map_size;j++)
        {
            if(MAP[i][j]==2048)
            {
                char c;
                cout<<"You win!Do you want to continue?\nPress 'y' to continue,press 'n' to exit.\n";
                cout<<"Your choice:";
                cin>>c;
                if(c=='y'||c=='Y'){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
    return 1;
}

void Fundamental::Rand(int(&MAP)[Map_size][Map_size]){
    int chose24;//生成2或者4
    
    if(rand021()<=0.05){
        chose24=4;
    }
    else{
        chose24=2;
    }
    
    int tmp[Map_size*Map_size][2]={0};//存储有空位的格子
    int volume_of_empty=0;//空格数量
    for(int i=0;i<Map_size;i++)
    {
        for(int j=0;j<Map_size;j++)
        {
            if(MAP[i][j]==0){
                
                tmp[volume_of_empty][0]=i;
                tmp[volume_of_empty++][1]=j;
                //存储坐标
            }
        }
    }
    
    int location_of_generate=randA2B(0,volume_of_empty);//在空位处随机选一个
    int x=tmp[location_of_generate][0];
    int y=tmp[location_of_generate][1];
    MAP[x][y]=chose24;//生成随机数
}

double Fundamental::rand021(){
    return rand()/(double)RAND_MAX;
}

double Fundamental::randA2B(int start,int end){
    return rand()%(end-start)+start;
}

void Fundamental::Generate(int(&MAP)[Map_size][Map_size]){
    int cnt_of_output=0;//已经输出了地图的多少个数字
    for(int k=0;k<4;k++)//每次循环输出
    {
        for(int i=0;i<4;i++)
        {
            Print(cnt_of_output++);
        }
        cout<<endl<<endl;
    }
    HelpMessage();
}

void Fundamental::HelpMessage(){
    cout<<"Press 'w':up,'s':down,'a':left,'d',right"<<endl;
    cout<<"Your input:";
}

int Fundamental::GetUserInput(){
    char c;
    labe:std::cin>>c;
    switch (c) {
        case 'w':
        case 'W':
            return UP;
            break;
        case'a':
        case'A':
            return LEFT;
            break;
        case's':
        case'S':
            return DOWN;
            break;
        case'd':
        case'D':
            return RIGHT;
            break;
        default:
            cerr<<"Error Direcion!"<<endl;
            goto labe;
            break;
    }
    return -1;
}

void Fundamental::Print(int cnt){
    int t=MAP[cnt/4][cnt%4];
    if(t!=0)
    {
        cout<<std::left<<std::setw(4)<<std::setfill(' ')<<t;
    }
    else
    {
        cout<<std::left<<std::setw(4)<<std::setfill(' ')<<'-';
    }
}

arr& Fundamental::ReturnMap(){
    return MAP;
}

arr1& Fundamental::ReturnPos(){
    return POS;
}

void Fundamental::PrintMap(){
    for(int i=0;i<Map_size;i++){
        for(int j=0;j<Map_size;j++){
            cout<<ReturnMap()[i][j]<<" ";
        }
        cout<<endl;
    }
}


#endif /* class_fundamental_h */
