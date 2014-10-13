#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

using namespace std;

#define INF 1e9
#define MAX_V 5010
#define tipo long long
#define forr(i, b) for (int i = 0; i < b; ++i)
#define ford(i, a, b) for (int i = a; i <= b; ++i)
#define pb(i) push_back(i)

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, string> mis;
typedef map<string, int> msi;

int cases, s, t, qt_vertex, mf;
int res[MAX_V][MAX_V];
vi graph[MAX_V];

//particular
int qt_columns, qt_rows, tt;
int dh[] = {0, 1, 0, -1};
int dv[] = {1, 0, -1, 0};

//dinic
int work[MAX_V], dist[MAX_V];

void connect(int u, int v, int w){
 graph[u].pb(v);
 graph[v].pb(u);
 res[u][v] = w;
}


/*
 Dinic -> O(V^2E)
*/

int dinic_dfs(int u, int flow){
 if (u==t) return flow;
 for (int &i = work[u]; i < (int) graph[u].size(); i++){
  int v = graph[u][i];
  if (res[u][v] <= 0) continue;
  if (dist[v] == dist[u] + 1){
   int df = dinic_dfs(v, min(flow, res[u][v]) );
   if (df > 0){
    res[u][v] -= df; res[v][u] += df;
    return df;
   } 
  }
 }
 return 0;
}

bool dinic_bfs(){
  memset(dist, -1, sizeof dist);
  dist[s] = 0;
  queue<int> q; q.push(s);
  while(!q.empty()){
   int u = q.front(); q.pop();
   for (int i = 0; i < (int)graph[u].size(); i++){
    int v = graph[u][i];
    if (dist[v] < 0 && res[u][v]) dist[v] = dist[u] + 1, q.push(v);
   }
  }
  return dist[t] >= 0;  
}

int maxFlow(){
  int result = 0;
  while(dinic_bfs()){
   memset(work, 0, sizeof work);
   while (int delta = dinic_dfs(s, INF)) result += delta;
  }
  return result;
}
/*
 FIM
*/

//PARTICULAR

int mapIn(int x, int y){
 return (y*qt_columns + x + 2);
}

int mapOut(int vin){
 return vin+2500;
}

int split(int vin, int w){
 connect(vin, mapOut(vin), w);
}

bool inside(int x, int y){
 if (x >=0 && y >=0 && x < qt_columns && y < qt_rows) return true;
 return false;
}


void integrate(int x, int y){
	int xx, yy, vout;
	vout = mapOut(mapIn(x, y));
	forr (i, 4){
	   xx = x + dh[i]; yy = y + dv[i];
       if ( inside(xx, yy) )
       	connect(vout, mapIn(xx, yy), 1);
	}
    
	if (x == 0 || y == 0 || (x == (qt_columns-1)) || (y == (qt_rows-1)) ) connect(vout, t, 1);
	if ( (x==0 && y==0) || (x == (qt_columns-1) && y ==0) || (x==0 && y==(qt_rows-1)) || (x == (qt_columns-1) && y == (qt_rows-1)) ) res[vout][t]++;
}

//FIM PARTICULAR


//STANDARD
void init(){
 memset(res, 0, sizeof res);
 forr (i, MAX_V) graph[i].clear();
 s = 0;
 t = 1; 
 tt=1;
}

void read(){
	int vin, x, y;
    scanf("%d %d %d", &qt_columns, &qt_rows, &qt_vertex);
    forr(i, qt_vertex){
    	scanf("%d %d", &x, &y);
    	connect(s, mapIn(x-1, y-1), 1);
    }
    
    forr(yy, qt_rows){
    	forr(xx, qt_columns){
            vin = mapIn(xx, yy);
    		split(vin, 1);
            integrate(xx, yy);
    	}
    }
}

void solve(){
	mf = maxFlow();
}

void output(){
   if (mf == qt_vertex) printf("possible\n");
   else printf("not possible\n");
}

//FIM STANDARD

int main(){
    scanf("%d", &cases);
    while (cases--){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
