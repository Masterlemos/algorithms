#include <cstdio>
#include <cstring>
#include <bitset>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define INF 10000
#define MAX 65
#define MAX_V 2101

typedef pair<int, int> ii;
typedef vector<int> vi;

int res[MAX_V][MAX_V], p[MAX_V];

char grid[MAX][MAX];

vi graph[MAX_V];

int row, col, pp, mf, f, s, t;

bitset<MAX_V> visited;

int dh[] = {0, 1, 0, -1};
int dv[] = {-1, 0, 1, 0};

ii getCords(int v){
    int r, c;
    if (!(v%col)){
     r = (v/col) - 1;
     c = col - 1;
    }else{
     r = v/col;	
     c = (v%col) - 1;
    }
    return ii(r,c);
}

char getNode(int v){
	ii cords = getCords(v);
	return grid[cords.first][cords.second];
}

bool star(int v){
 if (getNode(v) == '*') return true;
 return false;
}

bool sharp(int v){
 if (getNode(v) == '#') return true;
 return false;
}

bool water(int v){
 if (getNode(v) == '~') return true;
 return false;
}

bool dot(int v){
 if (getNode(v) == '.') return true;
 return false;
}

bool at(int v){
 if (getNode(v) == '@') return true;
 return false;
}

bool inside(int r, int c){
 if (r >= 0 && r < row && c >= 0 && c < col) return true;
 return false;
}

void init(){
	s = 0;
	t = 2100;
       
	for (int i = 0; i < MAX_V; i++){
	 graph[i].clear();
	 for (int j = 0; j < MAX_V; j++)
	  res[i][j] = 0;
	}
}

void augment(int v, int minEdge){
 if (v==s){f = minEdge; return;}
 else if (p[v] != -1){
   augment(p[v], min(minEdge, res[p[v]][v]));
   res[v][p[v]] += f;
   res[p[v]][v] -= f;
 }
}

void bfs(){
 visited.reset(); visited[s]=1;
 queue <int> q; q.push(s);
 while(!q.empty()){
  int u = q.front();
  q.pop();
  if (u==t) break;
  for (int i=0; i<graph[u].size(); i++){
   int v = graph[u][i];
   if (res[u][v] > 0 && !visited[v]){
    visited[u] = 1;
    q.push(v); 
    p[v] = u;
   }
  }
 }
}

void maxFlow(){
 mf = 0;
 while(1){
  f = 0;
  memset(p, -1, sizeof p);
  bfs();
  augment(t, 1e9);
  if (!f) break;
  mf += f;
 }
}

int mapVertex(int r, int c){
 return (r+1)*col - (col-(c+1));
}

int mapOut(int in){
 return in+900;
}

void build(int vout, int uin){
   if (!water(uin)){
    graph[vout].push_back(uin);
    graph[uin].push_back(vout);
    res[vout][uin] = INF;
   }
}


void connect(int r, int c){

   int vin = mapVertex(r, c);
   int vout = mapOut(vin);
   graph[vin].push_back(vout);
   graph[vout].push_back(vin);
   
   int lim = INF;
   
   if (star(vin)) {  res[s][vin] = 1; lim = 1;    graph[s].push_back(vin);} 
   if (sharp(vin)){  res[vout][t] = pp;           graph[vout].push_back(t);}
  
   if (dot(vin)) lim = 1;
   
   res[vin][vout] = lim;
   
   for (int i=0; i<4; i++){
    int nr = r + dv[i];
    int nc = c + dh[i];
    if (inside(nr, nc)) build(vout, mapVertex(nr, nc));
   }
   
}

int main(){
    while(scanf("%d %d %d", &row, &col, &pp) != EOF){
       init();
       for (int r = 0; r < row; r++)
       	scanf("%s", grid[r]);
       
       for(int r = 0; r < row; r++)
       	for (int c = 0; c < col; c++)
          connect(r, c);
       
       maxFlow();
       printf("%d\n", mf);
    }
    return 0;
}
