#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Aluno {
    double nota_media;
    double horas_estudo;
    int rotulo;
} Aluno;

typedef struct AlunoQ {
    int index;
    double distanceTest;
} AlunoQ;

void swap (AlunoQ *a, AlunoQ *b) {
    AlunoQ temp = *a;
    *a = *b;
    *b = temp;
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

    AlunoQ* alunosQ = (AlunoQ*) malloc ((sizeof (AlunoQ) * num_vizinhos) + 1);

    Aluno* alumni_teste = (Aluno*) malloc (sizeof (Aluno));

    int i = 0;

    while (i < num_amostras_teste) {

        scanf ("%lf %lf", &alumni_teste->nota_media, &alumni_teste->horas_estudo);

        for (int j = 0; j < num_vizinhos; j++)
        alunosQ [j].distanceTest = INFINITY;

        for (int j = 0; j < num_amostras_treinamento; j++) {    
            
            double distance = sqrt (pow ((alumni_teste->nota_media - alumnis[j].nota_media), 2) + 
                                    pow ((alumni_teste->horas_estudo - alumnis[j].horas_estudo), 2));
            
            if (distance < alunosQ [num_vizinhos - 1].distanceTest) {
                
                AlunoQ novoAluno = {j, distance};
                alunosQ[num_vizinhos - 1] = novoAluno;
                
                for (int k = num_vizinhos - 1; k > 0 && alunosQ [k].distanceTest < alunosQ [k - 1].distanceTest; k--) {
                    swap(&alunosQ[k], &alunosQ[k - 1]);
                }

            }

        }

        int qntd_aprovados = 0, qntd_reprovados = 0;

        for (int j = 0; j < num_vizinhos; j++) {

            int index = alunosQ[j].index;
            
            if (alumnis[index].rotulo == 0)
                qntd_reprovados++;
            else
                qntd_aprovados++;
        }

        if (qntd_aprovados > qntd_reprovados)
            printf ("Aluno %d: (%.2lf, %.2lf) = Aprovado\n", i, alumni_teste->nota_media, alumni_teste->horas_estudo);

        else
            printf ("Aluno %d: (%.2lf, %.2lf) = Reprovado\n", i, alumni_teste->nota_media, alumni_teste->horas_estudo);

        i++;
    }

    free (alumni_teste);
    free (alunosQ);
    free (alumnis);

    return 0;
}