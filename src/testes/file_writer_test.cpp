#include <string>

#include <gtest/gtest.h>

#include "io/file_writer.h"

const char* conteudo_esperado = R"(INC 11
REM 42
REM 42
SUC 50 65
IMP 65
IMP 20
)";

std::string le_conteudo_arquivo(const std::string& nome_arquivo)
{
    std::string conteudo;

    std::ifstream arquivo(nome_arquivo);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha))
        {
            conteudo += linha + "\n";
        }
    }

    return conteudo;
}

TEST(file_writer_test, deve_ser_capaz_de_ler_arquivo)
{
    const char* nome_arquivo = "teste_escrita.txt";
    ufc::eda::io::file_writer fwriter(nome_arquivo);

    fwriter << ufc::eda::io::op(ufc::eda::io::op::tipo::INCLUSAO, 11)
            << ufc::eda::io::op(ufc::eda::io::op::tipo::REMOCAO, 42)
            << ufc::eda::io::op(ufc::eda::io::op::tipo::REMOCAO, 42)
            << ufc::eda::io::op(ufc::eda::io::op::tipo::SUCESSAO, 50, 65)
            << ufc::eda::io::op(ufc::eda::io::op::tipo::IMPRESSAO, 65)
            << ufc::eda::io::op(ufc::eda::io::op::tipo::IMPRESSAO, 20);

    EXPECT_STREQ(le_conteudo_arquivo(nome_arquivo).c_str(), conteudo_esperado);
}
