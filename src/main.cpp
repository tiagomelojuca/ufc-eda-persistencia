#include <iostream>

#include "io/executor.h"

int main()
{
    ufc::eda::io::executor e("testa_cli.txt");
    e.executa();

    std::cout << "Hello, EDA!" << std::endl;
}
