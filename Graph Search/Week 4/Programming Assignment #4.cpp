#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;


int Counter(map<long,vector<long>> table){
    bool ans[20001]={false};
    //negetive/0: midsize-abs(key)=midsize+key, positive: key+midsize
    map<long,vector<long>>::iterator iter=table.begin();
    while(iter!=table.end()){
        int key1=iter->first;
        //actually not num is less than 10000 and bigger than -10000,so key1 will not equal to 0
        if(key1<=0 || iter->second.size()==0){
            iter++;
            continue;
        }
        int ind_key21=-key1;
        int ind_key22=-key1+1;
        int ind_key23=-key1-1;

        for(int j=0;j<iter->second.size();j++){
            for(int k=0;k<table[ind_key21].size();k++){
                if(iter->second[j]+table[ind_key21][k]>=-10000 && iter->second[j]+table[ind_key21][k]<=10000 ){
                    long sum=iter->second[j]+table[ind_key21][k];
                    cout<<"1: "<<iter->second[j]<<" 2: "<<table[ind_key21][k]<<" sum: "<<sum<<endl;
                    ans[sum+10000]=true;
                }
            }
            for(int k=0;k<table[ind_key22].size();k++){
                if(iter->second[j]+table[ind_key22][k]>=-10000 && iter->second[j]+table[ind_key22][k]<=10000 ){
                    long sum=iter->second[j]+table[ind_key22][k];
                    cout<<"1: "<<iter->second[j]<<" 2: "<<table[ind_key22][k]<<" sum: "<<sum<<endl;
                    ans[sum+10000]=true;
                }
            }
            for(int k=0;k<table[ind_key23].size();k++){
                if(iter->second[j]+table[ind_key23][k]>=-10000 && iter->second[j]+table[ind_key23][k]<=10000 ){
                    long sum=iter->second[j]+table[ind_key23][k];
                    cout<<"1: "<<iter->second[j]<<" 2: "<<table[ind_key23][k]<<" sum: "<<sum<<endl;
                    ans[sum+10000]=true;
                }
                
            }
        }
        iter++;
    }
    int res=0;
    //find the count of t (x+y=t)
    for(int i=0;i<20001;i++){
        if(ans[i]==true)
            res++;
    }
    return res;
}

int main(){
    map<long,vector<long>>  table;
    
    //read the file
    ifstream input("2_SUM.txt");
    if(!input.is_open()){
        cout<<"Cannot open the file"<<endl;
        return 0;
    }

    string readLine;
    while(getline(input,readLine)){
        long num;
        stringstream st;
        st<<readLine;
        st>>num;
        long key=num/10000;
        //negetive/0: midsize-abs(key)=midsize+key, positive: key+midsize
        map<long,vector<long>>::iterator iter2;
        if(iter2!=table.end()){//find the key
            table[key].push_back(num);
        }
        else{
            vector<long> tmp;
            tmp.push_back(num);
            table.insert(make_pair(key, tmp));
        }
        
    }
    int res=Counter(table);
    cout<<res<<endl;
    //result:427
    return 0;
}


