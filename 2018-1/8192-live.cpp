#include <bits/stdc++.h>
using namespace std;

string s;
int m;
vector<vector<int> > dp;

vector<string> resp;;

int res(int pos, int mod, int ant){
	if(dp[pos][mod]!=-1) {
		resp[pos] = (char)(ant+'0') + resp[pos+1];
		return dp[pos][mod];
	}
	if(pos == s.size()){ 
		return mod==0? 1:0;
	}
		if(s[pos] == '?'){
			int ans = 0;
			for(int i=0;i<10;i++){
				if(pos == 0 && i == 0) continue;
				if(res(pos+1,(mod*10+i)%m,i)== 1){
				resp[pos] =(char)(i+'0') + resp[pos+1] ;
				 return dp[pos][mod] = 1;
				}
			}
			return dp[pos][mod] = 0;

		}
		else{
			dp[pos][mod] = res(pos+1,(mod*10+(s[pos]-'0'))%m,s[pos]-'0') == 1? 1:0;
			resp[pos] = s[pos] +resp[pos+1] ;
			return dp[pos][mod];
		}
	

}

int main(){

	while(cin >> s >> m){
		resp.clear();
		resp.resize(s.size()+1,"");
		dp.clear();
		dp.resize(s.size()+1,vector<int>(m,-1));
		int ans = res(0,0,0);
		if(ans == 1){
			cout << resp[0] << endl;
		}
		else puts("*");
	}


	return 0;
}