#include<iostream>
#include<ctime>

using namespace std;

int main(){
    clock_t start = clock();
    for(int i;i<9999;i++){
        const int N = 1000;
        int sieve[N];
        for (int i=0; i<N; i++){
            sieve[i]=0;
        }
        for(int i=2; i*i<N; i++){
            if(sieve[i]==0){
                for(int k = i*i; k<N; k+=i){
                    sieve[k] = 1;
                }
            }
        }
        int c = 0;  
        for(int j = 2; j<N; j++){
            if(sieve[j]==0){
                c++;
                if(c==28||c==35||c==46||c==114){
                    cout<<j<<"\t";
                }
            }
        }
    }
    clock_t end = clock();
    float seconds = (float(end - start)) / CLOCKS_PER_SEC;

    cout<<"Execution time: "<<float(end - start);
         
    return 0;
}