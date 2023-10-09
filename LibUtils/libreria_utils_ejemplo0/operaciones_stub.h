#ifndef OPERACIONES_STUB_H
#define OPERACIONES_STUB_H
#include "utils.h"

#define OP_FIN  -1
#define OP_SUMA 0
#define OP_LEEFICHERO 1

class operaciones_stub
{
    connection_t conn;
public:
    operaciones_stub();
    int suma(int a, int b);
    std::vector<unsigned char> leeFichero(std::string nombre);
    ~operaciones_stub();
};

#endif // OPERACIONES_STUB_H
