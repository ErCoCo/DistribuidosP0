#include "utils.h"
#include <iostream>
#include <string>
#include "operaciones_imp.h"
#include <thread>
#include <list>


std::list<std::thread*> threadList;
void clientManager(int clientID)
{
    operaciones_imp* op=new operaciones_imp(clientID);

     while(!op->salir){
       op->recvOP();
     }
     delete op;

}

int main(int argc, char** argv)
{
 int server_fd=initServer(60000);
 int lastClientID=-1;
 while(1){
     while(!checkClient()){
         usleep(1000);
     }
     int clientID=getLastClientID();

     threadList.push_back(new std::thread(clientManager,clientID));
 }

  closeConnection(server_fd);
 return 0;
}
