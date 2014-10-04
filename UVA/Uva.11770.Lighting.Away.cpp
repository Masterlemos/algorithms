#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;


#define MAX 10010
#define UNVISITED -1
#define START 0
#define DOWN 1
#define DAD 2

vector<int> graph[MAX], scc, scc_roots;
int qt_vertex, qt_edges, st[MAX], tiles;
int dfs_num[MAX], dfs_low[MAX], numSCC, dfsCount, root[MAX], comp[MAX];
bool visited[MAX];


void clear(){
	for (int i = 0; i <= qt_vertex; i++){
		graph[i].clear();
		st[i] = UNVISITED;
		dfs_num[i] = UNVISITED;
		visited[i] = 0;
		root[i] = i;
		comp[i] = i;
	}
	numSCC=0;
	dfsCount=0;
	scc.clear();
	scc_roots.clear();
	
}

void dfs(int vertex, int tipo){
 if (tipo == START) st[vertex] = DAD;
 else st[vertex] = tipo;
 for (int i = 0; i < graph[vertex].size(); i++){
   int new_vertex = graph[vertex][i];
   if (comp[new_vertex] != comp[vertex]) new_vertex = root[new_vertex];
  if (st[new_vertex] == UNVISITED){
   tiles--;
   dfs(new_vertex, DOWN);
  }else{
   if (st[new_vertex] == START) {
    tiles--; st[new_vertex] = DOWN;
   }
  }
 }
 if (tipo == START) st[vertex] = START;
}

void tarjanSCC(int vertex){
	dfs_num[vertex] = dfs_low[vertex] = dfsCount++;
	scc.push_back(vertex);
	visited[vertex] = 1;
    for (int i = 0; i < graph[vertex].size(); i++){
    	int new_vertex = graph[vertex][i];
    	if (dfs_num[new_vertex] == UNVISITED)
    		tarjanSCC(new_vertex);
    	if (visited[new_vertex])
    		dfs_low[vertex] = min(dfs_low[vertex], dfs_low[new_vertex]);
    }

    //get SCC
    if (dfs_low[vertex] == dfs_num[vertex]){
      numSCC++;
      while(1){
       int vcc = scc.back(); scc.pop_back();
       visited[vcc] = 0;
       root[vcc] = vertex;
       comp[vcc] = numSCC;
       if (vcc == vertex){ scc_roots.push_back(vcc); break;}
      }
    }
}

int main(){
        int cases, u, v;
        scanf("%d", &cases);
	for (int i=1; i<=cases; i++){
	 scanf("%d %d", &qt_vertex, &qt_edges);
	 clear();
	 tiles = qt_vertex;
         for (int i =0; i<qt_edges; i++){
          scanf("%d %d", &u, &v);
          graph[u].push_back(v);
         }

         for (int i = 1; i <= qt_vertex; i++)
          if (dfs_num[i] == UNVISITED) tarjanSCC(i);
         
         for (int i = 0; i < scc_roots.size(); i++)
          if (st[scc_roots[i]] == UNVISITED) dfs(scc_roots[i], START);
         
         printf("Case %d: %d\n", i, tiles);
    }    
	return 0;
}
