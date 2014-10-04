#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

#define fori(i, n) for (int i=0; i<n; ++i)
#define forr(i, a, n) for (int i=a; i<=n; ++i)

#define tipo long long

#define MAX 100

typedef vector<int> vi;
typedef vector<vi> vtrio;
typedef pair<int, int> par;
 
struct TYPE {
    int a, b, c;
 
    TYPE() { a = b = c = 0; }
    TYPE(int a, int b, int c) { this->a = a, this->b = b, this->c = c; }
    TYPE operator +(TYPE x) { return TYPE(a+x.a,b+x.b,c+x.c); }
};

 int num(char c){
    return ((c - '0') % 48);
 }
 
int cases, n, canhao, r;
int proj[60][2], dp[110];

int main(){
  
 scanf("%d", &cases);
 while(cases--){
  scanf ("%d", &n);
  for (int i =0; i<n; i++)
   scanf("%d %d", &proj[i][0], &proj[i][1]);
  scanf("%d", &canhao);
  scanf("%d", &r);
  memset(dp, -1, sizeof dp);
  for (int pro = 0; pro<n;pro++){
   int patual = proj[pro][1];
   int vatual = proj[pro][0];
   for (int i = 1; i<= canhao; i++){
    if (dp[i] != -1){
     if (i >= patual){
      int atual = dp[i - patual];
      dp[i - patual] = max(atual, dp[i]+vatual);
     }
    }
   }
   if (patual <= canhao){
    int atual = dp[canhao - patual];
    dp[canhao - patual] = max(atual, vatual);
   }
  }
  bool ok = false;
  for (int i =0; i<canhao; i++)
   if (dp[i] >= r) {ok=1; break;}
  
  if (ok) printf("Missao completada com sucesso\n");
  else printf("Falha na missao\n");
 }
 return 0;
}
