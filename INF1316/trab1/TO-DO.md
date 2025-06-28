# Itens a serem implementados


1. Main 
- Parar interpretador quando todos as processos ja tiverem sido lidos
- Aguardar o escalonador terminar sozinho --> Quando todos os proceessos terminarem
- Main para de rodar quando ambos os processos terminarem (interpretador e escalonador)

2. Interpretador
- Pensar melhor nesses tempos de espera no wwhile da main no interpretador
- Rever o valor do campo processo->lido atribuido pela funcao criaProcesso
- Talvez trocar o uso do elemento processo->lida para o uso de sinais 

3. Escalonador
- Mostrar as filas de prontos a cada preempção, indicar que processo parou de executar e que processo passou a executar.
- Talvez adicionar um else if p->tipo == PRIORIDADE e deixar o else para testar o caso de o tipo ser desconhecido.
- Implementar testes de vericacao de periodos conflitantes e de duracao maior que 60 segundos no escalonamento REAL-TIME
- Talvez alterar o campo referente ao nome do arquivo de um processo para um array de tamnaho predefinido ao inves de dar malloc, porque o chat recomendou nao usar alocacao dinamica com meoria compartilhada.
- Processos de prioridade devem serfinitos e serem executados por apenas 3 UT
- Usar tempo de duracao ou e fim dos processos REAL-TIME na struct Processo????


## Duvidas a serem tiradas

1. O que fazer quando tiver dois processos REAL-TIME com perriodos de execucao conflitantes?????

2. O interpretador deve ficar rodando infinito ou pode parar depois de ler todo o arquivo?????

3. Duvida no gerenciamento da prioridade na funcao insere_lista --> Perguntar ao Gabri --> Acho que tratou a maior prioridade sendo o menor numero mas eh ao contrario, quanto maior o numero maior eh a prioridade.

4. Seibel colocou dois formatos de string do arquivo exec.txt para os processos do tipo REAL-TIME, definindo a duracao com "D=" e "T=". A principio estou usando "D=" no codigo
