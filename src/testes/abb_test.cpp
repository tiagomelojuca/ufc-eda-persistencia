#include <gtest/gtest.h>

#include "persistencia/abb.h"

TEST(abb_test, temporario)
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

    EXPECT_EQ(arvore.sucessor(2, -1), 5);
    EXPECT_EQ(arvore.sucessor(5, -1), 6);
    EXPECT_EQ(arvore.sucessor(6, -1), 7);
    EXPECT_EQ(arvore.sucessor(7, -1), 8);
    EXPECT_EQ(arvore.sucessor(8, -1), _MAXINT);
    EXPECT_EQ(arvore.sucessor(3, -1), 5);
    EXPECT_EQ(arvore.sucessor(4, -1), 5);
}
