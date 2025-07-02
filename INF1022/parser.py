# Observações gerais:

# 1) É muito importante ter esses comentarios dentro das funcoes, já que eles definem a gramatica

## TO-DO
# 2) Adicionar a funcionalidade OU ("||")
# 4) 

'''
R0 : (V) PROGRAM −→ DEVICES CMDS
R1 : (V) DEVICES −→ DEVICE DEVICES
R2 : (V) DEVICES −→ DEVICE
R3 : (V) DEVICE −→ dispositivo : {namedevice}
R4 : (V) DEVICE −→ dispositivo : {namedevice, observation}
R5 : (V) CMDS −→ CMD. CMDS | CMD. 
R6 : (V) CMDS −→ CMD. 
R7 : (V) CMD −→ ATTRIB
R8 : (V) CMD −→ OBSACT
R9 : (V) CMD −→ ACT
R10: (V) ATTRIB −→ set observation = VAR
R11: (V) OBSACT −→ se OBS entao ACT
R12: (V) OBSACT −→ se OBS entao ACT senao ACT
R13: (V) OBS −→ observation oplogic VAR
R14: (V) OBS −→ observation oplogic VAR && OBS
R15: (V) VAR −→ num 
R16: (V) VAR −→ bool
R17: (V) ACT −→ ACTION namedevice
R18: (V) ACT −→ enviar alerta (msg) namedevice
R19: (V) ACT −→ enviar alerta (msg, observation) namedevice
R20: (V) ACTTION −→ ligar 
R21: (V) ACTTION −→ desligar

NOVAS REGRAS CRIADAS:
R22: (V) ACT −→ enviar alerta (msg) para todos : LISTA_DEVICES
R23: (V) OPLOGIC −→ > | == | < | <= | >= | != | && 
R24: (V) LISTA_DEVICES −→ namedevice  
R25: (V) LISTA_DEVICES −→ namedevice, LISTA_DEVICES


'''

import ply.yacc as yacc
from lexer import tokens  # temos que criar um lexer
import re

name_device_re = re.compile(r'^[A-Za-z]+$')
name_sensor_re = re.compile(r'^[A-Za-z][A-Za-z0-9]*$')

def eh_namedevice(lexema):
    return bool(name_device_re.match(lexema))

def eh_namesensor(lexema):
    return bool(name_sensor_re.match(lexema))

dispositivos = set()
sensores = set()   # oriundos de DEVICE ou usados em OBS
sensores_atribuidos = set()   # que receberam 'set ... = NUMERO' --> variaveis que nao foram atribuidas colocamos 0
sensores_declarados = set() # já impressos com 'int ...' no código C

start = 'PROGRAM'

#R3
def p_device_simples(p):
    """
    DEVICE : DISPOSITIVO DOIS_PONTOS ABRE_CHAVES IDENTIFICADOR FECHA_CHAVES
    """
    nome = p[4]
    if not eh_namedevice(nome):
        print(f"[ERRO] nome de dispositivo inválido: {nome}")
        print("Vamos encerrar o programa para não escrever mais nada")
        exit(1)
    dispositivos.add(nome)
    pass

#R4
def p_device_duplo(p):
    """
    DEVICE : DISPOSITIVO DOIS_PONTOS ABRE_CHAVES IDENTIFICADOR VIRGULA IDENTIFICADOR FECHA_CHAVES
    """
    nome_disp, obs = p[4], p[6]
    if not eh_namedevice(nome_disp):
        print(f"[ERRO] nome de dispositivo inválido: {nome_disp}")
        print("Vamos encerrar o programa para não escrever mais nada")
        exit(1)
    if not eh_namesensor(obs):
        print(f"[ERRO] observation deve ser sensor válido entre aspas: {obs}")
        print("Vamos encerrar o programa para não escrever mais nada")
        exit(1)
        
    dispositivos.add(nome_disp)
    sensores.add(obs)

#R2
def p_devices_simples(p):
    """
    DEVICES : DEVICE
    """
    p[0] = [p[1]]

#R1
def p_devices_rec(p):
    """
    DEVICES : DEVICE DEVICES
    """
    p[0] = [p[1]] + p[2]
    
#R25
def p_lista_devices_rec(p):
    """
    LISTA_DEVICES : IDENTIFICADOR VIRGULA LISTA_DEVICES
    """
    p[0] = [p[1]] + p[3]

#R24
def p_lista_devices_simples(p):
    """
    LISTA_DEVICES : IDENTIFICADOR
    """
    p[0] = [p[1]]

#R0 
def p_program(p):
    """
    PROGRAM : DEVICES CMDS
    """
    # Gera o código diretamente a partir dos comandos
    sensores_nao_atribuidos = sensores - sensores_atribuidos
    inicializacoes = "\n".join(f"unsigned int {s} = 0;" for s in sensores_nao_atribuidos)
    
    comandos_c = "\n".join(p[2])
    p[0] = inicializacoes + ("\n" if inicializacoes else "") + comandos_c


#R7, R8, R9
def p_cmd(p):
    """
    CMD : ATTRIB  
        | OBSACT
        | ACT
    """
    p[0] = p[1]


#R6
def p_cmds(p):
    """
    CMDS : CMD PONTO
    """
    p[0] = [p[1]]


#R5
def p_cmds_duplo(p):
    """
    CMDS : CMD PONTO CMDS
    """
    p[0] = [p[1]] + p[3]


#R13
def p_obs(p):
    """ 
    OBS : IDENTIFICADOR OPERADOR_LOGICO VAR
    """
    sensor = p[1]
    if sensor not in sensores:
        print(f"[ERRO] Sensor '{sensor}' não declarado. Declarados: {sensores}")
        print("Abortando o programa...")
        exit(1)
    p[0] = f" {p[1]} {p[2]} {p[3]}"


