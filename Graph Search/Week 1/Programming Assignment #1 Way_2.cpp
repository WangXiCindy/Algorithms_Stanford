#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define maxn 875714

const long Max=875714;
using namespace std;
//the edges are directed from the first column vertex to the second column vertex
//Use kosaraju Algorithm to solve the problem

//Use linked list to save the graph
class EdgeNode{
public:
    long vertex;
    EdgeNode* next;
    EdgeNode(long v=0,EdgeNode* n=NULL): vertex(v),next(n){}
    
};
class VerNode{
public:
    long num;
    EdgeNode * first;
    VerNode(long n=0,EdgeNode* f=NULL):num(n),first(f){}
};
class Graph{
public:
    VerNode* VerArr=new VerNode[Max];
    
    //Add to the first Edge
    void addEdge(long srt,long fin){
        EdgeNode *temp=new EdgeNode(fin);
        temp->next=VerArr[srt].first;
        VerArr[srt].first=temp;
    }
    
    void initG(){
        for(long i=0;i<Max;i++){
            VerArr[i].num=i;
            VerArr[i].first=NULL;
        }
        ifstream input("SCC.txt");
        if(!input.is_open()){
            cout<<"Cannot open the file"<<endl;
            return;
        }
        string readLine;
        while(getline(input,readLine)){
            long srt;
            long fin;
            stringstream st;
            st<<readLine;
            st>>srt;
            st>>fin;
            addEdge(srt-1,fin-1);//The list starts from 0
        }
        return;
    }
    
    void initGrev(){
        for(long i=0;i<Max;i++){
            VerArr[i].num=i;
            VerArr[i].first=NULL;
        }
        ifstream input("SCC.txt");
        if(!input.is_open()){
            cout<<"Cannot open the file"<<endl;
            return;
        }
        string readLine;
        while(getline(input,readLine)){
            long srt;
            long fin;
            stringstream st;
            st<<readLine;
            st>>srt;
            st>>fin;
            addEdge(fin-1,srt-1);//The list starts from 0
        }
    }
    
};

bool cmp(long a,long b){
    return a>b;
}

class DFSearch{
public:
    bool* marked;
    vector<long> TimeP;//time by time to push back
    vector<long> leader;
    long s;//which SCC?
    void init(){
        marked=new bool[Max];
        for(long i=0;i<Max;i++)
            marked[i]=false;
    }
    //Reference the silde
    void search(Graph graph,int Gflag){
        init();
        leader.resize(Max);
        for(long i=Max-1;i>=0;i--){
            if(Gflag==1){//loop as vertex
                if(marked[i]==false){
                    DFS(graph,i,Gflag);
                }
            }//G
            else{//loop as time
                if(marked[TimeP[i]]==false){
                    s=TimeP[i];
                    DFS(graph,TimeP[i],Gflag);
                }
            }
        }
    }
    //Use stack to do the DFS
    //Gflag is used to judge the reverse Graph
    void DFS(Graph graph,long i,int Gflag){
        marked[i]=true;
        stack<VerNode> saveVer;
        saveVer.push(graph.VerArr[i]);
        leader[i]=s;
        while(!saveVer.empty()){
            bool fin=true;//To make sure all the points of i can be linked to are marked;
            VerNode vtemp=saveVer.top();
            EdgeNode* etemp=vtemp.first;
            //cout<<vtemp.num+1<<" ";
            while(etemp){
                if(!marked[etemp->vertex]){
                    marked[etemp->vertex]=true;
                    saveVer.push(graph.VerArr[etemp->vertex]);
                    fin=false;
                    break;
                }
                etemp=etemp->next;
            }
            if(fin==true){
                if(Gflag==1){
                    TimeP.push_back(vtemp.num);//time->vertex,save the fin time
                    //cout<<endl;
                }
                else
                    leader[vtemp.num]=s;//in the same SCC
                saveVer.pop();
            }
        }
    }
    
    
    //Judge the five largest SCCS
    void judgeFive(){
        vector<long> res;
        res.resize(Max);
        for(long i=0;i<Max;i++){
            res[leader[i]]++;//The size of the same SCC
        }
        sort(res.begin(),res.end(),cmp);
        for(int i=0;i<4;i++){
            cout<<res[i]<<",";
        }
        cout<<res[4]<<endl;
    }
    
};


int main(){
    Graph g;
    DFSearch D;
    g.initG();
    D.search(g, 1);//search g
    g.initGrev();
    D.search(g, 0);//search grev
    D.judgeFive();
    return 0;
}

/*
1 2
2 3
2 5
2 6
3 4
3 7
4 3
4 8
5 1
5 6
6 7
7 6
7 8
res: 3 2 2
*/

/*
1 2
1 3
2 4
3 5
4 1
4 6
5 6
res: 3
*/
