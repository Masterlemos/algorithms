#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>


using namespace std;

#define INF 1e9
#define MAX_V 55
#define tipo long long

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int cases, s, t, f, qt_vertex, qt_edges;

int mf;

int res[MAX_V][MAX_V], p[MAX_V];

vi graph[MAX_V];

bitset<MAX_V> visited;


void init(){
	memset(res, 0, sizeof res);
	for (int i = 1; i <= qt_vertex; i++) graph[i].clear();
	s = 1;
        t = 2;
}

void read(){
     int u, v, w;
    
     for (int i = 0; i < qt_edges; i++){
     	scanf("%d %d %d", &u, &v, &w);
     	graph[u].push_back(v);
     	graph[v].push_back(u);
     	res[u][v] = res[v][u] = w;
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
         bfs();
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
	minCut();
}

void output(){
        
        for (int i = 1; i <= qt_vertex; i++)
          if (visited[i])
           for (int j = 0; j < graph[i].size(); j++){
            int v = graph[i][j];
            if (!visited[v]) printf("%d %d\n", i, v);
           }
        
	printf("\n");
}

int main(){
    
    while(scanf("%d %d", &qt_vertex, &qt_edges) && qt_vertex){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
