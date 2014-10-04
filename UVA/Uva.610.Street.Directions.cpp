#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX 1100
#define WHITE -1

typedef pair<int,int> par;

int qt_vertex, qt_edges, dfs_num[MAX], dfs_low[MAX], dfs_parent[MAX], dfsCount;
int st_edges[MAX][MAX];
vector<int> graph[MAX];
vector<par> edges;

void clear(){
 for (int i = 0; i<=qt_vertex; i++){
  graph[i].clear();
  dfs_num[i] = WHITE;
 }
 edges.clear();
 dfsCount = 0;
 memset(st_edges, 0, sizeof st_edges);
}

void artic(int atual){
 dfs_num[atual] = dfs_low[atual] = dfsCount++;
 for (int i = 0; i < graph[atual].size(); i++){
  int novo = graph[atual][i];
  if (dfs_num[novo] == WHITE){
   dfs_parent[novo] = atual;
   st_edges[atual][novo]=-2;
   artic(novo);
   if (dfs_low[novo] > dfs_num[atual]){
    if (st_edges[atual][novo]){
     st_edges[atual][novo]=2;
    }else if (st_edges[novo][atual]) st_edges[novo][atual]=2;
   }
   edges.push_back(par(atual, novo));
   dfs_low[atual] = min(dfs_low[atual], dfs_low[novo]);
  }else{
   if (!st_edges[atual][novo] && !st_edges[novo][atual]){
    st_edges[atual][novo]=-2;
    edges.push_back(par(atual,novo));
   }
   if (dfs_parent[atual] != novo)
    dfs_low[atual] = min(dfs_low[atual], dfs_num[novo]);
  }
 }
}

int main(){
 int u, v, cases=1;
 while(scanf("%d %d", &qt_vertex, &qt_edges) && qt_vertex){
  clear();
  for (int i = 0; i < qt_edges; i++){
   scanf("%d %d", &u, &v);
   graph[u].push_back(v);
   graph[v].push_back(u);
  }
  artic(1);
  
  printf("%d\n\n", cases++);
  for (int i=0; i<edges.size(); i++){
   int a,b;  a = edges[i].first; b = edges[i].second; 
   printf("%d %d\n", a, b);
   if (st_edges[a][b]>1)
    printf("%d %d\n", b, a);
   else if (st_edges[b][a]>1) printf("%d %d\n", b, a);
  }
  printf("#\n");
 }
 return 0;
}
