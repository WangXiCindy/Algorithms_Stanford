#include <iostream>
using namespace std;


int addfun(int x,int y,int add){
    return x+y+add;
}

string addmore(string x,string y){
    string res="";
    int i=x.length()-1;
    int j=y.length()-1;
    int add=0;
    for(;;i--,j--){
        int first=0,second=0;
        if(i<0&&j>=0){
            first=0;
            second=y[j]-'0';
        }
        else if(i>=0&&j<0){
            first=x[i]-'0';
            second=0;
        }
        else if(i<0&&j<0)
            break;
        else{
            first=x[i]-'0';
            second=y[j]-'0';
        }
        int temp=addfun(first,second,add);
        if(temp>=10){
            add=temp/10;
            temp%=10;
        }
        else
            add=0;
        res=to_string(temp)+res;
    }
    if(add!=0){
        res=to_string(add)+res;
    }
    
    return res;
}

int mulfun(int x,int y,int add){
    return x*y+add;
}

string mul(string x,string y){
    string res="0";
    int j=y.length()-1;
    for(;j>=0;j--){
        int add=0;
        int i=x.length()-1;
        string stemp="";
        for(;i>=0;i--){
            int temp=mulfun(x[i]-'0',y[j]-'0',add);
            if(temp>=10){
                add=temp/10;
                temp%=10;
            }
            else
                add=0;
            stemp=to_string(temp)+stemp;
        }
        if(add!=0){
            stemp=to_string(add)+stemp;
        }
        string s(y.length()-1-j,'0');
        stemp+=s;
        res=addmore(res,stemp);
    }
    return res;
}
int main(){
    string x="3141592653589793238462643383279502884197169399375105820974944592";
    string y="2718281828459045235360287471352662497757247093699959574966967627";
    string res=mul(x,y);
    cout<<res<<endl;
}

//The result is 8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184
