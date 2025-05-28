#include <memory>

#include <gtest/gtest.h>

#include "io/utils.h"
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
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  1).c_str(), "6");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  2).c_str(), "5 6");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  3).c_str(), "5 6 7");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  4).c_str(), "5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  5).c_str(), "5 5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  6).c_str(), "2 5 5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  7).c_str(), "2 4 5 5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  8).c_str(), "2 4 4 5 5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore,  9).c_str(), "2 4 5 5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore, 10).c_str(), "2 5 5 6 7 8");
        EXPECT_STREQ(ufc::eda::io::utils::to_string(*arvore, arvore->ultima_versao() + 1).c_str(), "2 5 5 6 7 8");
    }
    {
        // Deve duplicar a raiz se as modificacoes diretas nela excederem 2p = 4
        ufc::eda::persistencia::abb arvore;
        arvore.inclui(5); // gera v1
        arvore.remove(5); // gera v2
        arvore.inclui(5); // gera v3
        arvore.remove(5); // gera v4
        arvore.inclui(6); // gera v5
        arvore.remove(6); // gera v6
        arvore.inclui(7); // gera v7

        EXPECT_STREQ(ufc::eda::io::utils::to_string(arvore, 7).c_str(), "7");
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

        EXPECT_STREQ(ufc::eda::io::utils::to_string(arvore, 6).c_str(), "5 7");
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

    EXPECT_EQ(arvore->sucessor(2, 3), 5);
    EXPECT_EQ(arvore->sucessor(5, 3), 6);
    EXPECT_EQ(arvore->sucessor(6, 3), 7);
    EXPECT_EQ(arvore->sucessor(7, 3), _MAXINT);
    EXPECT_EQ(arvore->sucessor(8, 3), _MAXINT);

    EXPECT_EQ(arvore->sucessor(2, 4), 5);
    EXPECT_EQ(arvore->sucessor(5, 4), 6);
    EXPECT_EQ(arvore->sucessor(6, 4), 7);
    EXPECT_EQ(arvore->sucessor(7, 4), 8);
    EXPECT_EQ(arvore->sucessor(8, 4), _MAXINT);
    EXPECT_EQ(arvore->sucessor(9, 4), _MAXINT);

    EXPECT_EQ(arvore->sucessor(2, 5), 5);
    EXPECT_EQ(arvore->sucessor(5, 5), 6);
    EXPECT_EQ(arvore->sucessor(6, 5), 7);
    EXPECT_EQ(arvore->sucessor(7, 5), 8);
    EXPECT_EQ(arvore->sucessor(8, 5), _MAXINT);
    EXPECT_EQ(arvore->sucessor(9, 5), _MAXINT);

    EXPECT_EQ(arvore->sucessor(1, 6), 2);
    EXPECT_EQ(arvore->sucessor(2, 6), 5);
    EXPECT_EQ(arvore->sucessor(5, 6), 6);
    EXPECT_EQ(arvore->sucessor(6, 6), 7);
    EXPECT_EQ(arvore->sucessor(7, 6), 8);
    EXPECT_EQ(arvore->sucessor(8, 6), _MAXINT);
    EXPECT_EQ(arvore->sucessor(9, 6), _MAXINT);

    EXPECT_EQ(arvore->sucessor(1, 7), 2);
    EXPECT_EQ(arvore->sucessor(2, 7), 4);
    EXPECT_EQ(arvore->sucessor(4, 7), 5);
    EXPECT_EQ(arvore->sucessor(5, 7), 6);
    EXPECT_EQ(arvore->sucessor(6, 7), 7);
    EXPECT_EQ(arvore->sucessor(7, 7), 8);
    EXPECT_EQ(arvore->sucessor(8, 7), _MAXINT);
    EXPECT_EQ(arvore->sucessor(9, 7), _MAXINT);

    EXPECT_EQ(arvore->sucessor(1, 8), 2);
    EXPECT_EQ(arvore->sucessor(2, 8), 4);
    EXPECT_EQ(arvore->sucessor(4, 8), 5);
    EXPECT_EQ(arvore->sucessor(5, 8), 6);
    EXPECT_EQ(arvore->sucessor(6, 8), 7);
    EXPECT_EQ(arvore->sucessor(7, 8), 8);
    EXPECT_EQ(arvore->sucessor(8, 8), _MAXINT);
    EXPECT_EQ(arvore->sucessor(9, 8), _MAXINT);

    EXPECT_EQ(arvore->sucessor(1, 9), 2);
    EXPECT_EQ(arvore->sucessor(2, 9), 4);
    EXPECT_EQ(arvore->sucessor(4, 9), 5);
    EXPECT_EQ(arvore->sucessor(5, 9), 6);
    EXPECT_EQ(arvore->sucessor(6, 9), 7);
    EXPECT_EQ(arvore->sucessor(7, 9), 8);
    EXPECT_EQ(arvore->sucessor(8, 9), _MAXINT);
    EXPECT_EQ(arvore->sucessor(9, 9), _MAXINT);

    EXPECT_EQ(arvore->sucessor(2, 10), 5);
    EXPECT_EQ(arvore->sucessor(5, 10), 6);
    EXPECT_EQ(arvore->sucessor(6, 10), 7);
    EXPECT_EQ(arvore->sucessor(7, 10), 8);
    EXPECT_EQ(arvore->sucessor(8, 10), _MAXINT);
    EXPECT_EQ(arvore->sucessor(3, 10), 5);
    EXPECT_EQ(arvore->sucessor(4, 10), 5);
}
