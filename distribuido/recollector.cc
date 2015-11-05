//Carlos Andres Martinez - {Client - workers - recollector }
#include <iostream>  // std::cout
#include <fstream>  //std::ifstream
#include <string>
#include <list>
#include <cassert>
#include <map>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

int main(int argc, char **argv)
{
  string port, ipc;
  port = argv[1];
  cout << "Running Servidor with ip: " << ipc <<", port: " << port << endl;

  int indice=0;

  context ctx;
  socket sx(ctx, socket_type::xrep);         // socket broker-server
  sx.bind("tcp://*:"+port);
  int longitud_msg;
	while(true)
	{
			message r;
			sx.receive(r);
			cout << "recibe" << r.parts() << "partes" << endl;
			longitud_msg = r.parts();
			for(size_t i = 0; i < r.parts(); i++) {
				cout << r.get(i) << endl;
			}
			string idc, idb;        // id
			r >> idc >> idb;
			//cout << ipc << endl;
			ipc = r.get(longitud_msg -1);
			cout <<"ip cliente:"<< ipc <<endl;
			int operador;     // 1 buscar, 2 reproducir
			r >> operador;
			message scm;
			//cout << idc << idb << operador << ipc << endl;
			if(operador == 1){             // 1 message [id,"lista",name-song]
				scm << idc;
				scm << operador;
				scm << "nombre_cancion";
			  cout << "Partes a enviar: " << scm.parts() << endl;
			  indice=0;
			  socket sc(ctx, socket_type::xreq);         // socket servidor-cliente  5559 5560 5561
	  		sc.connect("tcp://"+ipc+":6666");
			  sc.send(scm);
			}else if(operador == 2){       // 2 message [id,"reproducir",namesong,string bytes]
				string nombre_cancion;
				scm << idc;
				scm << operador;
			  cout << "partes envia: " << scm.parts() << endl;
				socket sc(ctx, socket_type::xreq);         // socket servidor-cliente  5559 5560 5561
				sc.connect("tcp://"+ipc+":6666");
				sc.send(scm);
			}
  	}
	return 0;
}
