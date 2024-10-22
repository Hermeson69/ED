#include<stdio.h>

int main(){

    int N, total_soma, soma;

    scanf("%d", &N);

    int casas[N];

    for(int i = 0; i< N; i++){
        scanf("%d", &casas[i]);
    }

    scanf("%d", &total_soma);

    for(int i = 1; i<=N; i++){
        soma = casas[i-1] + casas[i];
        if(soma == total_soma){
            printf("\n%d %d", casas[i-1], casas[i] );
        }
    }
    return 0;
}

