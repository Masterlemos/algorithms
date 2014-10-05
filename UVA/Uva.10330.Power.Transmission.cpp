#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

#define INF 1e9
#define MAX_V 210
#define tipo long long
#define forr(i, b) for (int i = 0; i < b; ++i)
#define ford(i, a, b) for (int i = a; i <= b; ++i)
#define pb(i) push_back(i)

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int cases, s, t, qt_vertex, qt_edges;

int res[MAX_V][MAX_V];

vi graph[MAX_V];

//edmonds
bool visited[MAX_V], p[MAX_V];
int mf, f;

//dinic
int work[MAX_V], dist[MAX_V];

void connect(int u, int v, int w){
 graph[u].pb(v);
 graph[v].pb(u);
 res[u][v] = w;
}

/*
 Dinic -> O(V^2E)
*/

int dinic_dfs(int u, int flow){
 if (u==t) return flow;
 for (int &i = work[u]; i < (int) graph[u].size(); i++){
  int v = graph[u][i];
  if (res[u][v] <= 0) continue;
  if (dist[v] == dist[u] + 1){
   int df = dinic_dfs(v, min(flow, res[u][v]) );
   if (df > 0){
    res[u][v] -= df; res[v][u] += df;
    return df;
   } 
  }
 }
 return 0;
}

bool dinic_bfs(){
  memset(dist, -1, sizeof dist);
  dist[s] = 0;
  queue<int> q; q.push(s);
  while(!q.empty()){
   int u = q.front(); q.pop();
   for (int i = 0; i < graph[u].size(); i++){
    int v = graph[u][i];
    if (dist[v] < 0 && res[u][v]) dist[v] = dist[u] + 1, q.push(v);
   }
  }
  return dist[t] >= 0;  
}

int maxFlow(){
  int result = 0;
  while(dinic_bfs()){
   memset(work, 0, sizeof work);
   while (int delta = dinic_dfs(s, INF)) result += delta;
  }
  return result;
}
/*
 FIM
*/


void solve(){
	mf = maxFlow();
}

void output(){
   printf("%d\n", mf);
}

void split(int vin, int w){
 connect(vin, vin+100, w);
}

void init(){
 memset(res, 0, sizeof res);
 forr (i, MAX_V) graph[i].clear();
 s = 0;
 t = 205;
}

void read(){
 int w, a, b;
 forr(i, qt_vertex){
  scanf("%d", &w);
  split(i+1, w);
 }
 scanf("%d", &qt_edges);
 forr (i, qt_edges){
  scanf("%d %d %d", &a, &b, &w);
  connect(a+100, b, w);
 }
 scanf("%d %d", &a, &b);
 forr (i, a){ scanf("%d", &w); connect(s, w, INF);}
 forr (i, b){ scanf("%d", &w); connect(w+100, t, INF);}
}

int main(){
    cases = 1;
    while(scanf("%d", &qt_vertex) != EOF){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
