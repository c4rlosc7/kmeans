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

	struct Punto // struct Punto with x,y as input
	{
		int x,y;
	}puntos[88233];

	int distance(int px, int py, int cx, int cy){
		int distance=0;
		distance=sqrt((pow((px-cx),2)) + (pow((py-cy),2)));
		return distance;
	}

	int minimum(int arr[], int maxIndex) //minimum between k distance
	{
		int min = 10000000;
		for(int i=0; i < maxIndex; i++)
		{
			if(arr[i] < min)
			min = arr[i];
		}
		return min;
	}

	int indexOf(int number, int arr[], int maxIndex) //position of minimum
	{
		int index;
		for(int i=0; i < maxIndex; i++)
		{
			if(number == arr[i])
			{
	      index = i;
	      break;
			}
		}
		return index; // return position on cluster
	}

	int meanx(vector<Punto> vc ) // average of x
	{
	  int sumx=0;
	  for(int i=0; i < vc.size(); i++){
			sumx = sumx + vc[i].x;
		}
	  return sumx/vc.size();
	}

	int meany(vector<Punto> vc ) // average of y
	{
		int sumy=0;
	  for(int i=0; i < vc.size(); i++){
			sumy = sumy + vc[i].y;
		}
	  return sumy/vc.size();
	}

	void show(vector<Punto> vc ) // show out
	{
		int i=0;
	  for(i=0; i < vc.size(); i++){
	  //cout <<"("<<vc[i].x<<","<< vc[i].y<<")"<< " ";
	  }
		cout << i;
	}

	bool isEqual(Punto arr1[], Punto arr2[], int maxIndex){ // oldcluster cluster k
		for(int i=0; i < maxIndex; i++)
		{
			if( (arr1[i].x != arr2[i].x) || (arr1[i].y != arr2[i].y) )
			return false;
		}
		return true;
	}
/*____________________________________________________________________________*/
	int * loadX(int nums1[], int k){
		int nums2[k];
		ifstream infile;
		int num = 0; // num must start at 0
		infile.open("databook.txt");// file containing numbers in 3 columns
				 while(num <= 7) // reads file to end of *file*, not line
				{
					 infile >> nums1[num]; // read first column number
					 infile >> nums2[num]; // read second column number
					 //cout <<"P("<<nums1[num]<<","<<nums2[num]<< ")"<<endl;
					 ++num; // go to the next number
				}
		infile.close();
		return nums1;
	}
/*____________________________________________________________________________*/
	int * loadY(int nums2[], int k){
		int nums1[k];
		ifstream infile;
		int num = 0; // num must start at 0
		infile.open("databook.txt");// file containing numbers in 3 columns
				 while(num <= 7) // reads file to end of *file*, not line
				{
					 infile >> nums1[num]; // read first column number
					 infile >> nums2[num]; // read second column number
					 //cout <<"P("<<nums1[num]<<","<<nums2[num]<< ")"<<endl;
					 ++num; // go to the next number
				}
		infile.close();
		return nums2;
	}
/*____________________________________________________________________________*/
	void show(int x[], int y[], int k){
		for (int i=0; i<=k; i++){
			cout << "dato ( "<<x[i]<< " , "<<y[i]<<" )"<<endl;
		}
	}
/*____________________________________________________________________________*/
	int higher(int arr[], int maxIndex) //higher number of array
	{
		int higher = 0;
		for(int i=0; i < maxIndex; i++)
		{
			if(arr[i] > higher)
			higher = arr[i];
		}
		return higher;
	}
/*____________________________________________________________________________*/
int main(int argc, char **argv)
{
		string ink = argv[1];
	  int k = std::stoi (ink);
		int noOfItems=88233;
		Punto centros[k], cviejos[k];
		int row[k];
		float bcv;
		vector < vector<Punto> > groups;
/*____________________________________________________________________________*/
	int *arrayDatosX;                            // then where you want to use it.
	int *arrayDatosY;
	int columnX[k];
	int columnY[k];
	arrayDatosX = loadX(columnX,k);
	arrayDatosY = loadY(columnY,k);
	show(arrayDatosX, arrayDatosY, k);
	int higherX, higherY;
	higherX = higher(arrayDatosX, k);
	higherY = higher(arrayDatosY, k);
	/*____________________________________________________________________________*/
	int m=higherX;
	int n=higherY;
	int c, d, v, matrix[m][n];
	int *matriz;

	for (  c = 0 ; c <= m ; c++ )  // m = 5 row
		 for ( d = 0 ; d <= n ; d++ ) // n = 3 column
				matrix[c][d]=0;

	for (  c = 0 ; c <= m ; c++ )  // m = 5 row
		 for ( d = 0 ; d <= n ; d++ ) // n = 3 column
				for ( v = 0; v < k; v++){
					if(arrayDatosX[v] == c){
							matrix[c][arrayDatosY[v]]=1;
					}
				}

	for (int jj=1; jj<=m; jj++){ // 5 row
		for (int ii=1; ii<=n; ii++) // 3 column
			cout << matrix[jj][ii] <<" ";
		cout <<" "<<endl;
	}
	cout <<" "<<endl;
/*____________________________________________________________________________*/
		//num = num -2;
		srand(time(NULL));
		cout << "\n";
		for (int i = 0; i < k; i++){  // random centros initials
			centros[i].x = 1 + rand() % 4038;
			centros[i].y = 1 + rand() % 4038;
			cout << "Centro Iniciales["<<i+1<<"]: "<<"("<<centros[i].x<<","<<centros[i].y<<")"<<endl;
		}

		for(int i=0; i < k; i++) // K groups empty to groups
		{
	  	vector<Punto> newGroup;
	  	groups.push_back(newGroup);
		}
		int iter =1;

		do{
			// min and clasification
			for(int i=0; i <= noOfItems; i++)  //noOfItems
			{
				for(int j=0; j < k; j++){ // distance cluster - points
					//row[j] = sqrt( (pow((puntos[i].x-centros[j].x),2)) + (pow((puntos[i].y-centros[j].y),2)));
					row[j] = distance(puntos[i].x, puntos[i].y, centros[j].x, centros[j].y);
				}
				groups[indexOf(minimum(row,k),row,k)].push_back(puntos[i]);// add puntos position groups
			}

			for(int j=0; j < k; j++) // update centros
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
