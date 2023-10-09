#ifndef OPERACIONES_IMP_H
#define OPERACIONES_IMP_H
#include "operaciones.h"

class operaciones_imp
{
    int clientID;
    operaciones* op;

public:
      bool salir=false;
    operaciones_imp(int clientID);
    void recvOP();
    ~operaciones_imp();
};

#endif // OPERACIONES_IMP_H
