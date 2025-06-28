#include <stdlib.h>
#include <stdio.h>

void read_file(char* nome)
{
    FILE* f = fopen(nome, "r");

    if (!f)
    {
        printf("O arquivo nao pode ser aberto.\n");
        exit(1);
    }
    char c;
    while( (c = fgetc(f)) != EOF)
        printf("%c", c);
    
    fclose(f);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Deve ser passado ao menos um arquivo --> ./meucat <arquivo1> <arquivo2> ... <arquivoN> ...\n");
        exit(1);
    }
    for(int i = 1; i < argc; i++)
    {
        read_file(argv[i]);
    }
    return 0;
}