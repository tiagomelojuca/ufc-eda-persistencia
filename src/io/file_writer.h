#ifndef FILE_WRITER_H_
#define FILE_WRITER_H_

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

class file_writer {
public:
    file_writer(const std::string& filename)
    {
        file.open(filename);
    }

    ~file_writer()
    {
        file.close();
    }

    template<typename T>
    file_writer& operator<<(const T& t)
    {
        anexa(t);
        return *this;
    }

    bool anexa(const op& operacao)
    {
        return anexa(operacao.to_string()) && anexa("\n");
    }

    bool anexa(const std::string& str)
    {
        if (!file.is_open())
        {
            return false;
        }

        // Deixa o ambiente lidar com a forma adequada de quebra de linha
        if (str == "\n" || str == "\r\n")
        {
            file << std::endl;
        }
        else
        {
            file << str;
        }

        return true;
    }

private:
    std::ofstream file;
    std::vector<op> _operacoes;
};

}
}
}

#endif // FILE_WRITER_H_
