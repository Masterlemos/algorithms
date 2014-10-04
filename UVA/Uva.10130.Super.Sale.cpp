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
#define MAX 40

typedef pair<string, int> si;
typedef vector<si> vsi;

int dp[35][1010], p[1010], w[1010], personW[110];
int t, n, g;
int buy(int we, int obj){
 if (we){
  if (obj == n) return 0;
  else{
   if (dp[we][obj] != -1) return dp[we][obj];
   else{
    if (we >= w[obj])
     return dp[we][obj] = max(buy(we, obj+1), buy(we-w[obj], obj+1)+p[obj]);
    else return dp[we][obj] = buy(we, obj+1);
   }
  }
 }else return 0;
}
int main(){

 scanf("%d", &t);
 while(t--){
  scanf("%d", &n);
  fori(i, n)
   scanf("%d %d", &p[i], &w[i]); 
  scanf("%d", &g);
  fori(i, g) scanf("%d", &personW[i]);
  memset(dp, -1, sizeof dp);
  //buy(30, 0);
  int res =0;
  fori(i, g)
   res += buy(personW[i], 0);
  printf("%d\n", res); 
 }
 return 0;
}
