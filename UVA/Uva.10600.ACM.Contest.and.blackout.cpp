#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 1010
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
private:
  vi p, rank, setSize;                       // remember: vi is vector<int>
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) { numSets--; 
    int x = findSet(i), y = findSet(j);
    // rank is used to keep the tree short
    if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
    else                   { p[x] = y; setSize[y] += setSize[x];
                             if (rank[x] == rank[y]) rank[y]++; } } }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};


int qt_vertex, qt_edges;

int main() {
  int u,v,w,cases;
  scanf("%d", &cases);
  while(cases--){
  scanf("%d %d", &qt_vertex, &qt_edges);
  vector< pair<int, ii> > EdgeList;
  for (int i = 0; i < qt_edges; i++){
    scanf("%d %d %d", &u, &v, &w);
    EdgeList.push_back(make_pair(w, ii(u, v)));
  } 
  sort(EdgeList.begin(), EdgeList.end()); 
  UnionFind UF(qt_vertex+1);
  int cost = 0;
  
   vector< int > mst;
  for (int j = 0; j < qt_edges; j++) {                   
       pair<int, ii> front = EdgeList[j];
       if (!UF.isSameSet(front.second.first, front.second.second)) { 
         cost += front.first;
         mst.push_back(j);
         UF.unionSet(front.second.first, front.second.second);  
       }
  }
  
  int sec, qt_edges_smst = 0;
  int ans = 1000000000;
  
  for (int flag = 0; flag < mst.size(); flag++){
   qt_edges_smst = 0;
   sec = 0;
   UnionFind uf(qt_vertex+1);
   for (int i = 0; i < qt_edges; i++){
      pair<int, ii> front = EdgeList[i];
      if (mst[flag] != i){
       if (!uf.isSameSet(front.second.first, front.second.second)){ 
         sec += front.first;
         qt_edges_smst++;
         uf.unionSet(front.second.first, front.second.second);  
       } 
      }
   }
   if (qt_edges_smst == mst.size())
    ans = min(ans, sec);
  
  }
  
  printf("%d %d\n", cost, ans);
  }
  return 0;
}
