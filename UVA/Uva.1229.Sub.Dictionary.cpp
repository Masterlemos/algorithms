#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <queue>

using namespace std;


#define MAX 200
#define UNVISITED -1

vector<int> graph[MAX], scc, sub[MAX];
int qt_vertex;
int dfs_num[MAX], dfs_low[MAX], numSCC, dfsCount;
bool visited[MAX], has_edge[MAX][MAX], inside[MAX];
char line[2500];
map<string, int> str_to_int;
map<int, string> int_to_str;
vector<string> words;

void clear(){
	for (int i = 0; i <= qt_vertex; i++){
		graph[i].clear();
		dfs_num[i] = UNVISITED;
		visited[i] = 0;
		inside[i] = 0;
		sub[i].clear();
	}
	numSCC = dfsCount = 0;
	scc.clear();
	str_to_int.clear();
	int_to_str.clear();
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
      while(1){
       int vcc = scc.back(); scc.pop_back();
       visited[vcc] = 0;
       sub[numSCC].push_back(vcc);
       if (vcc == vertex) break;
      }
      numSCC++;
    }
}

void dfs(int vertex){
 if (!inside[vertex]){
  words.push_back(int_to_str[vertex]);
  inside[vertex] = 1;
  for (int i = 0; i < graph[vertex].size(); i++)
   dfs(graph[vertex][i]);
 }
}

int main(){
     
    while(scanf("%d", &qt_vertex) && qt_vertex){
       if (getchar()==' ') getchar();
       clear();
       int count = 1;
       for (int i = 0; i < qt_vertex; i++){
        gets(line); 
        char *token = strtok(line, " ");
        string u(token);
        if (str_to_int[u] == NULL) {str_to_int[u] = count; int_to_str[count++] = u;}
        token = strtok(NULL, " ");
        while(token != NULL){
         string v(token);
         if (str_to_int[v] == NULL) {str_to_int[v] = count; int_to_str[count++] = v;}
         int iu = str_to_int[u], iv = str_to_int[v];
         if (!has_edge[iu][iv])
            graph[iu].push_back(iv);
         has_edge[iu][iv] = 1;
         token = strtok(NULL, " ");
        }
       }
       for (int i = 1; i<= qt_vertex; i++) if (dfs_num[i] == UNVISITED) tarjanSCC(i); 
       words.clear();
       for (int i =0; i<numSCC; i++) if (sub[i].size() > 1) dfs(sub[i][0]);
       cout << words.size() << endl;
       sort(words.begin(), words.end());
       if(words.size() > 0)
        cout << words[0];
       for(int i = 1; i < words.size(); i++)
        cout << " " << words[i];
       cout << endl;
       }
       return 0;
}
