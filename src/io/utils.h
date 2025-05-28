#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include "persistencia/abb.h"

namespace ufc
{
namespace eda
{
namespace io
{

    namespace utils
    {
        inline std::string to_string(const ufc::eda::persistencia::abb& arvore, size_t versao)
        {
            std::string str;

            arvore.visita_em_ordem(versao, [versao, &arvore, &str](const ufc::eda::persistencia::abb::noh& x) {
                str += std::to_string(x.chave(versao));
                str += ",";
                str += std::to_string(arvore.profundidade(versao, x));
                str += " ";
            });

            if (!str.empty())
            {
                str.pop_back();
            }

            return str;
        }
    }

}
}
}

#endif // UTILS_H_
