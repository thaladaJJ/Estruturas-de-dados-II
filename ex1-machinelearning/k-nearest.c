#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Aluno {
    double nota_media;
    double horas_estudo;
    int rotulo;
} Aluno;

typedef struct AlunoQ {
    int rotulo;
    double distanceTest;
} AlunoQ;

void sortByDistances (double distances[], int n) {
    

}

int main () {

    int num_amostras_treinamento;
    int num_amostras_teste;
    int num_vizinhos;

    scanf ("%d %d %d", &num_amostras_treinamento, &num_amostras_teste, &num_vizinhos);

    Aluno* alumnis = (Aluno*) malloc (sizeof (Aluno) * num_amostras_treinamento);
    
    if (!alumnis)   
        return 1;

    for (int i = 0; i < num_amostras_treinamento; i++) {
        scanf ("%lf %lf %d", &alumnis[i].nota_media, &alumnis[i].horas_estudo, &alumnis[i].rotulo);
    }

    int i = 0;
    while (i < num_amostras_teste) {

        Aluno* alumni_teste = (Aluno*) malloc (sizeof (Aluno));
        scanf ("%lf %lf", &alumni_teste->nota_media, &alumni_teste->horas_estudo);

        double distancesArray[num_amostras_treinamento];

        for (int j = 0; j < num_amostras_treinamento; j++) {    
            
            double distance = sqrt (pow ((alumni_teste->nota_media - alumnis[i].nota_media), 2) + 
                                    pow ((alumni_teste->horas_estudo - alumnis[i].horas_estudo), 2));

            distancesArray[j] = distance;
        }

        sortByDistances (distancesArray, num_amostras_treinamento);

        int qntd_aprovados = 0, qntd_reprovados = 0;

        for (int j = 0; j < num_vizinhos; j++) {

            

        }

        free (alumni_teste);
        i++;
    }
    

    free (alumnis);

    return 0;
}