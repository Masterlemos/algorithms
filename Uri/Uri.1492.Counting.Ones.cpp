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

#define tipo unsigned long long

typedef vector<int> vi;
typedef vector<vi> vtrio;
typedef pair<int, int> par;
 
struct TYPE {
    int a, b, c;
 
    TYPE() { a = b = c = 0; }
    TYPE(int a, int b, int c) { this->a = a, this->b = b, this->c = c; }
    TYPE operator +(TYPE x) { return TYPE(a+x.a,b+x.b,c+x.c); }
};
tipo ac[68], a[68], f[68];

tipo decimal(string str, int inicio){
  tipo soma = 0;int exp = 0;
  for(int j = str.length()-1; j>=inicio; j--){
   if (str[j] == '1') soma+=pow(2, exp);
   exp++;
  }
  return soma;
}

tipo computar(string& str, int inicio){
  if (inicio == str.length()) return 0;
  int i = inicio+1;
  for(; i<str.length(); i++) if (str[i]=='1') break;
  return (f[str.length() - inicio] + decimal(str, i) + computar(str, i));
}
string tobin(tipo n){
 vector<char> num; tipo k;
 bool tem = 0;
for (int c = 63; c >= 0; c--)
  {
    k = n >> c;
 
    if (k & 1){
      num.push_back('1'); tem = 1;//agora tem tem tem
    }
    else{
      if (tem)
      num.push_back('0');
    }
  }
  int j = num.size();
  string nova; nova.resize(j);
  for(int i =0; i<j; i++) nova[i] = num[i];
  return nova;
}
int main(){
 tipo s1,s2;
 ac[1] = 1;
 a[1] = 0;
 ac[2] = 4;
 a[2] = 1;
 f[0] = 0;
 f[1] = 1;
 f[2] = 2;
 for (int i=3; i < 67; i++){
  a[i] = a[i-1] + pow(2, i-2);
  ac[i] = 2*ac[i-1] + a[i] +1;
  f[i] = ac[i-1]+1;
 } 

 while(scanf("%llu %llu",&s1,&s2)!=EOF){ 
 	string bb = tobin(s2);
 	string aa = tobin(s1);
    tipo res = computar(bb,0) - computar(aa,0);
    tipo un=0;
    for(int j = 0; j < aa.length(); j++){
     if (aa[j] == '1') un++;
    }
    printf("%llu\n", res+un);
 }
 return 0;
}
