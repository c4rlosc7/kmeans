#include <stdio.h>      /* printf */
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
/*_____________________struct Punto with x,y as input_________________________*/
struct Punto {
  int x, y;
} puntos[7];
/*_____________________struct Centroid with x,y as input double _______________*/
struct Centroid {
  double x, y;
};
/*________________________minimum of cluster double__________________________________*/
double minimum(double arr[], int maxIndex) {
  double min = 10000000;
  for (int i = 0; i < maxIndex; i++) {
    if (arr[i] < min)
      min = arr[i];
  }
  return min;
}
/*_______________________position of minimum cluster__________________________*/
int indexOf(double number, double arr[], int maxIndex) {
  int index;
  for (int i = 0; i < maxIndex; i++) {
    if (number == arr[i]) {
      index = i;
      break;
    }
  }
  return index; // return position on cluster
}
/*______________________________average of x__________________________________*/
double meanx(vector<Punto> vc) {
  double sumx = 0;
  for (int i = 0; i < vc.size(); i++) {
    sumx = sumx + vc[i].x;
  }
  return sumx / vc.size();
}
/*______________________________average of y___________________________________*/
double meany(vector<Punto> vc) {
  double sumy = 0;
  for (int i = 0; i < vc.size(); i++) {
    sumy = sumy + vc[i].y;
  }
  return sumy / vc.size();
}
/*______________________________show____________________________________________*/
void show(vector<Punto> vc) {
  int i = 0;
  for (i = 0; i < vc.size(); i++) {
      //cout <<"("<<vc[i].x<<","<< vc[i].y<<")"<< " ";
  }
  cout << "Puntos "<<i;
}
/*______________________________Until is equal_________________________________*/
bool isEqual(Centroid arr1[], Centroid arr2[], int maxIndex) { // oldcluster cluster k
  for (int i = 0; i < maxIndex; i++) {
    if ((arr1[i].x != arr2[i].x) && (arr1[i].y != arr2[i].y))
      return false;
  }
  return true;
}
/*____________________________________________________________________________*/
int main(int argc, char **argv) {
  string ink = argv[1];
  int k = std::stoi(ink);
  int noOfItems = 7;
  Centroid centros[k], cviejos[k];
  double row[k];
  vector<vector<Punto>> groups;
  /*______________________________Load
   * Dataset____________________________________*/
  ifstream infile;
  int num = 0;                 // num must start at 0
  infile.open("databook.txt"); // file containing numbers in 2 columns
  while (!infile.eof())        // reads file to end of *file*, not line
  {
    infile >> puntos[num].x; // read first column number
    infile >> puntos[num].y; // read second column number
    ++num;                   // go to the next number
  }
  infile.close();

  num = num - 2;

  srand(time(NULL));
  cout << "\n";
  for (int i = 0; i < k; i++) { // random centros initials
    centros[i].x = 1 + rand() % 5;
    centros[i].y = 1 + rand() % 5;
    cout << "Centro Iniciales[" << i + 1 << "]: "
         << "(" << centros[i].x << "," << centros[i].y << ")" << endl;
  }
/*
centros[0].x = 1;
centros[0].y = 1;
centros[1].x = 2;
centros[1].y = 1;

cout << "Centro Iniciales[" << 1 << "]: "
     << "(" << centros[0].x << "," << centros[0].y << ")" << endl;

cout << "Centro Iniciales[" << 2 << "]: "
      << "(" << centros[1].x << "," << centros[1].y << ")" << endl;
*/

  /*____________________________________________________________________________*/
  for (int i = 0; i < k; i++) // K groups empty to groups
  {
    vector<Punto> newGroup;
    groups.push_back(newGroup);
  }
  int iter = 0;
  double oldDistance = 0.0;
  double newDistance = 0.0;
  double sse = 0.0;
  double delta = 0.46;
  double sse_aux = 0.0;
  double flags;
  double error;
  /*____________________________________________________________________________*/
  do {
      //cout << "Iteration "<<iter<< endl;
	   oldDistance = newDistance;

    for (int i = 0; i <= noOfItems; i++) {
      for (int j = 0; j < k; j++) { // distance cluster - points
        double d = sqrt((pow((puntos[i].x - centros[j].x), 2)) +
                      (pow((puntos[i].y - centros[j].y), 2)));
        row[j] = d;
      }
      double minDistance = minimum(row, k);
      //printf ("min = %f\n", minDistance);
      double sse = pow(minDistance, 2);
      groups[indexOf(minDistance, row, k)].push_back(
          puntos[i]); // add puntos position groups
      newDistance += minDistance;
      sse_aux += sse;
      //printf ("min 2 = %f\n", sse);
    }
    printf ("SSE = %f\n", sse_aux);
    double s1;
    s1 = sqrt((pow((centros[1].x - centros[0].x), 2)) +
                  (pow((centros[1].y - centros[0].y), 2)));
    printf ("BCV = %f\n", s1);
    flags = s1 / sse_aux;
    printf ("SSE/BCV = %f\n", flags);
    error = abs(error -flags);
    printf ("Error = %f\n\n", error);
    sse =0;
    sse_aux =0;
    s1=0;


    for (int j = 0; j < k; j++) // update centros
    {
      if (!groups[j].empty()) {
        cviejos[j] = centros[j];
        centros[j].x = meanx(groups[j]);
        centros[j].y = meany(groups[j]);
      }
    }

    if (flags < delta) {
      for (int i = 0; i < k; i++)
        groups[i].clear();
    }

    iter++;
    cout << "Iteration "<<iter<< endl;

  } while (flags < delta);
  //while (abs(oldDistance - newDistance) < delta);
  // while (!isEqual(cviejos, centros, k));
  /*____________________________________________________________________________*/
  cout << "\n";
  for (int i = 0; i < k; i++) {
    cout << "CF" << (i + 1) << " : "
         << "(" << centros[i].x << "," << centros[i].y << ")" << endl;
  }
  for (int i = 0; i < k; i++) {
    cout << "\nGrupo " << (i + 1) << " : ";
    show(groups[i]);
  }
  cout << "\n";
  //cout << "\nNumero de Iteraciones " << iter << endl;
  return 0;
}
