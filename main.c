#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int main() {
    Fila* fila = criarFila();
    int escolha;
    do {
        printf("\n-----------------------    Sistema De Fila    ----------------------\n");
        printf("1 - Inserir paciente na fila\n");
        printf("2 - Atender proximo paciente\n");
        printf("3 - Imprimir fila completa\n");
        printf("0 - Sair do sistema\n");
        printf("-----------------------------------------------------------------------\n");
        printf("Escolha qual opcao: ");

        // Validação da entrada do menu
        if (scanf("%d", &escolha) != 1) {
            printf("Entrada invalida! Digite apenas o numero da opcao!\n");
            limparBuffer(); // Remove as letras do buffer
            escolha = -1;   // Seta valor neutro para repetir o loop
            continue;
        }
        // Limpa o '\n' que sobra após o número ser lido
        limparBuffer(); 
        switch (escolha) {
            case 1:
                if (inserirPaciente(fila)) {
                    printf("Paciente inserido com sucesso!\n");
                } else {
                    printf("Falha ao inserir paciente.\n");
                }
                break;

            case 2:
                atendimento(fila);
                break;

            case 3:
                imprimirFila(fila);
                break;

            case 0:
                printf("Encerrando o sistema e liberando memoria...\n");
                break;

            default:
                printf("Opcao inexistente. Tente novamente.\n");
                break;
        }

    } while (escolha != 0);

    // Libera todos os nós e a estrutura da fila antes de fechar
    liberarMemoria(fila);
    
    printf("Sistema finalizado com seguranca.\n");
    return 0;
}