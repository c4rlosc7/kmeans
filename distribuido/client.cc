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
}puntos[88233];
/*__________________________________________________________________*/

int main(int argc, char **argv){
  string ip; 		// 10.253.96.236 U, 192.168.1.12 CASA
  ip = argv[1];

  cout<<"running client with ip: " << ip << endl;
	string ink = argv[2];
	int k = std::stoi (ink);
/*__________________________________________________________________*/
	ifstream infile;
	int num = 0; // num must start at 0
	infile.open("facebook.txt");// file containing numbers in 2 columns
			 while(!infile.eof()) // reads file to end of *file*, not line
			{
				 infile >> puntos[num].x ; // read first column number
				 infile >> puntos[num].y; // read second column number
				 ++num; // go to the next number
			}
	infile.close();
/*__________________________________________________________________*/
  context ctx;
  socket cb(ctx, socket_type::xreq); // socket cliente-broker 5555
  cb.connect("tcp://"+ip+":5555");

  socket sc(ctx, socket_type::xrep); // socket servidor-cliente 5559
  sc.bind("tcp://*:6666");

  string ipc = "192.168.1.12";
  message m;                 // mensaje m

	//while(true)
	//{
		//cout << "\n1.PlayList  2.Play : ";
		//cin >> c;
		m << k;
		m << ipc;
		cb.send(m);

	  message bserver;
	  sc.receive(bserver);
	  string idb, ids;
	  bserver >> idb >> ids;
	  //cout << "canciones encontradas: " << bserver.parts()-3 <<endl;
	  //for(size_t ii = 0; ii < bserver.parts(); ii++) {
	  //  cout << "name song["<< ii-3 << "]: "<< bserver.get(ii) << endl;
	  //}
	  int tarea;
	  bserver >> tarea;
		cout << "Cluster: " <<tarea<<endl;
	  //if(tarea == 1){cout <<"Es uno";
	  	//cout << "Canciones encontradas: " << bserver.parts()-3<< endl;
			//for(size_t i = 3; i < bserver.parts(); i++) {
				//cout << "name song[" << i-3 <<"]: " << bserver.get(i) << endl;
			//}

	  //}else if(tarea == 2){ cout << "Es dos"; }
	//}
  return 0;
}
