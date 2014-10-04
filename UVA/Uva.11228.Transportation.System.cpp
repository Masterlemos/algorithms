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

ii cords[MAX];
int V, r;

bool isSameState(double d){
 return (d <= (double) r);
}

double dist(ii a, ii b){
 return sqrt(pow(a.first-b.first, 2) + pow(a.second-b.second, 2));
}

int main() {
  int E, cases;
  scanf("%d", &cases);
  for (int i = 1; i <= cases; i++){
  
  scanf("%d %d", &V, &r);

  vector< pair<double, ii> > EdgeList;
  for (int j = 0; j < V; j++){
   scanf("%d %d", &cords[j].first, &cords[j].second);
   for (int k = 0; k < j; k++){
    double w = dist(cords[j], cords[k]); 
    EdgeList.push_back(make_pair(w, ii(j, k)));
   }
  }
   sort(EdgeList.begin(), EdgeList.end()); 
   E = EdgeList.size();
   double rail = 0, road = 0;
   int qt_states=V;
   UnionFind UF(V);
   for (int j = 0; j < E; j++) {                   
    pair<double, ii> front = EdgeList[j];
    if (!UF.isSameSet(front.second.first, front.second.second)) { 
      if (isSameState(front.first)){ road += front.first; qt_states--;}
      else rail += front.first;
      UF.unionSet(front.second.first, front.second.second);  
    }
   }
   printf("Case #%d: %d %d %d\n", i, qt_states, (int)round(road), (int)round(rail));
  }
  return 0;
}
