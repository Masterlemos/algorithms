#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
#define MAX 1010
char matrix[MAX][MAX];
bool visited[MAX][MAX];

int ans, r, c;

int sumdir(int dir[]){
 
 int p = 0, idx=0;
 for (int i=0;i<5;i++)
  if (dir[i]>p){ idx = i; p = dir[i];}
 dir[idx] = 0;
 idx = 0;
 for (int i=0;i<5;i++)
  idx = max(idx, dir[i]);
 return p+idx;
}

int dfs(int rr, int cc, int count){

 if (!visited[rr][cc]){
  visited[rr][cc]=1;
  int dir[] = {0,0,0,0,0};
  int path = 0;
  if (rr > 0 && matrix[rr-1][cc]=='.')
   dir[0] = dfs(rr-1, cc, count+1);
  path = max(path, dir[0]);
  
  if (rr < r-1 && matrix[rr+1][cc] == '.')
   dir[1] = dfs(rr+1, cc, count+1);
  path = max(path, dir[1]);
  
  if (cc > 0 && matrix[rr][cc-1] == '.')
   dir[2] = dfs(rr, cc-1, count+1);
  path = max(path, dir[2]);
     
  if (cc < c-1 && matrix[rr][cc+1] == '.')
   dir[3] = dfs(rr, cc+1, count+1);
  path = max(path, dir[3]);
     
  dir[4] = count;
  int sdir = sumdir(dir);
  ans = max(ans, sdir); 
  return path+1;
 }else return 0;
}

int main(){
 int cases;
 scanf("%d",&cases);
 while(cases--){
  scanf("%d %d", &c, &r);
  memset(visited, 0, sizeof visited);
  ans = 0;
  for (int i = 0; i < r; i++)
   scanf("%s", matrix[i]);

  for (int i=0; i<r; i++)
   for (int j=0;j<c;j++)
    if (matrix[i][j] == '.') dfs(i, j, 0);
  printf("Maximum rope length is %d.\n",ans);  
 }
 return 0;
}
