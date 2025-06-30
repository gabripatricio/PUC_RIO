# Trabalho Prático de Banco de Dados (BD1) - 2024.2

## Professores
- **Veronica dos Santos (3WA)**
- **Sérgio Lifschitz (3WB)**
- **Marcos Villas (3WC)**

## Descrição do Projeto

Este projeto prático é parte da disciplina de Banco de Dados 1 (BD1) e tem como objetivo projetar e construir uma base de dados relacional sobre o mercado de **Educação Superior no Brasil**. A proposta é praticar os conceitos e fundamentos de bancos de dados relacionais através da modelagem, construção e manipulação de dados. O trabalho envolve o desenvolvimento de uma base de dados experimental que fornece uma visão externa e comparativa das Instituições de Ensino Superior (IES) brasileiras.

## Contexto

O setor de Educação Superior no Brasil cresceu significativamente nas últimas duas décadas, impulsionado pela demanda por qualificação profissional e políticas de inclusão educacional. Além do ensino presencial, o Ensino a Distância (EAD) teve uma expansão acelerada, oferecendo flexibilidade e menor custo para estudantes. No entanto, o setor ainda enfrenta desafios, como a alta taxa de evasão em cursos de graduação.

Este projeto é inspirado nos dados coletados pelo **Censo da Educação Superior** realizado anualmente pelo INEP. O objetivo é modelar uma base de dados que permita o armazenamento de informações sobre instituições, cursos, infraestrutura, vagas, matrículas, concluintes, abandonos, além de dados demográficos e socioeconômicos de discentes e docentes. Essa base pode ser utilizada para análises macro e comparações entre diferentes IES brasileiras.

## Objetivos

1. **Definir Requisitos**: Desenvolver um texto base para especificação do banco de dados, utilizando informações sobre o setor de Educação Superior e inspirando-se no Censo do INEP e outras fontes.
   
2. **Modelagem Conceitual**: Criar o modelo conceitual da base de dados usando o Modelo de Entidades e Relacionamentos (MER). O diagrama ER será gerado usando a ferramenta CASE BRModelo, incluindo cardinalidades min-max para os relacionamentos e descrição dos atributos e domínios de dados.

3. **Definir Regras de Negócio**: Identificar e enunciar ao menos três restrições de integridade semântica (regras de negócio) para o sistema. Essas regras devem ir além das restrições estruturais do modelo de dados.

4. **Mapeamento para Esquema Relacional**: Criar um esquema lógico-relacional a partir do modelo ER, listando as tabelas, atributos e explicando as restrições de integridade, incluindo chaves primárias (PK) e estrangeiras (FK).

5. **Análise de Normalização**: Analisar a tabela com mais atributos do esquema relacional em relação às formas normais, justificando a escolha da chave primária com base nas dependências funcionais.

6. **Implementação no PostgreSQL**: Escrever códigos SQL DDL para criar as tabelas no servidor PostgreSQL, incluindo restrições de integridade. Usar `ALTER TABLE` para definir ao menos uma PK e uma FK em tabelas diferentes.

7. **Inserção de Dados Realistas**: Inserir dados realistas e possíveis em todas as tabelas, usando datasets públicos, como os disponíveis no site do INEP. Os códigos SQL DML de inserção serão documentados no repositório, mas apenas um exemplo de inserção será incluído no relatório.

## Arquitetura do Repositório

- `README.md`: Documentação do projeto.
- `/SQL_DDL`: Códigos SQL DDL para criação das tabelas no PostgreSQL.
- `/SQL_DML`: Scripts SQL DML com as inserções de dados.
- `relatorio.pdf`: Relatório completo com as respostas para cada questão do trabalho prático.

## Ferramentas e Tecnologias

- **BRModelo**: Ferramenta CASE para criar o diagrama ER.
- **PostgreSQL**: Banco de dados relacional usado para implementar o esquema lógico.
- **Git e GitHub**: Controle de versão e repositório remoto para colaboração.

