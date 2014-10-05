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
typedef vector<string> vs;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> msi;

int cases, s, t;
int res[MAX_V][MAX_V];
vi graph[MAX_V];

//particular
msi shirts;
vs words[26];
int pos[26][26], qt_vertex;

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

char low(char c){
 if (c > 90) return c;
 return c+32;
}

void format(string w){
 ford (i, 1, (int) w.size()-1) cout << low(w[i]);
}

void output(){ 
 int v;
 char let;
 string word;
 forr(i, qt_vertex){
  forr(j, (int) graph[i+2].size()){
   v = graph[i+2][j];
   if (res[i+2][v]) continue;
   
   let = i+65;
   word = words[v-28][pos[v-28][i]];
   
   cout<<let;
   format(word);
   cout<<endl;
  }
 }
}

void split(int vin, int w){
 connect(vin, vin+100, w);
}

void init(){
 memset(res, 0, sizeof res);
 forr (i, MAX_V) graph[i].clear();
 forr(i, 26) words[i].clear();
 s = 0;
 t = 1;
}

int mapVertex(int u){
 return u+28;
}

int upper(char c){
 if (c > 90) return c-32;
 return c;
}

void read(){
 string a, b;
 int qt_words, v;
 char letter;
 cin >> qt_vertex;
 forr(i, qt_vertex){
  cin >> qt_words;
  connect(mapVertex(i), t, 1);
  forr (j, qt_words){
   cin >> a;
   words[i].push_back(a);
   letter = upper(a[0]);
   v = letter - 65;
   pos[i][v] = j;
   connect(s, v+2, 1);
   connect(v+2, mapVertex(i), 1);
  }
 }
}

int main(){

    cin >> cases;
    forr (i, cases){
     init();
     read();
     solve();
     printf("Case #%d:\n",i+1);
     output();
    }
    return 0;
}
