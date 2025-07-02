from parser import parser
import os 

preambulo = """#include <stdio.h>

// CODIGO PRODUZIDO POR GABRIEL PATRICIO E GABRIEL MARTINS
void ligar(const char *nome) {
    printf("%s ligado!\\n", nome);
}

void desligar(const char *nome) {
    printf("%s desligado!\\n", nome);
}

void alerta(const char *nome, const char *msg) {
    printf("%s recebeu o alerta:\\n%s\\n", nome, msg);
}

void alerta_var(const char *nome, const char *msg, int var) {
    printf("%s recebeu o alerta:\\n%s %d\\n", nome, msg, var);
}

int main(void) {
"""

rodape = "\n    return 0;\n}\n"

with open("entrada.obs") as f:
    obs_code = f.read()
    print(obs_code)


codigo_gerado = parser.parse(obs_code)

print(codigo_gerado)

codigo_final = preambulo + "\n".join("    " + linha for linha in codigo_gerado.split("\n")) + rodape


with open("saida.c", "w") as f:
    f.write(codigo_final)

print("Gerado com sucesso: saida.c")  
    