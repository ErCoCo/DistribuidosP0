#include "operaciones.h"
#include <stdio.h>
#include <stdlib.h>


operaciones::operaciones()
{

}

int operaciones::suma(int a, int b)
{
    return a+b;
}


std::vector<unsigned char> operaciones::leeFichero(std::string nombre)
{


    FILE* f=0x00;
    std::vector<unsigned char> datos;

    f=fopen(nombre.c_str(),"r");
    if(f!=NULL)
    {
        //averiguar el tamaño de fichero
        fseek(f,0,SEEK_END);
        int dataLen=ftell(f);
        fseek(f,0,SEEK_SET);

        datos.resize(dataLen+1);
        fread(datos.data(),1,dataLen,f);
        fclose(f);

        datos[dataLen]='\0';
    }

    return datos;
}
