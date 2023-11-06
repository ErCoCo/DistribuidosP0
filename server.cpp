#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"

template<typename T>
T suma(T d1, T d2)
{
	return d1+d2;
}

void suma3Int(int* vres,int* v1, int* v2)
{
	for(int i=0;i<3;i++)
	{
		vres[i]=v1[i]+v2[i];
	}

}


int main(int argc, char** argv)
{
	int clientId=-1;
	int serverSocket=initServer(10001);
	
	while(1)
	{
		if(!checkClient())
		{
			usleep(1000);
		}else{
			clientId=getLastClientID();
			//recibir petición de operación
			std::vector<unsigned char> packetIn;
			std::vector<rpcOperacion> operaciones;

			std::vector<rpcResultado> packetOut;
			recvMSG(clientId,packetIn);
			
			operaciones.push_back(deserializaOperacion(packetIn));
			operaciones.push_back(deserializaOperacion(packetIn));
			
			
			//ejecutar operación
			for(auto &op: operaciones)
			{
				switch(op.operacion)
				{
					
					case opSumaFloat:
					{
						rpcResultado resultado;
						resultado.operacion=opSumaFloat;
						resultado.sumaFloat.res=suma(op.sumaFloat.d1, op.sumaFloat.d2);
						packetOut.push_back(resultado);
					}break;					
					case opSumaDouble:
					{
						rpcResultado resultado;
						resultado.operacion=opSumaDouble;
						resultado.sumaDouble.res=suma(op.sumaDouble.d1, op.sumaDouble.d2);
						packetOut.push_back(resultado);
					}break;					
					case opSumaInt:
					{	rpcResultado resultado;
						resultado.operacion=opSumaInt;
						resultado.sumaInt.res=suma(op.sumaInt.d1, op.sumaInt.d2);
						packetOut.push_back(resultado);
					}break;

					case opSuma3Int:
					{	rpcResultado resultado;
						resultado.operacion=opSuma3Int;
						suma3Int(resultado.suma3Int.res,op.suma3Int.d1, op.suma3Int.d2);
						packetOut.push_back(resultado);
					}break;					
					default:
						std::cout<<"ERROR: operación no válida\n";
					break;
				}
			}
			
			sendMSG(clientId,packetOut);
			
			
			//devolver resultado
			
			
			closeConnection(clientId);
		}
		
	}
	
	close(serverSocket);
	return 0;
	
}