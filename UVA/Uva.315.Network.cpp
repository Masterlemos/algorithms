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
 
typedef vector<int> vi;
typedef vector<vi> vtrio;
typedef pair<int, int> par;
  
struct TYPE {
    int a, b, c;
  
    TYPE() { a = b = c = 0; }
    TYPE(int a, int b, int c) { this->a = a, this->b = b, this->c = c; }
    TYPE operator +(TYPE x) { return TYPE(a+x.a,b+x.b,c+x.c); }
};
 
int num(char c){
    return ((c - '0') % 48);
}

char linha[200];
vector<int> graph[200];
bool art_vertex[200];
int dfs_num[200], dfs_low[200], n, dfsCount, dfsRoot, dfs_parent[200], rootChildren, art;

//articulations
void artic(int u){
 dfs_num[u] = dfs_low[u] = dfsCount++;
 int s = graph[u].size(),v;

 for (int i =0; i<s; i++){
    v = graph[u][i];
    if (dfs_num[v] == WHITE){
    	dfs_parent[v] = u;
    	if (u == dfsRoot) rootChildren++;
    	artic(v);
        if (dfs_low[v] >= dfs_num[u])
          art_vertex[u] = 1;
    	dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }else
     if (dfs_parent[u] != v)
        dfs_low[u] = min(dfs_low[u], dfs_num[v]);
 }
}

void clear(){
	for (int i = 1; i <= n; i++){
		graph[i].clear();
		dfs_num[i] = WHITE;
		dfs_low[i] = i;
		art = 0;
		art_vertex[i] = 0;
		dfsCount = 0;
		rootChildren = 0;
	}
}

int main(){
     int u,vertex;
     while(scanf("%d", &n) && n){
       clear();
       getchar();
       while(gets(linha) && linha[0]!='0'){
         char *f = strtok(linha," ");
         u = atoi(f);
         f = strtok(NULL," ");
         while(f!=NULL){
 	       vertex = atoi(f);
 	       graph[u].push_back(vertex);
 	       graph[vertex].push_back(u);
 	       f = strtok(NULL, " ");
         }
       }
        dfsRoot=1;
 	artic(dfsRoot);	  
 	art_vertex[1] = (rootChildren > 1);
        art=0; 
        for (int i =1; i<=n; i++)
           if (art_vertex[i])
             art++; 
        printf("%d\n",art);
   }
   return 0;
}
