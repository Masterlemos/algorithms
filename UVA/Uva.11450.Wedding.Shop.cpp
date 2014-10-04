#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;

int classes[21][30];
int gasto[2][210];

int main()
{
   int cases, m, c, k;
   scanf("%d", &cases);
   while(cases--){
    scanf("%d %d", &m, &c);
    
    memset(classes, 0, sizeof classes);
    memset(gasto, -1, sizeof gasto);
    
    for (int i = 0; i < c; i++){
        scanf("%d", &k);
        classes[i][0] = k;
        for (int j = 1; j <= k; j++){
          scanf("%d", &classes[i][j]);
        }
    }

    for (int i=1; i <= classes[0][0]; i++){
      int g = m - classes[0][i];
      if (g>=0){
       gasto[0][g] = 0;
      }
    }
    int ant = 1;
    int atu = 0;
    for (int cla =1; cla < c; cla++){
        ant = !ant;
        atu = !atu;
        for (int peca =1; peca <= classes[cla][0]; peca++){
            for (int valor =0; valor<=m; valor++){
                if (gasto[ant][valor] == cla-1){
                    int g = valor - classes[cla][peca];
                    if (g >=0){
                        gasto[atu][g] = cla;
                    }
                }
            }
        }
    }
    
    int menor = 301;
    bool ok =false;
    for (int i=0; i<=m; i++){
        if (gasto[atu][i] == c-1){
         ok = true;
         menor = min(menor, i);
        }
    }
    if (ok)
     printf("%d\n", m-menor);
    else printf("no solution\n"); 
    
   }
   
   return 0;
}
