//Carlos Andres Martinez - {Client - workers - recollector }
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

/*_______________________struct Punto with x,y as input_______________________*/
struct Punto
{
	int x,y;
};
/*_______________________assignmentCentroid Random____________________________*/
Punto assignmentCentroid(int k){
	Punto centrosi[k];
	for (int i = 0; i <= k; i++){  // random centros initials
		srand(time(NULL));
		//centrosi[i].x = 1 + rand() % 7;
		//centrosi[i].y = 1 + rand() % 7;
		centrosi[i].x = 1;
		centrosi[i].y = 1;
		cout << "Centro Iniciales["<<i+1<<"]: "<<"("<<centrosi[i].x<<","<<centrosi[i].y<<")"<<endl;
	}
	return centrosi[k];
}
/*_______________________Load graph to file___________________________________*/
Punto loadGraph(int l){
	Punto graph[l];
	ifstream infile;
	int num = 0; // num must start at 0
	infile.open("databook.txt");// file containing numbers in 2 columns
			 while(num <= l) // reads file to end of *file*, not line
			{
				 infile >> graph[num].x ; // read first column number
				 infile >> graph[num].y; // read second column number
				 cout <<"/* message */"<<graph[num].x<<" "<<graph[num].y<<endl;
				 ++num; // go to the next number
			}
	infile.close();
	return graph[l];
}
/*_______________________Create clusters group________________________________*/
vector < vector <Punto> > groupClusters(int k){
	vector < vector<Punto> > groupsClusters;
	for(int i=0; i < k; i++) // K groups empty to groups
	{
		vector<Punto> newGroup;
		groupsClusters.push_back(newGroup);
	}
	return groupsClusters;
}
/*_______________________Distance between Centroid and Any Point on Graph_____*/
int distance(int px, int py, int cx, int cy){
	int distance=0;
	distance = sqrt((pow((px-cx),2)) + (pow((py-cy),2)));
	std::cout << "/* message */"<<distance<< std::endl;
	return distance;
}
/*____________________________________________________________________________*/
int main(int argc, char **argv)  // ./workers 192.168.1.12 5557 o 5558 o 5559
{
		string ip, port;
  	ip = argv[1];
		port = argv[2];
		Punto puntos[7];
		int ck=0;
		vector < vector <Punto> > groups;
  	cout<<"Running worker, connect at recollector " <<ip<<" port "<<port<<endl;
		/*__________________________________________________________________*/
		puntos[7] = loadGraph(7);
		for(int i=0; i<=7; i++){
			cout<<puntos[i].x<<" "<< puntos[i].y<<endl;
		}
		/*__________________________________________________________________*/
		context ctx;
		socket wr(ctx, socket_type::xreq);
		wr.connect("tcp://"+ip+":6667");
		socket wx(ctx, socket_type::xrep);   // socket client-workers 5557 5558 5559
		wx.bind("tcp://*:"+port);

		message cworkers;
  	string idc,ipc;
  	int k, CentroidPoint;
  	while(true)
  	{
			wx.receive(cworkers);                  // receive idc,k,ipc
			cworkers >> idc >> k >> ipc;
			/*_________________________Assignment Centroid Random___________________*/
			Punto centros[k];
			centros[ck] = assignmentCentroid(ck);
			/*_________________________Create Groups of Cluster_____________________*/
			groups = groupClusters(k);
			/*______________________________________________________________________*/
			cout << "recibe" << cworkers.parts() << "partes" << endl;
			message wrecollector;               // envia al recolector
			wrecollector << idc << k << ipc;
			cout << "idcliente " <<idc<<" cluster "<<k<<" ipcliente "<<ipc<<endl;
			/*_________________distance between centroid and point of graph_________*/
			for (int i=0; i<7; i++){
				CentroidPoint=distance(puntos[i].x, puntos[i].y, centros[0].x, centros[0].y);
				//cout << puntos[i].x <<" "<< puntos[i].y <<" "<<centros[0].x <<" "<<centros[0].y<<endl;
				wrecollector << CentroidPoint;
				CentroidPoint=0;
			}
			/*______________________________________________________________________*/
			cout << "envio" << wrecollector.parts() << "partes" << endl;
			wr.send(wrecollector);
  	}
	return 0;
}
