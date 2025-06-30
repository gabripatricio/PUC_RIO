leciona_no:
CREATE TABLE LECIONA_NO (
    CPF VARCHAR(11),
    codigoEMecCurso INT,
    PRIMARY KEY (CPF, codigoEMecCurso),
    FOREIGN KEY (CPF) REFERENCES DOCENTE(CPF),
    FOREIGN KEY (codigoEMecCurso) REFERENCES CURSO(codigoEMacCurso)
);

possui:
CREATE TABLE POSSUI (
    codigoEMecIES INT,
    codigoEMecCurso INT,
    quantidade INT,
    PRIMARY KEY (codigoEMecIES, codigoEMecCurso),
    FOREIGN KEY (codigoEMecIES) REFERENCES IES(codigoEMECIES),
    FOREIGN KEY (codigoEMecCurso) REFERENCES CURSO(codigoEMacCurso)
);

trabalha:
CREATE TABLE TRABALHA (
    codigoEMecIES INT,
    CPF VARCHAR(11),
    Salário DECIMAL(10, 2),
    PRIMARY KEY (codigoEMecIES, CPF),
    FOREIGN KEY (codigoEMecIES) REFERENCES IES(codigoEMECIES),
    FOREIGN KEY (CPF) REFERENCES DOCENTE(CPF)
);

docente:
CREATE TABLE DOCENTE (
    CPF VARCHAR(11) PRIMARY KEY,
    idade INT,
    nome VARCHAR(100),
    raça VARCHAR(50),
    gênero VARCHAR(10),
    nacionalidade VARCHAR(50),
    titularidade VARCHAR(50)
);

discente:
CREATE TABLE DISCENTE (
    CPF VARCHAR(11) PRIMARY KEY,
    idade INT,
    nome VARCHAR(100),
    raça VARCHAR(50),
    gênero VARCHAR(10),
    nacionalidade VARCHAR(50),
    financiamento VARCHAR(50),
    PCD BOOLEAN,
    rendaFamiliar DECIMAL(10, 2),
    codigoEMecCurso INT,
    Status VARCHAR(20),
    anoMatricula INT,
    CRAcumulado DECIMAL(5, 2),
    FOREIGN KEY (codigoEMecCurso) REFERENCES CURSO(codigoEMacCurso)
);

curso:
CREATE TABLE CURSO (
    codigoEMacCurso INT PRIMARY KEY,
    nome VARCHAR(100),
    grauAcademico VARCHAR(50),
    modalidade VARCHAR(50),
    chaveMEC INT,
    FOREIGN KEY (chaveMEC) REFERENCES AREADOCONHECIMENTO(chaveMEC)
);

areaDoConhecimento:
CREATE TABLE AREADOCONHECIMENTO (
    chaveMEC INT PRIMARY KEY,
    atributo VARCHAR(100)
);

ies:
CREATE TABLE IES (
    codigoEMECIES INT PRIMARY KEY,
    nLivrosBiblioteca INT,
    nPCsDisponives INT,
    nLabs INT,
    nAlunos INT,
    CI DECIMAL(5, 2),
    IGC DECIMAL(5, 2),
    CI_EAD DECIMAL(5, 2),
    Tipo VARCHAR(50),
    Nome VARCHAR(100),
    OrgAcademica VARCHAR(100),
    notaEnsinoRUF DECIMAL(5, 2),
    notaRUFInovacao DECIMAL(5, 2),
    notaRUFmercado DECIMAL(5, 2),
    notaRUFInternacionalizacao DECIMAL(5, 2),
    Localizacao VARCHAR(100),
    Campus VARCHAR(100)
);

