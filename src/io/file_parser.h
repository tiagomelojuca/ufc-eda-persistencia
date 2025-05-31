#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <fstream>
#include <string>
#include <vector>

#include "operacao.h"

namespace ufc
{
namespace eda
{
namespace io
{

class file_parser
{
public:
    file_parser(const std::string& filename)
    {
        file.open(filename);
    }

    ~file_parser()
    {
        file.close();
    }

    bool parse()
    {
        if (!file.is_open())
        {
            return false;
        }

        std::string linha;
        while (std::getline(file, linha))
        {
            if (op* operacao = parse_line(linha))
            {
                _operacoes.push_back(*operacao);
                delete operacao;
            }
        }

        return true;
    }

    const std::vector<op>& operacoes() const
    {
        return _operacoes;
    }

private:
    op* parse_line(const std::string& linha)
    {
        if (linha.size() < 5 || linha[3] != ' ')
        {
            return nullptr;
        }

        const std::string instrucao = linha.substr(0, 3);
        const std::string params = linha.substr(4);

        int n_espacos = 0;
        for (char c : params)
        {
            if (c == ' ')
            {
                n_espacos++;
            }
        }
        if (n_espacos > 1)
        {
            return nullptr;
        }

        if (n_espacos == 0)
        {
            if (instrucao == "INC")
            {
                return new op(op::tipo::INCLUSAO, std::atoi(params.c_str()));
            }

            if (instrucao == "REM")
            {
                return new op(op::tipo::REMOCAO, std::atoi(params.c_str()));
            }

            if (instrucao == "IMP")
            {
                return new op(op::tipo::IMPRESSAO, std::atoi(params.c_str()));
            }
        }

        if (n_espacos == 1 && instrucao == "SUC")
        {
            const auto posEspaco = params.find(' ');
            const std::string lparam = params.substr(0, posEspaco);
            const std::string rparam = params.substr(posEspaco + 1);

            return new op(op::tipo::SUCESSAO, std::atoi(lparam.c_str()), std::atoi(rparam.c_str()));
        }

        return nullptr;
    }

    std::ifstream file;
    std::vector<op> _operacoes;
};

}
}
}

#endif // FILE_PARSER_H_
