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

int main()
{
  cout << "Running recollector, connect at ip ";
  context ctx;
  socket wr(ctx, socket_type::xrep);         // socket workers to recollector
  wr.bind("tcp://*:6667");

	while(true)
	{
			message wrecollector;
			wr.receive(wrecollector);
			cout << "recibe" << wrecollector.parts() << "partes" << endl;
			//longitud_msg = wrecollector.parts();
			for(size_t i = 0; i < wrecollector.parts(); i++) {
				cout << wrecollector.get(i) << endl;
			}
			string idc, idw, ipc;        // id
			wrecollector >> idw >> idc;
			cout <<"idworkers "<<idw<<" idcliente "<<idc<<endl;
			int operador;     // 1 buscar, 2 reproducir
			wrecollector >> operador;
      wrecollector >> ipc;
			cout <<" Cluster "<<operador<<" ipcliente "<<ipc<<endl;

      socket rc(ctx, socket_type::xreq);         // socket recollector to client
      rc.connect("tcp://"+ipc+":6666");
      message rclient;
      rclient << idc;
      rclient << operador; // k
      cout << "envio" << rclient.parts() << "partes" << endl;
      rc.send(rclient);

  	}
	return 0;
}
