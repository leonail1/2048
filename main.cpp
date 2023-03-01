#include"class-fundamental.h"
#include"class-TransposeMove.h"
#include"Parameter.h"
#include<time.h>
using namespace std;



int main()
{
    srand((int)time(0));
    TransposeMove f;
    f.Initlize(f.ReturnMap());
    f.Rand(f.ReturnMap());
    while(!f.Isover(f.ReturnMap()))
    {
        f.Rand(f.ReturnMap());
        f.Generate(f.ReturnMap());
        int ch=f.GetUserInput();
        f.Move(ch, f.ReturnPos()[ch]);
    }
    return 0;
}
