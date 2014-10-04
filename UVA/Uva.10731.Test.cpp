#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define MAX 30
#define UNVISITED -1

typedef pair<int, int> par;
typedef vector<int> vi;


vector<int> graph[MAX], scc, sub[MAX];
map<char, int> char_to_int;
map<int, char> int_to_char;
int dfs_num[MAX], dfs_low[MAX];
int dfsCount, numSCC;
bool visited[MAX];

void clear(){
 for (int i = 0; i < MAX; i++){
 	graph[i].clear();
 	sub[i].clear();
        dfs_num[i] = UNVISITED;
 }
 scc.clear();
 char_to_int.clear();
 int_to_char.clear();
 dfsCount = numSCC = 0;
}

void tarjanSCC(int vertex){
 dfs_num[vertex] = dfs_low[vertex] = dfsCount++;
 visited[vertex] = 1;
 scc.push_back(vertex);

 for (int i =0; i<graph[vertex].size(); i++){
 	int new_vertex = graph[vertex][i];
 	if (dfs_num[new_vertex] == UNVISITED) tarjanSCC(new_vertex);
 	if (visited[new_vertex]) dfs_low[vertex] = min(dfs_low[new_vertex], dfs_low[vertex]);
 }

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

int main(){
	int questions, last=0,p=1;
	int ans[5];
	char c, u;
	while( cin >> questions && questions){
	  last = 0;
          int count = 1; clear();
          if (p!=1) cout<<endl; p=0;
	  for (int q = 0; q < questions; q++){
	   for (int i = 0; i < 5; i++){
	    cin >> c;
	    if (char_to_int[c] == NULL){
	     char_to_int[c] = count;
             int_to_char[count++] = c;
	    }
            ans[i] = char_to_int[c];
            last = max(last, ans[i]);
	   }
	   cin>>u;
	   if (char_to_int[u] == NULL){
             char_to_int[u] = count;
             int_to_char[count++] = u;
           }
           last = max(last, char_to_int[u]);
	   for (int i = 0; i < 5; i++){
	    if (ans[i] != char_to_int[u])
	     graph[char_to_int[u]].push_back(ans[i]);
	   }
         }
         for (int i = 1; i <= last; i++)
            if (dfs_num[i] == UNVISITED) tarjanSCC(i);
            
         vector<par> sets;
         for (int i = 0; i < numSCC; i++){
          vector<int> res;
          for (int j = 0; j < sub[i].size(); j++)
           res.push_back(int_to_char[sub[i][j]]);
          sort(res.begin(), res.end());
          sub[i] = res;
          sets.push_back(par(sub[i][0], i));
         }
         sort(sets.begin(), sets.end());
         for (int i = 0; i < sets.size(); i++){
           int comp = sets[i].second;
           for (int j = 0; j < sub[comp].size(); j++){
            char n_c = sub[comp][j];
            if (j!=0) cout<<" "<<n_c;
            else cout<<n_c;
           }
     	   if (sub[comp].size()>0)
            cout<<endl;
         }
        
	}
	return 0;
}
