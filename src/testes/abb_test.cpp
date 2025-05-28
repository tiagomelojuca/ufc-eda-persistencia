#include <memory>

#include <gtest/gtest.h>

#include "persistencia/abb.h"

ufc::eda::persistencia::abb* monta_arvore_videoaula()
{
    auto arvore = new ufc::eda::persistencia::abb;

    arvore->inclui(6); // gera  v1
    arvore->inclui(5); // gera  v2
    arvore->inclui(7); // gera  v3
    arvore->inclui(8); // gera  v4
    arvore->inclui(5); // gera  v5
    arvore->inclui(2); // gera  v6
    arvore->inclui(4); // gera  v7
    arvore->inclui(4); // gera  v8
    arvore->remove(4); // gera  v9
    arvore->remove(4); // gera v10

    return arvore;
}

TEST(abb_test, deve_ser_capaz_de_imprimir_qualquer_versao)
{
    {
        std::unique_ptr<ufc::eda::persistencia::abb> arvore { monta_arvore_videoaula() };

        EXPECT_EQ(arvore->ultima_versao(), 10u);
        EXPECT_STREQ(arvore->to_string( 1).c_str(), "6");
        EXPECT_STREQ(arvore->to_string( 2).c_str(), "5 6");
        EXPECT_STREQ(arvore->to_string( 3).c_str(), "5 6 7");
        EXPECT_STREQ(arvore->to_string( 4).c_str(), "5 6 7 8");
        EXPECT_STREQ(arvore->to_string( 5).c_str(), "5 5 6 7 8");
        EXPECT_STREQ(arvore->to_string( 6).c_str(), "2 5 5 6 7 8");
        EXPECT_STREQ(arvore->to_string( 7).c_str(), "2 4 5 5 6 7 8");
        EXPECT_STREQ(arvore->to_string( 8).c_str(), "2 4 4 5 5 6 7 8");
        EXPECT_STREQ(arvore->to_string( 9).c_str(), "2 4 5 5 6 7 8");
        EXPECT_STREQ(arvore->to_string(10).c_str(), "2 5 5 6 7 8");
        EXPECT_STREQ(arvore->to_string(arvore->ultima_versao() + 1).c_str(), "2 5 5 6 7 8");
    }
    {
        // Deve duplicar a raiz se as modificacoes diretas excederem 2p = 4
        ufc::eda::persistencia::abb arvore;
        arvore.inclui(5); // gera v1
        arvore.remove(5); // gera v2
        arvore.inclui(5); // gera v3
        arvore.remove(5); // gera v4
        arvore.inclui(5); // gera v5
        arvore.remove(5); // gera v6
        arvore.inclui(6); // gera v7

        EXPECT_STREQ(arvore.to_string(7).c_str(), "6");
    }
    {
        // Se o noh raiz for duplicado indiretamente, a arvore deve ser avisada
        ufc::eda::persistencia::abb arvore;
        arvore.inclui(5); // gera v1
        arvore.inclui(6); // gera v2
        arvore.remove(6); // gera v3
        arvore.inclui(6); // gera v4
        arvore.remove(6); // gera v5
        arvore.inclui(7); // gera v6

        EXPECT_STREQ(arvore.to_string(6).c_str(), "7");
    }
}

TEST(abb_test, deve_ser_capaz_de_encontrar_sucessor_para_qualquer_versao)
{
    std::unique_ptr<ufc::eda::persistencia::abb> arvore { monta_arvore_videoaula() };

    EXPECT_EQ(arvore->sucessor(2, 1), 6);
    EXPECT_EQ(arvore->sucessor(5, 1), 6);
    EXPECT_EQ(arvore->sucessor(6, 1), _MAXINT);
    EXPECT_EQ(arvore->sucessor(7, 1), _MAXINT);

    EXPECT_EQ(arvore->sucessor(2, 2), 5);
    EXPECT_EQ(arvore->sucessor(5, 2), 6);
    EXPECT_EQ(arvore->sucessor(6, 2), _MAXINT);
    EXPECT_EQ(arvore->sucessor(7, 2), _MAXINT);

    EXPECT_EQ(arvore->sucessor(2, 10), 5);
    EXPECT_EQ(arvore->sucessor(5, 10), 6);
    EXPECT_EQ(arvore->sucessor(6, 10), 7);
    EXPECT_EQ(arvore->sucessor(7, 10), 8);
    EXPECT_EQ(arvore->sucessor(8, 10), _MAXINT);
    EXPECT_EQ(arvore->sucessor(3, 10), 5);
    EXPECT_EQ(arvore->sucessor(4, 10), 5);
}
