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
        noh(abb* parent) : _arvore_associada(parent) {};

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
            const mod m = { nova_versao, c, t };
            if (!adiciona_mod(m))
            {
                noh* novo_noh = copia_compacta();
                novo_noh->mods[0] = m;

                avisa_observadores(nova_versao, novo_noh);

                // ToDo: aqui estava permitindo chamar direto a std::list
                //       de nohs_unificados da abb. Nao deveria. Investigar.
                _arvore_associada->_registra_noh(novo_noh);
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
            if (_esq != nullptr)
            {
                _esq->pai(nova_versao, novo_noh);
            }
            
            if (_dir != nullptr)
            {
                _dir->pai(nova_versao, novo_noh);
            }

            if (_pai != nullptr)
            {
                if (this == _pai->_esq)
                {
                    _pai->esq(nova_versao, novo_noh);
                }
                else
                {
                    _pai->dir(nova_versao, novo_noh);
                }
            }
            else
            {
                // Se o pai eh nulo, o noh eh raiz
                // Precisa avisar a arvore tambem
                _arvore_associada->raiz(nova_versao, novo_noh);
            }
        }

        int _chave = _MAXINT;
        noh* _pai = nullptr;
        noh* _esq = nullptr;
        noh* _dir = nullptr;
        abb* _arvore_associada = nullptr;

        // Numa ABB, um noh em particular pode ser apontado por no maximo
        // outros 3 nohs: seu pai, seu filho esquerdo e seu filho direito
        // Logo, p = 3. Numa estrutura persistente, guardamos 2p mods = 6 mods
        std::array<noh::mod, 6> mods;
    };

    class noh_raiz
    {
        enum class campo { nenhum, noh };
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

    public:
        noh_raiz(abb* arvore_associada) : _arvore(arvore_associada) {}

        noh_raiz* copia_compacta() const
        {
            auto noh_raiz_compactado = new noh_raiz(*this);

            for (mod& m : noh_raiz_compactado->mods)
            {
                if (m.campo_modificado == campo::noh)
                {
                    noh_raiz_compactado->_noh = m.valor;
                }

                m = mod{};
            }

            return noh_raiz_compactado;
        }

        noh* get_noh(size_t versao)
        {
            noh* _noh = nullptr;

            for (const mod& m : mods)
            {
                if (m.campo_modificado == campo::noh && m.versao <= versao)
                {
                    _noh = m.valor;
                }
            }

            return _noh;
        }

        void set_noh(size_t nova_versao, noh* n)
        {
            bool adicionou = false;
            for (mod& mod_corrente : mods)
            {
                if (mod_corrente.disponivel())
                {
                    mod_corrente = { nova_versao, campo::noh, n };
                    adicionou = true;
                    break;
                }
            }

            if (!adicionou)
            {
                auto novo_noh_raiz = copia_compacta();
                _arvore->_registra_raiz(nova_versao, novo_noh_raiz);
                novo_noh_raiz->mods[0] = { nova_versao, campo::noh, n };
            }
        }

    private:
        abb* _arvore = nullptr;
        noh* _noh = nullptr;

        // A ideia dessa classe eh ser um wrapper para a raiz, um "noh de noh".
        // Apenas a propria arvore aponta para ele, logo, p = 1 => 2p = 2 mods
        std::array<noh_raiz::mod, 2> mods;
    };

    abb()
    {
        _registra_raiz(0, new noh_raiz(this));
    }

    ~abb()
    {
        for (noh* noh_corrente : nohs_unificados)
        {
            delete noh_corrente;
        }
    }

    size_t ultima_versao() const
    {
        return _versao;
    }

    void inclui(int chave)
    {
        const size_t novaVersao = ++_versao;

        auto z = new noh(this);
        z->chave(novaVersao, chave);
        inclui(novaVersao, z);

        _registra_noh(z);
    }

    void remove(int chave)
    {
        const size_t novaVersao = ++_versao;

        if (noh* z = busca(novaVersao, raiz(novaVersao), chave))
        {
            remove(novaVersao, z);
        }
    }

    int sucessor(int x, size_t versao) const
    {
        const int menor_chave_arvore = min(versao, raiz(versao))->chave(versao);
        if (x < menor_chave_arvore)
        {
            return menor_chave_arvore;
        }

        if (noh* n = busca_menor_igual(versao, x))
        {
            if (n = sucessor(versao, n))
            {
                return n->chave(versao);
            }
        }

        return _MAXINT;
    }

    void visita_em_ordem(size_t versao, std::function<void(const noh&)> visita) const
    {
        visita_em_ordem(versao, raiz(versao), visita);
    }

    void _registra_noh(noh* n)
    {
        nohs_unificados.push_back(n);
    }
    void _registra_raiz(size_t nova_versao, noh_raiz* nova_raiz)
    {
        raizes_nas_versoes.push_back({ nova_versao, nova_raiz });
    }

private:
    // Referencias:
    // https://www.youtube.com/watch?v=f7sIuYI5M2Y
    // https://www.youtube.com/watch?v=QA2wFn9nQU4

    void visita_em_ordem(size_t versao, noh* x, std::function<void(const noh&)> visita) const
    {
        if (x != nullptr)
        {
            visita_em_ordem(versao, x->esq(versao), visita);
            visita(*x);
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
        return get_noh_raiz(versao)->get_noh(versao);
    }
    void raiz(size_t nova_versao, noh* n)
    {
        get_noh_raiz(nova_versao)->set_noh(nova_versao, n);
    }

    noh_raiz* get_noh_raiz(size_t versao) const
    {
        for (auto i = static_cast<int>(raizes_nas_versoes.size()) - 1; i >= 0; i--)
        {
            const auto raiz_na_versao = raizes_nas_versoes[i];
            if (versao >= raiz_na_versao.versao)
            {
                return raiz_na_versao.raiz;
            }
        }

        return nullptr;
    }

    struct par_versao_raiz
    {
        size_t versao;
        noh_raiz* raiz;
    };

    size_t _versao = 0;
    std::vector<par_versao_raiz> raizes_nas_versoes;
    std::list<noh*> nohs_unificados;
};

}
}
}

#endif // ABB_H_
