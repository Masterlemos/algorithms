#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;


typedef vector<int> vi;

int t,r;

bool adj[110][110];
bool dom[110][110];
bool visto[110];
int n;

bool busca(int inicio, int target){
 queue<int> fila;
 fila.push(0);
 memset(visto, 0, sizeof visto);
 bool ini = false;
 if (inicio == 0) ini = true;
 if (target == 0 && ini) return true;
  while(!fila.empty()){
    int u = fila.front();
    fila.pop();
    if (!visto[u]){
         for (int z = 0; z < n; z++){
          if (adj[u][z]){
           if (z == inicio) ini = true;
           if (z == target && ini) return true;
           fila.push(z); 
          }            
         }    
         visto[u] = 1;
    }
  }
  return false;
}

bool bfs(int atual, int target){
   queue<int> fila;

   fila.push(0);
   memset(visto, 0, sizeof visto);

   while(!fila.empty()){
    int u = fila.front();
    fila.pop();
    if (!visto[u]){
        if (u!=atual){
         for (int z = 0; z < n; z++){
          if (adj[u][z]){
           if (z==target) return true;
           fila.push(z);
          }
         }
        }
        visto[u] = 1;
    }
   }
   return false;

}

int main(){
 scanf("%d", &t);
 for(int ca = 1; ca<=t; ca++){
  //memset(dom, 1, sizeof dom);
  memset(adj, 0, sizeof adj);
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
   for (int j = 0; j<n; j++){
    scanf("%d", &r);
    if (r) adj[i][j]=1;
   }
  }
  //-----------------
  for (int i = 0; i < n; i++){
   for (int u = 0; u < n; u++){
     if (busca(i, u)){
      if (i==u) dom[i][i] = 1;
      else{
       if (bfs(i,u)) dom[i][u] = 0;
       else dom[i][u] = 1; 
      }
     }else{
      dom[i][u] = 0;
     }    
   }
   if (i>0)
   dom[i][0] = 0;
  }
  //-----------------
  printf("Case %d:\n", ca);
  
  for (int i=0; i<n; i++){
   printf("+"); for (int traco = 1; traco <= 2*n-1; traco++) printf("-"); printf("+\n");
   printf("|"); 
   for (int d = 0; d < n; d++){
    if (dom[i][d]) printf("Y|");
    else printf("N|");
   }
   printf("\n");
  }
  
  printf("+"); for (int traco = 1; traco <= 2*n-1; traco++) printf("-"); printf("+");
  printf("\n");
 } 
 return 0;
}
