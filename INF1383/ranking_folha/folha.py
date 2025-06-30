import pandas as pd
import random


def df_universidades():
    df = pd.read_csv("ranking_folha_univ.csv", delimiter=';')
    df = df[["Universidade", "Estado", "Pública ou Privada", "Nota em Ensino", "Nota em Internacionalização",
             "Nota em Mercado", "Nota em Inovação"]]

    ids = random.sample(range(1, 204), len(df))
    df["Código MEC"] = ids

    org = ['Faculdade', 'Centro Universitário', 'Institutos Federais', 'Universidade', 'Escola de Governo']
    with open("inserts_universidades.txt", "w", encoding="utf-8") as f:
        for _, linha in df.iterrows():
            igc = round(random.uniform(1, 5), 2)
            ci_ead = round(random.uniform(1, 5), 2)
            ci = round(random.uniform(1, 5), 2)
            npcs = random.randint(3000, 4000)
            nlabs = random.randint(1, 20)
            nlivros = random.randint(10000, 20000)
            nalunos = random.randint(5000, 30000)
            org_random = random.choice(org)
            localizacao = linha['Estado']

            # Função para converter NaN para NULL no SQL
            def format_value(value):
                return 'NULL' if pd.isna(value) else value

            sql = (
                f"INSERT INTO ies (codigoemecies, nlivrosbiblioteca, npcsdisponiveis, nlabs, nalunos, ci, igc, "
                f"ci_ead, tipo, nome, orgacademica, notaensinoruf, notrufinovacao, notarufmercado, "
                f"notarufinternacionalizacao, localizacao) "
                f"VALUES ({linha['Código MEC']}, {nlivros}, {npcs}, {nlabs}, {nalunos}, {ci}, {igc}, {ci_ead}, "
                f"'{linha['Pública ou Privada']}', '{linha['Universidade']}', '{org_random}', "
                f"{format_value(linha['Nota em Ensino'])}, {format_value(linha['Nota em Inovação'])}, "
                f"{format_value(linha['Nota em Mercado'])}, {format_value(linha['Nota em Internacionalização'])}, "
                f"'{localizacao}');\n"
            )

            f.write(sql)

    return df

df_universidades()
