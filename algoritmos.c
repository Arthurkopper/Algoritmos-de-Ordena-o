#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crescente(int *vet1, int tamanho); // Responsável por deixar o vetor ordenado em ordem crescente;
void decrescente(int *vet1, int tamanho); // Responsável por deixar o vetor ordenado em ordem decrescente;
void imprimeVetor(int *vet1, int tamanho); // Responsável por imprimir o vetor;
void aleatorio(int *vet1, int min, int max, int tamanho); // Responsável por gerar um vetor de valores aleatórios;
void selectionSort(int *vet1, int tamanho);
void bogoSort(int *vet1, int tamanho);
void radixSort(int *vet1, int tamanho);

int main(void){

    int tamanho = 10, *vet1;
    srand(time(NULL));
    clock_t time;
    vet1 = calloc(tamanho, sizeof(int));
    
    aleatorio(vet1, -1000, 1000, tamanho); //Responsável por criar um vetor aleatorio;
    time = clock();
    selectionSort(vet1, tamanho); //chamada do primeiro algoritmo de ordenaçao;
    time = clock() - time;
    printf("\nTempo de execucao do algoritmo Selection Sort: %.4lf ms\n\n", ((double) time) / (CLOCKS_PER_SEC / 1000));
    
    aleatorio(vet1, -1000, 1000, tamanho); //deixa o vetor aleatorio denovo;
    time = clock();
    bogoSort(vet1, tamanho); //chamada do segundo algoritmo de ordenaçao;
    time = clock() - time;   
    printf("Tempo de execucao do algoritmo Bogo Sort: %.4lf ms\n\n", ((double) time) / (CLOCKS_PER_SEC / 1000));

    aleatorio(vet1, -1000, 1000, tamanho); //deixa o vetor aleatorio denovo;
    time = clock();
    radixSort(vet1, tamanho); //chamada do terceiro algoritmo de ordenaçao;
    time = clock() - time;
    printf("Tempo de execucao do algoritmo Radix Sort: %.4lf ms\n", ((double) time) / (CLOCKS_PER_SEC / 1000));
    
    free(vet1);
    return EXIT_SUCCESS;
}

void imprimeVetor(int *vet1, int tamanho){
    printf("Vetor antes do algoritmo: ");
    for(int i = 0; i < tamanho; i++)
        printf("%d ", vet1[i]); // printa o vetor;
    printf("\n");
}

void aleatorio(int *vet1, int min, int max, int tamanho){
    for(int i = 0; i < tamanho; i++)
        vet1[i] = -(rand() % min) + (rand() % max); //gera valores aleatorios para o vetor;
}

void selectionSort(int *vet1, int tamanho){
    int menor, troca; 
    for(int i = 0; i < tamanho; i++){
        menor = i; //Primeiro definimos o menor igual ao i;
        for(int j = i+1; j < tamanho; j++){
            if(vet1[menor] > vet1[j]) {menor = j;} //Se o vet1[menor] for maior que o proximo conseguentemente, o menor acabar tendo o indice
                                                  // do j, que servira futuramente para a troca de posicoes do maior com o menor.
        }
        troca = vet1[i];   // Salvamos o valor do que será trocado para nao perde-lo.
        vet1[i] = vet1[menor]; // Trocamos o valor do maior com o menor se houver menor, se nao houver continua o mesmo valor ("menor=i" inicial).
        vet1[menor] = troca; // E onde era o menor numero, agora e trocado pelo maior, se houver mudança.
    }
}

void bogoSort(int *vet1, int tamanho){
    int aleatorio=0, troca=0, final = 2, teste = 1;
    while(final > 1){
        teste = 0;
        for(int i = 0; i < tamanho; i++){
            aleatorio = (rand() % tamanho);
            troca = vet1[i]; //salva o valor do indice i do vetor;
            vet1[i] = vet1[aleatorio]; //troca o valor do vetor[i] pelo vetor de indice aleatorio;
            vet1[aleatorio] = troca; // e por fim troca o vetor inicial que foi trocado pelo lugar do aleatorio que tambem foi mudado;
        }
        for(int i = 1; i < tamanho; i++)
            if(vet1[i - 1] > vet1[i]) teste++; //Se o valor anterior do vetor for maior que o proximo, entao executa denovo o bogoSort para deixar em ordem crescente e ordenado;
        if (teste == 0) final--;
        }
}

