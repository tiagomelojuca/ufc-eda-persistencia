#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <string>
#include <vector>

#include "io/file_writer.h"
#include "io/operacao.h"
#include "persistencia/abb.h"

namespace ufc
{
namespace eda
{
namespace io
{

class executor
{
public:
    executor(const std::string& arquivo_saida)
        : arquivo_saida(arquivo_saida) {}

    void enfila(const ufc::eda::io::op& op)
    {
        _operacoes.push_back(op);
    }

    void executa()
    {
        ufc::eda::io::file_writer fwriter(arquivo_saida);

        for (const ufc::eda::io::op& op : _operacoes)
        {
            executa(fwriter, op);
        }
    }

private:
    void executa(ufc::eda::io::file_writer& fwriter, const ufc::eda::io::op& op)
    {
        if (op.tipoOperacao == ufc::eda::io::op::tipo::INCLUSAO)
        {
            arvore.inclui(op.lparam);
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::REMOCAO)
        {
            arvore.remove(op.lparam);
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::SUCESSAO)
        {
            fwriter << op << std::to_string(arvore.sucessor(op.lparam, op.rparam)) << "\n";
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::IMPRESSAO)
        {
            fwriter << op << arvore.to_string(op.lparam) << "\n";
        }
    }

    std::string arquivo_saida;
    ufc::eda::persistencia::abb arvore;
    std::vector<op> _operacoes;
};

}
}
}

#endif // EXECUTOR_H_
