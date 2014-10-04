#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>


using namespace std;

#define INF 1e9
#define MAX_V 215
#define tipo long long

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int cases, s, t, f, qt_horses, qt_soldiers, qt_edges, mf;

int res[MAX_V][MAX_V], p[MAX_V];

bool has[MAX_V][MAX_V];

vi graph[MAX_V];

bitset<MAX_V> visited;


void init(){
	memset(res, 0, sizeof res);
	memset(has, 0, sizeof has);
	for (int i = 0; i <= t; i++) graph[i].clear();
	s = 0;
        t = 210;
}

void read(){
     int u, v, w;
    
     for (int i = 0; i < qt_horses; i++){
     	scanf("%d", &w);
     	res[s][i+1] = w;
     }
     for (int i = 0; i < qt_edges; i++){
      scanf("%d %d", &u, &v);
      if (!has[u][v]){
       graph[u].push_back(v+100);
       graph[v+100].push_back(u);
       res[u][v+100] = 1;
       has[u][v+100] = 1;
      }
      if (!has[s][u]) {
       graph[s].push_back(u);
       graph[u].push_back(s);
       has[s][u] = 1;
      }
      
      if (!has[v+100][t]){
       graph[v+100].push_back(t);
       graph[t].push_back(v+100);
       has[v+100][t] = 1;
       res[v+100][t] = 1;
      }
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

void augment(int v, int minEdge){
       if(v == s){ f = minEdge; return;}
       else{
 	if (p[v] != -1){
 	  int parcialMin = minEdge;
 	  if (res[p[v]][v] < minEdge) parcialMin =  res[p[v]][v];
 	  
          augment(p[v], parcialMin);
          res[p[v]][v] -= f;
          res[v][p[v]] += f;
 	}
      }
}

void maxFlow(){
	mf = 0;
	while(1){
	 f = 0;
//         bfs();
         visited.reset();
         memset(p, -1, sizeof p);
         dfs(s); 
         augment(t, INF);
         if (!f) break;
         mf += f;
        }
}

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
   printf("Instancia %d\n", cases++);
   printf("%d\n\n", mf);
}

int main(){
    cases = 1;
    while(scanf("%d %d %d", &qt_horses, &qt_soldiers, &qt_edges) != EOF){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
