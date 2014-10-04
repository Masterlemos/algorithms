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

int f[2000];
int fib(int n){
  return f[n];
}
int exp(int p, int q){
 int r= 1;
    while (q != 0) {
        if (q % 2 == 1) {    // q is odd
            r = (r*p)%1500;
            q--;
        }
        p = (p*p)%1500;
        q /= 2;
    }
    return r;
}
int main(){
 int cases;
 char num[10010];
 scanf("%d",&cases);
 f[1]=f[2]=1;
 for (int i=3; i<1510;i++)
  f[i] = (f[i-1] + f[i-2])%1000;
  
 while(cases--){
  scanf("%s", num);
  int sum = 0;
  int size = strlen(num);
  int ex = 0;
  
  for (int i = size-1; i>=0; i--){
   if (num[i]=='1')
    sum = (sum+exp(2,ex))%1500;
   ex++;
  }
  sum = fib(sum);
    
  if (sum<10) printf("00%d\n",sum);
  else{
    if (sum<100) printf("0%d\n",sum);
    else    printf("%d\n",sum);
  }
 }
 return 0;
}
