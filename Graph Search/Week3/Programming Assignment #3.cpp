#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class MinMaxHeap{
private:
    int size;
    bool min;//Min or Max Heap
    vector<int> arr;//save the heap elements
    
public:
    MinMaxHeap(bool m){
        min=m;
        size=0;
    }
    void swap(int x,int y){
        int temp=arr[x];
        arr[x]=arr[y];
        arr[y]=temp;
    }
    int top(){
        if(!arr.empty())
            return arr[0];
        return 0;
    }
    int getSize(){
        return size;
    }
    void insert(int num){
        int pos=size;
        arr.push_back(num);
        size=arr.size();
        while(pos>0){
            int parent=(pos-1)/2;
            if(min){//minheap
                if(arr[parent]<=arr[pos])
                    break;
            }
            else{//maxheap
                if(arr[parent]>=arr[pos])
                    break;
            }
            swap(parent,pos);
            pos=parent;//update pos;
        }
    }
    
    void pop(){
        //find the max or min to be the root
        arr[0]=arr[size-1];
        arr.pop_back();
        size=arr.size();
        int pos=0;
        while(pos<size/2){//or pos is a leaf, because heap is a complete binary tree
            int left=pos*2+1;
            //remember you start from 0, so it is pos*2+1, not pos*2
            int right=left+1;
            int temproot=0;
            if(min){//find the smallest
                if(right<size && arr[left]>arr[right]){
                    temproot=right;
                }
                else
                    temproot=left;
                // pos is smaller than children
                if(arr[pos]<arr[temproot])
                    break;
            }
            else{
                if(right<size && arr[left]<arr[right]){
                    temproot=right;
                }
                else
                    temproot=left;
                // pos is bigger than children
                if(arr[pos]>arr[temproot])
                    break;
                
            }
            swap(pos,temproot);
            pos=temproot;
            
        }
        
    }
    
};

int main(){
    MinMaxHeap minHeap(true);
    MinMaxHeap maxHeap(false);
    
    //read the file
    ifstream input("Median.txt");
    if(!input.is_open()){
        cout<<"Cannot open the file"<<endl;
        return 0;
    }
    // we just need to sum median
    minHeap.insert(10005);
    maxHeap.insert(0);
    string readLine;
    long res=0;
    while(getline(input,readLine)){
        int num;
        stringstream st;
        st<<readLine;
        st>>num;
        
        if(num<maxHeap.top()){
            maxHeap.insert(num);
        }
        else{
            minHeap.insert(num);
        }
        if(maxHeap.getSize()>minHeap.getSize()+1){
            int max_top=maxHeap.top();
            maxHeap.pop();
            minHeap.insert(max_top);
        }
        if(minHeap.getSize()>maxHeap.getSize()+1){
            int min_top=minHeap.top();
            minHeap.pop();
            maxHeap.insert(min_top);
        }
        if(minHeap.getSize()==maxHeap.getSize()+1){
            res+=minHeap.top();
        }
        else{
            //if k is odd, choose (k+1)/2 as median
            res+=maxHeap.top();
        }
    }
    
    cout<<res%10000<<endl;
    
    //result:1213
    return 0;
}

