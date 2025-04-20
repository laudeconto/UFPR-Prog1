/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h> 
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main (){
  struct racional r1, r2, soma, subtracao, multiplicacao, divisao;
    
  int max, n, i;

    // Leitura do valor n (0 < n < 100)
    do {
        scanf("%d", &n);
    } while (n < 0 || n > 100);

    // Leitura do valor max (0 < max < 30)
    do {
        scanf("%d", &max);
    } while (max < 0 || max > 30);

  srand (0); /* use assim, com zero */
  // Iniciar a semente do gerador de números aleatórios

    // Loop principal para gerar e operar com os racionais
    for (i = 1; i <= n; i++) {
        printf("%d: ", i);

        // Gera os valores para os racionais
        r1 = sorteia_r((-1 * max), max);  // Sorteia racionais dentro do intervalo [-max, max]
        r2 = sorteia_r((-1 * max), max);

        // Imprime os dois racionais gerados
        imprime_r(r1); 
        imprime_r(r2);

        // Verifica se ambos racionais são válidos
        if (!valido_r(r1) || !valido_r(r2)) {
            printf(" NUMERO INVALIDO\n");
            return 1;
        }

        // Operações: soma, subtração, multiplicação, divisão
        soma = soma_r(r1, r2);
        subtracao = subtrai_r(r1, r2);
        multiplicacao = multiplica_r(r1, r2);

        // Verificação de divisão inválida (denominador de r2 não pode ser 0)
        if (r2.num == 0) {
            printf(" DIVISAO INVALIDA\n");
            return 1;
        }
        divisao = divide_r(r1, r2);

        // Imprime as operações realizadas
        imprime_r(soma);
        imprime_r(subtracao);
        imprime_r(multiplicacao);
        imprime_r(divisao);

        // Mudar de linha ao final de cada iteração
        printf("\n");
    }

    return 0;
}