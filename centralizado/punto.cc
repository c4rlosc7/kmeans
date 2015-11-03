#include <stdio.h>
#include <cstdlib>
#include <array>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;
	struct Punto
	{
		int x,y;
	}puntos[88233];

	void pintar(const Punto p){
		cout << "P( " << p.x <<" , "<< p.y<<" )" <<endl;
	}

	int min(int arr[], int maxIndex) //array[distance] and k
	{
		int min = 10000000;
		for(int i=0; i < maxIndex; i++)
		{
			if(arr[i] < min)
			min = arr[i];
		}
		return min;
	}

	int indexOf(int number, int arr[], int maxIndex)
	{
		int index;
		for(int i=0; i < maxIndex; i++) //number=min, maxIndex = k, arr = row
		{
			if(number == arr[i])
			{
	      index = i;
	      break;
			}
		}
		return index; // return position on cluster
	}

	int meanx(vector<Punto> vc )
	{
	  int sumx=0;
	  for(int i=0; i < vc.size(); i++){
			sumx = sumx + vc[i].x;
		}
	  return sumx/vc.size();
	}

	int meany(vector<Punto> vc )
	{
		int sumy=0;
	  for(int i=0; i < vc.size(); i++){
			sumy = sumy + vc[i].y;
		}
	  return sumy/vc.size();
	}

	void show(vector<Punto> vc )
	{
		int i=0;
	  for(i=0; i < vc.size(); i++){
	  //cout <<"("<<vc[i].x<<","<< vc[i].y<<")"<< " ";
	  }
		cout << i <<endl;
	}

	bool isEqual(Punto arr1[], Punto arr2[], int maxIndex){
		for(int i=0; i < maxIndex; i++)
		{
			if( (arr1[i].x != arr2[i].x) || (arr1[i].y != arr2[i].y) )
			return false;
		}
		return true;
	}

int main(int argc, char **argv)
{
		string ink = argv[1];
	  int k = std::stoi (ink); // input k
		int noOfItems=88233;
		//int noOfItems=7;
		Punto centros[k], cviejos[k];

		ifstream infile;
    int num = 0; // num must start at 0
    infile.open("facebook.txt");// file containing numbers in 3 columns
         while(!infile.eof()) // reads file to end of *file*, not line
        {
           infile >> puntos[num].x ; // read first column number
           infile >> puntos[num].y; // read second column number
           ++num; // go to the next number
        }
    infile.close();

		num = num -2;
		srand(time(NULL));
		cout << "\n";
		for (int i = 0; i < k; i++){
			centros[i].x = 1 + rand() % 4038;
			centros[i].y = 1 + rand() % 4038;
			cout << "Centro Iniciales["<<i<<"]: "<<"("<<centros[i].x<<","<<centros[i].y<<")"<<endl;
		}

		int row[k];
		vector < vector<Punto> > groups;

		for(int i=0; i < k; i++)
		{
	  	vector<Punto> newGroup;
	  	groups.push_back(newGroup);
		}
		int iter =1;

		do{
			// min and clasification
			for(int i=0; i <= noOfItems; i++)  //noOfItems
			{
				for(int j=0; j < k; j++){
					//row[j] = abs(cluster[j] - objects[i]); // distance cluster - points
					row[j] = sqrt( (pow((puntos[i].x-centros[j].x),2)) + (pow((puntos[i].y-centros[j].y),2)));
					//cout <<"P"<<i<<" M"<<j<<": "<<row[j]<<endl;
				}
				groups[indexOf(min(row,k),row,k)].push_back(puntos[i]);// min,array,maxIndex
			}

			for(int j=0; j < k; j++) // actualizar cluster
			{
				if(!groups[j].empty())
				{
					cviejos[j] = centros[j];
					centros[j].x = meanx(groups[j]);
					centros[j].y = meany(groups[j]);
					//cout << " nuevo centro " << centros[j].x <<" "<< centros[j].y<<endl;
				}
			}

			if(!isEqual(cviejos,centros,k))
			{
				for(int i=0; i < k; i++)
				groups[i].clear();
			}
			iter++;

		}while(!isEqual(cviejos,centros,k));

		cout<<"\n";
		for(int i=0; i < k; i++)
		{
			cout<< "CF" <<(i+1)<< " : "<<"("<<centros[i].x<<","<<centros[i].y<<")"<<endl;
		}
		for(int i=0; i < k; i++)
		{
			cout << "\nGrupo " << (i+1) << " : ";
			show(groups[i]);
		}
	  cout << "\n";
		cout << "\nNumero de Iteraciones " << iter <<endl;

		return 0;
}
