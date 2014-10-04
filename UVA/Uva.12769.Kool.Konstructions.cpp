#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
 
#define ui unsigned long long
typedef vector<ui> vi;
#define LSOne(S) (S & (-S))
 
 
 
class FenwickTree {
private:
  vi B1,B2;int size;
 
public:
  FenwickTree() {}
  // initialization: n + 1 zeroes, ignore index 0
  FenwickTree(int n) { B1.assign(n + 1, 0); B2.assign(n + 1, 0); size=n+1;}
  
  //essas pestinhas sao internas,nao usar
  ui query(vi& ft, int b) {
        ui sum = 0;
        for (; b; b -= LSOne(b)) sum += ft[b];
        return sum;
  }
    //essas pestinhas sao internas,nao usar query-> use range_query passando igual
  ui query(int b) {
    return query(B1, b) * b - query(B2, b);
  }
  
  
  
  ui range_query(int i, int j)    {
    return query(j) - query(i - 1);
  }
   
  void update(vi& ft, int k, ui v) {
        for (; k < size; k += LSOne(k)) ft[k] += v;
  }
  
// Range update: adiciona v para cada elemento entre [i,j] atencao indices comecam com 1
void range_update(int i, int j, ui v)   {
        update(B1, i, v);
        update(B1, j + 1, -v);
        update(B2, i, v * (i - 1));
        update(B2, j + 1, -v * j);
}
};
 
int main() {              // idx   0 1 2 3 4 5 6 7  8 9 10, no index 0!
  int range, a, b, queries, value;
  char q;
  range = 100000;
  while(cin>>queries && queries){
      FenwickTree ft(range);  
       
      while(queries--){
          cin>>q;
          if (q=='Q'){//consulta-indices comecao em 1
           cin>>a;
           printf("%llu\n", ft.range_query(a,a));
          }else{//update
           cin>> a >> b >> value;
           ft.range_update(a,b, value);
          }
      }
  }
 
  return 0;
} 
