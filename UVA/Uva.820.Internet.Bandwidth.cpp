#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>


using namespace std;

#define INF 1e9
#define MAX_V 110

typedef vector<int> vi;

int cases, s, t, f, mf, qt_vertex, qt_edges;

int res[MAX_V][MAX_V], p[MAX_V];

vi graph[MAX_V];

bitset<MAX_V> visited;

void init(){
	memset(res, 0, sizeof res);
	for (int i = 1; i<=qt_vertex; i++) graph[i].clear();
}

void read(){
	 int u, v, w;
     scanf("%d %d %d", &s, &t, &qt_edges);
    
     for (int i = 0; i < qt_edges; i++){
     	scanf("%d %d %d", &u, &v, &w);
     	if (!res[u][v]){
     	 graph[u].push_back(v);
     	 graph[v].push_back(u);
        }
     	res[u][v] += w;
     	res[v][u] += w;
     }
	
}

void bfs(){
	visited.reset(); visited[s] = 1;
	queue<int> q; q.push(s);
	memset(p, -1, sizeof p);
    while(!q.empty()){
     int u = q.front(); q.pop();
     if (u==t) break;
     for (int i = 0; i < graph[u].size(); i++){
     	int v = graph[u][i];
     	if (!visited[v] && res[u][v]){
     		p[v] = u;
     		visited[u] = 1;
     		q.push(v);
     	}
     }
    }
} 

void augment(int v, int minEdge){
 if(v == s){ f = minEdge; return;}
 else{
 	if (p[v] != -1){
      augment(p[v], min(minEdge, res[p[v]][v]));
      res[p[v]][v] -= f;
      res[v][p[v]] += f;
 	}
 }
}

void maxFlow(){
	mf = 0;
	while(1){
	 f = 0;
     bfs();
     augment(t, INF);
     if (!f) break;
     mf += f;
	}
}

void solve(){
	maxFlow();
}

void output(){
	printf("Network %d\n", cases++);
	printf("The bandwidth is %d.\n\n", mf);
}

int main(){
    cases = 1;
    while(scanf("%d", &qt_vertex) && qt_vertex){
     init();
     read();
     solve();
     output();
    }
	return 0;
}