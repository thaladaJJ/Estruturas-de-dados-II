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

void sortByDistances (AlunoQ alunosQ[], int n) {
    
    int i, j;
    AlunoQ key;

    for (i = 1; i < n; i++) {

        key = alunosQ[i];
        j = i - 1;

        while (j >= 0 && alunosQ[j].distanceTest > key.distanceTest) {
            alunosQ[j + 1] = alunosQ[j];
            j = j - 1;
        }

        alunosQ[j + 1] = key;
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

        AlunoQ alunosQ [num_amostras_treinamento];

        for (int j = 0; j < num_amostras_treinamento; j++) {

            alunosQ[j].rotulo = alumnis[j].rotulo;    
            
            double distance = sqrt (pow ((alumni_teste->nota_media - alumnis[j].nota_media), 2) + 
                                    pow ((alumni_teste->horas_estudo - alumnis[j].horas_estudo), 2));

            alunosQ[j].distanceTest = distance;
        }

        sortByDistances (alunosQ, num_amostras_treinamento);

        int qntd_aprovados = 0, qntd_reprovados = 0;

        for (int j = 0; j < num_vizinhos; j++) {
            
            if (alunosQ[j].rotulo == 0)
                qntd_reprovados++;
            else
                qntd_aprovados++;
        }

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