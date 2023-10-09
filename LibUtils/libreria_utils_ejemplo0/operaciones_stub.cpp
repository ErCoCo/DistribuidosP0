#include "operaciones_stub.h"
#include "utils.h"


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

operaciones_stub::operaciones_stub()
{
     conn=initClient("127.0.0.1",60000);
}

int operaciones_stub::suma(int a, int b)
{

    std::vector<rpcPacket_t> rpc(1);
    std::vector<int> result(0);

    rpc[0].opType=OP_SUMA;
    rpc[0].suma.a=a;
    rpc[0].suma.b=b;
    
    sendMSG(0,rpc);//send operation
    recvMSG(0,result);//receive result    

    return result[0];
}


std::vector<unsigned char> operaciones_stub::leeFichero(std::string nombre)
{

    std::vector<rpcPacket_t> rpc(1);
    std::vector<unsigned char> result(0);
    
    rpc[0].opType=OP_LEEFICHERO;
    strncpy(rpc[0].leeFichero.nombre,nombre.c_str(),sizeof(rpc[0].leeFichero.nombre));
    
    sendMSG(0,rpc);//send operation
    
    recvMSG(0,result);//receive result    

    return result;
}

operaciones_stub::~operaciones_stub()
{

    std::vector<rpcPacket_t> rpc(1);
    rpc[0].opType=OP_FIN;

    sendMSG(0,rpc);//send operation

    closeConnection(0);
}
