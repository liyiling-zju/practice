#include<iostream>
using namespace std;
//static void stFun();

void Fun(){
    cout << "Fun()" <<endl;
};

//namespace{
//    void nameFun();
//}

//namespace{
//    static void stnameFun();
//}

static void stFun(){
    cout << "stFun()" << endl;
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
void nameglobalFun();
static void stnameglobalFun()//{
//    cout << "stnameglobalFun()" << endl;
//}
    ;
}
void Global::stnameglobalFun(){
    cout << "stnameglobalFun()" << endl;
}

typedef void (*FUN)();

template<FUN f>
void A(){
    class Local {
    public:
        void localnameFun(){
            cout << "localnameFun()" << endl;
        }
    };
    f();
}