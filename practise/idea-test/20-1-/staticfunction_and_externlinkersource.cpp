#include<iostream>
#include"staticfunction_and_externlinker.h"
using namespace std;


static void stFun(){
    cout << "stFun()" << endl;
}

void Fun(){
    cout << "Fun()" << endl;
}

namespace{
    void nameFun(){
        cout << "nameFun()" << endl;
    }
}

namespace{
    static void stnameFun(){
        cout << "stnameFun()" << endl;
    }
}

namespace Global {
void nameglobalFun(){
    cout << "nameglobalFun()" << endl;
}
static void stnameglobalFun(){
    cout << "stnameglobalFun()" << endl;
}
}