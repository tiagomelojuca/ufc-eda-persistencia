#include <gtest/gtest.h>

#include "persistencia/abb.h"

TEST(abb_test, deve_ser_capaz_de_inserir_elemento)
{
    ufc::eda::persistencia::abb arvore;

    arvore.inclui(6);
    arvore.inclui(5);
    arvore.inclui(7);
    arvore.inclui(8);
    arvore.inclui(5);
    arvore.inclui(2);

    arvore.inclui(4);
    arvore.inclui(4);
    arvore.remove(4);
    arvore.remove(4);

    EXPECT_STREQ(arvore.to_string().c_str(), "2 5 5 6 7 8");
}
