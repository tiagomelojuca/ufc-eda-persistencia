#include <iostream>

#include "io/arg_parser.h"
#include "io/executor.h"
#include "io/file_parser.h"

#define SEM_ERRO                 0
#define ERRO_ENTRADA_INVALIDA    1
#define ERRO_ABERTURA_ARQUIVO    2

namespace string_table_tabajara
{
    constexpr static const char* STR_ERRO_NUM_ARGS_INVALIDO = "Numero de argumentos invalido!";
    constexpr static const char* STR_ERRO_ARQUIVO_ENTRADA_INVALIDO = "Nome invalido do arquivo de entrada!";
    constexpr static const char* STR_ERRO_ARQUIVO_SAIDA_INVALIDO = "Nome invalido do arquivo de saida!";
    constexpr static const char* STR_ERRO_ARQUIVOS_INVALIDOS = "Nome dos arquivos invalidos!";
    constexpr static const char* STR_ERRO_ABERTURA_ARQUIVO = "Nao foi possivel abrir o arquivo de entrada!";
    constexpr static const char* STR_INSTRUCOES = "./cli [arquivo_entrada] [arquivo_saida]";
    constexpr static const char* STR_ROTINA_EXECUTADA_COM_SUCESSO = "Rotina executada com sucesso";
}

void imprime_erro_na_saida_padrao(const char* str)
{
    std::cout << "[ERRO] " << str << std::endl;
    std::cout << "       " << "USO: " << string_table_tabajara::STR_INSTRUCOES << std::endl;
}

int main(int argc, char** argv)
{
    ufc::eda::io::arg_parser arg_parser = ufc::eda::io::cria_arg_parser(argc, argv);
    const ufc::eda::io::arg_parser::status status = arg_parser.parse();

    if (status != ufc::eda::io::arg_parser::status::SUCESSO)
    {
        const char* msg_erro = "";
        if (status == ufc::eda::io::arg_parser::status::NUMERO_DE_ARGUMENTOS_INVALIDO)
        {
            msg_erro = string_table_tabajara::STR_ERRO_NUM_ARGS_INVALIDO;
        }
        else if (status == ufc::eda::io::arg_parser::status::AMBOS_ARQUIVOS_INVALIDOS)
        {
            msg_erro = string_table_tabajara::STR_ERRO_ARQUIVOS_INVALIDOS;
        }
        else if (status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO)
        {
            msg_erro = string_table_tabajara::STR_ERRO_ARQUIVO_ENTRADA_INVALIDO;
        }
        else if (status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO)
        {
            msg_erro = string_table_tabajara::STR_ERRO_ARQUIVO_SAIDA_INVALIDO;
        }

        imprime_erro_na_saida_padrao(msg_erro);

        return ERRO_ENTRADA_INVALIDA;
    }

    ufc::eda::io::file_parser fparser(arg_parser.arquivo_entrada());
    if (!fparser.parse())
    {
        imprime_erro_na_saida_padrao(string_table_tabajara::STR_ERRO_ABERTURA_ARQUIVO);

        return ERRO_ABERTURA_ARQUIVO;
    }

    ufc::eda::io::executor executor(arg_parser.arquivo_saida());
    for (const ufc::eda::io::op& operacao : fparser.operacoes())
    {
        executor.enfila(operacao);
    }
    executor.executa();

    std::cout << "[OK] " << string_table_tabajara::STR_ROTINA_EXECUTADA_COM_SUCESSO << std::endl;

    return SEM_ERRO;
}
