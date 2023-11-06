#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include "operaciones.h"



void sendStringOp(int serverId,std::string dato, personaOp op)
{
	
	std::vector<unsigned char> mensaje;
	std::vector<unsigned char> res;
	int tam=(dato.length()+1);
	pack(mensaje,op);
	pack(mensaje,tam);
	
	packv(mensaje,dato.c_str(),tam);
	sendMSG(serverId,mensaje);
	recvMSG(serverId,res);
	int ok=unpack<int>(res);
	if(!ok)
		std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<" \n";
}

std::string recibeStringOp(int serverId, personaOp op)
{
	std::string dato="ERROR";

	std::vector<unsigned char> mensaje;
	std::vector<unsigned char> res;
	pack(mensaje,op);
	sendMSG(serverId,mensaje);
	recvMSG(serverId,res);
	
	int ok=unpack<int>(res);
	if(ok!=1)
		std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<" \n";
	else{
		int tam=unpack<int>(res);
		char* d=new char[tam];
		unpackv<char>(res,d,tam);
		dato=std::string(d);
		delete[] d;
	}
	return dato;
}

class Persona_stub
{
	private:

		std::string ip="172.31.57.250";
		int puerto=10001;
		connection_t serverConnection;
	public:
		Persona_stub(){

				serverConnection=initClient(ip, puerto);
				std::vector<unsigned char> mensaje;
				std::vector<unsigned char> res;
				
				pack(mensaje,constructorOp);
				sendMSG(serverConnection.serverId,mensaje);
				recvMSG(serverConnection.serverId,res);
				
				int ok=unpack<int>(res);
				if(!ok)
				{
					std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<" \n";
				}
				
		};
		
		~Persona_stub(){
			std::vector<unsigned char> mensaje;
			std::vector<unsigned char> res;
			
			pack(mensaje,destructorOp);
			sendMSG(serverConnection.serverId,mensaje);
			recvMSG(serverConnection.serverId,res);
			
			int ok=unpack<int>(res);
			if(!ok)
			{
				std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<" \n";
			}
			
			closeConnection(serverConnection.serverId);
		};
		
		void setDni(std::string dato){
			sendStringOp(serverConnection.serverId,dato,setDniOp);
		};
		void setSs(std::string dato){
			sendStringOp(serverConnection.serverId,dato,setSsOp);
		};
		void setNombre(std::string dato){
			sendStringOp(serverConnection.serverId,dato,setNombreOp);

		};
		void setEdad(int dato){
			
		};
	
	
		std::string getDni(){
			return recibeStringOp(serverConnection.serverId,getDniOp);
			
		};
		std::string getSs(){};
		std::string getNombre(){};
		int getEdad() {};
	
		void salvar(std::string file){
			sendStringOp(serverConnection.serverId,file,salvarOp);
		}

		
		void cargar(std::string file){
			sendStringOp(serverConnection.serverId,file,cargarOp);
		};
};