#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#include <ctype.h>

#define MAX 110
#define INF 1e9

using namespace std;

typedef pair<int, int> ii;

bool visited[MAX][MAX];
int row, ans, mask;
char grid[MAX][MAX];

int pos(char c) {
        return tolower(c) - 'a';
}

bool check(char c) {
        if(islower(c)) 
          return !((1 << pos(c)) & mask);
        return ((1 << pos(c)) & mask);
}

bool inside(int l, int c){
	if (l>=0 && l<row && c>=0 && c<row) return true;
	return false;
}

bool able(ii v){ 
	int l = v.first, c = v.second;
	if (inside(l, c)){
		char s = grid[l][c];
		return check(s);
	}
	return false;
}


void bfs(){
	memset(visited, 0, sizeof visited);
	queue< pair <int,ii> > q;
	ii start(0, 0);
	if (!able(start)) return;
	q.push(make_pair(0,start));
	while(!q.empty()){
		pair<int, ii> new_vertex = q.front(); q.pop();
		ii cords = new_vertex.second;
		int l = cords.first, c = cords.second, count = new_vertex.first;
		if (able(cords) && !visited[l][c]){
			if (l == row-1 && c == row-1) ans = min(ans, count+1);
			else{
				if (inside(l-1, c)) q.push(make_pair(count+1, ii(l-1, c) ) );
				if (inside(l+1, c)) q.push(make_pair(count+1, ii(l+1, c) ) );
				if (inside(l, c+1)) q.push(make_pair(count+1, ii(l, c+1) ) );
				if (inside(l, c-1)) q.push(make_pair(count+1, ii(l, c-1) ) );
				visited[l][c]=1;
			}
		}
	}
}

void solve() {
        for(int mask2 = 0; mask2 < (1 << 10) -1 ; mask2++){ 
                mask = mask2;
                bfs();
        }
        
}


int main(){
	while(scanf("%d", &row) != EOF){
		for (int i = 0; i < row; i++)
			scanf("%s", grid[i]);
		ans = INF;
		solve();
		if (ans == INF) printf("-1\n");
		else printf("%d\n", ans);
	}
	return 0;
}
