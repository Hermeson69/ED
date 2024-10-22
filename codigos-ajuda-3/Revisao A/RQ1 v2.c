#include<stdio.h>

int main(){

    int N, total_soma, soma;

    scanf("%d", &N);

    int casas[N];

    for(int i = 0; i< N; i++){
        scanf("%d", &casas[i]);
    }

    scanf("%d", &total_soma);

    for(int i = 0; i< N; i++){
       
       for (int j = i + 1; j < N; j++)
       {
            if (casas[i] + casas[j] == total_soma)
            {
                printf("%d %d", casas[i], casas[j]);
                return 0;
            }
        
       }
       
    }
    return 0;
}

