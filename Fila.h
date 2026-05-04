#ifndef FILA_H_
#define FILA_H_
#include <time.h>

struct cliente{
    char nome[100];
    int senha;
    int prioridade;
    time_t hora_chegada;
    struct cliente* prox;
};
typedef struct cliente No;

struct fila{
    No* inicio;
    No* final;
    int contador;
};
typedef struct fila Fila;

Fila* criarFila();
int inserirPaciente(Fila* li);
int atendimento(Fila* li);
void imprimirFila(Fila* li);
void liberarMemoria(Fila* li);
void limparBuffer();

#endif
