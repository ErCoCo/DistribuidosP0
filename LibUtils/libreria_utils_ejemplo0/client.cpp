#include "utils.h"
#include <string>
#include "operaciones.h"
#include "operaciones_stub.h"
#include <iostream>
#include <string>


int main(int argc,char** argv)
{
/*
	int op1=0;
	int op2=0;
	char* buffer;
	int bufferSize=0;
	int server_fd=initClient("10.0.2.7",60000);
	std::string msg= "Hola desde cliente\n";
	bufferSize=msg.length()+1;

	recvMSG(server_fd,(void**)&buffer,&bufferSize);
	op1=((int*)buffer)[0];
	delete [] buffer;

	recvMSG(server_fd,(void**)&buffer,&bufferSize);
	op2=((int*)buffer)[0];
	
	
	int result=suma(op1,op2);
		
	sendMSG(server_fd,(void*)&result,sizeof(int));
		
	
	closeConnection(server_fd);
    return 0;*/


    operaciones_stub* op=new operaciones_stub();
    int res=op->suma(10,35);
    std::vector<unsigned char> frase= op->leeFichero("Holamundo.txt");
    
    std::cout<<" El resultado es "<<res<<" el fichero contiene "<<std::string(frase.begin(),frase.end())<<"\n";

    delete op;
    return 0;
}
