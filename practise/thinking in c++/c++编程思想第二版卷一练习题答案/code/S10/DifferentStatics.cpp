//: S10:DifferentStatics.cpp
// From "Thinking in C++, 2nd Edition, Volume 1, Annotated Solutions Guide"
// by Chuck Allison, (c) 2001 MindView, Inc. all rights reserved
// Available at www.BruceEckel.com.
//{L} FileStatic1 FileStatic2
#include <iostream>

extern void setVal1(int);
extern void setVal2(int);
extern int getVal1();
extern int getVal2();

int main() {
    using namespace std;
    setVal1(1);
    setVal2(2);
    cout << "val in FileStatic1.cpp == " << getVal1() << endl;
    cout << "val in FileStatic2.cpp == " << getVal2() << endl;
}

/* Output:
val in FileStatic1.cpp == 1
val in FileStatic2.cpp == 2
*/
///:~
