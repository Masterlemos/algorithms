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
 
vi dp;
int memo[1010], t1, t2, comp;
int cobrir(int a, int b){
  if (a==b) return min(t1,t2);
  if (a>b) return 0;
  if (memo[a]!=-1) return memo[a];
 
  int resto = t1;
  int i = a;
  while (resto>0 && i<b){
   resto -= dp[i];
   i++;
  }
  if (resto>=0) i++;
 
  resto = t2;
  int j = a;
  while (resto>0 && j<b){
   resto -= dp[j];
   j++;
  }
  if (resto>=0) j++;
   
  return memo[a] = min(t1+cobrir(i, b), t2+cobrir(j, b));
}
 
int main(){
 int f, ia, ma, n,c;
 while(scanf("%d %d %d %d", &n, &c, &t1, &t2)!=EOF){
   ia = -1; ma = -1;
   memset(memo, -1, sizeof memo);
   vi  dif;
   vi furos;
   fori(i, n){
     scanf("%d", &f);
     furos.push_back(f);
   }
   //sort(furos.begin(), furos.end());
 
   fori(i,n){
 
     if (i>0){
      f = furos[i]-furos[i-1];
      if (f){
       dif.push_back(f);
       if (f>ma) {ma = f; ia = i-1;}
      }
     }
     if (i==n-1){
      f = c-furos[n-1] + furos[0];
      dif.push_back(f);
      if (f>ma) {ma = f; ia = dif.size()-1;}
     }
   }
   for (int i = ia+1; i <= dif.size()-1; i++) dp.push_back(dif[i]);
   for (int i = 0; i<= ia-1; i++) dp.push_back(dif[i]);

   printf("%d\n",cobrir(0, dp.size()));
    
   dp.clear();
 }
 
 return 0;
}
