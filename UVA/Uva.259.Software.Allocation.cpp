#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <bitset>

using namespace std;

typedef vector<int> vi;
#define MAX 50
#define INF 1e9

int res[MAX][MAX], p[MAX];
int mf, f, s, t;
char str[MAX];
bitset<MAX> visited;


int num(char c){
    return ((c - '0') % 48);
}

int mapVertex(char c){
 return (c - 'A' + 11);
}

void augment(int v, int minEdge){
 if (v==s){f = minEdge; return;}
 else if (p[v] != -1){ augment(p[v], min(minEdge, res[p[v]][v])); res[p[v]][v] -= f; res[v][p[v]] += f;}
}

void maxFlow(){
 mf = 0;
 while(1){
  f = 0;
  visited.reset(); visited[s] = 1; queue<int> q; q.push(s);
  memset(p, -1, sizeof p);
  while(!q.empty()){
   int u = q.front(); q.pop();
   if (u==t) break;
   for (int v = 0; v < MAX; v++)
    if (res[u][v] > 0 && !visited[v]){
     visited[v] = 1;
     q.push(v);
     p[v] = u;
    }
  }
  augment(t, 1e9);
  if (!f) break;
  mf += f;
 }
}

void solution(){
 for (int pc=1; pc<11; pc++){
  bool has = 0;
  if (!res[pc][t]){
   for (int app = 'A'; app <= 'Z'; app++){
    if (res[pc][mapVertex(app)]){ 
     printf("%c", app);
     has=1;
     break;
    }
   }
  }
  if (!has) printf("_");
 }
 printf("\n");
}

//26 letters + 10 computers + 2 (s, t) = 38 [0..37]

//0 - s
//1..10 computers
//11 - 36 [A..Z]
//37 - t

//in
//A9 0123456789;

int main(){
    s = 0;
    t = 37;
    while(1){
        memset(res, 0, sizeof res);
        int qt_users = 0;
    	while(1){
    		if (gets(str) == NULL || str[0] == 0){
    		 maxFlow();
    		 if (mf == qt_users)
    		  solution();
    		 else printf("!\n");
    		 if (str[0] == 0) break;
                 return 0;
                }else{
                 int letter = mapVertex(str[0]);
                 int qt_users_app = num(str[1]);
                 qt_users += qt_users_app;
                 res[s][letter] = qt_users_app;
                 res[letter][s] = qt_users_app;
                 
                 for(int i = 3; i < strlen(str) - 1; i++){
                  int pc = num(str[i]) + 1;
                  res[letter][pc] = 1;
                  res[pc][letter] = 0;
                  
                  res[pc][t] = 1;
                  res[t][pc] = 0;
                 }
                }
    	}
    }
    return 0;
}
