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
  int u,v,E;
  while(scanf("%d %d", &qt_vertex, &qt_edges) && qt_vertex){
      vector< pair<long, ii> > EdgeList;
      long full = 0,w;
      for (int i = 0; i < qt_edges; i++){
       scanf("%d %d %ld", &u, &v, &w);
       //pode causar bug se repetir-200000 -sem has edge
       full += w;
       EdgeList.push_back(make_pair(w, ii(u, v)));
       //EdgeList.push_back(make_pair(w, ii(v, u)));
      }
      sort(EdgeList.begin(), EdgeList.end()); 
      E = EdgeList.size();
      //long minimum = 0;
      UnionFind UF(qt_vertex);
      vector<long> weights;
      for (int j = 0; j < E; j++) {                   
       pair<long, ii> front = EdgeList[j];
       if (!UF.isSameSet(front.second.first, front.second.second)) { 
         //minimum += front.first;
         UF.unionSet(front.second.first, front.second.second);  
       }else weights.push_back(front.first);
      }
      if (weights.size()>0){
       sort(weights.begin(), weights.end());
       for (int i =0; i < weights.size(); i++){
        if (i!=0) printf(" %ld", weights[i]);
        else printf("%ld", weights[i]);
       }
       printf("\n");
      }else
       printf("forest\n");
  }
  
  return 0;
}
