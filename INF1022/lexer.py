import ply.lex as lex


#todos os tokens devem estar com caps-lock 
# 
reservadas = {
    'se': 'SE',
    'entao': 'ENTAO',
    'senao': 'SENAO',
    'dispositivo': 'DISPOSITIVO',
    'set': 'SET',
    'TRUE': 'TRUE',
    'FALSE': 'FALSE',
    'para': 'PARA',
    'todos': 'TODOS',
    'enviar': 'ENVIAR',
    'alerta': 'ALERTA',
    'ligar': 'LIGAR',
    'desligar': 'DESLIGAR',
}


#so token tem expressao regular
tokens = [
    "ABRE_CHAVES", "FECHA_CHAVES",
    "ABRE_PARENTESES", "FECHA_PARENTESES",
    "DOIS_PONTOS",
    "VIRGULA", 
    "PONTO", 
    "IGUAL",
    "MAIOR", "IGUAL_IGUAL", "MENOR", "MENOR_IGUAL", "MAIOR_IGUAL", "DIFERENTE", "OU_DUPLO",
    "IDENTIFICADOR",
    "MSG",
    "AND_DUPLO",
    "NUMERO",
]

tokens += list(reservadas.values())

print(f"\n\n [LEXER.PY] Esses são todos os tokens que nós temos até agora:\n{tokens}\n\n")


#Observação 1) Poderiamos criar apenas um NOME_VARIAVEL_OBJETO (sei la), mas eu achei melhor dividir em mais expressoes regulares pq eu achei que fosse ficar mais facil
# ja que tem mta restricao entre namesensor, namedevice etc... achei que fosse ficar mais facil, basicamente essa a justificativa

#Observacao 2) Também achei melhor dividir os operadores lógicos


#OBSERVAÇÃO 3) ACHO INTERESSANTE NÓS COLOCARMOS UM "    OU" JÁ QUE NÓS SÓ TEMOS O AND

#expressao regular pros tokens:

#Operadores 
t_AND_DUPLO = r'&&'
t_IGUAL_IGUAL = r'=='
t_MENOR_IGUAL = r'<='
t_MAIOR_IGUAL = r'>='
t_DIFERENTE = r'!='
t_MAIOR    = r'>'
t_MENOR    = r'<'
t_IGUAL = r'='
t_OU_DUPLO = r'\|\|'

#Pontuacoes
t_PONTO = r'\.'
t_VIRGULA = r','  
t_DOIS_PONTOS = r'\:'

#Chaves e Parenteses
t_ABRE_PARENTESES = r'\('
t_ABRE_CHAVES = r'\{'
t_FECHA_PARENTESES = r'\)'
t_FECHA_CHAVES = r'\}'




t_ignore = ' \t' # para ignorar espaco e tab

def t_novaLinha(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_error(t):
    print(f"Caractere ilegal '{t.value[0]}' na linha {t.lexer.lineno}")
    t.lexer.skip(1)

def t_IDENTIFICADOR(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    t.type = reservadas.get(t.value, 'IDENTIFICADOR')
    if len(t.value) > 100:
        print(f"[ERRO] IDENTIFICADOR excede 100 caracteres na linha {t.lineno}: {t.value}")
        t.value = t.value[:100]
    return t


def t_MSG(t):
    r'\"[^\n\"]+\"' # so tem que tomar cuidado com as aspas (restricao da gramatica)...
    if len(t.value) - 2 > 100:  # -2 para excluir as aspas
        print(f"[ERRO] MSG excede 100 caracteres na linha {t.lineno}: {t.value}")
        t.value = t.value[:102] + "\""  # Trunca com aspas finais
    return t

def t_NUMERO(t):
    r'\d+'
    t.value = int(t.value)
    return t

lexer = lex.lex()