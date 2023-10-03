#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"

int main(int argc, char** argv)
{
    int serverSocket = initServer(10001);

    while(1)
    {
        if(checkClient())
        {
            usleep(1000); 
        }else{
            int clientId = getLastClientID();

            std::vector<char> packetIn;
            recvMSG(clientId, packetIn);

            //for( auto c : packetIn){ Asi esta creando copias
            for (auto &c : packetIn){
                std::cout << c;
            }
            std::cout << '\n';

            std::vector<int> packetOut;
            packetOut.resize(1);
            packetOut[0] = 1;

            sendMSG(clientId, packetOut);

            closeConnection(clientId);
        }
    }

    close(serverSocket);
    return 0;
}
