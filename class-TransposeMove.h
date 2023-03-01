//  转置矩阵派生类，以转置矩阵作为核心算法
//  class-TransposeMove.h
//  2048
//
//  Created by 木林 on 2022/11/17.
//

#ifndef class_TransposeMove_h
#define class_TransposeMove_h
#include"Parameter.h"
#include"class-fundamental.h"

class TransposeMove final: public Fundamental{
public:
    void Move(int direction,int position);//根据用户输入进行移动
private:
    void Gather(int direction,int position);//把所有有数字的格子向一个方向聚集，不合并
    void Combine(int direction,int position);//合并操作
    void Transpose(int(&MAP)[Map_size][Map_size]);//矩阵转置

};

void TransposeMove::Move(int direction,int position){//方向，position用数组获取
    if(direction==LEFT||direction==RIGHT){
        Transpose(MAP);//左右操作，转置矩阵之后再进行上下操作
    }
    
    Gather(direction-2,position);//左->上，右->下
    Combine(direction-2, position);
    Gather(direction-2, position);//先聚集，再合并，再聚集因为合并产生的空格
    
    if(direction==LEFT||direction==RIGHT){
        Transpose(MAP);//如果转置了，要转回去
    }
}

void TransposeMove::Gather(int direction,int position){
    for(int j=0;j<Map_size;j++)//每一列单独操作
    {
        for(int i=0-position;i<Map_size-1-position;i++)
        {
            //每一行向上向下操作合并
            //如果向上，就从0到Map_size-1搜索
            //如果向下,就从-Map_size+1到0搜索，并取绝对值
            if(MAP[abs(i)][j]==0)
            {
                //从最底部（最顶部）开始向上（向下）找第一个为0的空格
                //如果找到，循环找比他更上面（下面）一个不为0的格子，并聚集过来
                for(int non_zero_position=i+1;
                    non_zero_position<Map_size-position;
                    non_zero_position++){
                    if(MAP[abs(non_zero_position)][j]!=0){
                        //找到不为0的值就和0的空格交换位置
                        std::swap(MAP[abs(non_zero_position)][j],MAP[abs(i)][j]);
                        break;
                    }
                }
            }
        }
    }
}

void TransposeMove::Combine(int direction,int position){
    for(int j=0;j<Map_size;j++)//每一列单独操作
    {
        for(int i=0-position;i<Map_size-1-position;i++)
        {
            //如果向上，从0到3判断，前一个和后一个格子的数是否相同
            //如果相同，则合并到前一个格子，后一个格子变成0
            //如果向下，从-3到0判断
            if((MAP[abs(i)][j]==MAP[abs(i+1)][j])&&(MAP[abs(i)][j]!=0)){
                MAP[abs(i)][j]*=2;
                MAP[abs(i+1)][j]=0;
                i++;
            }
            else{
                continue;
            }
        }
    }
}

void TransposeMove::Transpose(int(&MAP)[Map_size][Map_size]){
    int tmp[Map_size][Map_size];
    for(int i=0;i<Map_size;i++){
        for(int j=0;j<Map_size;j++){
            tmp[i][j]=MAP[i][j];
        }
    }
    for(int i=0;i<Map_size;i++){
        for(int j=0;j<Map_size;j++){
            MAP[i][j]=tmp[j][i];
        }
    }
}


#endif /* class_TransposeMove_h */
