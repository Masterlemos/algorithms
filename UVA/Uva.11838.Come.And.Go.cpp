#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define UNVISITED -1
#define MAX 10010

vector<int> graph[MAX], scc;
int qt_vertex, dfs_num[MAX], dfs_low[MAX], numSCC, dfsCount, qt_edges;
bool visited[MAX];

void clear(){
	for (int i = 0; i <= qt_vertex; i++){
		graph[i].clear();
		dfs_num[i] = UNVISITED;
		visited[i] = 0;
	}
	dfsCount = 0;
	numSCC = 0;
    scc.clear();
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
       if (vcc == vertex) break;
      }
    }
}

int main(){
	while(scanf("%d %d", &qt_vertex, &qt_edges) && qt_vertex){
		int u, v, way;
		clear();
        for (int i = 0; i < qt_edges; i++){
        	scanf("%d %d %d", &u, &v, &way);
        	graph[u].push_back(v);
        	if (way>1) graph[v].push_back(u);
        }
        for (int i = 1; i <= qt_vertex; i++)
         if (dfs_num[i] == UNVISITED)
          tarjanSCC(i);
        if (numSCC>1)
        	printf("0\n");
        else
        	printf("1\n");
	}
    
	return 0;
}