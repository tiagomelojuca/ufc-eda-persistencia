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
    struct noh
    {
        int chave = 0;

        noh* pai = nullptr;
        noh* esq = nullptr;
        noh* dir = nullptr;
    };

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
    // Referencias:
    // https://www.youtube.com/watch?v=f7sIuYI5M2Y
    // https://www.youtube.com/watch?v=QA2wFn9nQU4

    const noh* busca(const noh* x, int chave) const
    {
        while (x != nullptr && x->chave != chave)
        {
            x = chave < x->chave ? x->esq : x->dir;
        }

        return x;
    }

    noh* min(noh* x) const
    {
        while (x->esq != nullptr)
        {
            x = x->esq;
        }

        return x;
    }

    noh* max(noh* x) const
    {
        while (x->dir != nullptr)
        {
            x = x->dir;
        }

        return x;
    }

    noh* sucessor(const noh* x) const
    {
        if (x->dir != nullptr)
        {
            return min(x->dir);
        }

        noh* y = x->pai;
        while (y != nullptr && x == y->dir)
        {
            x = y;
            y = x->pai;
        }

        return y;
    }

    void inclui(noh* z)
    {
        noh* y = nullptr;
        noh* x = raiz;

        while (x != nullptr)
        {
            y = x;
            x = z->chave < x->chave ? x->esq : x->dir;
        }

        z->pai = y;
        if (y == nullptr)
        {
            raiz = z;
        }
        else if (z->chave < y->chave) {
            y->esq = z;
        }
        else {
            y->dir = z;
        }
    }

    void remove(const noh* z)
    {
        if (z->esq == nullptr)
        {
            transplanta(z, z->dir);
        }
        else if (z->dir == nullptr)
        {
            transplanta(z, z->esq);
        }
        else
        {
            noh* y = sucessor(z);
            transplanta(y, y->dir);

            y->esq = z->esq;
            z->esq->pai = y;
            y->dir = z->dir;

            if (z->dir != nullptr)
            {
                z->dir->pai = y;
            }
            transplanta(z, y);
        }
    }

    void transplanta(const noh* u, noh* v)
    {
        if (u == nullptr)
        {
            return;
        }

        if (u->pai == nullptr)
        {
            raiz = v;
        }
        else if (u == u->pai->esq)
        {
            u->pai->esq = v;
        }
        else
        {
            u->pai->dir = v;
        }

        if (v != nullptr)
        {
            v->pai = u->pai;
        }
    }

    noh* raiz = nullptr;
    int versao = 0;
};

}
}
}

#endif // ABB_H_
