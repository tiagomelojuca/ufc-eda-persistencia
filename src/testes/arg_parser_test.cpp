#include <gtest/gtest.h>

#include "io/arg_parser.h"

TEST(arg_parser_test, deve_ser_capaz_de_validar_argumentos)
{
    {
        // OK, caso padrao
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada");
        arg_parser.adiciona("saida");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::SUCESSO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "/usr/bin/cli");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "entrada.txt");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "saida.txt");
    }
    {
        // OK, o usuario pode passar a extensao .txt explicitamente
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::SUCESSO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "/usr/bin/cli");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "entrada.txt");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "saida.txt");
    }
    {
        // OK, a extensao do arquivo eh o que vem apos o ultimo ponto
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.bmp.txt");
        arg_parser.adiciona("saida.bmp.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::SUCESSO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "/usr/bin/cli");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "entrada.bmp.txt");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "saida.bmp.txt");
    }
    {
        // ERRO, o arquivo de entrada eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de entrada eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona(".");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de entrada eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("a.");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de entrada eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona(".a");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de entrada possui extensao invalida
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.bmp");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, a extensao do arquivo eh o que vem apos o ultimo ponto
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt.bmp");
        arg_parser.adiciona("saida.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_ENTRADA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de saida eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona("");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de saida eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona(".");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de saida eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona("a.");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de saida eh invalido
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona(".a");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, o arquivo de saida possui extensao invalida
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona("saida.bmp");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, a extensao do arquivo eh o que vem apos o ultimo ponto
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona("saida.txt.bmp");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::ARQUIVO_SAIDA_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, arquivo de entrada e de saida possuem extensao invalida
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.bmp");
        arg_parser.adiciona("saida.bmp");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::AMBOS_ARQUIVOS_INVALIDOS);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, a extensao do arquivo eh o que vem apos o ultimo ponto
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt.bmp");
        arg_parser.adiciona("saida.txt.bmp");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::AMBOS_ARQUIVOS_INVALIDOS);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, nao passou nenhum argumento
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::NUMERO_DE_ARGUMENTOS_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, faltou o arquivo de saida
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::NUMERO_DE_ARGUMENTOS_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
    {
        // ERRO, passou argumentos inesperados
        ufc::eda::io::arg_parser arg_parser;
        arg_parser.adiciona("/usr/bin/cli");
        arg_parser.adiciona("entrada.txt");
        arg_parser.adiciona("saida.txt");
        arg_parser.adiciona("argumento extra");
        const auto status = arg_parser.parse();

        EXPECT_TRUE(status == ufc::eda::io::arg_parser::status::NUMERO_DE_ARGUMENTOS_INVALIDO);
        EXPECT_STREQ(arg_parser.caminho_executavel().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_entrada().c_str(), "");
        EXPECT_STREQ(arg_parser.arquivo_saida().c_str(), "");
    }
}
