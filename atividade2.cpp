//Daniel Fernandes Silva 222008459
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int mdc(int a , int b){
    if(b == 0) return a;
    return mdc(b , a%b);
}
int mmc( int a , int b ){
    return (a*b) / mdc(a , b);
}
int main(){

    int n ;
    cin >> n ;
    vector<int> xs;
    for(int i = 0 ; i < n ; i++ ){
        int c;
        cin >> c;
        xs.push_back(c);

    }
    


    int res = xs[0];
    for (int i = 1 ; i < xs.size() ; i++){
        res = mmc(res , xs[i]);
    }

    if (res > 50){
        cout << "Passou de 50" << endl;
    }

    cout << res << endl;
}