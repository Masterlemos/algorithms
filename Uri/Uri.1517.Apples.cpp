//A sacanagem eh que ele pode ficar no mesmo lugar

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

typedef vector<int> vi;
typedef vector<vi> vtrio;
typedef pair<int, int> par;
 
struct TYPE {
    int a, b, c;
 
    TYPE() { a = b = c = 0; }
    TYPE(int a, int b, int c) { this->a = a, this->b = b, this->c = c; }
    TYPE operator +(TYPE x) { return TYPE(a+x.a,b+x.b,c+x.c); }
};

int dp[25][25][2005], n, m, k, lim;
bool pos[25][25][2005];

int tsp(int linha, int col, int ti){
  if ((linha > 0) && (linha <= n) && (col > 0) && (col <= m) && (ti<=lim)){
    if (dp[linha][col][ti] != -1) return dp[linha][col][ti];
    
    int res = 0, plus=0;
    if (pos[linha][col][ti]) plus=1;
    //cima
    res = max(res, tsp(linha+1, col, ti+1));

    //baixo
    res = max(res, tsp(linha-1, col, ti+1));

    //esq
    res = max(res, tsp(linha, col-1, ti+1));

    //dir
    res = max(res, tsp(linha, col+1, ti+1));

    //diag sup esq
    res = max(res, tsp(linha+1, col-1, ti+1));

    //diag sup dir
    res = max(res, tsp(linha+1, col+1, ti+1));

    //diag inf esq
    res = max(res, tsp(linha-1, col-1, ti+1));

    //diag inf dir
    res = max(res, tsp(linha-1, col+1, ti+1));

    res = max(res, tsp(linha, col, ti+1));

    return dp[linha][col][ti] = res+plus;
  }else return 0;
}

int main(){
 int l,c,t,a,b;

 while(1){
   scanf("%d %d %d", &n, &m, &k);
   if (n){
      memset(dp, -1, sizeof dp);
      memset(pos, 0, sizeof pos); 
      
      fori(i,k){
        scanf("%d %d %d", &l, &c, &t);
        pos[l][c][t] = 1;
      }
      lim = t;
      scanf("%d %d", &a, &b);
      printf("%d\n", tsp(a, b, 0));
   }else break;
 }
 return 0;
}
