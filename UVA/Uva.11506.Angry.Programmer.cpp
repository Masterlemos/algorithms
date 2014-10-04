#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>


using namespace std;

#define INF 1e9
#define MAX_V 300
#define tipo long long

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int cases, s, t, f, qt_vertex, qt_edges;

tipo mf;

int res[MAX_V][MAX_V], p[MAX_V];

vi graph[MAX_V];

bitset<MAX_V> visited;


void init(){
	memset(res, 0, sizeof res);
	for (int i = 0; i < MAX_V; i++) graph[i].clear();
	s = 1;
        t = qt_vertex;
}

int mapIn(int v){
 return v+50;
}

void createEdge(int u, int v){
 if (u && v) graph[u].push_back(v), graph[v].push_back(u);
}

void residual(int u, int v, int w){
	if (u && v) res[u][v] = w; 
}

void read(){
     int u, v, w;

     for (int i = 2; i < qt_vertex; i++){
      scanf("%d %d", &v, &w);
      int inV = mapIn(v);
      createEdge(inV, v); res[inV][v] = w;
     }

     int vout, vin, uin, uout;
     for (int i = 0; i < qt_edges; i++){
     	scanf("%d %d %d", &uout, &vout, &w);

        uin = mapIn(uout);
        vin = mapIn(vout);

        if (uout == s || uout == t) uin = uout; if (vout == s || vout == t) vin = vout;

        createEdge(uout, vin); residual(uout, vin, w); 

        if (!uin && !vin) residual(uout, vout, w), residual(vout, uout, w);
        else createEdge(vout, uin), residual(vout, uin, w); 
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

bool dfs(int v){
  visited[v] = 1;
  if (v == t) return 1;
  for (int i = 0; i < graph[v].size(); i++){
   int new_vertex = graph[v][i];
   if (res[v][new_vertex] && !visited[new_vertex]){
    p[new_vertex] = v;
    if (dfs(new_vertex)) return 1;
   }
  }
  return 0;
}

void dfsRotine(int v){
   visited.reset();
   memset(p, -1, sizeof p);
   dfs(v); 
}


void augment(int v, int minEdge){
       if(v == s){ f = minEdge; return;}
       else{
 	     if (p[v] != -1){
          augment(p[v], min(res[p[v]][v], minEdge) );
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
     //dfsRotine(s);
     augment(t, INF);
     if (!f) break;
     mf += f;
    }
}

//mincut
void color(int origin){
    visited.reset(); visited[origin] = 1;
	queue<int> q; q.push(origin);
	int u, v;
	while(!q.empty()){
  	     int u = q.front(); q.pop();
         for (int i = 0; i < graph[u].size(); i++){
            v = graph[u][i];
            if (res[u][v] && !visited[v])
             q.push(v), visited[v] = 1;
         } 
	}
}


void minCut(){
 color(s);
}

void solve(){
	maxFlow();
}

void output(){
   printf("%lld\n", mf);
}

int main(){
    cases = 1;
    while(scanf("%d %d", &qt_vertex, &qt_edges) && qt_vertex){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
