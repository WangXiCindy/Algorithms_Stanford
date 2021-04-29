#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

#define inf 1000000 //the shortest-path distance between 1 and v to is 1000000

//use to save the min length and whether it is known
struct vertex{
    int num;
    bool known;
    long minlen;
};

long Graph[205][205]={0};
vector<int> verSave;
vertex verSet[205];

void dijkstra(){
    verSet[0].minlen=0;
    while(verSave.size()<200){
        long mintemp=inf;
        int tempver=0;
        for(int i=0;i<200;i++){
            if(verSet[i].known==false && verSet[i].minlen<mintemp){
                //find the minlen from verSave
                mintemp=verSet[i].minlen;
                tempver=i;
            }
        }
        if(mintemp==inf)// all nodes are saved
            break;
        verSet[tempver].known=true;
        verSave.push_back(tempver);
        //refresh the min length of each points
        for(int i=0;i<200;i++){
            if(Graph[tempver][i]>0 && verSet[tempver].minlen+Graph[tempver][i]<verSet[i].minlen){
                verSet[i].minlen=verSet[tempver].minlen+Graph[tempver][i];
            }
        }
    }
}

void init(){
    for(int i=0;i<200;i++){
        verSet[i].num=i;
        verSet[i].known=false;
        verSet[i].minlen=inf;
    }
}

int main(){
    init();
    ifstream input("dijkstraData.txt");
    if(!input.is_open()){
        cout<<"Cannot open the file"<<endl;
        return 0;
    }
    string readLine;
    long beg,end,len=0;
    while(getline(input,readLine)){
        stringstream st;
        st<<readLine;
        st>>beg;
        while(st>>end){
            char c;
            st>>c;//read the ,
            st>>len;
            Graph[beg-1][end-1]=len;
        }
    }
    dijkstra();
    int finIn[10]={7,37,59,82,99,115,133,165,188,197};
    for(int i=0;i<10;i++){
        cout<<verSet[finIn[i]-1].minlen;
        if(i==9)
            cout<<endl;
        else
            cout<<",";
    }
    return 0;
}


