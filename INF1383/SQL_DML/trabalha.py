import random

def extrair_cpfs(arquivo):
    cpfs = []
    
    # Abrir o arquivo para leitura
    with open(arquivo, 'r') as f:
        for linha in f:
            # Verificar se a linha contém 'VALUES', onde o CPF aparece
            if 'VALUES' in linha:
                # Dividir a linha para encontrar a parte dos valores
                valores = linha.split('VALUES')[1].strip()
                # Remover os parênteses e separar os valores por vírgula
                valores = valores.strip('();').split(',')
                # O CPF é o segundo valor (posição 1) após a separação
                cpf = valores[1].strip().strip("'")
                cpfs.append(cpf)
    
    return cpfs

def gera_tabela_trabalha(cpfs):
    media = 12000
    desvio_padrao = 3000

    with open("trabalha_sql.txt", "w") as arquivo:
        for cpf in cpfs:
            # Gerar um número aleatório entre 1 e 203
            numero_aleatorio = random.randint(1, 203)
            # Gerar um salário aleatório com distribuição normal
            salario_aleatorio = round(random.normalvariate(media, desvio_padrao))
            
            # Escrever a instrução SQL no arquivo
            sql = f"INSERT INTO trabalha (cpf, codigoEMecIES, salário) VALUES ('{cpf}', {numero_aleatorio}, {salario_aleatorio});\n"
            arquivo.write(sql)

# Exemplo de uso
arquivo_txt = 'docentes_sql.txt'  # Agora com o nome correto do arquivo
cpfs = extrair_cpfs(arquivo_txt)
gera_tabela_trabalha(cpfs)
print(cpfs)
