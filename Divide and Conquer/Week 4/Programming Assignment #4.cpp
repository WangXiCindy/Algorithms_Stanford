#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void random(vector<vector<int>>& graph){
    int ind_u=rand()%graph.size();//random u
    int uv=rand()%(graph[ind_u].size()-1)+1;//get random v from the u vector
    int u=graph[ind_u][0];
    int v=graph[ind_u][uv];
    
    
    int ind_v=0;//find the index of v in the graph
    //merge, father is u, all edges connected with v are changed to u
    for(int i=0;i<graph.size();i++){
        for(int j=1;j<graph[i].size();j++){
            if(graph[i][0]!=v){
                if(graph[i][j]==v){
                    graph[i][j]=u;
                }
            }
            else{
                //get v index
                ind_v=i;
                //if i==v, push the point connected with v
                graph[ind_u].push_back(graph[i][j]);
            }
        }
    }
    
    //remove self-loop
    for(int i=1;i<graph[ind_u].size();i++){
        if(graph[ind_u][i]==u){
            graph[ind_u].erase(graph[ind_u].begin()+i);
            i--;
        }
    }
    graph.erase(graph.begin()+ind_v);//remove point v
}

int RandomContraction(vector<vector<int>>& graph){
    while(graph.size()>2){//finally only have two cuts
        random(graph);
    }
    return graph[0].size()-1;//return the min cut
}


int main(){
    vector<vector<int>> graph;
    //read the file
    ifstream input("kargerMinCut.txt");
    if(!input.is_open()){
        cout<<"Cannot open the file"<<endl;
        return 0;
    }

    string readLine;
    while(getline(input,readLine)){
        int num,n;
        stringstream st;
        st<<readLine;
        st>>n;
        vector<int> temp;
        temp.push_back(n);//have to know the save position of every vertex(the v will be deleted so cannot find the vertex by index)
        while(st>>num){
            temp.push_back(num);
        }
        graph.push_back(temp);
        temp.clear();
    }
    
    //run many times to find the answer
    int min=INT_MAX;
    for(int i=0;i<500;i++){
        vector<vector<int>> tmpgraph=graph;
        int tmp=RandomContraction(tmpgraph);
        cout<<i<<" is "<<tmp<<endl;
        if(tmp<min)
            min=tmp;
    }
    cout<<"min: "<<min<<endl;
    //result:17
    return 0;
}


