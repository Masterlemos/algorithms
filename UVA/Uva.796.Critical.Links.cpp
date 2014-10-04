#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
 
using namespace std;
 
#define fori(i, n) for (int i=0; i<n; ++i)
#define forr(i, a, n) for (int i=a; i<=n; ++i)
 
#define tipo long long

#define WHITE -1

#define MAX 500

typedef pair<int, int> par;
  
int num(char c){
    return ((c - '0') % 48);
}

char linha[MAX];
vector<int> graph[MAX];
vector<par> art_edge;
int dfs_num[MAX], dfs_low[MAX], n, dfsCount, dfsRoot, dfs_parent[MAX], rootChildren;

//articulations
void artic(int u){
 dfs_num[u] = dfs_low[u] = dfsCount++;
 int s = graph[u].size(),v;

 for (int i =0; i<s; i++){
    v = graph[u][i];
    if (dfs_num[v] == WHITE){
    	dfs_parent[v] = u;
    	artic(v);
        if (dfs_low[v] > dfs_num[u])
         art_edge.push_back(par(min(u,v), max(u,v)));
    	dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }else
     if (dfs_parent[u] != v)
        dfs_low[u] = min(dfs_low[u], dfs_num[v]);
 }
}

void clear(){
	for (int i = 0; i < n; i++){
		graph[i].clear();
		dfs_num[i] = dfs_low[i] = WHITE;
		dfs_parent[i] = i;
	}
	dfsCount = 0;
	art_edge.clear();
}

int main(){

   while(scanf("%d", &n) != EOF) {
		clear();
		for(int i = 0; i < n; i++) {
			int x, y, k;
			scanf("%d (%d) ",&x,&k);
			for(int j = 0; j < k; j++) {
				scanf("%d",&y);
	                        graph[x].push_back(y);
	                        graph[y].push_back(x);
			}
		}
		for(int i = 0; i < n; i++)
		 if (dfs_num[i] == WHITE)
		  artic(i);
		
		sort(art_edge.begin(),art_edge.end());
		printf("%lu critical links\n",art_edge.size());
		for(int i = 0; i < art_edge.size(); i++) printf("%d - %d\n",art_edge[i].first, art_edge[i].second);
		printf("\n");
	}
   return 0;
}
