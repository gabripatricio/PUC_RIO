import random

class Pessoa:
    def __init__(self, cpf, idade, raca, genero, nacionalidade, nome):
        self.cpf = cpf
        self.idade = idade
        self.raca = raca
        self.genero = genero
        self.nacionalidade = nacionalidade
        self.nome = nome

class Discente(Pessoa):
    def __init__(self, cpf, idade, raca, genero, nacionalidade, nome,renda, pcd, financiamento, codigoEmec, status, anoMatricula, CR):
        super().__init__(cpf, idade, raca, genero, nacionalidade, nome)
        self.renda = renda
        self.pcd = pcd
        self.financiamento = financiamento
        self.codigoEmec = codigoEmec
        self.status = status
        self.anoMatricula = anoMatricula
        self.CR = CR

    def mostrar_informacoes(self):
        print("=== Informações do Discente ===")
        print(f"Nome: {self.nome}")
        print(f"CPF: {self.cpf}")
        print(f"Idade: {self.idade} anos")
        print(f"Raça: {self.raca}")
        print(f"Gênero: {self.genero}")
        print(f"Nacionalidade: {self.nacionalidade}")
        print(f"Renda: R$ {self.renda:.2f}")
        print(f"PCD: {self.pcd}")
        print(f"Financiamento: {'Sim' if self.financiamento else 'Não'}")
        print(f"Código EMEC: {self.codigoEmec}")
        print(f"Status: {self.status}")
        print(f"Ano de Matrícula: {self.anoMatricula}")
        print(f"Coeficiente de Rendimento (CR): {self.CR}")

class Docente(Pessoa):
    def __init__(self, cpf, idade, raca, genero, nacionalidade, nome, titularidade):
        super().__init__(cpf, idade, raca, genero, nacionalidade, nome)
        self.titularidade = titularidade

    def mostrar_informacoes(self):
        print("=== Informações do Docente ===")
        print(f"Nome: {self.nome}")
        print(f"CPF: {self.cpf}")
        print(f"Idade: {self.idade} anos")
        print(f"Raça: {self.raca}")
        print(f"Gênero: {self.genero}")
        print(f"Nacionalidade: {self.nacionalidade}")
        print(f"Titularidade: {self.titularidade}")

def gerador_de_cpf():
    return "".join([str(random.randint(0, 9)) for _ in range(11)])

def gerar_raca():
    racas = ['Branca', 'Negra', 'Parda', 'Amarela', 'Indígena']
    return random.choice(racas)

def gerar_genero():
    generos = ['Masculino', 'Feminino']
    return random.choice(generos)

def gerar_nacionalidade():
    if random.random() < 0.9:
        return 'Brasileira'
    else:
        nacionalidades = ['Portugal', 'Argentina', 'Colombia', 'Mexico', 'Franca', 'Alemanha', 'Austria', 'EUA', 'Japao', 'China', 'Russia' ]
        return random.choice(nacionalidades)

def gerar_idade_prof():
    pesos = [1 if 30 <= i < 50 or 60 < i <= 75 else 5 for i in range(30, 76)]
    return random.choices(range(30, 76), weights=pesos, k=1)[0]

def gerar_titularidade():
    titularidades = ['Adjunto', 'Substituto', 'Agregado', 'Titular', 'Emerito']
    return random.choice(titularidades)

def gerar_nome():
    nomes_masculinos = [
    "Adriano", "Alan", "Alexandre", "André", "Antonio", "Bruno", "Caio", "Carlos",
    "César", "Daniel", "Diego", "Eduardo", "Fábio", "Felipe", "Fernando", "Francisco",
    "Gabriel", "Guilherme", "Gustavo", "Henrique", "Hugo", "Igor", "João", "José",
    "Juliano", "Leonardo", "Lucas", "Luís", "Marcelo", "Marcos", "Mateus", "Matheus",
    "Miguel", "Nicolas", "Pedro", "Rafael", "Ricardo", "Rodrigo", "Samuel", "Thiago", "Tiago", "Vinícius"
]

    nomes_femininos = [
    "Adriana", "Alice", "Amanda", "Ana", "Beatriz", "Bianca", "Bruna", "Camila",
    "Carla", "Catarina", "Clara", "Daniela", "Elaine", "Elisa", "Eduarda", "Fernanda", "Gabriela",
    "Helena", "Isabela", "Jéssica", "Joana", "Juliana", "Larissa", "Laura", "Letícia", "Lívia",
    "Luana", "Luiza", "Manuela", "Maria", "Maria Clara", "Maria Eduarda", "Mariana", "Natália", "Patrícia", "Paula",
    "Raquel", "Renata", "Rita", "Sabrina", "Sara", "Tatiana", "Thaís", "Valéria", "Vanessa", "Yasmin"
    ]

    sobrenomes = [
    "Almeida", "Alves", "Andrade", "Araujo", "Barbosa", "Barros", "Batista", "Borges", 
    "Campos", "Cardoso", "Carvalho", "Castro", "Cavalcanti", "Costa", "Dias", "Duarte", 
    "Fernandes", "Ferreira", "Freitas", "Garcia", "Gomes", "Gonçalves", "Lima", "Lopes", 
    "Machado", "Martins", "Melo", "Mendes", "Monteiro", "Moraes", "Moreira", "Nogueira", 
    "Oliveira", "Pereira", "Pinto", "Ramos", "Rezende", "Ribeiro", "Rocha", "Santos", 
    "Silva", "Souza", "Teixeira", "Vieira"
    ]

    # Escolher se será masculino ou feminino
    if random.random() < 0.5:
        nome = random.choice(nomes_masculinos)
        genero = 'M'
    else:
        nome = random.choice(nomes_femininos)
        genero = 'F'

    sobrenome1 = random.choice(sobrenomes)
    sobrenome2 = random.choice(sobrenomes)

    # Garantir que os dois sobrenomes sejam diferentes
    while sobrenome1 == sobrenome2:
        sobrenome2 = random.choice(sobrenomes)

    nome_completo = f"{nome} {sobrenome1} {sobrenome2}"

    return nome_completo, genero

