#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <map>

using namespace std;


#define MAX 1010
#define UNVISITED -1

vector<int> graph[MAX], scc;
bool visited[MAX], has_edge[MAX][MAX];
int qt_vertex, qt_edges, dfsCount, numSCC;
int dfs_num[MAX], dfs_low[MAX];
map<string, int> str_to_int;

void clear(){
	for (int i = 0; i <= qt_vertex; i++){
		graph[i].clear();
		dfs_num[i] = UNVISITED;
		visited[i] =0;
	}
	numSCC = dfsCount = 0;
	str_to_int.clear();
	scc.clear();
	memset(has_edge, 0, sizeof has_edge);
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
    char cname[200];
    while(scanf("%d %d", &qt_vertex, &qt_edges) && qt_vertex){
     getchar();
     clear();
     int count = 1;
     for (int i = 0; i < qt_vertex; i++){
              gets(cname);
              string name(cname);
              if (str_to_int[name] == NULL) {str_to_int[name] = count++;}
     }
     string u, v; int iu, iv;
     for (int i = 0; i < qt_edges; i++){
      gets(cname);
      string u(cname);
      gets(cname);
      string v(cname);

      iu = str_to_int[u];
      iv = str_to_int[v];
      if (!has_edge[iu][iv])
       graph[iu].push_back(iv);
     }
     for (int i = 1; i <= qt_vertex; i++) if (dfs_num[i] == UNVISITED) tarjanSCC(i);
     printf("%d\n", numSCC);
    }
    return 0;
}
