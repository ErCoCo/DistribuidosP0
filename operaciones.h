#pragma once
#include <vector>
#include <iostream>

typedef enum{
	opSumaInt=1,
	opSumaFloat=2,
	opSumaDouble=3,
	opSuma3Int=4
}tipoOperacion;

typedef enum  personaOp
{
	constructorOp=1,
	destructorOp=2,
	
	setDniOp=3,
	getDniOp=4,
	
	setNombreOp=5,
	getNombreOp=6,
	setSsOp=7,
	getSsOp=8,
	setEdadOp=9,
	getEdadOp=10,
	
	salvarOp=11,
	cargarOp=12
	
}personaOp;


typedef struct {
	
	tipoOperacion operacion;
	union{
		struct{
			int d1;
			int d2;
		}sumaInt;
		/////////
		struct{
			float d1;
			float d2;
		}sumaFloat;
		/////////
		struct{
			double d1;
			double d2;
		}sumaDouble;
		
			/////////
		struct{
			int d1[3];
			int d2[3];
		}suma3Int;
	
	};
	
}rpcOperacion;



typedef struct __attribute__((packed)){
	tipoOperacion operacion;
	
	union{
		struct{
			int res;
		}sumaInt;
		/////////
		struct{
			float res;
		}sumaFloat;
		/////////
		struct{
			double res;
		}sumaDouble;
		
		/////////
		struct{
			int res[3];
		}suma3Int;
	};
	
}rpcResultado;


template <typename T>
inline void pack(std::vector<unsigned char> &packet, T data)
{
	unsigned char* ptr=(unsigned char*)&data;
	int dataSize=sizeof(T);
	int init=packet.size();
	packet.resize(init+dataSize);
	std::copy(ptr, ptr+dataSize, packet.begin()+init);
	
}

template <typename T>
inline T unpack(std::vector<unsigned char> &packet)
{
	T data;
	T* ptr=(T*)packet.data();
	data=ptr[0];
	int dataSize=sizeof(T);
	int init=packet.size();
	for(int i=dataSize;i<packet.size();i++)
	{
		packet[i-dataSize]=packet[i];
	}
	packet.resize(init-dataSize);
	return data;
}


template<typename T>
inline void packv(std::vector<unsigned char> &packet,T* arr,int size)
{
		for(int i=0;i<size;i++)
			pack(packet,arr[i]);
	
}

template<typename T>
inline void unpackv(std::vector<unsigned char> &packet,T* arr,int size)
{
	
		for(int i=0;i<size;i++)
			arr[i]=unpack<T>(packet);
	
	
}



inline void serializaOperacion(std::vector<unsigned char> &packet, rpcOperacion op)
{
	
	//primer byte: Tipo operación , 256 posibilidades
	unsigned char tipoOp=op.operacion;
	pack(packet, tipoOp);
			switch(op.operacion)
				{
					
					case opSumaFloat:
					{
						pack(packet,op.sumaFloat.d1);
						pack(packet,op.sumaFloat.d2);
						
					}break;					
					case opSumaDouble:
					{
						pack(packet,op.sumaDouble.d1);
						pack(packet,op.sumaDouble.d2);
					}break;					
					case opSumaInt:
					{	pack(packet,op.sumaInt.d1);
						pack(packet,op.sumaInt.d2);
					}break;

					case opSuma3Int:
					{
						for(int i=0;i<3;i++)
							pack(packet,op.suma3Int.d1[i]);
		
						for(int i=0;i<3;i++)
							pack(packet,op.suma3Int.d2[i]);
					}break;					
					default:
						std::cout<<"ERROR: operación no válida\n";
					break;
				}
	
	
	
}


inline rpcOperacion deserializaOperacion(std::vector<unsigned char> &packet)
{
	rpcOperacion op;
		
	unsigned char tipoOp=unpack<unsigned char>(packet);
		
	//primer byte: Tipo operación , 256 posibilidades
	op.operacion=(tipoOperacion)tipoOp;
	
			switch(op.operacion)
				{
					
					case opSumaFloat:
					{
						op.sumaFloat.d1=unpack<float>(packet);
						op.sumaFloat.d2=unpack<float>(packet);
						
					}break;					
					case opSumaDouble:
					{
						op.sumaDouble.d1=unpack<double>(packet);
						op.sumaDouble.d2=unpack<double>(packet);
					}break;					
					case opSumaInt:
					{
						op.sumaInt.d1=unpack<int>(packet);
						op.sumaInt.d2=unpack<int>(packet);
					}break;

					case opSuma3Int:
					{
						for(int i=0;i<3;i++)
							op.suma3Int.d1[i]=unpack<int>(packet);
		
						for(int i=0;i<3;i++)
							op.suma3Int.d2[i]=unpack<int>(packet);
					}break;					
					default:
						std::cout<<"ERROR: operación no válida\n";
					break;
				}
	return op;
	
	
}














