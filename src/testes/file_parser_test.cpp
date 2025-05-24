#include <fstream>

#include <gtest/gtest.h>

#include "io/file_parser.h"

// TODO: Criar casos de teste para outras instrucoes invalidas
//       ex.: passando ponto flutuante, string etc.
const char* conteudo_arquivo = R"(
INC
INC 
INC 13 12
INC 11

REM 42
REM 42
REM 47 42
SUC 50 65
SUC 40
SUC 40 10 20
IMP 65
IMP 20
IMP 10 15
IMP
FOO
FOO 42
)";

void gera_arquivo_teste(const std::string& nome_arquivo)
{
    std::ofstream arquivo(nome_arquivo);
    if (arquivo.is_open())
    {
        arquivo << conteudo_arquivo;
        arquivo.close();
    }
}

TEST(file_parser_test, deve_ser_capaz_de_ler_arquivo)
{
    const char* nome_arquivo = "teste_leitura.txt";
    gera_arquivo_teste(nome_arquivo);
    ufc::eda::io::file_parser fparser(nome_arquivo);
    fparser.parse();

    const std::vector<ufc::eda::io::op>& operacoesObtidas = fparser.operacoes();
    std::vector<ufc::eda::io::op> operacoesEsperadas = {
        ufc::eda::io::op(ufc::eda::io::op::tipo::INCLUSAO, 11),
        ufc::eda::io::op(ufc::eda::io::op::tipo::REMOCAO, 42),
        ufc::eda::io::op(ufc::eda::io::op::tipo::REMOCAO, 42),
        ufc::eda::io::op(ufc::eda::io::op::tipo::SUCESSAO, 50, 65),
        ufc::eda::io::op(ufc::eda::io::op::tipo::IMPRESSAO, 65),
        ufc::eda::io::op(ufc::eda::io::op::tipo::IMPRESSAO, 20)
    };

    EXPECT_EQ(operacoesObtidas.size(), operacoesEsperadas.size());
    for (size_t i = 0; i < operacoesObtidas.size(); ++i)
    {
        EXPECT_EQ(operacoesObtidas[i], operacoesEsperadas[i]);
    }
}