void radixSort(int *vet1, int tamanho) {
    int maior = vet1[0], divisor = 1, troca[tamanho], negativo = 0, positivo = 0;
    int vetorAuxiliar[10];

    for(int i = 0; i < tamanho; i++)
        if(vet1[i] > maior) maior = vet1[i]; // Serve para achar o maior valor do vetor;
    
    for(int i = 0; i < tamanho; i++)
        if(vet1[i] >= 0) positivo++; // Nesse for é utilizado uma técnica para descobrir quantos números negativos e positivos o vetor total possui
        else negativo++;             // pois diferente de alguns algoritmos, o radix possui problemas quando lidado com número negativos, e por isso
                                     // precisei separa-los para resolver;
    
    int positivos[positivo], negativos[negativo]; // Logo após criei os vetores para os positivos e negativos, com seu tamanho ja definido anteriormente;

    for(int i = 0, j = 0, k = 0; i < tamanho; i++)
        if(vet1[i] >= 0) positivos[j++] = vet1[i]; // Aqui eu percorro o vetor total e vou salvando quais sao positivos no vetor positivo;
        else negativos[k++] = vet1[i];             // e a mesma coisa para os negativos;
      
    int troca2[negativo]; // Vetor que sera utilizado futuramente para os valores negativos;

    while(maior/divisor > 0){   // Aqui e feito a ordenação para os numeros POSITIVOS;
        for(int i = 0; i < 10; i++){
            vetorAuxiliar[i] = 0; // Zera todos os valores do vetor auxiliar;
        }
        for(int i = 0; i < positivo; i++){
            vetorAuxiliar[(positivos[i] / divisor) % 10]++; // Nesse caso ele pega o ultimo digito do numero, exemplo 59, ele divide 59 por 1(inicial)                                               
        }                                                   // e faz o resto da divisao por 10, que vai dar o numero 9;

        for(int i = 1; i < 10; i++) vetorAuxiliar[i] += vetorAuxiliar[i-1]; // Aqui é realizado o somatorio dos valor atual com o anterior;
        
        for (int i = positivo - 1; i >= 0; i--)
    	    troca[--vetorAuxiliar[(positivos[i] / divisor) % 10]] = positivos[i]; // Nesse for e realizado a ordenaçao dos numeros menores para os maiores
    	
        for (int i = 0; i < positivo; i++)
    	    positivos[i] = troca[i]; //Salva o valor obtido do vetor teste no vetor original, pois se ainda nao for concluido totalmente a ordenaçao
                                //ele vai continuar na ordenaçao atual;
        
        divisor *=10;
    }

    if(negativo > 0){ //Se houver algum valor no vetor negativo;
        int divisor = 1, menor = negativos[0];
        for(int i = 0; i < negativo; i++)
            if(negativos[i] < menor) menor = negativos[i]; // Pega o menor valor

        for(int i = 0; i < negativo; i++)
            negativos[i] *= -1; // Multiplica por -1, para deixar eles positivos, e eu conseguir aproveitar o codigo anterior para achar o maior,
                                // e no final eu apenas irei inverter o vetor e multiplicar por -1 denovo para voltar a ser negativo, e assim ordenado;

        while(menor/divisor < 0){         // Repete todo o progresso novamente, dos positivos;
            for(int i = 0; i < 10; i++){
                vetorAuxiliar[i] = 0; 
            }
            for(int i = 0; i < negativo; i++){
                vetorAuxiliar[(negativos[i] / divisor) % 10]++; 
            }

            for(int i = 1; i < 10; i++) vetorAuxiliar[i] += vetorAuxiliar[i-1]; 
            
            for (int i = negativo - 1; i >= 0; i--)
                troca[--vetorAuxiliar[(negativos[i] / divisor) % 10]] = negativos[i]; 
            
            for (int i = 0; i < negativo; i++)
                negativos[i] = troca[i];
            
            divisor *=10;
        }
        for(int i = negativo - 1, j = 0; i >= 0; i--)
            troca2[j++] = negativos[i] * -1; // Aqui eu pego o vetor Troca2, e salvo neles o valor ao contrario, pois quanto maior o numero negativo
                                             // menor ele sera, e entao multiplico ele por -1 denovo para voltar a ser negativo
                                             // Ex: (8, 10, 112) vai ser > (-112, -10, -8), do jeito que deveria ser;
    }
    for(int i = 0, j = 0; i < tamanho; i++){ // Esse for serve para deixar em ordem o vetor original;
        if (negativo > 0) {      //Se tiver numero negativo salvo, logo eu pego os valores negativos primeiros, ja em ordem, e adiciono no vetor;
            vet1[i] = troca2[i]; 
            negativo--;
            }
        else vet1[i] = positivos[j++]; // Se acabar os negativos, ou nao houver mais, entao logo o resto sera o vetor organizado dos positivos;
    }

}

void crescente(int *vet1, int tamanho){ // Função responsavel por criar um vetor de ordem crescente;
    for(int i = 0; i < tamanho; i++)
        vet1[i] = i;
}

void decrescente(int *vet1, int tamanho){ // Função responsavel por criar um vetor de ordem decrescente;
    int j = 0;
    for(int i = tamanho; i >= 0; i--)
        vet1[j++] = i;
}