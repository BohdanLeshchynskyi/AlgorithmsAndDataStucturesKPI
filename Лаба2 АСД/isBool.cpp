#include<iostream>
#include<ctime>

using namespace std;

bool isPrime(int x){
    for(int i = 2; (i*i)<=x ; i++){
        if((x%i)==0){
            return false; 
        }    
    }
    return true;
}

int main(){
    clock_t start = clock();
    for(int i=0;i<9999;i++){
        int k = 0;
        for(int i = 2 ; i < 620; i++ ){
            if(isPrime(i)){
                k++;
                if(k==28||k==35||k==46||k==114){
                    cout<<i<<"\t";
                    }
            }   
        }
    }
    clock_t end = clock();
    float seconds = (float(end - start)) / CLOCKS_PER_SEC;

    cout<<"Execution time: "<<float(end - start);

    return 0;
}