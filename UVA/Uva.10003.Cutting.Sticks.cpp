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

#define tipo int
//%lld
//%llu unsigned
typedef pair<string, int> si;
typedef vector<si> vsi;

int n, l, dp[1010][1010];
bool v[1010];
int cut(int e, int d){
 

 if (e+1 == d)
  return 0;
 else{
  if (dp[e][d] != -1) return dp[e][d];
  int res = 200000000;
  bool ok = false;
  forr(i, e+1, d-1){
   if (v[i]){
    res = min(res, cut(e, i) + cut(i, d));
    ok = true;
   }
  }
  if (!ok) return dp[e][d] = 0;

  return dp[e][d] = (d-e + res);
 }
}

int main(){
 while(1){
  scanf("%d", &l);
  if (l){
    memset(v, 0, sizeof v);
    memset(dp, -1, sizeof dp);
    scanf("%d", &n);
    int c;
    fori(i, n){
     scanf("%d", &c);
     v[c] = 1;
    }
    printf("The minimum cutting is %d.\n", cut(0, l));
  }else return 0;
 }

 return 0;
}
