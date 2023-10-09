#include "operaciones_imp.h"
#include "operaciones_stub.h"
#include "utils.h"
#include <string.h>
#include <vector>

typedef struct rpcPacket_t{

    int opType;
    union{
        struct{
            int a;
            int b;
        }suma;
        struct{
            char nombre[256];
        }leeFichero;
    };
}rpcPacket_t;


operaciones_imp::operaciones_imp(int clientID)
{
    this->clientID=clientID;//waitForConnections(server_fd);
    op=new operaciones();
}


void operaciones_imp::recvOP()
{
    int op=-1;
    
    std::vector<rpcPacket_t> rpc;
    recvMSG<rpcPacket_t>(clientID,rpc);
    op=rpc[0].opType;

    switch(op)
    {
    case OP_SUMA:
    {
        int op1=rpc[0].suma.a;
        int op2=rpc[0].suma.b;

        std::vector<int> res;
        res.push_back(this->op->suma(op1,op2));
        
        sendMSG<int>(clientID,res);
        break;
    }
    case OP_LEEFICHERO:
    {
     
        std::string buff=std::string(rpc[0].leeFichero.nombre);
        std::vector<unsigned char> data=this->op->leeFichero(buff);
        sendMSG(clientID,data);
        break;
        
    }

    case OP_FIN:
    {    salir=true;
        break;
    }
    default:
    {      printf("ERROR OP NO DEFINIDA: %d\n",op);
        break;
    }
    }
}

operaciones_imp::~operaciones_imp()
{

    closeConnection(clientID);

  delete op;
}
