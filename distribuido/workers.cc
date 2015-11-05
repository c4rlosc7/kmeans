//Carlos Andres Martinez - {Client - workers - recollector }
#include <iostream>
#include <string>
#include <cassert>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

int main(int argc, char **argv)
{
		string ip;
  	ip = argv[1];
  	cout<<"Running broker with ip: " << ip <<endl;

  	context ctx;
  	socket cb(ctx, socket_type::xrep);  // socket cliente-broker
  	cb.bind("tcp://*:5555");

  	int count=0;
  	message cbroker;
  	string idc,ipc;
  	int c;
  	while(true)
  	{
			//message cbroker;                  // recibe del cliente
			cb.receive(cbroker);
			cbroker >> idc >> c;
			cout << c <<endl;
			if (c <= 2 && c > 0){
				cout << "recibe" << cbroker.parts() << "partes" << endl;
				message bserver;               // envia al servidor
				bserver << idc << c;
				//if (c == 2){int index; cbroker >> index; bserver << index;} //play index song
				cbroker >> ipc;
				for(size_t i = 0; i < cbroker.parts(); i++) //mensaje recibido
					cout << i << cbroker.get(i) << endl;

				bserver << ipc;
				cout << "envio" << bserver.parts() << "partes" << endl;
				for(size_t ii = 0; ii < bserver.parts(); ii++)
					cout << ii << bserver.get(ii) << endl;

				//Round Robin
				if (count == 0){
					socket sx(ctx, socket_type::xreq);  // socket (1) servidor-cliente  5559 5560 5561
					sx.connect("tcp://"+ip+":5557");
					cout << "running server #1\n";
					sx.send(bserver);
					count = count + 1;
				}else if (count == 1){
					socket sx(ctx, socket_type::xreq);  // socket (2) servidor-cliente  5559 5560 5561
					sx.connect("tcp://"+ip+":5558");
					cout << "running server #2\n";
					sx.send(bserver);
					count = count + 1;
				}else if (count == 2){
					socket sx(ctx, socket_type::xreq);  // socket (3) servidor-cliente  5559 5560 5561
					sx.connect("tcp://"+ip+":5559");
					cout << "running server #3\n";
					sx.send(bserver);
					count=0;
				}
			}
  	}
	return 0;
}
