import random
import pandas as pd

# Lista de cursos
cursos = [
    "Administração", "Administração Pública", "Agroecologia", "Agronegócio", "Agronomia", 
    "Análise de Sistemas", "Antropologia", "Arquitetura e Urbanismo", "Arquivologia", "Artes", 
    "Artes Cênicas", "Astronomia", "Biblioteconomia", "Biologia", "Biomedicina", 
    "Bioquímica", "Canto", "Cenografia", "Ciência da Computação", "Ciências Biológicas", 
    "Ciências Contábeis", "Ciências Econômicas", "Ciências Sociais", "Cinema e Audiovisual", 
    "Composição e Regência", "Computação", "Comunicação e Marketing", "Comunicação Social", 
    "Desenho Industrial", "Design", "Design de Ambientes", "Design de Games", 
    "Design de Interiores", "Design de Moda", "Design de Produto", "Design Digital", 
    "Design Gráfico", "Direção", "Direito", "Educação Física", "Enfermagem", 
    "Engenharia Acústica", "Engenharia Aeroespacial", "Engenharia Aeronáutica", 
    "Engenharia Agrícola", "Engenharia Agroindustrial", "Engenharia Agronômica", 
    "Engenharia Ambiental", "Engenharia Automotiva", "Engenharia Bioenergética", 
    "Engenharia Biomédica", "Engenharia Bioquímica", "Engenharia Biotecnológica", 
    "Engenharia Cartográfica", "Engenharia Civil", "Engenharia da Computação", 
    "Engenharia da Mobilidade", "Engenharia de Agrimensura", "Engenharia de Agronegócios", 
    "Engenharia de Alimentos", "Engenharia de Aquicultura", "Engenharia de Automação", 
    "Engenharia de Bioprocessos", "Engenharia de Biossistemas", "Engenharia de Biotecnologia", 
    "Engenharia de Energia", "Engenharia de Gestão", "Engenharia de Informação", 
    "Engenharia de Instrumentação, Automação e Robótica", "Engenharia de Manufatura", 
    "Engenharia de Materiais", "Engenharia de Minas", "Engenharia de Pesca", 
    "Engenharia de Petróleo", "Engenharia de Produção", "Engenharia de Recursos Hídricos", 
    "Engenharia de Saúde e Segurança", "Engenharia de Sistemas", "Engenharia de Software", 
    "Engenharia de Telecomunicações", "Engenharia de Transporte e Logística", 
    "Engenharia Elétrica", "Engenharia Eletrônica", "Engenharia em Sistemas Digitais", 
    "Engenharia Ferroviária e Metroviária", "Engenharia Física", "Engenharia Florestal", 
    "Engenharia Geológica", "Engenharia Hídrica", "Engenharia Industrial", 
    "Engenharia Mecânica", "Engenharia Mecatrônica", "Engenharia Metalúrgica", 
    "Engenharia Naval", "Engenharia Química", "Engenharia Têxtil", "Estatística", 
    "Farmácia", "Filosofia", "Física", "Fisioterapia", "Fonoaudiologia", "Geografia", 
    "Gestão Ambiental", "Gestão da Informação", "Gestão de Políticas Públicas", 
    "Gestão de Serviços de Saúde", "Gestão do Agronegócio", "Gestão Pública", 
    "História", "Hotelaria", "Jornalismo", "Letras", "Marketing", "Matemática", 
    "Mecânica Industrial", "Medicina", "Medicina Veterinária", "Moda", "Música", 
    "Nutrição", "Odontologia", "Pedagogia", "Políticas Públicas", "Propaganda e Marketing", 
    "Psicologia", "Publicidade e Propaganda", "Química", "Rádio, TV e Internet", 
    "Relações Internacionais", "Relações Públicas", "Secretariado Executivo", 
    "Serviço Social", "Sistemas de Informação", "Tecnologias Digitais", "Teologia", 
    "Terapia Ocupacional", "Tradutor e Intérprete", "Turismo", "Zootecnia", 
    "Acupuntura", "Agrimensura", "Agrocomputação", "Agroindústria", "Agropecuária", 
    "Alimentos", "Análise de Dados", "Análise e Desenvolvimento de Sistemas", 
    "Apicultura e Meliponicultura", "Aquicultura", "Arqueologia", "Arquitetura de Dados", 
    "Artes do Espetáculo", "Artes e Mídias Digitais", "Assessoria Executiva Digital", 
    "Atividades de Inteligência e Gestão de Sigilos", "Auditoria em Saúde", 
    "Automação de Escritórios e Secretariado", "Automação e Manufatura Digital", 
    "Automação Industrial", "Banco de Dados", "Big Data e Inteligência Analítica", 
    "Big Data no Agronegócio", "Biocombustíveis", "Bioenergia", "Bioinformática", 
    "Biotecnologia", "Blockchain e Criptografia Digital", "Cafeicultura", "Cibersegurança", 
    "Ciência de Dados", "Coach Digital", "Coaching e Mentoring", "Coding", 
    "Comércio Exterior", "Computação em Nuvem", "Comunicação Assistiva", 
    "Comunicação Digital", "Comunicação em Computação Gráfica", "Comunicação em Mídias Digitais", 
    "Comunicação Institucional", "Conservação e Restauro", "Construção Civil", 
    "Construção de Edifícios", "Construção Naval", "Controle Ambiental", "Controle de Obras", 
    "Cosmetologia e Estética", "Cozinha Contemporânea", "Data Science", "Defesa Cibernética", 
    "Defesa Médica Hospitalar", "Desenho de Animação", "Desenvolvimento Back-End", 
    "Desenvolvimento de Aplicativos para Dispositivos Móveis", 
    "Desenvolvimento de Produtos Plásticos", "Desenvolvimento de Sistemas", 
    "Desenvolvimento e Gestão de Startups", "Desenvolvimento Mobile", "Desenvolvimento para Internet", 
    "Desenvolvimento para Web", "Design Comercial", "Design de Animação", 
    "Design de Aplicações e Interfaces Digitais", "Design de Experiência e de Serviços", 
    "Devops", "Digital Influencer", "Digital Security", "E-Commerce", 
    "Educação e Processos de Trabalho: Alimentação Escolar", "Educador Social", 
    "Eletrônica Automotiva", "Eletrônica Industrial", "Eletrotécnica Industrial", 
    "Embelezamento e Imagem Pessoal", "Empreendedorismo", "Energias Renováveis", 
    "Escrita Criativa", "Estética e Cosmética", "Estilismo", "Estradas", "Eventos", 
    "Fabricação Mecânica", "Filmmaker", "Finanças, Blockchain e Criptomoedas", 
    "Fitoterapia", "Fotografia", "Fruticultura", "Futebol", "Game Design", "Gastronomia", 
    "Geoprocessamento", "Gerenciamento de Redes de Computadores", "Gerontologia", 
    "Gestão Comercial", "Gestão Cultural", "Gestão da Avaliação", 
    "Gestão da Inovação e Empreendedorismo Digital", "Gestão da Produção Industrial", 
    "Gestão da Qualidade", "Gestão da Segurança Pública e Patrimonial", 
    "Gestão das Organizações do Terceiro Setor", "Gestão das Relações Eletrônicas", 
    "Gestão da Tecnologia da Informação", "Gestão de Agronegócios", "Gestão de Cidades Inteligentes", 
    "Gestão de Cloud Computing", "Gestão de Cooperativas", "Gestão de Energia e Eficiência Energética", 
    "Gestão de Equinocultura", "Gestão de Inventário Extrajudicial", "Gestão de Investimentos", 
    "Gestão de Lojas e Pontos de Vendas", "Gestão de Mercado de Capitais", 
    "Gestão de Micro e Pequenas Empresas", "Gestão de Negócios", "Gestão de Pessoas", 
    "Gestão de Produção Industrial", "Gestão de Qualidade na Saúde", "Gestão de Recursos Hídricos", 
    "Gestão de Recursos Humanos", "Gestão de Representação Comercial", "Gestão de Resíduos de Serviços de Saúde", 
    "Gestão de Saúde Pública", "Gestão de Segurança Privada", "Gestão de Seguros", 
    "Gestão de Serviços Judiciários e Notariais", "Gestão Desportiva e de Lazer", "Gestão de Telecomunicações", 
    "Gestão de Trânsito", "Gestão de Turismo", "Gestão Empresarial", "Gestão em Serviços", 
    "Gestão Financeira", "Gestão Hospitalar", "Gestão Portuária", "Gestão Tributária", "Horticultura", 
    "Hotelaria", "Informática", "Informática para Negócios", "Instalações Elétricas", 
    "Instrumentação Cirúrgica", "Inteligência Artificial", "Interiores e Decorações", 
    "Internet das Coisas", "Investigação e Perícia Criminal", "Irrigação e Drenagem", 
    "Jogos Digitais", "Laticínios", "Logística", "Luteria", "Manufatura Avançada", 
    "Manutenção de Aeronaves", "Manutenção Industrial", "Massoterapia", "Mecânica Automobilística", 
    "Mecânica de Precisão", "Mecânica", "Mecatrônica Automotiva", "Mecatrônica Industrial", 
    "Mediação", "Microeletrônica", "Mídias Sociais", "Mineração", "Ministério Pastoral", 
    "Moda", "Multidisciplinar em Dependência Química", "Negócios Digitais", "Negócios Imobiliários", 
    "Oftálmica", "Óptica e Optometria", "Paisagismo", "Papel e Celulose", "Paramedicina", 
    "Petróleo e Gás", "Pilotagem Profissional de Aeronaves", "Planejamento Logístico de Cargas", 
    "Podologia", "Polímeros", "Política e Gestão Cultural", "Políticas e Estratégicas Públicas", 
    "Práticas Integrativas e Complementares", "Processamento de Dados", "Processos Ambientais", 
    "Processos Escolares", "Processos Gerenciais", "Processos Metalúrgicos", "Processos Químicos", 
    "Produção Agrícola", "Produção Agropecuária", "Produção Audiovisual", "Produção Cervejeira", 
    "Produção Cultural", "Produção de Cacau e Chocolate", "Produção de Cachaça", 
    "Produção de Fármacos", "Produção de Grãos", "Produção de Plástico", "Produção Fonográfica", 
    "Produção Gráfica", "Produção Industrial", "Produção Leiteira", "Produção Multimídia", 
    "Produção Musical", "Produção Pesqueira", "Produção Publicitária", "Produção Sucroalcooleira", 
    "Produção Têxtil", "Projeto de Estruturas Aeronáuticas", "Projetos Mecânicos", 
    "Qualidade de Vida na Contemporaneidade", "Quiropraxia", "Radiologia", 
    "Redes de Computadores", "Refrigeração e Climatização", "Rochas Ornamentais", 
    "Saneamento Ambiental", "Saúde Coletiva", "Secretariado", "Segurança Alimentar", 
    "Segurança no Trabalho", "Service Design", "Silvicultura", "Sistema de Informação", 
    "Sistemas Automotivos", "Sistemas Biomédicos", "Sistemas para Internet", "Soldagem", 
    "Streaming Profissional", "Tecnologia da Informação", "Tecnologia Eletrônica", 
    "Tecnologia em Controle Ambiental", "Tecnologia Mecânica", "Tecnologias Educacionais", 
    "Telemática", "Terapias Integrativas e Complementares", "Toxicologia Ambiental", 
    "Trânsito", "Transporte Terrestre", "Tutoria de Educação a Distância", "Varejo Digital", 
    "Visagismo e Terapias Capilares", "Viticultura e Enologia"
]

