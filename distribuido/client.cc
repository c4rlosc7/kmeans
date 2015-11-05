//Carlos Andres Martinez - {Client - workers - recollector }
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <zmqpp/zmqpp.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace zmqpp;
/*__________________________________________________________________*/
struct Punto // struct Punto with x,y as input
{
	int x,y;
}puntos[7];
/*__________________________________________________________________*/

int main(int argc, char **argv){                     // .client 192.168.1.12 k
  string ip; 		// 10.253.96.236 U, 192.168.1.12 CASA
  ip = argv[1];
  cout<<"running client, connect at ip " << ip << endl;

	string ink = argv[2];
	int k = std::stoi (ink);
/*__________________________________________________________________*/
	ifstream infile;
	int num = 0; // num must start at 0
	infile.open("databook.txt");// file containing numbers in 2 columns
			 while(!infile.eof()) // reads file to end of *file*, not line
			{
				 infile >> puntos[num].x ; // read first column number
				 infile >> puntos[num].y; // read second column number
				 ++num; // go to the next number
			}
	infile.close();
/*__________________________________________________________________*/
	int count=0;
	context ctx;
  socket rc(ctx, socket_type::xrep); // socket recollector to client
  rc.bind("tcp://*:6666");

  string ipc = "192.168.1.12";
  message cworkers;                 // mensaje cworkers

	int i=0;
	while(true)
	{
		while(i<k)
		{
			cworkers << k;
			cworkers << ipc;
			//Round Robin All connect
			if (count == 0){
				socket wx(ctx, socket_type::xreq);  // socket (wx) cliente - workers (5557)
				wx.connect("tcp://"+ip+":5557");
				cout << "running worker #1\n";
				wx.send(cworkers);
				count = count + 1;
			}else if (count == 1){
				socket wx(ctx, socket_type::xreq);  // socket (wx) cliente - workers (5557)
				wx.connect("tcp://"+ip+":5558");
				cout << "running worker #2\n";
				wx.send(cworkers);
				count = count + 1;
			}else if (count == 2){
				socket wx(ctx, socket_type::xreq);  // socket (wx) cliente - workers (5557)
				wx.connect("tcp://"+ip+":5559");
				cout << "running worker #3\n";
				wx.send(cworkers);
				count=0;
			}
			i++;
		}
/*_________________________________________________________________________*/
		message rclient;
	  rc.receive(rclient);
	  string idr, idc;
	  rclient >> idr >> idc;
		int tarea;
	  rclient >> tarea;
		cout << "Cluster: " <<tarea<<endl;
	}
  return 0;
}
