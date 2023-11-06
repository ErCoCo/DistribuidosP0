#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"

void recibeDatos(rpcResultado & res)
{
	switch(res.operacion)
				{
					
					case opSumaFloat:
					{
						std::cout<<"el resultado es: "<<res.sumaFloat.res<<"\n";
					}break;					
					case opSumaDouble:
					{
						std::cout<<"el resultado es: "<<res.sumaDouble.res<<"\n";
					}break;					
					case opSumaInt:
					{	
						std::cout<<"el resultado es: "<<res.sumaInt.res<<"\n";

					}break;
					case opSuma3Int:
					{
						std::cout<<"el resultado es: ";
						for(int i=0;i<3;i++) 						
							std::cout<<res.suma3Int.res[i]<<",";
						std::cout<<"\n";
					}break;
					default:
						std::cout<<"ERROR: operación no válida\n";
					break;
				}		
}


int main(int argc, char** argv)
{
	auto serverConnection=initClient("172.31.57.250",10001);
	//crear paquete operación
	std::vector<unsigned char> packetOut;
	std::vector<rpcResultado> packetIn;
	
	int d1=5;
	int d2=7;
	
	rpcOperacion op1,op2;
	op1.sumaInt.d1=d1;
	op1.sumaInt.d2=d2;
	op1.operacion=opSumaInt;
	
	for(int i=0;i<3;i++)
	{
		op2.suma3Int.d1[i]=i;
		op2.suma3Int.d2[i]=i;
	}
	op2.operacion=opSuma3Int;
	
	serializaOperacion(packetOut,op1);
	serializaOperacion(packetOut,op2);
	
	//enviar paquete
	sendMSG(serverConnection.serverId, packetOut);
	//recibir resultado
	recvMSG(serverConnection.serverId, packetIn);
	//if(packetIn.size()!=packetOut.size())
	//{
	
		//std::cout<<"ERROR: resultados recibidos distinto de peticiones enviadas\n";
	//}else{
	for(auto &loquesea: packetIn)
		{
			recibeDatos(loquesea);
		}	
	//}	
	
	closeConnection(serverConnection.serverId);
	return 0;
}