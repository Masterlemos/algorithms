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
#define MAX_V 100
#define tipo long long
#define forr(i, b) for (int i = 0; i < b; ++i)
#define ford(i, a, b) for (int i = a; i <= b; ++i)
#define pb(i) push_back(i)

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> msi;

int cases, s, t;
int res[MAX_V][MAX_V];
vi graph[MAX_V];

//particular
msi shirts;
int qt_shirts, qt_volunteers;

//edmonds
bool visited[MAX_V], p[MAX_V];
int mf, f;

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
   for (int i = 0; i < graph[u].size(); i++){
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


void solve(){
	mf = maxFlow();
}

void output(){
  if (mf == qt_volunteers) cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
}

void split(int vin, int w){
 connect(vin, vin+100, w);
}

void init(){
 memset(res, 0, sizeof res);
 forr (i, MAX_V) graph[i].clear();
 s = 0;
 t = 1;
}

void read(){
 string a, b;
 cin >> qt_shirts >> qt_volunteers;
 qt_shirts /= 6;
 
 connect(shirts["XXL"], t, qt_shirts);
 connect(shirts["XL"], t, qt_shirts);
 connect(shirts["L"], t, qt_shirts);
 connect(shirts["M"], t, qt_shirts);
 connect(shirts["S"], t, qt_shirts);
 connect(shirts["XS"], t, qt_shirts);
 
 forr(i, qt_volunteers){
  cin >> a >> b;
  connect(s, i+8, 1);
  connect(i+8, shirts[a], 1);
  connect(i+8, shirts[b], 1);
 }
}

int main(){
    shirts["XXL"] = 2; shirts["XL"] = 3;  shirts["L"] = 4; shirts["M"] = 5; shirts["S"] = 6; shirts["XS"] = 7;
    cin >> cases;
    while (cases--){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
