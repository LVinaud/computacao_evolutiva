//minha primeira tentativa de criação de um algoritmo evolutivo-25/07/2023
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define tamanhopop 10
#define taxamutacao 1
#define ngeracoes 20

float mediafitness(int* vetor){
    float y = 0;
    for(int i = 0; i <tamanhopop; i++) {
        y+=vetor[i];
    }
    return y / tamanhopop;
}

int avalia(int a) {
    if(a > 500) {
        return 1000-a;
    }
    return a;
}

int main(void) {
    srand(time(NULL));
    
    int geracao = 1;
//inicializar população

int populacao[tamanhopop];
for(int i = 0; i < tamanhopop; i++) {
  if(rand() % 2 == 0) 
    populacao[i] = rand() % 1001;
  else 
    populacao[i] = -1 * (rand() % 1001);
}

int maiornota = 0;
while(geracao <= ngeracoes) {
//avaliar individuos

int notas[tamanhopop];

for(int i = 0; i < tamanhopop; i++) {
    notas[i] = avalia(populacao[i]);
}

// selecao

int indmaior;
for(int i = 0; i < tamanhopop; i++) {
    if(notas[i] > maiornota) {
            maiornota = notas[i];
            indmaior = i;
    }
}

// crossover 

for(int i = 0; i < tamanhopop; i++) {
    if(i==indmaior) {
        continue;
    }
    populacao[i] = (populacao[indmaior] + populacao[i])/2;
}

// mutacao(chernobyl)

for(int i = 0; i < tamanhopop; i++) {
    if(i == indmaior) {
        continue;
    }
    if(rand()%2==0){
        populacao[i] += taxamutacao;
    } else {
        populacao[i] -= taxamutacao;
    }
}

printf("A geração %d tem média %f e melhor valor %d\n", geracao, mediafitness(populacao), maiornota);
geracao++;
}
}
