
//CodeChef  - Chef and Digit Jumps

#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;

#define MAX 100010
int n, res;
char v[MAX];

int dp[MAX];
int best[10];

 int num(char c){
    return ((c - '0') % 48);
 }

int main(){
	scanf("%s", v);
    n = strlen(v);
    res = 0;
    int times = 9;

    for (int i = 0; i < 10; i++)
    	 best[i] = 100;

    for (int i = 0; i < n; i++)
    	 dp[i] = 100;
   
    dp[n-1] = 0; best[num(v[n-1])] = 0;
    
    while(times--)
    for (int i = n - 2; i >= 0; i--){
     	 int atual = num(v[i]);
    
     	 dp[i] = min(dp[i], dp[i+1] + 1);
         dp[i] = min(dp[i], dp[abs(i-1)] + 1);
         dp[i]   = min(best[atual] + 1, dp[i]);
        
         if (dp[i] < best[atual]) best[atual] = dp[i];
    }

    printf("%d", dp[0]);
	return 0;
}
