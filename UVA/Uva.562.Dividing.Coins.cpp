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

int sum, qt_coins,  my_sum, other, dif;
int coins[110];
int dp[60000];

int main(){
 int cases, ans;
 scanf("%d", &cases);
 while(cases--){
  sum = 0; ans = 1e9;
  scanf("%d", &qt_coins);
  for (int i =0; i<qt_coins; i++){
   scanf("%d", &coins[i]);
   sum += coins[i];
  }
  memset(dp, -1, sizeof dp);
  int lim = 1;
  dp[0] = 1;
  for (int i = 0; i < qt_coins; i++){
     int l = lim;
     for (int j = 0; j <= l; j++){
      if ((dp[j] != i && dp[j] != -1) || (j==0)){
       my_sum = j + coins[i]; lim = max(lim, my_sum);
       if (dp[my_sum] == -1) dp[my_sum] = i; 
      } 
     }
  }
  for (int i = 0; i<=lim; i++) if(dp[i] != -1) ans = min(ans, abs(sum - 2*i));
  printf("%d\n", ans);
 }
 return 0;
}
