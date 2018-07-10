#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second
using namespace std;

int main(){

	int k,n;
	while(scanf("%d %d",&k,&n)==2){
		int r1,r2;
		r1 = r2 = -1;
		vector<int> nums(k+1,0);
		for(int i=0;i<n;i++){ // 1 3 2 3 1
			int a;
			scanf("%d",&a);
			nums[a]++;        // hay nums[a] a's, hay 2 tres
		}
		map<int,int> num2;
		for(int i=1;i<=k;i++){
			num2[nums[i]]++;  // hay num2[nums[i]] que tienen nums[i] elementos, hay 2 que tienen 2 elementos
		}
		if(num2.size()>3){
			printf("*\n");
			continue;
		}
		if(num2.size()==3){
			map<int,int>::iterator it=num2.begin(),it2,it3;
			it2 = it3 = it;
			it2++;
			it3++;
			it3++;
			if(it3->second == 1 && it-> second == 1 && it3->first - it->first == 2){
				for(int i=1;i<=k;i++){
					if(nums[i] == it->first){
						nums[i]++;
						r1 = i;
						break;
					}
				}
				for(int i=1;i<=k;i++){
					if(nums[i] == it3->first){
						nums[i]--;
						r2 = i;
						break;
					}
				}
			}
		}
		else if(num2.size() == 2){
			map<int,int>::iterator it=num2.begin(),it2;
			it2=it;
			it2++;
			if(abs(it2->first-it->first)==1){
				if(it->second==1){
					for(int i=1;i<=k;i++){
						if(nums[i] == it->first){
							nums[i]++;
							r1= i;
							break;
						}
					}
				}
				else if(it2->second==1){
					for(int i=1;i<=k;i++){
						if(nums[i] == it2->first){
							nums[i]--;
							r2= i;
							break;
						}
					}
				}
			}
		}
		set<int> AH;
		for(int i=1;i<=k;i++){
			AH.insert(nums[i]);
		}
		if(AH.size()>1) printf("*\n");
		else{
			if(r1==-1) printf("-%d\n",r2);
			else if(r2==-1) printf("+%d\n",r1);
			else printf("-%d +%d\n",r2,r1);
		}
	}

	return 0;
}