#include <iostream>
using namespace std;
int main(){
    int N,K;
    cin>>N>>K;
    int cnt=0;
    int bit=1;
    int found=0;
    bool flag=true;
    for(int i=25;i>=0;i--){
        if(N&(bit<<i))cnt++;
        if(cnt==K&flag){found=(bit<<i);
                   flag=false;
        }
    }
    if(cnt<=K)cout<<0;
    else{
        int minus=found-1;
        N=N&minus;
        cout<<found-N;
    }
}