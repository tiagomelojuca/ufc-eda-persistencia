#include <fstream>

#include <gtest/gtest.h>

#include "io/executor.h"
#include "io/file_parser.h"

const char* conteudo_arquivo_entrada = R"(
INC
INC 
INC 13 12
INC 6

REM 42
REM 42

INC 5
INC 7
INC 8

REM 47 42
SUC 50 65
INC 5
INC 2
SUC 40
INC 4
SUC 40 10 20
INC 4
IMP 65
REM 4
REM 4
IMP 20
IMP 10 15
IMP
FOO
FOO 42
)";

void gera_arquivo_entrada_execucao(const std::string& nome_arquivo)
{
    std::ofstream arquivo(nome_arquivo);
    if (arquivo.is_open())
    {
        arquivo << conteudo_arquivo_entrada;
        arquivo.close();
    }
}

TEST(executor_test, deve_ser_capaz_de_instrumentar_a_partir_de_arquivo)
{
    const char* nome_arquivo_entrada = "teste_entrada_executor.txt";
    const char* nome_arquivo_saida = "teste_saida_executor.txt";

    gera_arquivo_entrada_execucao(nome_arquivo_entrada);
    ufc::eda::io::file_parser fparser(nome_arquivo_entrada);
    fparser.parse();

    ufc::eda::io::executor executor(nome_arquivo_saida);
    for (const ufc::eda::io::op& op : fparser.operacoes())
    {
        executor.enfila(op);
    }

    executor.executa();
}
