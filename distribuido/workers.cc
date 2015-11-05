//Carlos Andres Martinez - {Client - workers - recollector }
#include <iostream>
#include <string>
#include <cassert>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

int main(int argc, char **argv)  // ./workers 192.168.1.12 5557 o 5558 o 5559
{
		string ip, port;
  	ip = argv[1];
		port = argv[2];
  	cout<<"Running worker, connect at recollector " <<ip<<" port "<<port<<endl;

		context ctx;
		socket wr(ctx, socket_type::xreq);
		wr.connect("tcp://"+ip+":6667");

	  socket wx(ctx, socket_type::xrep);         // socket client-workers 5557 5558 5559
	  wx.bind("tcp://*:"+port);

		message cworkers;
  	string idc,ipc;
  	int k;
  	while(true)
  	{
			//message cbroker;                  // recibe del cliente
			wx.receive(cworkers);
			cworkers >> idc >> k >> ipc;
			cout << "recibe" << cworkers.parts() << "partes" << endl;

			message wrecollector;               // envia al recolector
			wrecollector << idc << k << ipc;
			//cworkers >> ipc;
			//for(size_t i = 0; i < cworkers.parts(); i++) //mensaje recibido
			//	cout << i << cworkers.get(i) << endl;
			cout << "idcliente " <<idc<<" cluster "<<k<<" ipcliente "<<ipc<<endl;
			//wrecollector << ipc;
			cout << "envio" << wrecollector.parts() << "partes" << endl;
			//for(size_t ii = 0; ii < wrecollector.parts(); ii++)
			//	cout << ii << wrecollector.get(ii) << endl;
			wr.send(wrecollector);
  	}
	return 0;
}
