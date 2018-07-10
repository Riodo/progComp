#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define ll long long
using namespace std;


struct SegTree{

	vector<int> st;
	vector<ll> A;
	int n;
	int left(int p){ return p<<1;}
	int right(int p){ return p<<1|1;}
	void build(int p, int L , int R){
		if(L==R){
			st[p] = L;
		}
		else{
			build(left(p),L,(L+R)/2);
			build(right(p),(L+R)/2+1,R);
			int p1=st[left(p)],p2=st[right(p)];
			st[p] = (A[p1] >= A[p2]) ? p1 : p2;
		}
	}

	ll rmq(int p, int L, int R, int i, int j){
		//cout << "("<<i<<","<<j<<")";
		//cout << "L: "<<L <<" R: "<<R<<endl;
		if(i>R || j < L) {
		//	cout << "SE SALE "<<endl;
			return -1;
		}
		if(L>=i && R<=j) return st[p];

		ll p1=rmq(left(p),L,(L+R)/2,i,j);
		ll p2=rmq(right(p),(L+R)/2+1,R,i,j);
		if(p1==-1) return p2;
		if(p2==-1) return p1;
		//cout << "Comparo " << A[p1] << " con " << A[p2] << ", "<<p1<<" "<<p2<<" L: " <<L <<" R: "<<R<< endl;
		return (A[p1] >= A[p2]) ? p1 : p2;
	}

	void update(int nodo,int L, int R, int pos, ll val){
		if(L == R && L == pos){
			//cout << "UPDATIE "<<L << endl;
			A[pos] = val;
			return;
		}
		if(pos < L || pos > R) return;
		update(left(nodo),L,(L+R)/2,pos,val);
		update(right(nodo),(L+R)/2+1,R,pos,val);
		st[nodo] = (A[st[left(nodo)]]>=A[st[right(nodo)]]) ? st[left(nodo)] : st[right(nodo)];
	}
	void print(){
		for(int i=0;i<st.size();i++){
			cout << st[i] << " ";
		}
		cout << endl;
		cout << "A: "<<endl;
		for(int i=0;i<A.size();i++){
			cout << A[i] << " ";
		}
		puts("");

	}
	SegTree(int _n){
		n = _n;
		st.assign(4*n,0);
		A.assign(n,0);
		build(1,0,n-1);


	}



};

int main(){
	int n;
	while(scanf("%d",&n)==1){
	//scanf("%d",&n);
		map<ll,int> m;
		vector <pair<pair<ll,ll>,ll> >pers(n);

		for(int i=0;i<n;i++){
			ll a,b,c;
			scanf("%lld %lld %lld",&a,&b,&c);
			pers[i]=mp(mp(a,b),c);
		}
		sort(pers.begin(),pers.end());
		pers.push_back(mp(mp(1e10,1e10),0));
		for(int i=0;i<n-1;i++){
			if(pers[i].f == pers[i+1].f){
				pers[i+1].s += pers[i].s;
				pers[i].s=0;
			}
		}
		vector <pair<pair<ll,ll>,ll> >pers2;
		set<ll> nums;
		for(int i=0;i<n;i++){
			if(pers[i].s!=0){
				pers2.push_back(pers[i]);
				nums.insert(pers2.back().f.s);
			}
		}
		int contador = 0;
		for(set<ll>::iterator it = nums.begin();it!=nums.end();it++){
			m[*it] = contador++;
		}
		m[1e10]=contador++;
		nums.insert(1e10);
		pers2.push_back(mp(mp(1e10,1e10),0));
		//cout << endl;
		SegTree ST(nums.size());
		//ST.print();
		ll MAX = 0;
		queue<pair<int,ll> > q;
		for(int i=pers2.size()-2;i>=0;i--){
			if(pers2[i].f.f!=pers2[i+1].f.f){
				while(!q.empty()){
					int indice = m[pers2[q.front().f].f.s];
					if(q.front().s>ST.A[indice]){
						ST.update(1,0,nums.size()-1,indice,q.front().s);
					//	cout << "update "<<m[pers2[q.front().f].f.s] << "con "<<q.front().s << endl;
					//	ST.print();
						//cout << "UPDATE " <<ST.rmq(1,0,nums.size()-1,m[pers2[q.front().f].f.s],nums.size()-1)<< endl;
					}
					q.pop();
				}
			}
			ll res = pers2[i].s + ST.A[ST.rmq(1,0,nums.size()-1,m[pers2[i].f.s]+1,nums.size()-1)];
			q.push(mp(i,res));
 			//cout << "persona : "<< pers2[i].f.f << " " << pers2[i].f.s <<" "<< pers2[i].s<< " MAX: "<< res << "RMQ: "<<ST.rmq(1,0,nums.size()-1,m[pers2[i].f.s]+1,nums.size()-1)<< "PAR; ("<<m[pers2[i].f.s]<<","<<nums.size()-1<<")"<<endl;
			MAX = max(MAX,res);
		}
		//cout << "ST: "<<endl;
		//ST.print();


		printf("%lld\n",MAX);
	}	
	return 0;
}