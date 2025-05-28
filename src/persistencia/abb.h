/**
 * @file abb.h
 * @brief Implementação de uma estrutura de dados persistente de Árvore Binária de Busca (ABB).
 *
 * Esta classe fornece operações básicas de inclusão, remoção, busca de sucessor e conversão para string,
 * mantendo versões persistentes da árvore binária de busca.
 */

#ifndef ABB_H_
#define ABB_H_

#include <array>
#include <functional>
#include <list>
#include <string>
#include <unordered_map>

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
    class noh
    {
        enum class campo { nenhum, chave, pai, filho_esq, filho_dir };
        struct mod
        {
            mod() = default;
            mod(size_t versao, campo campo_modificado, int valor)
                : versao(versao), campo_modificado(campo_modificado), valor_inteiro(valor) {}
            mod(size_t versao, campo campo_modificado, noh* valor)
                : versao(versao), campo_modificado(campo_modificado), valor_ponteiro(valor) {}

            bool disponivel() const
            {
                return campo_modificado == campo::nenhum;
            }

            size_t versao = 0;
            campo campo_modificado = campo::nenhum;
            int valor_inteiro = 0;
            noh* valor_ponteiro = nullptr;
        };

    public:
        noh* copia_compacta() const
        {
            auto noh_compactado = new noh(*this);

            for (mod& m : noh_compactado->mods)
            {
                if (m.campo_modificado == campo::chave)
                {
                    noh_compactado->_chave = m.valor_inteiro;
                }
                else if (m.campo_modificado == campo::pai)
                {
                    noh_compactado->_pai = m.valor_ponteiro;
                }
                else if (m.campo_modificado == campo::filho_esq)
                {
                    noh_compactado->_esq = m.valor_ponteiro;
                }
                else if (m.campo_modificado == campo::filho_dir)
                {
                    noh_compactado->_dir = m.valor_ponteiro;
                }

                m = mod{};
            }

            return noh_compactado;
        }

        int chave(size_t versao) const
        {
            return acessa_campo_inteiro(campo::chave, versao);
        }
        void chave(size_t nova_versao, int n)
        {
            modifica_campo(nova_versao, campo::chave, n);
        }

        noh* pai(size_t versao)
        {
            return acessa_campo_ponteiro(campo::pai, versao);
        }
        void pai(size_t nova_versao, noh* n)
        {
            modifica_campo(nova_versao, campo::pai, n);
        }

        noh* esq(size_t versao)
        {
            return acessa_campo_ponteiro(campo::filho_esq, versao);
        }
        void esq(size_t nova_versao, noh* n)
        {
            modifica_campo(nova_versao, campo::filho_esq, n);
        }

        noh* dir(size_t versao)
        {
            return acessa_campo_ponteiro(campo::filho_dir, versao);
        }
        void dir(size_t nova_versao, noh* n)
        {
            modifica_campo(nova_versao, campo::filho_dir, n);
        }

    private:
        int acessa_campo_inteiro(campo c, size_t versao) const
        {
            int valor_do_campo_na_versao = acessa_campo_inteiro(c);

            for (const mod& m : mods)
            {
                if (m.campo_modificado == c && m.versao <= versao)
                {
                    valor_do_campo_na_versao = m.valor_inteiro;
                }
            }

            return valor_do_campo_na_versao;
        }
        noh* acessa_campo_ponteiro(campo c, size_t versao) const
        {
            noh* valor_do_campo_na_versao = acessa_campo_ponteiro(c);

            for (const mod& m : mods)
            {
                if (m.campo_modificado == c && m.versao <= versao)
                {
                    valor_do_campo_na_versao = m.valor_ponteiro;
                }
            }

            return valor_do_campo_na_versao;
        }

        template <typename T>
        void modifica_campo(size_t nova_versao, campo c, T t)
        {
            if (!adiciona_mod({ nova_versao, c, t }))
            {
                avisa_observadores(nova_versao, copia_compacta());
            }
        }

        int acessa_campo_inteiro(campo c) const
        {
            if (c == campo::chave)
            {
                return _chave;
            }

            return _MAXINT;
        }

        noh* acessa_campo_ponteiro(campo c) const
        {
            if (c == campo::pai)
            {
                return _pai;
            }

            if (c == campo::filho_esq)
            {
                return _esq;
            }

            if (c == campo::filho_dir)
            {
                return _dir;
            }

            return nullptr;
        }

        bool adiciona_mod(mod m)
        {
            bool adicionou = false;

            for (mod& mod_corrente : mods)
            {
                if (mod_corrente.disponivel())
                {
                    mod_corrente = m;
                    adicionou = true;
                    break;
                }
            }

            return adicionou;
        }

        void avisa_observadores(size_t nova_versao, noh* novo_noh)
        {
            _esq->pai(nova_versao, novo_noh);
            _dir->pai(nova_versao, novo_noh);

            if (this == _pai->_esq)
            {
                _pai->esq(nova_versao, novo_noh);
            }
            else
            {
                _pai->dir(nova_versao, novo_noh);
            }
        }

        int _chave = 0;
        noh* _pai = nullptr;
        noh* _esq = nullptr;
        noh* _dir = nullptr;

        // Numa ABB, um noh em particular pode ser apontado por no maximo
        // outros 3 nohs: seu pai, seu filho esquerdo e seu filho direito
        // Logo, p = 3. Numa estrutura persistente, guardamos 2p mods = 6 mods
        std::array<noh::mod, 6> mods;
    };

    enum class campo { nenhum, raiz };
    struct mod
    {
        mod() = default;
        mod(size_t versao, campo campo_modificado, noh* valor)
            : versao(versao), campo_modificado(campo_modificado), valor(valor) {}

        bool disponivel() const
        {
            return campo_modificado == campo::nenhum;
        }

        size_t versao = 0;
        campo campo_modificado = campo::nenhum;
        noh* valor = nullptr;
    };

    ~abb()
    {
    }

    size_t ultima_versao() const
    {
        return _versao;
    }

    bool inclui(int chave)
    {
        const size_t novaVersao = ++_versao;
        auto z = new noh;
        z->chave(novaVersao, chave);
        inclui(novaVersao, z);

        return true;
    }

    bool remove(int chave)
    {
        const size_t novaVersao = ++_versao;

        noh* z = busca(novaVersao, raiz(novaVersao), chave);
        if (z == nullptr)
        {
            return false;
        }

        remove(novaVersao, z);

        return true;
    }

    int sucessor(int x, size_t versao) const
    {
        noh* n = busca_menor_igual(versao, x);
        if (n != nullptr)
        {
            if (x != n->chave(versao))
            {
                return n->chave(versao);
            }

            n = sucessor(versao, n);
            if (n != nullptr)
            {
                return n->chave(versao);
            }
        }

        return _MAXINT;
    }

    std::string to_string(size_t versao) const
    {
        std::string str;

        visita_em_ordem(versao, [versao, &str](const noh* x) {
            str += std::to_string(x->chave(versao));
            str += " ";
        });

        if (!str.empty())
        {
            str.pop_back();
        }

        return str;
    }

