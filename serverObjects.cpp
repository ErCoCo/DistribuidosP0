#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"
#include <thread>
#include "persona_imp.h"

void atiendeCliente(int clientId)
{

	Persona_imp* p=new Persona_imp();
	//mientras no cierre conexion
	while(!p->conexionCerrada){
		//atender operación
		p->recOp(clientId);
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
			std::thread *t= new std::thread(atiendeCliente,getLastClientID());

		}
	}
	close(serverSocket);
	
	return 0;
}