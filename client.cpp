#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"

int main(int argc, char** argv)
{
    auto serverConnection = initClient("127.0.0.1", 10001);

    std::string mensaje = "Hola mundo desde cliente\n";

    // Esto reemplaza las siguientes 3 lineas con resize y copy
    // std::vector<char> packetOut(mensaje.begin(), mensaje.end());
    std::vector<char> packetOut;
    packetOut.resize(mensaje.length());
    std::copy(mensaje.begin(), mensaje.end(), packetOut.begin());

    sendMSG(serverConnection.id, packetOut);

    std::vector<int> packetIn;
    recvMSG(serverConnection.id, packetIn);
    if(packetIn.size()==0){
        std::cout << "Error de conexión"<< __FILE__<<":"<<__LINE__<<"\n";
    }
        
    else{
        if(packetIn[0])
        {
            std::cout << "Conexion correcta\n";
        }else{
            std::cout << "Protocolo incorrectao\n";
        }
    }
        

    closeConnection(serverConnection.id);
    return 0;
}