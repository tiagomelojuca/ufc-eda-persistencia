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

    bool anexa(const op& operacao)
    {
        if (!file.is_open())
        {
            return false;
        }

        file << operacao.to_string() << std::endl;

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
