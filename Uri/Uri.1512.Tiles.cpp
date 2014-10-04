#include <iostream>

using namespace std;

int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }
int lcm(int a, int b) { return (a * (b / gcd(a, b))); } 

int main(){
 int n,a,b;
 while(1){
  cin >> n;
  if (n){
   cin >> a;
   cin >> b;
   
   int total = (n/a) + (n/b) - (n/lcm(a,b));
   cout << total<<"\n";
  }else break;
 }
 return 0;
}
