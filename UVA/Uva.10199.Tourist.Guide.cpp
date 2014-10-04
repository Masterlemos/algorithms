#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define WHITE -1
#define MAX 500

int  rootChildren, qt_locals, qt_routes, dfsRoot, dfsCount, dfs_num[MAX], dfs_low[MAX], dfs_parent[MAX];
map<string, int> locals;
map<int, string> localsInt;
vector<int> graph[MAX];
vector<string> art_vertex;
bool art[MAX];

void clear(){
	dfsCount = rootChildren = 0;
	for (int i = 0; i < qt_locals; i++){
		dfs_num[i] = WHITE;
		graph[i].clear();
		art[i] = 0;
	}
	art_vertex.clear();
	locals.clear(); localsInt.clear();
}

void artic(int atual){
	dfs_num[atual] = dfs_low[atual] = dfsCount++;
	for (int i = 0; i < graph[atual].size(); i++){
		int novo = graph[atual][i];
		if (dfs_num[novo] == WHITE){
		    dfs_parent[novo] = atual;
		    if (atual == dfsRoot) rootChildren++;

		    artic(novo);

		    if (dfs_low[novo] >= dfs_num[atual])
 		     art[atual]  = 1;
		    
		    dfs_low[atual] = min(dfs_low[atual], dfs_low[novo]);
		}else if (dfs_parent[atual] != novo) dfs_low[atual] = min(dfs_low[atual], dfs_num[novo]);
	}
}

int main(){
    string local;
    int city = 1;
    int p=1;
    while(cin>>qt_locals && qt_locals){
       clear();
       for (int i = 0; i < qt_locals; i++){
          cin>>local;
          locals[local] = i;
          localsInt[i] = local;
       }
       
       cin >> qt_routes;
       string ra,rb;
       for (int i =0; i < qt_routes; i++){
       	  cin >> ra >> rb;
       	  
          graph[locals[ra]].push_back(locals[rb]);
          graph[locals[rb]].push_back(locals[ra]);
       }
       for (int i =0; i < qt_locals; i++)
       	 if (dfs_num[i] == WHITE){
       	  dfsRoot = i;
       	  rootChildren=0;
          artic(i);
          art[i] = (rootChildren > 1);
         }
         
       for (int i =0; i<qt_locals; i++)
        if (art[i])
         art_vertex.push_back(localsInt[i]);
       if(!p)
        cout<<endl;
       p=0; 
       sort(art_vertex.begin(), art_vertex.end());
       cout<<"City map #"<<city++<<": "<<art_vertex.size()<<" camera(s) found\n";
       for (int i = 0; i < art_vertex.size() ; i++)
          cout << art_vertex[i] << endl;
    }
    return 0;
}
