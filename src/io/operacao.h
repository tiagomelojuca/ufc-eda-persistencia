#ifndef OPERACAO_H_
#define OPERACAO_H_

#include <string>

namespace ufc
{
namespace eda
{
namespace io
{

struct op
{
    enum class tipo { INCLUSAO, REMOCAO, SUCESSAO, IMPRESSAO };

    op(tipo tipoOperacao, int lparam, int rparam = -1)
        : tipoOperacao(tipoOperacao), lparam(lparam), rparam(rparam) {}

    bool operator==(const op& outra) const {
        return tipoOperacao == outra.tipoOperacao &&
               lparam == outra.lparam &&
               rparam == outra.rparam;
    }

    std::string to_string() const
    {
        std::string str;

        if (tipoOperacao == tipo::INCLUSAO)
        {
            str += "INC";
        }
        else if (tipoOperacao == tipo::REMOCAO)
        {
            str += "REM";
        }
        else if (tipoOperacao == tipo::SUCESSAO)
        {
            str += "SUC";
        }
        else if (tipoOperacao == tipo::IMPRESSAO)
        {
            str += "IMP";
        }

        str += " ";
        str += std::to_string(lparam);
        if (rparam != -1)
        {
            str += " ";
            str += std::to_string(rparam);
        }

        return str;
    }

    tipo tipoOperacao;
    int lparam = -1;
    int rparam = -1;
};

}
}
}

#endif // OPERACAO_H_
