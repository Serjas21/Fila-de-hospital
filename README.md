🏥 Sistema de Gerenciamento de Fila Hospitalar
Este projeto é uma implementação em Linguagem C de um sistema de triagem e atendimento dinâmico, desenvolvido para simular o fluxo de pacientes em uma unidade de saúde.

🚀 Funcionalidades
Inserção com Prioridade: Pacientes são classificados entre Normal (1) e Prioritário (2). O sistema reorganiza a fila automaticamente para que prioritários sejam atendidos primeiro.

Atendimento Inteligente: Função que remove o paciente da fila respeitando a ordem de chegada e a prioridade.

Prevenção de Starvation (Espera Infinita): Implementação de uma regra de "fura-fila" baseada em tempo real. Se um paciente comum aguardar por mais de um tempo determinado, ele ganha preferência de atendimento.

Gestão de Tempo Real: Uso da biblioteca <time.h> para calcular a espera exata de cada paciente desde o momento da entrada.

🛠️ Detalhes Técnicos
Estrutura de Dados: Lista Encadeada Dinâmica (Fila).

Algoritmo de Seleção: O sistema percorre a lista verificando a estampa de tempo (time_t) de cada nó antes de decidir o próximo atendimento.

Gerenciamento de Memória: Alocação dinâmica de memória com limpeza (free) eficiente após cada atendimento.

📋 Como funciona a lógica de atendimento?
Prioridade: Por padrão, quem tem Prioridade: 2 fica à frente.

Tempo de Espera: O sistema verifica se algum paciente (independente da prioridade) excedeu o limite de segurança (ex: 900 segundos).

Decisão: Se alguém excedeu o tempo, essa pessoa é atendida imediatamente. Caso contrário, segue-se a ordem da fila de prioridade.
