 #pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include "utils.h"
#include "operaciones.h"
#include "persona.h"

class Persona_imp{
	private:
		int clientId;
		Persona* p=nullptr;
	public:
		bool conexionCerrada=false;

		Persona_imp()
		{}
	
		void recOp(int clientId)
		{
			std::vector<unsigned char> packetIn;
			std::vector<unsigned char> packetOut;
			
			recvMSG(clientId,packetIn);
			
			personaOp op=unpack<personaOp>(packetIn);
			
			switch(op)
			{
				case constructorOp:
				{
					p=new Persona();
					int Ok=1;
					pack(packetOut,Ok);			
					
				}
				break;
				case destructorOp:
				{
					delete p;
					pack<int>(packetOut,1);
					conexionCerrada=true;
				}
				break;
				case setDniOp:
				{
					int tam=unpack<int>(packetIn);
					char* d=new char[tam];
					unpackv<char>(packetIn,d,tam);
					p->setDni(std::string(d));
					pack<int>(packetOut,1);
					delete[] d;
					
				}break;
				
				case getDniOp:
				{
					std::string dato;
					dato=p->getDni();
					pack(packetOut,1);
					pack<int>(packetOut,(int)(dato.length()+1));
					packv(packetOut,dato.c_str(),(int)dato.length()+1);					
				}break;
				
				case salvarOp:{
					int tam=unpack<int>(packetIn);
					char* d=new char[tam];
					unpackv<char>(packetIn,d,tam);
					p->salvar(std::string(d));
					pack<int>(packetOut,1);
					delete[] d;
					
				}break;
				
				case cargarOp:{
					int tam=unpack<int>(packetIn);
					char* d=new char[tam];
					unpackv<char>(packetIn,d,tam);
					p->cargar(std::string(d));
					pack<int>(packetOut,1);
					delete[] d;
					
				}break;
				
				
				default:
				{	
					std::cout<<"ERROR: operación no válida\n";
				}break;
			};
			
			sendMSG(clientId,packetOut);

		}
		
	
};
