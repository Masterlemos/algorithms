#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

using namespace std;

#define INF 1e9
#define MAX_V 3010
#define tipo long long
#define forr(i, b) for (int i = 0; i < b; ++i)
#define ford(i, a, b) for (int i = a; i <= b; ++i)
#define pb(i) push_back(i)

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<int, string> mis;
typedef map<string, int> msi;

int cases, s, t, qt_vertex, mf;
int res[MAX_V][MAX_V];
vi graph[MAX_V];

//particular
int nextParty, nextClub, nextPerson, first, qt_club;
char line[100];
mis club_int_str, party_int_str, person_int_str;
msi club_str_int, party_str_int, person_str_int;

//dinic
int work[MAX_V], dist[MAX_V];

void connect(int u, int v, int w){
 graph[u].pb(v);
 graph[v].pb(u);
 res[u][v] = w;
}


/*
 Dinic -> O(V^2E)
*/

int dinic_dfs(int u, int flow){
 if (u==t) return flow;
 for (int &i = work[u]; i < (int) graph[u].size(); i++){
  int v = graph[u][i];
  if (res[u][v] <= 0) continue;
  if (dist[v] == dist[u] + 1){
   int df = dinic_dfs(v, min(flow, res[u][v]) );
   if (df > 0){
    res[u][v] -= df; res[v][u] += df;
    return df;
   } 
  }
 }
 return 0;
}

bool dinic_bfs(){
  memset(dist, -1, sizeof dist);
  dist[s] = 0;
  queue<int> q; q.push(s);
  while(!q.empty()){
   int u = q.front(); q.pop();
   for (int i = 0; i < (int)graph[u].size(); i++){
    int v = graph[u][i];
    if (dist[v] < 0 && res[u][v]) dist[v] = dist[u] + 1, q.push(v);
   }
  }
  return dist[t] >= 0;  
}

int maxFlow(){
  int result = 0;
  while(dinic_bfs()){
   memset(work, 0, sizeof work);
   while (int delta = dinic_dfs(s, INF)) result += delta;
  }
  return result;
}
/*
 FIM
*/

//PARTICULAR

int half(int qt){
 if (qt==1) return 1;
 if (qt==2) return 1;
 if (qt%2) return qt/2;
 return qt/2-1;
}

//FIM PARTICULAR


//STANDARD
void init(){
 memset(res, 0, sizeof res);

 forr (i, MAX_V) graph[i].clear();

 s = 0;
 t = 1;
 nextPerson = 2;
 nextClub = 1002;
 nextParty = 2004;
 qt_club = 0;

 person_str_int.clear();
 person_int_str.clear();

 club_str_int.clear();
 club_int_str.clear();

 party_str_int.clear();
 party_int_str.clear();
}

void read(){
    int person_id, party_id, club_id;
   
	while(gets(line) != NULL){
 	 if (!line[0]) break;
     
 	 char *f = strtok(line, " ");
 	 string name(f);
 	 person_id = nextPerson++;
 	 
     person_str_int[name] = person_id;
     person_int_str[person_id] = name;
         
     f = strtok(NULL, " ");
     string party_name(f);
     party_id = party_str_int[party_name];
     if (party_id == NULL){
      party_id = nextParty++;
      party_str_int[party_name] = party_id;
      party_int_str[party_id] = party_name;
     }
     connect(person_id, party_id, 1);
     f = strtok(NULL, " ");
     while(f != NULL){
      string club_name(f);
      club_id = club_str_int[club_name];
      if (club_id == NULL){
       qt_club++;
       club_id = nextClub++;
       club_str_int[club_name] = club_id;
       club_int_str[club_id] = club_name;
       connect(s, club_id, 1);
      }
      connect(club_id, person_id, 1);
      f = strtok(NULL, " ");
     }
	}
	//connect parties
	ford (i, 2004, nextParty-1)
		connect(i, t, half(qt_club));
}

void solve(){
	mf = maxFlow();
}

void output(){
   if (!first) cout<<endl; first = 0;
   if (mf != qt_club) cout << "Impossible." <<endl; 
   else{
     forr(i, (int)graph[s].size()){
        int club = graph[s][i];
     	  forr (j, (int)graph[club].size()){
           int person = graph[club][j];
           if (!res[club][person]){
           	cout << person_int_str[person] << " " << club_int_str[club] << endl;
           	break;
           }
     	  }
     }
   }
}

//FIM STANDARD

int main(){
    first = 1;
    scanf("%d", &cases); getchar();
    getchar();
    while (cases--){
     init();
     read();
     solve();
     output();
    }
    return 0;
}
