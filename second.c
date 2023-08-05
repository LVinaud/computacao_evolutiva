//minha primeira tentativa de criação de um algoritmo evolutivo com taxa de mutacao variavel
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define tamanhopop 100
#define taxamutacaod 1
#define geracoes 40000

float mediafitness(float* vetor){
//media aritmetica da população
    float y = 0;
    for(int i = 0; i < tamanhopop; i++) {
        y += vetor[i];
    }
    return y / tamanhopop;
}

float avalia(float x) {
//função que avalia cada individuo de acordo com a função doida
  float y = (2*cos(0.039*x) + 5*sin(0.05*x) + 0.5*cos(0.01*x) + 10*sin(0.07*x) + 5*sin(0.1*x) + 5*sin(0.035*x))*10+500;
  return y;
}

int main(void) {
    srand(time(NULL));
    float taxamutacao = taxamutacaod;
    int geracao = 0;
    float notas[tamanhopop];
    float populacao[tamanhopop];
    float maiornota;
    float maioranterior;
    int indmaior;
    int maiorrepetido = 0;
//inicializar população

for(int i = 0; i < tamanhopop; i++) {
  if(rand()%2==0)
    populacao[i] = rand() % 10001;
  else {
    populacao[i] = -1*(rand() % 10001);
  }
}
//para inicializar a maiornota eu coloquei o valor como a nota do primeiro individuo(provavelmente será substituida logo na primeira geração, mas é preciso inicializar
maiornota = avalia(populacao[0]);
  
while(geracao < geracoes) {
  geracao++;
//avaliar individuos

for(int i = 0; i < tamanhopop; i++) {
    notas[i] = avalia(populacao[i]);
}
  

// selecao

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

// mutacao

  if(fabsf(maiornota-maioranterior) < 0.0001) {
    maiorrepetido++; // contador para quantas gerações tem o melhor repetido, se chegar em 50 gerações com o mesmo, a taxa de mutação dobra. 50 é para que dê tempo da média da população alcancar o melhor e fazer o ajuste fino
    if(maiorrepetido == 50) {
      taxamutacao *= 2;
      maiorrepetido = 0;
    }
  } else if (taxamutacao > taxamutacaod) {
    taxamutacao = taxamutacaod;
  }
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

  printf("A geração %d teve:\nMédia: %lf\nMelhor y: %lf\nTaxa de mutação: %lf\nMelhor x: %lf\n----------\n", geracao, mediafitness(notas), maiornota, taxamutacao, populacao[indmaior]);
  maioranterior = maiornota;
  }
}
