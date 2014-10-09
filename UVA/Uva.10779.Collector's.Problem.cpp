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
#define MAX_V 1500
#define tipo long long
#define forr(i, b) for (int i = 0; i < b; ++i)
#define ford(i, a, b) for (int i = a; i <= b; ++i)
#define pb(i) push_back(i)

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> msi;

int cases, s, t, qt_vertex, mf;
int res[MAX_V][MAX_V];
vi graph[MAX_V];

//particular
int has[10][25], spli[MAX_V];
int qt_people, qt_stickers, state;

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

//PARTICULAR


bool canTrade(int p, int a, int b){
  return (!has[p][a] && (has[p][b] > 1)); 
}

int mapPosition(int line, int col){
 return (25*(line-1) + col) + 278;
}

int mapOut(int u){
 return u+251;
} 

void split(int vin, int w){
   connect(vin, mapOut(vin), w);
}

int mapLine(int id_model, int people){
   return (10 * id_model + people + 27);
}

int mapLineOut(int lin){
  return lin+251;
}

// [s=0] [t=1] [model in 2..26] [25 ids * 10 lines in 27..37] [10 lines out 38..48] [vertex in 278+i....] [vertex out vertin+251..]
void crateGraph(){
    int vin, vout, linein, lineout;
    forr(st, qt_stickers){
    	if (has[0][st])
    	 connect(s, st+2, has[0][st]);
    	connect(st+2, t, 1);
    }
    
    forr (model, qt_stickers){
      ford (people, 1, qt_people-1){
         forr (stc, qt_stickers){
            if (model == stc) continue;
            if ( canTrade(people, model, stc) ){
             vin = mapPosition(people, stc);
             vout = mapOut(vin);

             linein = mapLine(model, people-1);
             lineout = mapLineOut(linein);

             connect(model+2, linein, 1);
             if (!res[linein][lineout]) connect(linein, lineout, 1);
             connect(lineout, vin, 1);
             if (!res[vin][vout])
              split(vin, has[people][stc]-1), connect(vout, stc+2, INF);
            }
         }
      }
    }
}
//FIM PARTICULAR


//STANDARD
void init(){
 memset(res, 0, sizeof res);
 memset(has, 0, sizeof has);
 memset(spli, 0, sizeof spli);

 forr (i, MAX_V) graph[i].clear();

 s = 0;
 t = 1;
 state = 27;
}

void read(){
	int qsp; //sticker per people
	int id_sticker; //id of sticker
	scanf("%d %d", &qt_people, &qt_stickers);
	forr(i, qt_people){
		scanf("%d", &qsp);
		while (qsp--){
			scanf("%d", &id_sticker);
			has[i][id_sticker-1]++;
		}
	}
}

void solve(){
	crateGraph();
	mf = maxFlow();
}

void output(){
   printf("%d\n", mf);
}

//FIM STANDARD

int main(){
    scanf("%d", &cases);
    ford (i, 1, cases){
     init();
     read();
     solve();
     printf("Case #%d: ", i);
     output();
    }
    return 0;
}
