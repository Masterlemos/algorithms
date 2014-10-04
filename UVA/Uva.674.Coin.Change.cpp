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

#define tipo long long
//%lld
//%llu unsigned
typedef pair<string, int> si;
typedef vector<si> vsi;

int n;
int values[] = {50, 25, 10, 5, 1};
int dp[10000][5];
int ways(int v, int i){
 if (v){
  if (i == 5) return 0;
  else{
    if (dp[v][i] != -1) return dp[v][i];
    int res = 0;
    int vv = v;
    int ii = i;
    while(v < values[i]) i++;
    res += ways(v, i+1);
    while(v >= values[i]){
     v -= values[i];
     res += ways(v, i+1);
    }
    return dp[vv][ii] = res;
  }
 }else return 1;
 
}
int main(){
 memset(dp, -1, sizeof dp);
 while(cin>>n)
  printf("%d\n", ways(n,0));
 
 return 0;
}
