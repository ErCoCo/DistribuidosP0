#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"
#include "persona_stub.h"

int main(int argc, char** argv)
{
	Persona_stub p1=Persona_stub();
	
	//p1.setNombre("Pepito");
	p1.setDni("123456789X");
	
	std::string dni=p1.getDni();
	std::cout<<"el dni es:"<<dni<<"\n";
	
	//p1.setSs("321654654P");
	//p1.setEdad(17);
	
	p1.salvar("pepito.pers");
	
	return 0;
}