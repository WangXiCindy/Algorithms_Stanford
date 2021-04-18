#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

long long CountSplitInv(vector<long>& vec,vector<long>& left,vector<long>& right){
    vector<long> temp;
    long long res=0;
    long long counter=0;
    long i=0,j=0;
    while(i<left.size() || j<right.size()){
        if(j>=right.size()){//left is not empty
            temp.push_back(left[i]);
            i++;
            res+=counter;
            continue;
        }
        if(i>=left.size()){//right is not empty
            temp.push_back(right[j]);
            j++;
            counter++;
            continue;
        }
        if(left[i]<=right[j]){//counter shows how many
            temp.push_back(left[i]);
            i++;
            res+=counter;//the res only needs to add counter when left[i] is bigger than right's saved numbers before j(which is counted by counter)
        }
        else{
            temp.push_back(right[j]);
            j++;
            counter++;
        }
    }
    vec=temp;// sort the array or the counter is useless because the counter counts the num that less than arr[now]
    return res;
}

long long Count(vector<long>& vec,long n){
    if(n==1)
        return 0;
    vector<long> vec1=vector<long>(vec.begin(),vec.begin()+vec.size()/2);
    vector<long> vec2=vector<long>(vec.begin()+vec.size()/2,vec.end());
    long long x=Count(vec1,vec1.size());
    long long y=Count(vec2,vec2.size());
    long long z=CountSplitInv(vec,vec1,vec2);
    return x+y+z;
}

//read the file
int main(){
    vector<long> array;
    ifstream input("IntegerArray.txt");
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
        array.push_back(num);
    }
    cout<<Count(array,array.size())<<endl;
    return 0;
}


