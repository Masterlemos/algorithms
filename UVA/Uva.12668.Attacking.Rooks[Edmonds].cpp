#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;

#define MAX 101
#define MAX_V 10010

typedef vector<int> vi;
typedef pair<int, int> ii;

int p[MAX_V];

int s, t, f, mf, n, nc, nr;

ii ids[MAX][MAX];
int res[MAX_V][MAX_V];
vi graph[MAX_V];
bitset<MAX_V> s_edge;
bitset<MAX_V> t_edge;
bitset<MAX_V> visited;
char grid[MAX][MAX];

void init(){
 s=0;
 t = 10009;
 nr = 1;
 nc = 5001;
 for (int i = 0; i <= t; i++) graph[i].clear();
 s_edge.reset();
 t_edge.reset();
}

void read(){
   for (int i=0; i<n; i++) scanf("%s", grid[i]);
}

void count_row(){
 for (int r=0; r<n; r++){
  bool dot = 0;
  for (int c=0; c<n; c++)
   if (grid[r][c] == '.' && !dot){
    ids[r][c] = ii(nr++, 0);
    dot = 1;
   }else if (grid[r][c] == 'X'){ dot=0;} else ids[r][c] = ii(ids[r][c-1].first, 0);
 }
}

void count_col(){
 for (int c=0; c<n; c++){
  bool dot = 0;

  for (int r=0; r<n; r++)
   if (grid[r][c] == '.' && !dot){
    ids[r][c].second = nc++;
    dot = 1;
   }else if (grid[r][c] == 'X') {dot=0;} else ids[r][c].second = ids[r-1][c].second;
 }
}

void count(){
 count_row();
 count_col();
}

void createGraph(){
   for (int r = 0; r<n; r++)
    for (int c =0; c<n; c++){
     if (grid[r][c] == 'X') continue;
     int u = ids[r][c].first;
     int v = ids[r][c].second;
     graph[u].push_back(v);
     graph[v].push_back(u);
     res[u][v] = 1;
     res[v][u] = 0;
     
     if (!s_edge[u]){
      graph[s].push_back(u);
      graph[u].push_back(s);
      res[s][u] = 1;
      res[u][s] = 0;
      s_edge[u]=1;
     }
     if (!t_edge[v]){
      graph[v].push_back(t);
      graph[t].push_back(v);
      res[v][t] = 1;
      res[t][v] = 0;
      t_edge[v] = 1;
     }
    }
    
}

void augment(int v, int minEdge){
 if (v==s){f = minEdge; return;}
 else if (p[v] != -1){
   augment(p[v], min(minEdge, res[p[v]][v]));
   res[v][p[v]] += f;
   res[p[v]][v] -= f;
 }
}

void bfs(){
 visited.reset(); visited[s]=1;
 queue <int> q; q.push(s);
 while(!q.empty()){
  int u = q.front();
  q.pop();
  if (u==t) break;
  for (int i=0; i<graph[u].size(); i++){
   int v = graph[u][i];
   if (res[u][v] > 0 && !visited[v]){
    visited[u] = 1;
    q.push(v); 
    p[v] = u;
   }
  }
 }
}

void maxFlow(){
 mf = 0;
 while(1){
  f = 0;
  memset(p, -1, sizeof p);
  bfs();
  augment(t, 1e9);
  if (!f) break;
  mf += f;
 }
}

void solve(){
 count();
 createGraph();

 maxFlow();
}

int main(){
 while(scanf("%d", &n) != EOF){
  init();
  read();
  solve();
  printf("%d\n", mf);
 }
 return 0;
}
