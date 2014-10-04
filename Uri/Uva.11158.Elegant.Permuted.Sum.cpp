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

 int num(char c){
    return ((c - '0') % 48);
 }
 
int n;
vector<int> arr;
bool mask[55];
int ans;

 
int main(){
   int cases;
   scanf("%d", &cases);
   for (int i =0; i<cases; i++){
     
     int ele; ans=0;
     scanf("%d", &n);   
     
     for (int j =0; j<n; j++){
      scanf("%d", &ele);
      arr.push_back(ele);
     }
     if (n==2){
       printf("Case %d: %d\n", i+1, abs(arr[0]-arr[1]));
     }else{
      sort(arr.begin(), arr.end());
      int u = n-1, p=1;
      ans += abs(arr[0] - arr[u]);
      int esq = arr[0], dir = arr[u], flip,f=2;
      u--;
      while(f!=n){
       //p ou u
       int mp = max(abs(esq-arr[p]), abs(dir-arr[p]));
       int mu = max(abs(esq-arr[u]), abs(dir-arr[u]));
       if (mp > mu) flip=1;
       else flip=0;
      if (flip){
       if (abs(esq-arr[p]) > abs(dir-arr[p])){
        ans += abs(esq-arr[p]);
        esq = arr[p];
       }else{
        ans += abs(dir-arr[p]);
        dir = arr[p];
       }
       p++; 
      }else{
       if (abs(esq-arr[u]) > abs(dir-arr[u])){
        ans += abs(esq-arr[u]);
        esq = arr[u];
       }else{
        ans += abs(dir-arr[u]);
        dir = arr[u];
       }
       u--;
      }
      f++;
      }
      printf("Case %d: %d\n", i+1, ans);
     }
     arr.clear();
   }
 return 0;
}
