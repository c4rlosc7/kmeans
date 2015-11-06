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
  string idc, idw, ipc;        // id
	while(true)
	{
			message wrecollector;
			wr.receive(wrecollector);
			cout << "recibe" << wrecollector.parts() << "partes" << endl;
			for(size_t i = 0; i < wrecollector.parts(); i++) {
				cout << wrecollector.get(i) << endl;
			}
			wrecollector >> idw >> idc;
			cout <<"idworkers "<<idw<<" idcliente "<<idc<<endl;
			int k,a,b;
			wrecollector >> k >> ipc >> a >>b;
      std::cout << "/* message */" <<a<< std::endl;
      std::cout << "/* message */" <<b<< std::endl;
			cout <<" Cluster "<<k<<" ipcliente "<<ipc<<endl;
      socket rc(ctx, socket_type::xreq);         // socket recollector to client
      rc.connect("tcp://"+ipc+":6666");
      message rclient;
      rclient << idc;
      rclient << k;
      cout << "envio" << rclient.parts() << "partes" << endl;
      rc.send(rclient);

  	}
	return 0;
}
