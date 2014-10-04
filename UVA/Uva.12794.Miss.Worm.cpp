#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <queue>

using namespace std;

#define INF 1e9
#define MAX 10010
#define UNVISITED -1

typedef pair<int, int> ii;
typedef vector<int> vi;

vector<int> graph[MAX];
int qt_vertex, qt_edges;
int edge[MAX][MAX], cicle[MAX], dist[MAX], comp[MAX];
bool visited[MAX];


void clear(){
	for (int i = 0; i <= qt_vertex; i++){
		graph[i].clear();
		cicle[i]=0;
		comp[i] = 0;
        }
}

void distance(int s){
       // Dijkstra routine
     int V = qt_vertex+1;  
     for (int i=1; i<=qt_vertex; i++) dist[i]=INF;
     dist[s] = 0;                    // INF = 1B to avoid overflow
     priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
                             // ^to sort the pairs by increasing distance from s
     while (!pq.empty()) {                                             // main loop
      ii front = pq.top(); pq.pop();     // greedy: pick shortest unvisited vertex
      int d = front.first, u = front.second;
      if (d > dist[u]) continue;   // this check is important, see the explanation
      for (int j = 0; j < (int)graph[u].size(); j++) {
       int v = graph[u][j];
       if (dist[u] + edge[u][v] < dist[v]) {
         dist[v] = dist[u] + edge[u][v];                 // relax operation
         pq.push(ii(dist[v], v));
     } } }  // note: this variant can cause duplicate items in the priority queue
}

int dfs(int c, int a, int b, int d){
 visited[a] = 1;
 for (int i = 0; i < graph[a].size(); i++){
  int new_vertex = graph[a][i];
  if (new_vertex == b && b!=d) {comp[a] = comp[b] = c; return edge[a][b];}
  if (new_vertex == b && b==d) d=0;
  if (!visited[new_vertex]){
   int path = dfs(c,new_vertex, b, a);
   if (path){comp[a]=c; return edge[a][new_vertex] + path;}
  }
 }
 return 0;
}


int main(){
    int u,v,w,q;
    while(scanf("%d %d", &qt_vertex, &qt_edges) != EOF){
     clear();
     vector< pair<int, ii> > EdgeList;  
     for (int i = 0; i < qt_edges; i++){
      scanf("%d %d %d", &u, &v, &w);
      EdgeList.push_back(make_pair(w, ii(u, v)));
      graph[u].push_back(v);
      graph[v].push_back(u);
      edge[u][v] = w;
      edge[v][u] = w;
     }
     int c = 1;
     for (int i = 1; i <= qt_vertex; i++){
      memset(visited, 0, sizeof visited);
      if (graph[i].size() > 1 && !comp[i]){
       int path = dfs(c++, i, i, 0);
       if (path) cicle[comp[i]] = path;
      }
     }
     scanf("%d",&q);
     for (int i=0;i<q;i++){
      scanf("%d %d", &v, &w);
      distance(v);
      int ans = INF;
      for (int j=1; j<=qt_vertex; j++){
       if (cicle[comp[j]] >= w)
        ans = min(ans, cicle[comp[j]] + 2*dist[j]);
      }
      if (ans == INF) printf("-1\n");
      else printf("%d\n",ans);
     }
    }
    return 0;
}
