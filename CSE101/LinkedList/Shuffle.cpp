#include "List.h"
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include<iomanip>
using namespace std;

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA5
* Shuffle.cpp
* Shuffle Main File
*********************************************************************************/


void shuffle(List &D){
    //have a 2 lists -> length / 2
    //listA stores first half
    //listB stores second half
        //one that takes in first half of D 

        //other one takes second half of D

    //while the listA and listB are not at the end
        //insert the elements of listB first and then listA -> a new list 

    //set completely newList to the inserted list
    List list,list2;
    //cout << D.length();
    for(D.moveFront();D.position()<D.length()/2;D.moveNext()){
        //cout<< D.peekNext();
        list.insertBefore(D.peekNext());
    }
    while(D.position()<=D.length()){
        //cout<< D.peekNext();
        list2.insertBefore(D.peekNext());
        D.moveNext();
    };
    List merge;
    list.moveFront();
    list2.moveFront();
    while(list.position()<list.length() && list2.position()<list2.length()){
        merge.insertBefore(list2.peekNext());
        merge.insertBefore(list.peekNext());
        list.moveNext();
        list2.moveNext();
    }
    if(D.length()%2!=0){
        merge.insertBefore(list2.peekNext());
    }
    //cout << "hi";
    D = List(merge);
}

int main(int argc, char* argv[]){
    int shufflecount = 0;
    if(argc!=2){
        cerr << "Wrong amount of args" << endl;
        exit(EXIT_FAILURE);
    }
    int size = atoi(argv[1]);
    List list;
    List shuffled;
    cout << "deck size" << "       " << "shuffle count" <<endl;
    cout << "------------------------------"<<endl;
    //int i = 0;
    /*while(i<size){
        shuffled.insertBefore(i);
        list.insertBefore(i);
        i++;
    }*/
    for(int j=1;j<=size;j++){
        shuffled.insertBefore(j-1);
        list.insertBefore(j-1);
        shufflecount=1;
        shuffle(shuffled);
        while(!list.equals(shuffled)){
            shuffle(shuffled);
            shufflecount++;
        }
        cout << j << "          " << shufflecount << endl;
    }
    /*shuffle(shuffled);
    cout << shuffled.to_string() << endl;
    shuffle(shuffled);
    cout << shuffled.to_string() << endl;
    shuffle(shuffled);
    cout << shuffled.to_string() << endl;*/
}

