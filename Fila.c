#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"Fila.h"

// Aloca a estrutura principal e prepara a fila para uso
Fila* criarFila(){
    Fila* li = (Fila*)malloc(sizeof(Fila));
    if(li == NULL)  return NULL;
    li->inicio = NULL;
    li->final = NULL;
    li->contador = 0;   // Inicializa o contador de senhas globais
    return li;
}

// Gerencia a entrada de novos pacientes com base na prioridade
int inserirPaciente(Fila* li){
    if (li == NULL) return 0; 
    No* Novo = (No*)malloc(sizeof(No));
    if(Novo == NULL)    return 0;
    printf("Digite o nome do Cliente: ");
    setbuf(stdin,NULL);
    fgets(Novo->nome,100,stdin);
    Novo->nome[strcspn(Novo->nome,"\n")] = 0;          
    // Valida se a prioridade digitada é válida (1 ou 2)
    Novo->hora_chegada = time(NULL);
    do {
        printf("Digite a prioridade (1-Normal, 2-Prioritario): ");
        if (scanf("%d", &Novo->prioridade) != 1) {
            setbuf(stdin, NULL);
            Novo->prioridade = 0;
        }
    } 
    while(Novo->prioridade < 1 || Novo->prioridade > 2);
    // Caso 1: A fila está vazia
    if(li->inicio == NULL){     
        Novo->prox = NULL;
        li->inicio = Novo;
        li->final = Novo;
    } 
    // Caso 2: Novo é prioritário e quem está na frente é normal (fura a fila)
    else if(Novo->prioridade > li->inicio->prioridade){
        Novo->prox = li->inicio;
        li->inicio = Novo;
    }
    // Caso 3: Novo é prioritário e deve entrar após outros prioritários
    else if(Novo->prioridade == 2){
        No* atual = li->inicio;
        while(atual->prox != NULL && atual->prox->prioridade == 2){
            atual = atual->prox;
        }
        Novo->prox = atual->prox;
        atual->prox = Novo;
        if(Novo->prox == NULL)  li->final = Novo;
    }
    // Caso 4: Paciente normal (sempre entra no final da fila
    else{
        li->final->prox = Novo;
        li->final = Novo;
    }
    // Gera a senha usando o contador global da fila
    li->contador++;
    Novo->senha = li->contador;
    return 1;
}

// Remove o primeiro da fila 
int atendimento(Fila* li){
    if(li == NULL || li->inicio == NULL){
        printf("A fila esta vazia!\n");
        return 0;
    }

    No* atual = li->inicio;
    No* anterior = NULL;
    No* alvo = NULL;
    No* antAlvo = NULL;

    time_t agora = time(NULL);
    int limite_espera = 900; // Paciente comum fura fila após 15 segundos de espera

    // Percorre a fila para ver se alguém (mesmo sem prioridade) excedeu o tempo limite
    while(atual != NULL){
        double segundos_espera = difftime(agora, atual->hora_chegada);
        if(segundos_espera >= limite_espera){
            antAlvo = anterior;
            alvo = atual;
            break; 
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se ninguém estourou o tempo, o alvo é o primeiro da fila (respeitando a prioridade da inserção)
    if(alvo == NULL){
        alvo = li->inicio;
        antAlvo = NULL;
    }

    // Lógica para remover o nó escolhido (alvo) da lista encadeada
    if(antAlvo == NULL){
        // O alvo é o primeiro da fila
        li->inicio = alvo->prox;
    } else {
        // O alvo está no meio ou no fim
        antAlvo->prox = alvo->prox;
    }

    // Ajusta o ponteiro final se o alvo for o último elemento
    if(alvo == li->final){
        li->final = antAlvo;
    }

    // Se a fila ficou vazia após a remoção
    if(li->inicio == NULL){
        li->final = NULL;
    }

    // Exibe os dados do atendimento e libera a memória
    double total_espera = difftime(agora, alvo->hora_chegada);
    printf("Atendimento: %s (Senha: %d) - Esperou %.0f segundos\n", 
            alvo->nome, alvo->senha, total_espera);
    
    free(alvo);
    return 1;
}

void imprimirFila(Fila* li){
    if(li == NULL || li->inicio == NULL){
        printf("Fila vazia\n");
        return ;
    }
    No* atual = li->inicio;
    printf("                       Fila dos pacientes                       \n");
    do{
        printf("----------------------------------------------------------------\n");
        printf("Nome do paciente: %s\n",atual->nome);
        printf("Senha: %d\n",atual->senha);
        printf("Prioridade: %d\n",atual->prioridade);
        printf("----------------------------------------------------------------\n");
        atual = atual->prox;
    }
    while(atual != NULL);
    printf("Fila imprimida com sucesso!\n");
    return;
}
// Libera todos os nós da lista e depois a estrutura da fila
void liberarMemoria(Fila* li){
    No* atual = li->inicio;
    while(atual != NULL){
        No* aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(li);
    return ;
}
// Limpa o lixo de memória do buffer do teclado para evitar erros de leitura
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}