// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// Estrutura de um nodo da fila
struct fpnodo_t {
  void *item;
  int tipo;
  int prio;
  struct fpnodo_t *prox;
};

// Estrutura da fila de prioridades
struct fprio_t {
  struct fpnodo_t *ini;
  int tamanho;
};

//------------------------------------------------------------------------------
// Cria uma fila vazia
struct fprio_t *fprio_cria() {
  struct fprio_t *f = malloc(sizeof(struct fprio_t));
  if (!f) return NULL;
  f->ini = NULL;
  f->tamanho = 0;
  return f;
}

//------------------------------------------------------------------------------
// Libera toda a memória da fila e dos itens
struct fprio_t *fprio_destroi(struct fprio_t *f) {
  if (!f) return NULL;

  struct fpnodo_t *atual = f->ini;
  while (atual) {
    struct fpnodo_t *prox = atual->prox;
    free(atual->item); // Libera o conteúdo apontado
    free(atual);       // Libera o nodo
    atual = prox;
  }

  free(f);
  return NULL;
}

//------------------------------------------------------------------------------
// Insere o item mantendo a ordem de prioridades respeitando a FIFO
int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio) {
  if (!f || !item) return -1;

  // Verifica se o item já existe (mesmo ponteiro)
  struct fpnodo_t *temp = f->ini;
  while (temp) {
    if (temp->item == item) 
      return -1; // Item já existe
    temp = temp->prox;
  }

  struct fpnodo_t *novo = malloc(sizeof(struct fpnodo_t));
  if (!novo) return -1;

  novo->item = item;
  novo->tipo = tipo;
  novo->prio = prio;
  novo->prox = NULL;

  // Inserção na lista encadeada ordenada por prioridade
  struct fpnodo_t **pp = &f->ini;
  while (*pp && ((*pp)->prio < prio || ((*pp)->prio == prio))) {
    pp = &((*pp)->prox);
  }

  novo->prox = *pp;
  *pp = novo;

  f->tamanho++;
  return f->tamanho;
}

//------------------------------------------------------------------------------
// Retira o primeiro item da fila
void *fprio_retira(struct fprio_t *f, int *tipo, int *prio) {
  if (!f || !tipo || !prio || f->tamanho == 0) return NULL;

  struct fpnodo_t *ret = f->ini;
  f->ini = ret->prox;

  *tipo = ret->tipo;
  *prio = ret->prio;
  void *conteudo = ret->item;
  free(ret);

  f->tamanho--;
  return conteudo;
}

//------------------------------------------------------------------------------
// Informa o número de itens na fila
int fprio_tamanho(struct fprio_t *f) {
  if (!f) return -1;
  return f->tamanho;
}

//------------------------------------------------------------------------------
// Imprime o conteúdo da fila
void fprio_imprime(struct fprio_t *f) {
  if (!f) return;

  struct fpnodo_t *p = f->ini;
  while (p) {
    printf("(%d %d)", p->tipo, p->prio);
    if (p->prox) printf(" ");
    p = p->prox;
  }
}
