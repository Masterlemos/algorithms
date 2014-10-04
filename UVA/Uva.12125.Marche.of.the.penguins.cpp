#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>


using namespace std;

#define INF 1e9
#define MAX_V 215
#define tipo long long

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

struct block{
 int qt_penguins, qt_jumps;
 ii cords;
};

int s, t, f, qt_vertex, qt_edges, mf, total;

block penguins[MAX_V];

int res[MAX_V][MAX_V], p[MAX_V];

int flag_res[MAX_V][MAX_V];

vi graph[MAX_V], ans;

bool visited[MAX_V];

double radius;

int getRes(int u, int v){
 return res[u][v] - flag_res[u][v];
}

void bfs(){
	memset(visited, 0, sizeof visited); visited[s] = 1;
	queue<int> q; q.push(s);
	memset(p, -1, sizeof p);
        while(!q.empty()){
         int u = q.front(); q.pop();
         //printf("|%d|\n", u);
         if (u==t) break;
         for (int i = 0; i < graph[u].size(); i++){
     	  int v = graph[u][i];
     	  int cap = getRes(u,v);
     	  if (!visited[v] && cap){
     		p[v] = u;
     		visited[u] = 1;
     		q.push(v);
     	  }  
         }
        }
} 

void augment(int v, int minEdge){
       if(v == s){ f = minEdge; return;}
       else{
 	     if (p[v] != -1){	  
          augment(p[v], min(getRes(p[v], v), minEdge) );
          flag_res[p[v]][v] += f;
          flag_res[v][p[v]] -= f;
 	     }
       }
}

void maxFlow(){
	mf = 0;
	memset(flag_res, 0, sizeof flag_res);
	while(1){
	 f = 0;
     bfs();
     augment(t, INF);
     if (!f) break;
     mf += f;
    }
}

bool canJump(ii a, ii b){
 return double(pow(a.first-b.first, 2) + pow(a.second - b.second, 2)) <= pow(radius, 2);
}

void createEdge(int u, int v){
 graph[u].push_back(v);
 graph[v].push_back(u);
}

int mapOut(int v){
 return v+100;
}

void split(int vin, int w){
 createEdge(vin, mapOut(vin));
 res[vin][mapOut(vin)] = w;
}

void connect(int u, int v, int w){
 createEdge(u, v);
 res[u][v] = w;
}

void createGraph(){
 for (int i = 1; i <= qt_vertex; i++){  
  split(i, penguins[i].qt_jumps);

  int qpb = penguins[i].qt_penguins;
  if (qpb) connect(s, i, qpb);

  ii a = penguins[i].cords;
  
  for (int j = i+1; j <= qt_vertex; j++){
   ii b = penguins[j].cords;
   if (canJump(a, b)) connect(mapOut(i), j, INF), connect(mapOut(j), i, INF);
  }

 }
}

void solve(){
        createGraph();        
        
        for (int i = 1; i <= qt_vertex; i++) {
          t = i;
          maxFlow();
          if (mf == total) ans.push_back(i-1);  
        }
}

void output(){
   if (ans.size()){
    for (int i=0; i < ans.size(); i++)
     if (i) printf(" %d", ans[i]); else printf("%d", ans[i]);
    printf("\n");
   }
   else printf("-1\n");  
}

void init(){
	memset(res, 0, sizeof res);
	for (int i = 0; i < MAX_V; i++) graph[i].clear();
	s = total = 0;
	ans.clear();
}


void read(){
     int x, y;
     scanf("%d %lf", &qt_vertex, &radius);
     for (int i = 1; i <= qt_vertex; i++){
      scanf("%d %d %d %d", &x, &y, &penguins[i].qt_penguins, &penguins[i].qt_jumps);
      penguins[i].cords = ii(x,y);
      total += penguins[i].qt_penguins;
     }
}

int main(){
	int cases;
    scanf("%d", &cases);
    while(cases--){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
