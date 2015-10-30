#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>
using namespace std;

int newCenter(int length, int array[]) //calculating new mean M1
{
    int count=0;
    int m1;
    for(int t1 = 0; t1 < length; t1++){
        count = count + array[t1];
    }
    m1 = count/length;
    return m1;
}

int main()
{
    int i1, i2, i3, t1, t2;
    int k0[10] = {2, 4, 10, 12, 3, 20, 30, 11, 25, 23};
    int k1[10];
    int k2[10];

    //initial means
    int m1, m2;

    //generation number random to m1, m2
    srand(time(NULL));
    m1 = 1 + rand() % 10;
    m2 = 1 + rand() % 10;
    cout << "old m1(" << m1 << ")" << std::endl;
    cout << "old m2(" << m2 << ")" << std::endl;
    int om1,om2;    //old means
    int count=0;
    do
    {
      //saving old means
      om1 = m1;
      om2 = m2;

      //creating clusters
      i1 = i2 = i3 = 0;
      for( i1 = 0; i1 < 10; i1++){

          //calculating distance to means m1
          t1 = k0[i1] - m1;
          //if(i1==0){cout <<t1;}
          if( t1 < 0){t1=-t1;} // change signal

          //calculating distance to means m2
          t2 = k0[i1] - m2;
          //if(i1==0){cout <<t2;}
          if( t2 < 0 ){t2=-t2;} // change signal

          if( t1 < t2 ){
              //near to first mean K1
              k1[i2] = k0[i1];
              i2++;
              //cout << i2;
          }
          else
          {
              //near to second mean K2
              k2[i3] = k0[i1];
              i3++;
          }
      }

      m1 = newCenter(i2, k1); // new mean M1
      m2 = newCenter(i3, k2); // new mean M2

  //printing clusters
      cout << "\nCluster 1, new m1 (" << m1 << "): ";
      for( t1 = 0; t1 < i2; t1++){
          cout << k1[t1] << " ";
      }
      //cout << "\nm1=" << m1;

      cout << "\nCluster 2, new m2 (" << m2 << "): ";
      for( t1 = 0; t1 < i3; t1++){
          cout << k2[t1] << " ";
      }
      //cout << "\nm2=" << m2;
      count = count + 1;
      cout << "\n ----" << count << "----iteration";
    }while(m1 != om1 && m2 != om2 );
    cout << "\n Clusters created";

return 0;
}
