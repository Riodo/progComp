#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;
 
typedef long long intt;
typedef pair<int, int> par;
typedef vector<vector<int> > graph;
typedef vector<vector<par> > wgraph;
#define pb push_back
#define ppb pop_back
vector <int> origen,destino,capacidad,costos,dia,orden,inicial;
class Dinic {
	struct edge {
		int to, rev;
		intt f, cap;
	};
	vector<vector<edge> > g;
	vector<intt> dist;
	vector<int> q, work;
	int n, sink;
	bool bfs(int start, int finish) {
		dist.assign(n, -1);
		dist[start] = 0;
		int head = 0, tail = 0;
		q[tail++] = start;
		while (head < tail) {
			int u = q[head++];
			for (const edge &e : g[u]) {
				int v = e.to;
				if (dist[v] == -1 and e.f < e.cap) {
					dist[v] = dist[u] + 1;
					q[tail++] = v;
				}
			}
		}
		return dist[finish] != -1;
	}
	intt dfs(int u, intt f) {
		if (u == sink) return f;
		for (int &i = work[u]; i < (int)g[u].size(); ++i) {
			edge &e = g[u][i];
			int v = e.to;
			if (e.cap <= e.f or dist[v] != dist[u] + 1)
				continue;
			intt df = dfs(v, min(f, e.cap - e.f));
			if (df > 0) {
				e.f += df;
				g[v][e.rev].f -= df;
				return df;
			}
		}
		return 0;
	}
public:
	Dinic(int n) {
		this->n = n;
		g.resize(n);
		dist.resize(n);
		q.resize(n);
	}
	Dinic(){
 
	}
	// aristas bidireccionales si cap de edge b = cap, si es 0 no son bidireccionales!!
	void add_edge(int u, int v, intt cap) {
    edge a = {v, (int)g[v].size(), 0, cap};
    edge b = {u, (int)g[u].size(), 0, 0};
    g[u].pb(a);
    g[v].pb(b);
	}
	intt max_flow(int source, int dest) {
		sink = dest;
		intt ans = 0;
		while (bfs(source, dest)) {
			work.assign(n, 0);
			while (intt delta = dfs(source, 1000)) ans += delta;
		}
		return ans;
	}
};
int r,c;
int actual(int f, int C){
	return 2*f*c + 2*C;
}
int der(int f, int C){
	return 2*f*c +2*C +2;
}

int izq(int f, int C){
	return 2*f*c +2*C -2;
}

int up(int f, int C){
	return 2*(f-1)*c +2*C ;
}
int down(int f,int C){
	return 2*(f+1)*c +2*C;
}
int main(){
	while(cin >> r >> c){
		char mat[r][c];
		int puntos = 0;
		int par=0,impar=0;
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				cin >> mat[i][j];
				if((i+j)%2==0)
						par+=2;
				else impar+=2;
				
				if(mat[i][j] == 'o'){
					puntos++;
					if((i+j)%2==0)
						par--;
					else impar--;
				}
			}
		}
		//cout << par << " " << impar << endl;
		if(puntos%2!=0 || par!=impar){
			cout << "N" << endl;
			continue;
		}
		//puts("");
		Dinic din(2*r*c + 2);
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				//cout << actual(i,j) << " ";
				din.add_edge(2*r*c,actual(i,j),1);
				if(mat[i][j]!='o')
				din.add_edge(actual(i,j)+1,2*r*c+1,1);
				if(i!=0){
					if(mat[i-1][j]!='o')
						din.add_edge(actual(i,j),up(i,j)+1,1);
				}
				if(i!=r-1){
					if(mat[i+1][j]!='o')
						din.add_edge(actual(i,j),down(i,j)+1,1);
				}
				if(j!=0){
					if(mat[i][j-1]!='o')
						din.add_edge(actual(i,j),izq(i,j)+1,1);
				}
				if(j!=c-1){
					if(mat[i][j+1]!='o')
						din.add_edge(actual(i,j),der(i,j)+1,1);
				}
			}
		//	puts("");
		}
		/*puts("");
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				cout << actual(i,j) << " : ";
				if(i!=0){
					cout << up(i,j) << " ";
				}
				if(i!=r-1){
					cout << down(i,j) << " ";
				}
				if(j!=0){
					cout << izq(i,j) << " ";
				}
				if(j!=c-1){
					cout << der(i,j) << " ";
				}
				puts("");
			}
			puts("");
		}
		puts("");*/
		int flow=din.max_flow(2*r*c,2*r*c+1);
		//cout << "FLOW: "<<flow<<endl;
		if(flow == r*c-puntos)
			cout << "Y" << endl;
		else cout << "N" << endl;



	}



	return 0;
}