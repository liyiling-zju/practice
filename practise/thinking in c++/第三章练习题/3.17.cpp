#include<iostream>
using namespace std;

union Packed {//Declaration similar to a class
    char i;
	short j;
	int k;
	long l;
    float f;
	double d;
	//The union will be the size of a
	//double,since that's the largest element 
};  //Semicolon ends a union ,like a struct

int main(){
	cout << "size of (Packed) = "
	     << sizeof(Packed) << endl;
	     Packed x;
	     x.i ='c';
	     cout << x.i << endl;
	     x.f = 3.14159;
	     cout << x.f << endl;
}