# Opções de grau acadêmico e suas probabilidades
graus_academicos = ["Bacharelado", "Licenciatura", "Tecnólogo"]
probabilidade_graus = [0.85, 0.07, 0.08]

# Opções de modalidade e suas probabilidades
modalidades = ["Presencial", "EAD", "Semipresencial"]
probabilidade_modalidades = [0.90, 0.06, 0.04]

# Função para gerar uma chave única (chavemec) para cada curso
def gerar_chave_mec():
    return random.randint(1000000, 9999999)

# Lista para armazenar os dados da tabela CURSO
dados_cursos = []

for idx, curso in enumerate(cursos):
    codigoemaccurso = 1000 + idx  # Código sequencial a partir de 1000
    grauacademico = random.choices(graus_academicos, probabilidade_graus)[0]
    modalidade = random.choices(modalidades, probabilidade_modalidades)[0]
    chavemec = gerar_chave_mec()
    dados_cursos.append([codigoemaccurso, curso, grauacademico, modalidade, chavemec])

# Convertendo para DataFrame para visualização e salvando em CSV para referência futura
df_cursos = pd.DataFrame(dados_cursos, columns=["codigoemaccurso", "nome", "grauacademico", "modalidade", "chavemec"])
df_cursos.to_csv("tabela_cursos.csv", index=False)

# Gerando instruções SQL
instrucoes_sql = []
for _, row in df_cursos.iterrows():
    instrucao = f"INSERT INTO Curso (codigoemaccurso, nome, grauacademico, modalidade, chavemec) VALUES ({row['codigoemaccurso']}, '{row['nome']}', '{row['grauacademico']}', '{row['modalidade']}', {row['chavemec']});"
    instrucoes_sql.append(instrucao)

# Salvando as instruções SQL em um arquivo .sql
with open("insercoes_cursos.sql", "w") as f:
    for instrucao in instrucoes_sql:
        f.write(instrucao + "\n")

# Exibindo um exemplo das instruções geradas
for instrucao in instrucoes_sql[:5]:
    print(instrucao)

print("Instruções SQL salvas em 'insercoes_cursos.sql'.")
