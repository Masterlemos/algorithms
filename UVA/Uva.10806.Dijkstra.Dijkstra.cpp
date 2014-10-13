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
#define MAX_V 110
#define tipo long long
#define forr(i, b) for (int i = 0; i < b; ++i)
#define ford(i, a, b) for (int i = a; i <= b; ++i)
#define pb(i) push_back(i)
 
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> msi;
 
int cases, s, t, qt_vertex, qt_edges;
 
vii graph[MAX_V];

int p[MAX_V];
int mf, f;

//particular
int dist[MAX_V];
int time_cost;
bool used[MAX_V][MAX_V], ans;

void distance(){
  forr(i, MAX_V) dist[i] = INF;
  dist[s] = 0;
  priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
  memset(p, -1, sizeof p);                         
  while (!pq.empty()) {      
    ii front = pq.top(); pq.pop();
    int d = front.first, u = front.second;
    if (u==t) break;
    if (d > dist[u]) continue;  
    for (int j = 0; j < (int) graph[u].size(); j++) {
      ii v = graph[u][j];     
      if (used[u][v.second]) continue;
      if ( (dist[u] + v.first) < dist[v.second]) {
        dist[v.second] = dist[u] + v.first;
        p[v.second] = u;
        pq.push(ii(dist[v.second], v.second));
  } } }  
}

void adjust(int v){
     for (int u = t; u != s; u = p[u]) {
       used[p[u]][u] = true;
       for (int k = 0; k < (int)graph[u].size(); ++k) {
         int v = graph[u][k].second;
         if (v != p[u]) continue;
         graph[u][k].first *= -1;
       }
     }
}

void init(){
	s = 1;
	t = qt_vertex;
	time_cost  = 0;
        memset(used, 0, sizeof used);
	ford(i, 1, t) graph[i].clear();
        ans = 0;
}

void read(){
  int u, v, w;
  scanf("%d", &qt_edges);
  forr(i, qt_edges){
  	scanf("%d %d %d", &u, &v, &w);
  	graph[u].pb(ii(w, v));
  	graph[v].pb(ii(w, u));
  }
}

void solve(){
  distance();
  if (dist[t] == INF) ans = 0;
  else{
   ans = 1;
   time_cost += dist[t];
   
   adjust(t);

   distance();
   if (dist[t] == INF) ans = 0;
   else ans = 1, time_cost += dist[t];
  }
}

void output(){
		if (ans) printf("%d\n", time_cost);
                else printf("Back to jail\n");
}

int main(){
	while(scanf("%d", &qt_vertex) && qt_vertex){
		init();
		read();
		solve();
		output();
	}
	return 0;
}
