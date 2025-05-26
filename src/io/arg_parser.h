#ifndef ARG_PARSER_H_
#define ARG_PARSER_H_

#include <string>
#include <vector>

namespace ufc
{
namespace eda
{
namespace io
{

class arg_parser
{
public:
    enum class status
    {
        SUCESSO,
        INDEFINIDO,
        NUMERO_DE_ARGUMENTOS_INVALIDO,
        ARQUIVO_ENTRADA_INVALIDO,
        ARQUIVO_SAIDA_INVALIDO,
        AMBOS_ARQUIVOS_INVALIDOS
    };

    arg_parser() = default;

    void adiciona(const std::string& arg)
    {
        if (_status == status::INDEFINIDO)
        {
            args.push_back(arg);
        }
    }

    status parse()
    {
        if (_status != status::INDEFINIDO)
        {
            return _status;
        }

        valida();

        return _status;
    }

    const std::string& caminho_executavel() const
    {
        return checked_arg(0);
    }

    const std::string& arquivo_entrada() const
    {
        return checked_arg(1);
    }

    const std::string& arquivo_saida() const
    {
        return checked_arg(2);
    }

private:
    struct nome_arquivo_separado
    {
        std::string nome_arquivo;
        std::string extensao;
    };

    void valida()
    {
        if (args.size() != 3)
        {
            _status = status::NUMERO_DE_ARGUMENTOS_INVALIDO;
        }
        else
        {
            const std::string arquivo_entrada_valido = nome_arquivo_validado(args[1]);
            const bool arquivo_entrada_eh_valido = arquivo_entrada_valido != "";

            const std::string arquivo_saida_valido = nome_arquivo_validado(args[2]);
            const bool arquivo_saida_eh_valido = arquivo_saida_valido != "";

            if (!arquivo_entrada_eh_valido && !arquivo_saida_eh_valido)
            {
                _status = status::AMBOS_ARQUIVOS_INVALIDOS;
            }
            else if (!arquivo_entrada_eh_valido)
            {
                _status = status::ARQUIVO_ENTRADA_INVALIDO;
            }
            else if (!arquivo_saida_eh_valido)
            {
                _status = status::ARQUIVO_SAIDA_INVALIDO;
            }
            else
            {
                args[1] = arquivo_entrada_valido;
                args[2] = arquivo_saida_valido;
                _status = status::SUCESSO;
            }
        }
    }

    std::string nome_arquivo_validado(const std::string& arg) const
    {
        auto nome_separado = separa_nome_arquivo(arg);
        std::string& nome_arquivo = nome_separado.nome_arquivo;
        const std::string& extensao = nome_separado.extensao;

        if (extensao != "" && extensao != "txt")
        {
            return "";
        }

        if (nome_arquivo != "")
        {
            nome_arquivo += ".txt";
        }

        return nome_arquivo;
    }

    nome_arquivo_separado separa_nome_arquivo(const std::string& arg) const
    {
        if (arg == "" || arg.back() == '.')
        {
            return { "", "" };
        }

        int posicaoPonto = -1;
        for (auto i = static_cast<int>(arg.size()) - 1; i >= 0; i--)
        {
            if (arg[i] == '.')
            {
                posicaoPonto = i;
                break;
            }
        }

        return posicaoPonto != -1
            ? nome_arquivo_separado { arg.substr(0, posicaoPonto), arg.substr(posicaoPonto + 1) }
            : nome_arquivo_separado { arg, "" };
    }

    const std::string& checked_arg(size_t idx) const
    {
        return _status == status::SUCESSO && idx < args.size()
            ? args[idx]
            : sentinela;
    }

    const std::string sentinela = "";
    std::vector<std::string> args;
    status _status = status::INDEFINIDO;
};

arg_parser cria_arg_parser(int argc, char** argv)
{
    arg_parser parser;
    for (int i = 0; i < argc; i++)
    {
        parser.adiciona(argv[i]);
    }

    return parser;
}

}
}
}

#endif // ARG_PARSER_H_
