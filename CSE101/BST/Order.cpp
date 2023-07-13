#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <stdexcept>
using namespace std;

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA7
* Order.Cpp
* Order C++ File
*********************************************************************************/



int main(int argc, char* argv[]){
    if(argc!=3){
        cerr << "Wrong amount of args" << endl;
        exit(EXIT_FAILURE);
    }
    fstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    Dictionary dictionary;
    string str = "";
    int count = 1;
    while(getline(infile,str)){
        dictionary.setValue(str,count);
        count++;
    }
    outfile << dictionary << endl;
    outfile << dictionary.pre_string() << endl;
    infile.close();
    outfile.close();
}