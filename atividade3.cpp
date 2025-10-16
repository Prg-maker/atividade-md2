#include <bits/stdc++.h>
#include <vector>
#include <math.h>
#include <map>
#include <iomanip>



using namespace std;

int primo (int n){

    for (int i =2 ; i <= sqrt(n) ; i++){
        if(n % i == 0) return 0;
    }
    return 1;
}
map<int , int > decomposition(int n ){
    map<int , int >  xs;
    int v= n;
    for (int i = 2 ; i<= n; i++){

        if(!primo(i)){
            continue;

        }
        while(v % i == 0){
            xs[i]++;
            v = v/i;
        }
        
        if(v == 1) break;
    }

    
    
   return xs; 
}

float  tal (map<int, int > xs){
    int res = 1 ;
    for (const auto & par: xs){
        int value = par.second;
        res *= (value+1);

    }
    return res;
}
float  sig(map<int, int > xs){

    int res = 1;
    for(const auto & par : xs){
        int key = par.first;
        int value = par.second;
        int denominador = key -1;
        int numerador = pow(key, value+1) -1 ;

        res *= numerador/denominador;
    }

    return res;
}
int main(){

    int n ;

    cin >> n;
    map<int , int > xs = decomposition(n);

    float restau = tal(xs);
    float ressigma = sig(xs);

    cout << "res tau: " << restau << endl;
    cout << "res sigma: " << ressigma << endl;

    float resfinal = (float)(ressigma/restau);
    
    cout << fixed << setprecision(2);
    cout << "resposta final: " << resfinal << endl;
}