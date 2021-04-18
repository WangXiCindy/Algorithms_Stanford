#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define maxn 875714

//Easier but more time

vector<long>G[maxn],Grev[maxn];//save G and G reverse
stack<long>St;//save the stack in the first dfs

//used for first dfs
long marked[maxn];

//used for mark the Sccpos and count the result
long scc_pos,saveScc[maxn],scc_cnt[maxn];
 
void dfs1(long i){//first dfs
    if(marked[i])
        return;
    marked[i]=1;
    for(long j=0;j<G[i].size();j++){
        dfs1(G[i][j]);
    }
    St.push(i);
}

void dfs2(long i){//second dfs
    if(saveScc[i])
        return;
    saveScc[i]=scc_pos;
    scc_cnt[scc_pos]++;
    for(long j=0;j<Grev[i].size();j++){
        dfs2(Grev[i][j]);
    }
}

//find_scc
void find_scc(){
    memset(marked,0,sizeof(marked));
    memset(saveScc,0,sizeof(saveScc));
    memset(scc_cnt,0,sizeof(saveScc));
    for(long i=0;i<maxn;i++)    dfs1(i);
    while(!St.empty()){
        if(!saveScc[St.top()]){
            scc_pos++;
            dfs2(St.top());
        }
        St.pop();
    }
}

bool cmp(long x,long y){
    return x>y;
}

int main(){
    ifstream input("SCC.txt");
    if(!input.is_open()){
        cout<<"Cannot open the file"<<endl;
        return 0;
    }
    string readLine;
    while(getline(input,readLine)){
        long srt;
        long fin;
        stringstream st;
        st<<readLine;
        st>>srt;
        st>>fin;
        G[srt-1].push_back(fin-1);
        Grev[fin-1].push_back(srt-1);
    }
    find_scc();
    sort(scc_cnt,scc_cnt+maxn,cmp);
    for(int i=0;i<5;i++)
    cout<<scc_cnt[i]<<endl;
    return 0;
}