def gerar_idade_aluno():
    pesos = [5 for _ in range(18, 26)] + [1 for _ in range(26, 61)]
    return random.choices(range(18, 61), weights=pesos, k=1)[0]

def cria_docente():
    cpf = gerador_de_cpf()
    idade = gerar_idade_prof()
    nome, genero = gerar_nome()
    raca = gerar_raca()
    nacionalidade = gerar_nacionalidade()
    titularidade = gerar_titularidade()
    return Docente(cpf, idade, raca, genero, nacionalidade, nome, titularidade)

def cria_discente():
    cpf = gerador_de_cpf()
    idade = gerar_idade_aluno()
    nome, genero = gerar_nome()
    raca = gerar_raca()
    nacionalidade = gerar_nacionalidade()

    renda = random.randint(800, 10000)
    pcd = "TRUE" if random.random() < 0.05 else "FALSE" # 5% pcds
    financiamento = random.random() < 0.10 # 10% tem bolsa
    codigoEmec = random.randint(1000, 1383)
    status = random.choices(
        ['Ativo', 'Formado', 'Jubilado', 'Inativo'], 
        weights=[77, 14, 3, 6], 
        k=1)[0]

    anoMatricula = random.randint(2015, 2023)
    CR = round(random.normalvariate(6.8, 1.2), 2)
    return Discente(cpf, idade, raca, genero, nacionalidade, nome, renda, pcd, financiamento, codigoEmec, status, anoMatricula, CR)

def escreve_docentes():
    with open("docentes_sql.txt", "w") as arquivo:
        lista = []
        for i in range(3500):
            docente = cria_docente()
            while docente.cpf in lista:
                docente = cria_docente
            lista.append(docente.cpf)

            arquivo.write(
                "INSERT INTO DOCENTE (nome, cpf, gênero, idade, raça, nacionalidade, titularidade) "
                f"VALUES ('{docente.nome}', '{docente.cpf}', '{docente.genero}', {docente.idade}, "
                f"'{docente.raca}', '{docente.nacionalidade}', '{docente.titularidade}');\n"
            )
    print("Todos os docentes foram criados com sucesso.")
    return lista #apenas uma maracutaia para facilitar na criação de novos alunos

def escreve_discentes(lista_cpfs):     
    with open("discentes_sql.txt", "w") as arquivo:
        lista = []
        for i in range(15000):
            discente = cria_discente()
            while discente.cpf in lista or discente.cpf in lista_cpfs:
                discente = cria_discente()
            lista.append(discente.cpf)
            arquivo.write(
                "INSERT INTO DISCENTE (nome, cpf, gênero, idade, raça, nacionalidade, rendafamiliar, pcd, "
                f"financiamento, codigoemeccurso, status, anomatricula, cracumulado) "
                f"VALUES ('{discente.nome}', '{discente.cpf}', '{discente.genero}', {discente.idade}, "
                f"'{discente.raca}', '{discente.nacionalidade}', {discente.renda}, '{discente.pcd}', "
                f"{'1' if discente.financiamento else '0'}, {discente.codigoEmec}, '{discente.status}', "
                f"{discente.anoMatricula}, {discente.CR});\n"
            )
        print("Todos os discentes foram criados com sucesso.")

def escreve_leciona_no(lista_cpfs):
    with open("leciona_no_sql.txt", "w") as arquivo:
        for i in range(len(lista_cpfs)):
            numero_aleatorio = random.randint(1300, 1383)
            arquivo.write(f"INSERT INTO LECIONA_NO (cpf, codigoemeccurso) VALUES ('{lista_cpfs[i]}', {numero_aleatorio});\n")
        
    
def main():
    cpfs = escreve_docentes()
    escreve_discentes(cpfs)
    escreve_leciona_no(cpfs)

if __name__ == '__main__':
    main()
