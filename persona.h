#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>



class Persona
{
	private:
		std::string dni;
		std::string ss;
		std::string nombre;
		int edad;
	public:
		Persona(){ dni="";ss="";nombre="";edad=0;};
		~Persona(){};
		
		void setDni(std::string dato){this->dni=dato;};
		void setSs(std::string dato){this->ss=dato;};
		void setNombre(std::string dato){this->nombre=dato;};
		void setEdad(int dato){this->edad=dato;};
	
	
		std::string getDni(){return dni;};
		std::string getSs(){return ss;};
		std::string getNombre(){return nombre;};
		int getEdad() {return edad;};
	
		void salvar(std::string file){
			FILE* f=fopen(file.c_str(),"wb");
			int dataLen=dni.length()+1;
			fwrite(&dataLen,sizeof(int),1,f);
			fwrite(dni.c_str(),dataLen,1,f);
			
			 dataLen=ss.length()+1;
			fwrite(&dataLen,sizeof(int),1,f);
			fwrite(ss.c_str(),dataLen,1,f);
			
			 dataLen=nombre.length()+1;
			fwrite(&dataLen,sizeof(int),1,f);
			fwrite(nombre.c_str(),dataLen,1,f);
			
			fwrite(&edad,sizeof(int),1,f);

			fclose(f);			
		};
		
		
		void cargar(std::string file){
			FILE* f=fopen(file.c_str(),"rb");
			int dataLen=0;
			char* cad=nullptr;
			
			
			fread(&dataLen,sizeof(int),1,f);
			cad=new char[dataLen];
			fread(cad,dataLen,1,f);
			dni=std::string(cad);
			delete[] cad;
			
			fread(&dataLen,sizeof(int),1,f);
			cad=new char[dataLen];
			fread(cad,dataLen,1,f);
			ss=std::string(cad);
			delete[] cad;
			
			fread(&dataLen,sizeof(int),1,f);
			cad=new char[dataLen];
			fread(cad,dataLen,1,f);
			nombre=std::string(cad);
			delete[] cad;
			
			fread(&edad,sizeof(int),1,f);

			fclose(f);	
		};
};