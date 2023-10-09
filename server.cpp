#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"


template<typename T>
T suma(T di, T d2)
{
    return d1+d2;
}


int main(int argc, char** argv)
{
    int serverSocket = initServer(10001);

    while(1)
    {
        if(!checkClient())
        {
            usleep(1000); 
        }else{
            clientId = getLastClientID();

            std::vector<rpcOperacion> packetIn;
            std::vector<int> packetOut;
            recvMSG(clientID, packetIn);

            for(auto &op:packetIn)
            {
                swtich(op.operacion)
                {
                    case opSuma:
                    {
                        int res=suma(op.d1, op.d2);
                        packetOut.push_back(res);
                    }
                }break;
                default:
                    std::cout<<"ERROR: operacion no valida\n"
                break;
            }

            sendMSG(clientId, packetOut);

            closeConnection(clientId);
        }
    }

    close(serverSocket);
    return 0;
}
