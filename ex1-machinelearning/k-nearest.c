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

void swap (AlunoQ *a, AlunoQ *b) {
    AlunoQ temp = *a;
    *a = *b;
    *b = temp;
}

int partition (AlunoQ alunosQ[], int low, int high) {

    double pivot = alunosQ[high].distanceTest;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {

        if (alunosQ[j].distanceTest < pivot) {
            i++;
            swap(&alunosQ[i], &alunosQ[j]);
        }
    }

    swap(&alunosQ[i + 1], &alunosQ[high]);

    return (i + 1);
}

void quicksort(AlunoQ alunosQ[], int low, int high) {

    if (low < high) {

        int pi = partition(alunosQ, low, high);

        quicksort(alunosQ, low, pi - 1);
        quicksort(alunosQ, pi + 1, high);
    }
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

        AlunoQ* alunosQ = malloc(sizeof(AlunoQ) * num_amostras_treinamento);

        for (int j = 0; j < num_amostras_treinamento; j++) {

            alunosQ[j].rotulo = alumnis[j].rotulo;    
            
            double distance = sqrt (pow ((alumni_teste->nota_media - alumnis[j].nota_media), 2) + 
                                    pow ((alumni_teste->horas_estudo - alumnis[j].horas_estudo), 2));

            alunosQ[j].distanceTest = distance;
        }

        quicksort (alunosQ, 0, num_amostras_treinamento - 1);

        int qntd_aprovados = 0, qntd_reprovados = 0;

        for (int j = 0; j < num_vizinhos; j++) {
            
            if (alunosQ[j].rotulo == 0)
                qntd_reprovados++;
            else
                qntd_aprovados++;
        }

        free (alunosQ);

        if (qntd_aprovados > qntd_reprovados)
            printf ("Aluno %d: (%.2lf, %.2lf) = Aprovado\n", i, alumni_teste->nota_media, alumni_teste->horas_estudo);

        else
            printf ("Aluno %d: (%.2lf, %.2lf) = Reprovado\n", i, alumni_teste->nota_media, alumni_teste->horas_estudo);

        free (alumni_teste);
        i++;
    }

    free (alumnis);

    return 0;
}