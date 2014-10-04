/*
 Minha solucao burra 0.227s - My stupid solution 0.227s

 Dinic's algorithm. O(V^2E) Pode ser resolvida com edmonds tambem. You can use edmonds karp.
 Nao esqueca de quebrar os intervalos. You must break the intervals.

 
 Num artigo encontrado na internet, um cara mostra como quebrar os intervalos com 100 operacoes constantes.
 In the internet some guy showed how to break intervals with 100 operations.
 
 A solucao aqui foi burra, o que eu fiz foi colocar ids de [1..100] para os macacos.
 Here in my stupid solution, ids from 1 to 100 were assigned to monkeys.
 
 e para todos os intervalos faco a multiplicacao e a soma para diferenciar os intervalos, isso gera 5kk operacoes.
 to create new states, ids of the monkeys that can drink water in some interval were multiplied e added, done with 5kk  operations.
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>



using namespace std;

#define INF 1e9
#define MAX_V 315
#define MAX_S 50010
#define tipo long long

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, int> mii;

struct monkey{
   int v, a, b;
   monkey(int v, int a, int b){this->v = v; this->a = a; this->b = b;}
};

struct st{
   int a, len, start;
};

int cases, s, t, f, qt_vertex, qt_edges, mf, m, firstState, water;

vector<monkey> monkeys;

int res[MAX_V][MAX_V], p[MAX_V], dist[MAX_V], work[MAX_V], mul[MAX_S], sum[MAX_S];

st st_info[MAX_V];

vi graph[MAX_V], states[MAX_S];

void createEdge(int u, int v){
 graph[u].push_back(v);
 graph[v].push_back(u);
}

int nextState(){
 return firstState++;
}

void connect(int u, int v, int w){
 createEdge(u, v); res[u][v] = w;
}

bool changed(int i){
 if (i>0 && (mul[i] != mul[i-1] || sum[i] != sum[i-1])) return true;
 if (!i) return sum[i] > 0;
 return false;
}

bool has_state(int i){
        if (i<0) return 0;
	return sum[i] > 0;
}

void createGraph(){
 int st, id, slot;
 
 for (int i = 0; i < MAX_S; i++){
  if (!changed(i)) continue; //mesmo estado

   //comeco	
   if (has_state(i)){
   	 st = nextState(); 	
   	 id = st-100;
         st_info[id].a = st_info[id].start = i;
   }
   
   //fim
   if (has_state(i-1)){
    if (has_state(i)) st--; else st = firstState-1;
    id = st-100;    
    int len = i-1 - st_info[id].a + 1;
    st_info[id].len = len;
    slot = m * len;
    for (int j = 0; j < (int)states[i-1].size(); j++)
      connect(states[i-1][j], st, len);
    connect(st, t, slot);
   }
 }
}

//Quebrar a solucao para entrar nos intervalos
void getAns(int u, int new_vertex, vii &intervals, mii &used){

          if( new_vertex != s){	
             st nvs = st_info[new_vertex-100];
             int len = nvs.len;
             int drunk = res[new_vertex][u];
             if( drunk == 0 ) return;
             ii ans;
             while( drunk > 0){
               int left = used[nvs.a], right = min(left+drunk,len);
               ans = ii( nvs.a + left, nvs.a + right);
               used[nvs.a] = (right == len) ? 0:right;	
               drunk -= (right - left);
               intervals.push_back( ans );	
             }	
          }
}

//combinar os intervalos
void combine(vii &intervals){
    int a, b;
    vii ans;
    for (int k = 0; k < (int)intervals.size(); k++){
      a = intervals[k].first; 
      b = intervals[k].second;	
      while( k+1 < intervals.size() && intervals[k+1].first == b) b = intervals[k+1].second, k++;
      ans.push_back(ii(a,b));
    }	
    printf("%d", (int) ans.size());
    for (int j = 0; j < (int) ans.size(); j++) printf(" (%d,%d)", ans[j].first, ans[j].second);
    printf("\n");
}

void output(){
    mii used;
    vii intervals;

    if (water != mf) printf("Case %d: No\n", cases++);
    else{
     printf("Case %d: Yes\n", cases++);
     
     for (int u = 1; u <= qt_vertex; u++){
      intervals.clear();
      for (int v = 0; v < (int) graph[u].size(); v++) getAns(u, graph[u][v], intervals, used);
      sort(intervals.begin(), intervals.end()); 
      combine(intervals);
     }
    }
}

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

void solve(){
        createGraph();        
        mf = maxFlow();
}

void read(){
     int a, b, v;

     for (int i = 1; i <= qt_vertex; i++){
      scanf("%d %d %d", &v, &a, &b);      
      water += v;
      monkey m(v, a, b);
      monkeys.push_back(m);
      connect(s, i, v);
      for (int j = a; j<b; j++){
        states[j].push_back(i);
        if (mul[j]) mul[j] *= i; else mul[j] = i;
        if (sum[j]) sum[j] += i; else sum[j] = i;
      } 
     }
}

void init(){
	memset(res, 0, sizeof res);
	for (int i = 0; i < MAX_V; i++) graph[i].clear();
	for (int i = 0; i < MAX_S; i++) states[i].clear();
	
	memset(mul, 0, sizeof mul);
	memset(sum, 0, sizeof sum);
	
	s = water = 0;
	t = 310;
	firstState = 101;
	monkeys.clear();
}

int main(){
    cases = 1;
    while(scanf("%d %d", &qt_vertex, &m) && qt_vertex){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
