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
int n;
long long dp[5010];
char dig[5005];
int main(){

 while(scanf("%s", dig)!=EOF){
  if (dig[0]!='0'){
   n = strlen(dig);
   if (dp[n-1]!='0') dp[n-1] = 1; else dp[n-1] = 0;
   if (n>1){
    if (dig[n-2]=='1' || (dig[n-2]=='2' && dig[n-1] < '7')){
     if (dig[n-1] == '0') dp[n-2] = 1;
     else      dp[n-2] = 2;
    }else
     dp[n-2] = 1;
    
    for (int i = n-3; i >= 0; i--) {
     if (dig[i]=='1' || (dig[i]=='2' && dig[i+1] < '7')){
      if (dig[i+1] == '0')
         dp[i] = dp[i+1]; 
      else{
       if (dig[i+2] == '0') dp[i] = dp[i+1];
       else     dp[i] = dp[i+1] + dp[i+2];
      }
     }else
      dp[i] = dp[i+1];
  
    }
   }

   printf("%lld\n", dp[0]);
  }else break;
 }

 return 0;
}
