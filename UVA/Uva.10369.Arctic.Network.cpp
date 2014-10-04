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
int x[MAX], y[MAX];

double distance(int x, int y, int xx, int yy){
 return sqrt(pow(x-xx, 2) + pow(y-yy, 2));
}

int main() {
  int cases, sat;
  
  scanf("%d", &cases);
  
  while (cases--){
      vector< pair<double, ii> > EdgeList;  
      scanf("%d %d", &sat, &qt_vertex);
      for (int i =0; i<qt_vertex; i++){
       scanf("%d %d", &x[i], &y[i]);
       for (int j = 0; j < i; j++){
          double w = distance(x[i], y[i], x[j], y[j]);
          EdgeList.push_back(make_pair(w, ii(i, j)));
       }
      }
      sort(EdgeList.begin(), EdgeList.end()); 
      int E = EdgeList.size();
      UnionFind UF(qt_vertex);
      vector< pair<double, ii> > mst;
      for (int j = 0; j < E; j++) {                   
       pair<double, ii> front = EdgeList[j];
       if (!UF.isSameSet(front.second.first, front.second.second)) { 
         mst.push_back(front);
         UF.unionSet(front.second.first, front.second.second);  
       }
      }
      int s = mst.size()-1;
      double d = mst[s-(sat-1)].first;
      printf("%.2f\n", d);
  }
  
  return 0;
}
