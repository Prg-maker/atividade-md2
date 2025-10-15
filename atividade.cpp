// Daniel Fernandes Silva - 222008459

#include <bits/stdc++.h>
#include <vector>
#include <math.h>

using namespace std;

int mdc( int a , int b){
	
		if(b == 0) return a;
	  return mdc( b , a% b );
}


int primo(int b){
	for(int i = 2 ; i <= sqrt(b) ; i++ ){
		if(b% i == 0){
			return 1;
			
		}
	}
	return 0;
	
}
int fermat(int a, int  b ){
		if( primo( b ) == 0){
			cout << "b nao é primo" << endl;
			return 0;
		}
		
		// a ^ p-1 = 1 mod b
		return 0;


	
}
int main(){
	
	int x , y ;

	cin >> x >> y;

	
}
