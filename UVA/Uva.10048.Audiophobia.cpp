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
bool visited[MAX];
vector< ii > graph[MAX];
int dfs(int u, int v){
 visited[u] = 1;

 for (int i = 0; i<graph[u].size(); i++){
  int new_vertex = graph[u][i].second;
  if (!visited[new_vertex]){
   int weight = graph[u][i].first;
   if (v == new_vertex) return weight;
   int wDfs = dfs(new_vertex, v);
   if (wDfs != -1)
    return max(weight, wDfs);
  }
 }
 return -1;
}

void clear(){
 for (int i =0; i<=qt_vertex; i++) graph[i].clear();
}

int main() {
  int cases = 1, u,v,w,qt_queries,p=1;
  while (scanf("%d %d %d", &qt_vertex, &qt_edges, &qt_queries) && qt_vertex){
      if (p!=1) printf("\n");p=0;
      clear();
      vector< pair<int, ii> > EdgeList;  
      for (int i = 0; i < qt_edges; i++){
       scanf("%d %d %d", &u, &v, &w);
       EdgeList.push_back(make_pair(w, ii(u, v)));
      }
      sort(EdgeList.begin(), EdgeList.end());
      int E = EdgeList.size();
      UnionFind UF(qt_vertex+1);
      for (int j = 0; j < E; j++) {                   
       pair<double, ii> front = EdgeList[j];
       u = front.second.first;
       v = front.second.second;
       w = front.first;
       if (!UF.isSameSet(u, v)) { 
         graph[u].push_back(ii(w,v));
         graph[v].push_back(ii(w,u));
         UF.unionSet(u, v);  
       }
      }
      printf("Case #%d\n", cases++);
      for (int i = 0; i < qt_queries; i++){
       scanf("%d %d", &u, &v);
       memset(visited, 0, sizeof visited);
       int wdfs = dfs(u, v);
       if(wdfs != -1) printf("%d\n", wdfs);
       else printf("no path\n");
      }
  }
  
  return 0;
}