#R14
def p_obs_and(p):
    """
    OBS : IDENTIFICADOR OPERADOR_LOGICO VAR AND_DUPLO OBS
    """

    sensor = p[1]
    if sensor not in sensores:
        print(f"[ERRO] Sensor '{sensor}' não declarado. Declarados: {sensores}")
        print("Abortando o programa...")
    p[0] = f"{p[1]} {p[2]} {p[3]} && {p[5]}"

#R
def p_obs_or(p):
    """
    OBS : IDENTIFICADOR OPERADOR_LOGICO VAR OU_DUPLO OBS
    """

    sensor = p[1]
    if sensor not in sensores:
        print(f"[ERRO] Sensor '{sensor}' não declarado. Declarados: {sensores}")
        print("Abortando o programa...")
        exit(1)
    
    p[0] = f"{p[1]} {p[2]} {p[3]} || {p[5]}"


#R.A.
def p_OPERADOR_LOGICO(p):
    """
    OPERADOR_LOGICO : MAIOR 
                    | IGUAL_IGUAL 
                    | MENOR 
                    | MENOR_IGUAL 
                    | MAIOR_IGUAL 
                    | DIFERENTE 
    """
    p[0] = p[1]


#R11
def p_obsact(p):
    """
    OBSACT : SE OBS ENTAO ACT
    """

    p[0] = f"if ({p[2]}) {{\n{p[4]}\n}}"


#R12
def p_obsact_senao(p):
    """
    OBSACT : SE OBS ENTAO ACT SENAO ACT
    """

    p[0] = f"if ({p[2]}) {{\n    {p[4]}\n}} else {{\n    {p[6]}\n}}"


#R15
def p_var_num(p):
    """
    VAR : NUMERO
    """
    p[0] = str(p[1])


#R16
def p_var_true(p):
    """
    VAR : TRUE 
    """
    p[0] = "1"


#R16
def p_var_bool_false(p):
    """
    VAR : FALSE
    """
    p[0] = '0'


#R9
def p_attrib(p):
    """
    ATTRIB : SET IDENTIFICADOR IGUAL VAR
    """
    nome = p[2]
    valor = p[4]
    if nome not in sensores:
        print(f"[ERRO] Sensor '{nome}' não declarado. Declarados: {sensores}")
        print("Abortando o programa...")
        exit(1)
    sensores_atribuidos.add(nome) # garantir que vai p 0

    # se ainda não declaramos, põe o tipo
    decl = "" if nome in sensores_declarados else "unsigned int "
    sensores_declarados.add(nome)
    
    p[0] = f"{decl}{nome} = {valor};"
    

#R21
def p_action_desligar(p):
    """
    ACTION : DESLIGAR
    """
    p[0] = p[1]


#R20
def p_action_ligar(p):
    """
    ACTION : LIGAR
    """
    p[0] = p[1]


#R18
def p_act_alert(p):
    """
    ACT : ENVIAR ALERTA ABRE_PARENTESES MSG FECHA_PARENTESES IDENTIFICADOR
    """
    nome_dispositivo = p[6]
    if nome_dispositivo not in dispositivos:
        print("Você não declarou o dispositivo! Erro terrível de sintaxe!")
        print("Dispositivos declarados: ", dispositivos)
        print(f"Seu dispositivo: {nome_dispositivo} não foi declarado.")
        p[0] = f"// ERRO: Dispositivo '{nome_dispositivo}' não existe."
    else:
        p[0] = f'alerta("{nome_dispositivo}", {p[4]});'


#R19
def p_act_alert_var(p):
    """
    ACT : ENVIAR ALERTA ABRE_PARENTESES MSG VIRGULA IDENTIFICADOR FECHA_PARENTESES IDENTIFICADOR
    """
    disp = p[8]
    if disp not in dispositivos:
        print(f"[ERRO] Dispositivo '{disp}' não declarado. Declarados: {dispositivos}")
        p[0] = f"/* ERRO: dispositivo '{disp}' inexistente */"
    else:
        p[0] = f'alerta_var("{disp}", {p[4]}, {p[6]});'


#R22
def p_act_alerta_broadcast(p):
    """
    ACT : ENVIAR ALERTA ABRE_PARENTESES MSG FECHA_PARENTESES PARA TODOS DOIS_PONTOS LISTA_DEVICES
    """
    msg = p[4]
    lista_devices = p[9]                       

    nao_declarados = [device for device in lista_devices if device not in dispositivos]
    if nao_declarados:
        print(f"[ERRO] dispositivos não declarados: {', '.join(nao_declarados)}")
        p[0] = "/* broadcast inválido */"
        return

    # gera uma chamada alerta(...) para cada dispositivo
    chamadas = '\n'.join([f'alerta("{device}", {msg});' for device in lista_devices])
    p[0] = chamadas


#R17
def p_act(p):
    """
    ACT : ACTION IDENTIFICADOR
    """
    nome_disp = p[2]

    if nome_disp not in dispositivos:
        print(f"[ERRO] dispositivo '{nome_disp}' não declarado. Declarados: {dispositivos}")
        p[0] = f"/* ERRO: dispositivo '{nome_disp}' inexistente */"
        return

    # p[1] contém a string 'ligar' ou 'desligar'
    func_c = 'ligar' if p[1] == 'ligar' else 'desligar'
    p[0] = f'{func_c}("{nome_disp}");'  


#R.A.
def p_error(p):
    if p:
        print(f"Erro de Sintaxe no token '{p.type}' ('{p.value}') na linha {p.lineno}")
    else:
        print("Erro de Sintaxe no final do código!")


parser = yacc.yacc()