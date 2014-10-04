//Problema uri 1224 - cartoes
//Solucao por Aldo Lemos

//Estrategia : transformar dp top down em bottom up
//Aldo Lemos - accepted tempo: 2.8 s.


#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define fori(i, n) for (int i = 0; i < n; i++)

#define tipo long long


int n;

tipo v[10010];

tipo dp[10010];

tipo est(int p, int u){
 return max(v[p+1], min(v[p], v[u]));
}

void dpmax(){
 fori(i, n-2){
  dp[i] = est(i, i+2);
 }
 bool flip = true;
 int comp = 3;
 int l = n-3;
 while(l > 0){
  fori(i, l){
   if (flip)
    dp[i] = max(v[i+comp] + dp[i], v[i] + dp[i+1]);
   else
    dp[i] = min(dp[i], dp[i+1]); 
  }
  flip = !flip;
  comp++;
  l--;
 }
}

int main(){
 while(scanf("%d", &n)!=EOF){
  memset(dp, 0, sizeof dp);
  fori(i, n) scanf("%lld", &v[i]);
  if (n==2) printf("%lld\n", max(v[0], v[1]));
  else{
   dpmax();
   printf("%lld\n", dp[0]);
  }
 }
 return 0;
}
