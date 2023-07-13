#include "Dictionary.h"
#include <iostream>
using namespace std;

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA7
* DictionaryTest.cpp
* DictionaryTest C++ File
*********************************************************************************/

int main(){
    cout << "Dictionary()" << endl;
    Dictionary A = Dictionary();
    cout << "size() = " << A.size() << endl;
    cout << "setValue() = 2" << endl;
    A.setValue("B",2);
    cout << "setValue() = 3" << endl;
    A.setValue("C",3);
    cout << "setValue() = 1" << endl;
    A.setValue("A",1);
    cout << "setValue() = 5" << endl;
    A.setValue("E",5);
    cout << "setValue() = 4" << endl;
    A.setValue("D",4);
    cout << "size() = " << A.size() << endl;
    cout << "A PRE STRING == "<< A.pre_string() << endl;
    cout << "A == "<< A.to_string() << endl;
    Dictionary B = A;
    cout << "size() = " <<  B.size() << endl;
    cout << "B == "<< B.to_string() << endl;
    cout << "A.contains(C) == " << boolalpha << A.contains("C") << endl;
    cout << "B.contains(C) == " << boolalpha << B.contains("C") << endl;
    cout << "A.getValue(C) == " << A.getValue("C") << endl;
    cout << "A.getValue(E) == " << A.getValue("E") << endl;
    cout << "B.getValue(B) == " << B.getValue("B") << endl;
    cout << "HasCurrent " << boolalpha << A.hasCurrent() << endl;
    A.begin();
    cout << "setValue(D) = 8" << endl;
    A.setValue("D",8);
    cout << "size() == " << A.size() << endl;
    cout << "remove(B) .... " << endl;
    A.remove("B");
    cout << "size() == " << A.size() << endl;
    cout << "A == "<< A.to_string() << endl;
    cout << "A == "<< A.pre_string() << endl;
    cout << "clear().............." << endl;
    A.clear();
    cout << "size() == " << A.size() << endl;
    cout << "HasCurrent " << boolalpha << A.hasCurrent() << endl;
    B.begin();
    cout << "B.currentKey ="<< B.currentKey() << endl;
    B.next();
    cout << "B.currentKey ="<< B.currentKey() << endl;
    B.end();
    cout << "B.currentKey ="<< B.currentKey() << endl;
    B.prev();
    cout << "B.currentKey ="<< B.currentKey() << endl;
    cout << "B.contains(A) == " << boolalpha << B.contains("A") << endl;
    cout << "B.remove(A) .... " << endl;
    B.remove("A");
    cout << "B.contains(A) == " << boolalpha << B.contains("A") << endl;
    cout << "B == "<< B.to_string() << endl;
    B.clear();
    cout << "B == "<< B.size() << endl;
}