private:
    // Referencias:
    // https://www.youtube.com/watch?v=f7sIuYI5M2Y
    // https://www.youtube.com/watch?v=QA2wFn9nQU4

    void visita_em_ordem(size_t versao, std::function<void(noh*)> visita) const
    {
        visita_em_ordem(versao, raiz(versao), visita);
    }

    void visita_em_ordem(size_t versao, noh* x, std::function<void(noh*)> visita) const
    {
        if (x != nullptr)
        {
            visita_em_ordem(versao, x->esq(versao), visita);
            visita(x);
            visita_em_ordem(versao, x->dir(versao), visita);
        }
    }

    noh* busca(size_t versao, noh* x, int chave) const
    {
        while (x != nullptr && x->chave(versao) != chave)
        {
            x = chave < x->chave(versao) ? x->esq(versao) : x->dir(versao);
        }

        return x;
    }

    noh* busca_menor_igual(size_t versao, int chave) const
    {
        noh* x = raiz(versao);
        noh* y = nullptr;
        while (x != nullptr && x->chave(versao) != chave)
        {
            y = x;
            x = chave < x->chave(versao) ? x->esq(versao) : x->dir(versao);
        }

        return x != nullptr ? x : y;
    }

    noh* min(size_t versao, noh* x) const
    {
        while (x->esq(versao) != nullptr)
        {
            x = x->esq(versao);
        }

        return x;
    }

    noh* sucessor(size_t versao, noh* x) const
    {
        if (x->dir(versao) != nullptr && x->dir(versao)->chave(versao) != x->chave(versao))
        {
            return min(versao, x->dir(versao));
        }

        noh* y = x->pai(versao);
        while (y != nullptr && x == y->dir(versao))
        {
            x = y;
            y = x->pai(versao);
        }

        return y;
    }

    void inclui(size_t nova_versao, noh* z)
    {
        noh* y = nullptr;
        noh* x = raiz(nova_versao);

        while (x != nullptr)
        {
            y = x;
            x = z->chave(nova_versao) < x->chave(nova_versao) ? x->esq(nova_versao) : x->dir(nova_versao);
        }

        z->pai(nova_versao, y);
        if (y == nullptr)
        {
            raiz(nova_versao, z);
        }
        else if (z->chave(nova_versao) < y->chave(nova_versao)) {
            y->esq(nova_versao, z);
        }
        else {
            y->dir(nova_versao, z);
        }
    }

    void remove(size_t nova_versao, noh* z)
    {
        if (z->esq(nova_versao) == nullptr)
        {
            transplanta(nova_versao, z, z->dir(nova_versao));
        }
        else if (z->dir(nova_versao) == nullptr)
        {
            transplanta(nova_versao, z, z->esq(nova_versao));
        }
        else
        {
            noh* y = sucessor(nova_versao, z);
            transplanta(nova_versao, y, y->dir(nova_versao));

            y->esq(nova_versao, z->esq(nova_versao));
            z->esq(nova_versao)->pai(nova_versao, y);
            y->dir(nova_versao, z->dir(nova_versao));

            if (z->dir(nova_versao) != nullptr)
            {
                z->dir(nova_versao)->pai(nova_versao, y);
            }
            transplanta(nova_versao, z, y);
        }
    }

    void transplanta(size_t nova_versao, noh* u, noh* v)
    {
        if (u == nullptr)
        {
            return;
        }

        if (u->pai(nova_versao) == nullptr)
        {
            raiz(nova_versao, v);
        }
        else if (u == u->pai(nova_versao)->esq(nova_versao))
        {
            u->pai(nova_versao)->esq(nova_versao, v);
        }
        else
        {
            u->pai(nova_versao)->dir(nova_versao, v);
        }

        if (v != nullptr)
        {
            v->pai(nova_versao, u->pai(nova_versao));
        }
    }

    noh* raiz(size_t versao) const
    {
        if (versao > _versao)
        {
            versao = _versao;
        }

        noh* raiz_na_versao = _raiz;
        auto it = raizesNasVersoes.find(versao);
        if (it != raizesNasVersoes.end())
        {
            raiz_na_versao = it->second;
        }

        for (const mod& m : mods)
        {
            if (m.campo_modificado == campo::raiz && m.versao <= versao)
            {
                raiz_na_versao = m.valor;
            }
        }

        return raiz_na_versao;
    }
    void raiz(size_t nova_versao, noh* n)
    {
        noh* raiz_na_nova_versao = raiz(nova_versao);

        bool adicionou = false;
        for (mod& mod_corrente : mods)
        {
            if (mod_corrente.disponivel())
            {
                mod_corrente = { nova_versao, campo::raiz, n };
                adicionou = true;
                break;
            }
        }

        if (!adicionou)
        {
            // raizesNasVersoes[]
        }

        raizesNasVersoes[nova_versao] = raiz_na_nova_versao;
    }

    noh* _raiz = nullptr;

    // O noh raiz de uma ABB pode ser apontado por no maximo
    // outros 2 nohs: seu filho esquerdo e seu filho direito
    // Logo, p = 2. Guardamos 2p mods = 4 mods
    std::array<abb::mod, 4> mods;

    size_t _versao = 0;
    std::unordered_map<size_t, noh*> raizesNasVersoes;
};

}
}
}

#endif // ABB_H_
