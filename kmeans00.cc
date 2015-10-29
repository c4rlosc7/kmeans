#include <iostream>
//#include <conio.h>
using namespace std;
int main()
{
    int i1,i2,i3,t1,t2;

    int k0[10];
    int k1[10];
    int k2[10];

    cout << "\nEnter 10 numbers:";
    for(i1=0;i1<10;i1++){
        cin >> k0[i1];
    }
    //for(int i=0;i<10;i++){cout << k0[i] << " ";}
    //initial means
    int m1;
    int m2;

    cout << "\nEnter initial mean [1]:";
    cin >> m1;
    cout << "Enter initial mean [2]:";
    cin >> m2;

    int om1,om2;    //old means

    do
    {
    //saving old means
    om1=m1;
    om2=m2;

    //creating clusters
    i1=i2=i3=0;
    for(i1=0;i1<10;i1++){
        //calculating distance to means m1
        t1 = k0[i1]-m1;
        //if(i1==0){cout <<t1;}
        if(t1<0){t1=-t1;} // change signal
        //calculating distance to means m2
        t2 = k0[i1]-m2;
        //if(i1==0){cout <<t2;}
        if(t2<0){t2=-t2;} // change signal

        if(t1<t2){
            //near to first mean K1
            k1[i2]=k0[i1];
            i2++;
            //cout << i2;
        }
        else
        {
            //near to second mean K2
            k2[i3]=k0[i1];
            i3++;
        }
    }
    t2=0;
    //cout << "i2: " << i2 << " " << "i3: " << i3 << endl;
//calculating new mean 3 7
    for(t1 = 0; t1 < i2; t1++){
        t2 = t2 + k1[t1];
    }
    //cout << t2 << endl;
    m1 = t2/i2;

    t2 = 0;
    for(t1=0;t1<i3;t1++){
        t2 = t2 + k2[t1];
    }
    //cout << t2;
    m2 = t2/i3;

//printing clusters
    cout << "\nCluster 1: ";
    for(t1=0;t1<i2;t1++){
        cout << k1[t1] << " ";
    }
    cout << "\nm1=" << m1;

    cout << "\nCluster 2: ";
    for(t1=0;t1<i3;t1++){
        cout << k2[t1] << " ";
    }
    cout << "\nm2=" << m2;

    cout << "\n ----";
    }while(m1!=om1&&m2!=om2);
    cout << "\n Clusters created";
}

/* OUTPUT
 Enter 10 numbers:
2 4 10 12 3 20 30 11 25 23

 Enter initial mean 1:2

 Enter initial mean 2:16

Cluster 1:2 4 3
m1=3
Cluster 2:10 12 20 30 11 25 23
m2=18
 ----
Cluster 1:2 4 10 3
m1=4
Cluster 2:12 20 30 11 25 23
m2=20
 ----
Cluster 1:2 4 10 3 11
m1=6
Cluster 2:12 20 30 25 23
m2=22
 ----
Cluster 1:2 4 10 12 3 11
m1=7
Cluster 2:20 30 25 23
m2=24
 ----
Cluster 1:2 4 10 12 3 11
m1=7
Cluster 2:20 30 25 23
m2=24
 ----
 Clusters created
*/
