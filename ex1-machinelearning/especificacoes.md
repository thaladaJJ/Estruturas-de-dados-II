### Para o problema deste laboratório, queremos que a máquina preveja se um dado aluno da escola, que ainda não prestou vestibular, passará ou não no mesmo, sabendo apenas sua nota média na escola e as horas de estudos semanais que ele se dedica. Por exemplo, suponha que a empresa colheu os seguintes dados de 30 alunos egressos para constituir nosso conjunto de treinamento, que são apresentados no plot abaixo:

![Gráfico do conjunto de treinamento](image.png)

### Suponha que desejamos saber se o aluno João passará no vestibular. Suas características (nota média, horas de estudos semanais) são, respectivamente: 5.5, 2.5. Ao plotar tais valores no mesmo gráfico, temos o seguinte:

![Valores de João no gráfico](image-1.png)

### Para predizer se João irá passar ou não no vestibular, baseado em nosso conjunto de treinamento, podemos assumir que João terá o rótulo do aluno com as características mais similares a ele. Desta maneira, ao analisar o gráfico, devemos selecionar a amostra/ponto mais próximo a João, como indicado abaixo. Como o aluno mais similar ao João não passou no vestibular, o sistema previu que João não passará no vestibular.

![Decisão do sistema](image-2.png)

### Entretanto, se ao invés de checar apenas o aluno mais similar, poderíamos checar os 3 alunos mais similares, atribuindo o rótulo mais frequente, ou seja, que mais vezes ocorreu. Neste caso, o sistema previu que João passará no vestibular, como mostrado no gráfico abaixo.

![3-nearest](image-3.png)

### Ao analisar a aluna Maria, cujas características são: 8.3 e 4.25, temos:

![alt text](image-4.png)


### Em ambos os casos, ao considerar apenas o aluno mais similar e os 3 mais similares, o sistema previu que Maria passará no vestibular. A técnica de classificação apresentada é chamada kNN (k-Nearest Neighbors). Dado uma amostra de teste q, o rótulo mais frequente das k amostras vizinhas mais próximas (mais similares) de q será o rótulo de q. A distância entre as amostras no espaço de características pode ser calculada utilizando a distância Euclidiana entre dois pontos, que, para o caso de apenas 2 características, resulta em:

d = sqrt ( (q1−p1)^2 + (q2−p2)^2 )

### Em que p = (p1,p2) é uma amostra de treinamento qualquer, e q = (q1,q2) é a amostra de teste analisada. As coordenadas p1, p2 correspondem, respectivamente, à nota média e às horas de estudos do aluno p. Idem para a amostra q.

### O número k de vizinhos é determinado pelo usuário. Para o caso de problemas de classificação com apenas 2 classes/rótulos, geralmente se escolhe um número ímpar, para evitar empates na atribuição do rótulo. Não há um número k mágico para resolver todos os problemas. O melhor valor de k varia de problema para problema, sendo encontra por meio de experimentação e avaliação de vários possíveis valores.


### Em resumo, o algoritmo kNN possui os seguintes passos: Dado a amostra de teste q a ser classificada:

> Compute a distância Euclidiana entre q e todas as amostras de treinamento;
> Ordene as amostras de treinamento, em ordem crescente, baseado nas distâncias;
> Atribua o rótulo mais frequente das k amostras mais próximas a q;

### Seu objetivo será desenvolver um sistema de classificação utilizando o algoritmo kNN.

> Especificação de entrada e saída
Entrada
A primeira linha corresponderá a 3 valores: o número de amostras de treinamento m, o número de amostras de teste n a serem classificadas e o valor de k.
As m linhas subsequentes contém as características e o rótulo de cada amostra do conjunto de treinamento.
As próximas n linhas consistem das características das amostras de teste a serem classificadas.

### Saída: para cada amostra de teste, o programa deverá exibir a seguinte mensagem:
> Aluno índice_amostra: (nota_media, horas_de_estudo) = resultado_previsto

Exemplos

Entrada
10 2 3
1.00 0.50 0
1.50 0.75 0
2.00 0.00 0
2.50 1.00 0
3.00 1.25 0
5.00 10.00 1
5.50 8.88 1
6.00 3.75 1
6.00 7.50 1
6.50 8.00 1
2.0 1.0
6.0 8.5	

Saída
Aluno 0: (2.00, 1.00) = Reprovado
Aluno 1: (6.00, 8.50) = Aprovado