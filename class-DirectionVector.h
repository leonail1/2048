//  方向向量派生类
//  class-DirectionVector.h
//  2048
//
//  Created by 林正刚 on 2022/11/17.
//

#ifndef class_DirectionVector_h
#define class_DirectionVector_h
#include"Parameter.h"
#include"class-fundamental.h"

class DirectionVector : public Fundamental{
public:
    void Move(int direction,int position);//根据用户输入进行移动
    void Gather(int direction,int position);
    void Swap(int x,int y,int change,int constant,int(&row_col)[2]);//聚集的交换函数
    void Merge(int x,int y,int (&row_col)[2]);//合并函数
    void Combine(int direction,int position);
    int ReturnX(int direction);
    int ReturnY(int direction);//对重载的Move函数给出x,y参数的值
private:
    int row_col[2];
};

void DirectionVector::Move(int direction,int position){//重载
    Gather(direction, position);
    Combine(direction, position);
    Gather(direction, position);
}





void DirectionVector::Gather(int direction,int position){//重载
    int x=ReturnX(direction);
    int y=ReturnY(direction);
    for(row_col[x]=0;row_col[x]<Map_size;row_col[x]++)
    {
        for(row_col[y]=0-position;row_col[y]<Map_size-1-position;row_col[y]++)
        {
            //上下操作：x=0,y=1,固定列对行操作
            //左右操作：x=1,y=0,固定行对列操作
            if(MAP[abs(row_col[1])][abs(row_col[0])]==0)
            {
                int change=row_col[y];
                for(;change<=Map_size-position-1;
                    change++){
                    Swap(x, y,change,row_col[x],row_col);
                }
            }
        }
    }
}
void DirectionVector::Swap(int x,int y,int change,int constant,int(&row_col)[2]){
    //上下：x==0,y==1,row_col[1]=tmp=-3,row_col[1]=tmp++,MAP对行操作
    //左右：x==1,y==0,row_col[0]=tmp=-3,row_col[0]=tmp++,MAP对列操作
    int tmp[2]={change,constant};
    if(MAP[abs(tmp[x])][abs(tmp[y])]!=0){
        //找到不为0的值就和0的空格交换位置
        std::swap(MAP[abs(tmp[x])][abs(tmp[y])],MAP[abs(row_col[1])][abs(row_col[0])]);
        return;
    }
}



void DirectionVector::Combine(int direction,int position){
    int row_col[2];
    int x=ReturnX(direction);
    int y=ReturnY(direction);
    for(row_col[x]=0;row_col[x]<Map_size;row_col[x]++)
    {
        for(row_col[y]=0-position;row_col[y]<Map_size-1-position;row_col[y]++)
        {
          
            //上下操作：x=0,y=1,固定列对行操作
            //左右操作：x=1,y=0,固定行对列操作
            Merge(x, y,row_col);
                
            
        }
    }
}

int DirectionVector::ReturnX(int direction){
    return (direction==UP||direction==DOWN)?0:1;//UP或DOWN->x=0，否则x=1
}

int DirectionVector::ReturnY(int direction){
    return (direction==LEFT||direction==RIGHT)?0:1;//left|right->y=0,否则y=1
}


void DirectionVector::Merge(int x,int y,int (&row_col)[2]){
    //row_col[0]:列 row_col[1]:行
    //上下移动：对行操作：x==0,y==1,row_col[1]=-3,row_col[1]++,保证Combine循环中行在内层
    //上下移动：内层if仅有row_col[1]更新，保证对行操作
    //左右移动：对列操作：x==1,y==0,row_col[0]=-3,row_col[0]++,保证Combine循环中列在内层
    //左右移动：内层if仅有row_col[0]更新，保证对列操作
    int cur_value=MAP[abs(row_col[1])][abs(row_col[0])];
    row_col[y]++;
    int next_value=MAP[abs(row_col[1])][abs(row_col[0])];
    if((cur_value==next_value)&&(cur_value!=0)){
        row_col[y]--;
        MAP[abs(row_col[1])][abs(row_col[0])]*=2;
        row_col[y]++;
        MAP[abs(row_col[1])][abs(row_col[0])]=0;
    }
    else{
        row_col[y]--;
        return;
    }
}


#endif /* class_DirectionVector_h */
