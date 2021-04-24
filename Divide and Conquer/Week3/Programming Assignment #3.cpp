#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//Question 1: pivot is the first element
int partition1(vector<long>& arr,int low,int high){
    long pivot=arr[low];
    int i=low+1;
    for(int j=low+1;j<=high;j++){
        if(arr[j]<pivot){
            long temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
            i++;
        }
    }
    //low~i is less than pivot, i~high is bigger than pivot
    arr[low]=arr[i-1];
    arr[i-1]=pivot;
    return (i-1);
}
//Question 2: pivot is the last element
int partition2(vector<long>& arr,int low,int high){
    long pivot=arr[high];
    int i=low+1;

    arr[high]=arr[low];//swap
    arr[low]=pivot;
    for(int j=low+1;j<=high;j++){
        if(arr[j]<pivot){
            long temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
            i++;
        }
    }
    //low~i is less than pivot, i~high is bigger than pivot
    arr[low]=arr[i-1];
    arr[i-1]=pivot;
    return (i-1);
}

int middle(vector<long>& arr,int fir,int mid,int fin){
    // fir is the biggest
    if(arr[fir]>arr[mid]&&arr[fir]>arr[fin]){
        if(arr[mid]>arr[fin])
            return mid;
        else
            return fin;
    }
    // fir is the smallest
    else if(arr[fir]<arr[mid]&&arr[fir]<arr[fin]){
        if(arr[mid]<arr[fin])
            return mid;
        else
            return fin;
    }
    // fir is the middle
    return fir;
}
//Question 3: pivot is the "middle" of first, middle, and final elements
int partition3(vector<long>& arr,int low,int high){
    long ind=middle(arr,low,high,(low+high)/2);
    long pivot=arr[ind];
    int i=low+1;
    
    arr[ind]=arr[low];//swap
    arr[low]=pivot;
    for(int j=low+1;j<=high;j++){
        if(arr[j]<pivot){
            long temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
            i++;
        }
    }
    //low~i is less than pivot, i~high is bigger than pivot
    arr[low]=arr[i-1];
    arr[i-1]=pivot;
    return (i-1);
}

long sort(vector<long>& arr,int low,int high){
    if(high<=low)
        return 0;
    int pivot=partition1(arr,low,high);
    //int pivot=partition2(arr,low,high);
    //int pivot=partition3(arr,low,high);
    long left=sort(arr,low,pivot-1);
    long right=sort(arr,pivot+1,high);
    return left+right+(high-low);
}

int main(){
    vector<long> array;
    //read the file
    ifstream input("QuickSort.txt");
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
    cout<<sort(array,0,array.size()-1)<<endl;
    //result:162085,164123,138382
    return 0;
}
