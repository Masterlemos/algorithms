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
/*
struct TYPE {
    int a, b, c;
 
    TYPE() { a = b = c = 0; }
    TYPE(int a, int b, int c) { this->a = a, this->b = b, this->c = c; }
    TYPE operator +(TYPE x) { return TYPE(a+x.a,b+x.b,c+x.c); }
};
//char *f = strtok(str, " "); f = strtok(NULL, " ");
//sort(ord())
struct ord {
 bool operator()(obj a, obj b){
  return a.oc > b.oc;
 }
};

int num(char c){
    return ((c - '0') % 48);
}
*/
struct TYPE {
    int qt, st;
    bool a,b;
    TYPE() { qt= st = a=b=0; }
  
};

int board[11][11];
int black, white, numC;
TYPE comp[200];
bool visited[11][11];

void dfs(int l, int c){
  visited[l][c] = 1;
  bool me = 0;
  if (board[l][c] == '.') me=1;
  comp[numC].qt++;
  comp[numC].st = board[l][c];
   
  int mst = comp[numC].st;
  //cima
  int st;
  bool vis;
  if (l>0){
   vis = visited[l-1][c];
   st = board[l-1][c];
   if (me){
     if (st=='X') comp[numC].a=1;
     if (st=='O') comp[numC].b=1;
   }
   if (!vis && st == board[l][c])
    dfs(l-1, c);
  }
  //baixo
  if (l<8){
   vis = visited[l+1][c];
   st = board[l+1][c];
   if (me){
     if (st=='X') comp[numC].a=1;
     if (st=='O') comp[numC].b=1;
   }
   if (!vis && st == board[l][c])
    dfs(l+1, c);
  }
  
  //esq
  if (c>0){
   vis = visited[l][c-1];
   st = board[l][c-1];
   if (me){
     if (st=='X') comp[numC].a=1;
     if (st=='O') comp[numC].b=1;
   }
   if (!vis && st == board[l][c])
    dfs(l, c-1);
  }
  //dir
  if (c<8){
   vis = visited[l][c+1];
   st = board[l][c+1];
   if (me){
     if (st=='X') comp[numC].a=1;
     if (st=='O') comp[numC].b=1;
   }
   if (!vis && st == board[l][c])
    dfs(l, c+1);
  }
}

int main(){
 int cases; char c;
 cin>>cases;
 while(cases--){
  white = 0; black = 0;
  for (int l = 0; l<9; l++){
   for (int col = 0; col<9; col++){
    cin>>c;
    board[l][col] = c;
   }
  }

  memset(visited, 0, sizeof visited);
  for (int i =0; i<200;i++){ comp[i].st = comp[i].qt = comp[i].a = comp[i].b = 0;}
  numC= black = white =0;
  for (int l = 0; l<9; l++)
   for (int col = 0; col<9; col++)
    if (!visited[l][col]){
     dfs(l,col);
     numC++;
    }
   for (int i =0; i<numC;i++) {
    if (comp[i].st == 'X') black+=comp[i].qt;
    else{
     if (comp[i].st == 'O') white+=comp[i].qt;
     else {
      if (comp[i].a && !comp[i].b) black+=comp[i].qt;
      else if (comp[i].b && !comp[i].a) white+=comp[i].qt;
     }
    }
   }
   cout<<"Black " <<black<< " White " <<white<<endl;
 }
 return 0;
}
