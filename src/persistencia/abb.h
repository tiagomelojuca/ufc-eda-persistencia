/**
 * @file abb.h
 * @brief Implementação de uma estrutura de dados persistente de Árvore Binária de Busca (ABB).
 *
 * Esta classe fornece operações básicas de inclusão, remoção, busca de sucessor e conversão para string,
 * mantendo versões persistentes da árvore binária de busca.
 */

#ifndef ABB_H_
#define ABB_H_

#include <string>

#define _MAXINT 2147483647

namespace ufc
{
namespace eda
{
namespace persistencia
{

class abb
{
public:
    bool inclui(int chave)
    {
        return false;
    }

    bool remove(int chave)
    {
        return false;
    }

    int sucessor(int x, int versao) const
    {
        return _MAXINT;
    }

    std::string to_string() const
    {
        return "";
    }

private:
    int versao = 0;
};

}
}
}

#endif // ABB_H_
