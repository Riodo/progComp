#include <bits/stdc++.h>
using namespace std;

int main(){
	string s;
	while(cin >> s){
		int start = -1;
		bool a=false;
		bool si = false;
		for(int i=0,j=0;j<s.size();i=(i+1)%s.size(),j++){
			if(s[i]=='P' && a==false){
				a=true;
				j=0;
			}

			else if(s[i]=='R' && a){
				si = true;
				start=i;
				break;
			}
			if(s[i] == 'R') si = true;
		}
		if(si == false){
			cout << "0" << endl;
			continue;
			//return 0;
		}
		if(start==-1){
			cout << s.size()-1 << endl;
			//return 0;
			continue;
		}
		start%=s.size();
		vector<int> mult;
		for(int i=2;i<=s.size()/2;i++){
			if(s.size()%i==0){
				mult.push_back(i);
			}
		}
		int resp = 0;
		//cerr << "AAAHHHH" << endl;
		vector<bool> AH(s.size(),false);
		for(int i=0;i<mult.size();i++){
			//cerr << i << endl;
			int pos = start;
			int cont = 0;
			bool next = false;
			for(int j=0;j<s.size();j++){
				//cerr << j << endl;
				int P=pos+j;
				if(P>=s.size()) P-=s.size();
				if(s[P]=='P'){
					cont = 0;
					next = false;
					continue;
				}
				if(next) continue;
				if(cont<mult[i]){
					cont++;
					int INICIO = P;
					P+=mult[i];
					bool vuelta=false;
					while(true){
						if(P>=s.size())P-=s.size();
						if(P<INICIO) vuelta=true;
						if(P==INICIO ) break;
						if(s[P]=='P') break;
						P+=mult[i];
					}
					if(P==INICIO){
						AH[mult[i]] = true;
						break;
					}
				}
				else next=true;

			}
		}
		for(int i=2;i<AH.size();i++){
			if(!AH[i]) continue;
			resp++;
			for(int j=i+i;j<AH.size();j+=i){
				AH[j] = true;
			}
		}
		cout << resp << endl;

	}

	return 0;
}