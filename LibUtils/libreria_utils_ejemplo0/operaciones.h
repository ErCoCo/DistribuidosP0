#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <vector>
#include <string>

class operaciones
{

public:
    operaciones();
    int suma(int a, int b);
    std::vector<unsigned char> leeFichero(std::string nombre);

};

#endif // OPERACIONES_H
