/**
 * @file abb.h
 * @brief Implementação de uma estrutura de dados persistente de Árvore Binária de Busca (ABB).
 *
 * Esta classe fornece operações básicas de inclusão, remoção, busca de sucessor e conversão para string,
 * mantendo versões persistentes da árvore binária de busca.
 */

#ifndef ABB_H_
#define ABB_H_

#include <functional>
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

    ~abb()
    {
        // TODO: limpar memoria
    }

    bool inclui(int chave)
    {
        auto z = new noh;
        z->chave = chave;
        inclui(z);

        return true;
    }

    bool remove(int chave)
    {
        const noh* z = busca(raiz, chave);
        if (z == nullptr)
        {
            return false;
        }

        remove(z);
        delete z;

        return true;
    }

    int sucessor(int x, int versao) const
    {
        const noh* n = busca_menor_igual(x);
        if (n != nullptr)
        {
            n = sucessor(n);

            if (n != nullptr)
            {
                return n->chave;
            }
        }

        return _MAXINT;
    }

    std::string to_string(int versao) const
    {
        std::string str;

        visita_em_ordem([&str](const noh* x) {
            str += std::to_string(x->chave);
            str += " ";
        });

        if (!str.empty())
        {
            str.pop_back();
        }

        return str;
    }

    // Metodos para depuracao
    std::string _arvore_em_ascii() const
    {
        std::string arvore;
        _arvore_em_ascii(arvore, raiz, "", true);

        return arvore;
    }

private:
    // Referencias:
    // https://www.youtube.com/watch?v=f7sIuYI5M2Y
    // https://www.youtube.com/watch?v=QA2wFn9nQU4

    void visita_em_ordem(std::function<void(const noh*)> visita) const
    {
        visita_em_ordem(raiz, visita);
    }

    void visita_em_ordem(const noh* x, std::function<void(const noh*)> visita) const
    {
        if (x != nullptr)
        {
            visita_em_ordem(x->esq, visita);
            visita(x);
            visita_em_ordem(x->dir, visita);
        }
    }

    const noh* busca(const noh* x, int chave) const
    {
        while (x != nullptr && x->chave != chave)
        {
            x = chave < x->chave ? x->esq : x->dir;
        }

        return x;
    }

    const noh* busca_menor_igual(int chave) const
    {
        const noh* x = raiz;
        const noh* y = nullptr;
        while (x != nullptr && x->chave != chave)
        {
            y = x;
            x = chave < x->chave ? x->esq : x->dir;
        }

        return x != nullptr ? x : y;
    }

    noh* min(noh* x) const
    {
        while (x->esq != nullptr)
        {
            x = x->esq;
        }

        return x;
    }

    noh* sucessor(const noh* x) const
    {
        if (x->dir != nullptr && x->dir->chave != x->chave)
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

    void _arvore_em_ascii(std::string& out, const noh* x, const std::string& prefixo, bool ehUltimo) const
    {
        if (x != nullptr)
        {
            out += prefixo;
            out += (ehUltimo ? "|___" : "|---");
            out += std::to_string(x->chave);
            out += "\n";

            const std::string novoPrefixo = prefixo + (ehUltimo ? "    " : "|   ");
            if (x->esq != nullptr || x->dir != nullptr)
            {
                if (x->dir != nullptr)
                {
                    _arvore_em_ascii(out, x->dir, novoPrefixo, x->esq == nullptr);
                }

                if (x->esq != nullptr)
                {
                    _arvore_em_ascii(out, x->esq, novoPrefixo, true);
                }
            }
        }
    }

    noh* raiz = nullptr;
    int versao = 0;
};

}
}
}

#endif // ABB_H_
