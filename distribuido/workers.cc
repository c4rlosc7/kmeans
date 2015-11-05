//Carlos Andres Martinez - {Client - workers - recollector }
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

/*__________________________________________________________________*/
struct Punto // struct Punto with x,y as input
{
	int x,y;
};
/*__________________________________________________________________*/
Punto centroid(int k){
	srand(time(NULL));
	Punto centrosi[k];
	for (int i = 0; i < k; i++){  // random centros initials
		centrosi[i].x = 1 + rand() % 7;
		centrosi[i].y = 1 + rand() % 7;
		cout << "Centro Iniciales["<<i+1<<"]: "<<"("<<centrosi[i].x<<","<<centrosi[i].y<<")"<<endl;
	}
	return centrosi[k];
}
/*__________________________________________________________________*/
Punto grafo(int l){
	Punto graph[l];
	ifstream infile;
	int num = 0; // num must start at 0
	infile.open("databook.txt");// file containing numbers in 2 columns
			 while(!infile.eof()) // reads file to end of *file*, not line
			{
				 infile >> graph[num].x ; // read first column number
				 infile >> graph[num].y; // read second column number
				 ++num; // go to the next number
			}
	infile.close();
	return graph[l];
}
/*__________________________________________________________________*/

int main(int argc, char **argv)  // ./workers 192.168.1.12 5557 o 5558 o 5559
{
		string ip, port;
  	ip = argv[1];
		port = argv[2];
		Punto puntos[7];
  	cout<<"Running worker, connect at recollector " <<ip<<" port "<<port<<endl;
		/*__________________________________________________________________*/
		puntos[7] = grafo(7);
		/*__________________________________________________________________*/
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
			wx.receive(cworkers);                  // recibe del cliente
			cworkers >> idc >> k >> ipc;
			/*__________________________________________________________________*/
			Punto centros[k];
			centros[k] = centroid(k);
			/*__________________________________________________________________*/
			cout << "recibe" << cworkers.parts() << "partes" << endl;
			message wrecollector;               // envia al recolector
			wrecollector << idc << k << ipc;
			cout << "idcliente " <<idc<<" cluster "<<k<<" ipcliente "<<ipc<<endl;
			cout << "envio" << wrecollector.parts() << "partes" << endl;
			wr.send(wrecollector);
  	}
	return 0;
}
