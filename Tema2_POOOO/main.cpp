#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "grup.h"
#include "hotel.h"
using namespace std;

int main() {
    ifstream f("hotel.txt");
    ifstream f1("grup1.txt");
    ifstream f2("grup2.txt");
    
    Hotel H;
    f>>H;

    cout<<H;

    Grup G1;
    f1>>G1;
    
    Grup G2;
    f2>>G2;
    
    for(int j=0; j<H.getNrApartamente(); j++) {
        cout<<"\n Apartamentul "<<H.getApartamente()[j].getId()<<": ";
        for (int i = 0; i < 50; i++)

            cout << H.getApartamente()[j].getOcupat(i) << " ";
    }
    
    
    H.citesteCerere(G1);
    cout<<endl<<G1<<endl;
    
    for(int j=0; j<H.getNrApartamente(); j++) {
        cout<<"\n Apartamentul "<<H.getApartamente()[j].getId()<<": ";
        for (int i = 0; i < 50; i++)

            cout << H.getApartamente()[j].getOcupat(i) << " ";
    }
    
    
    H.citesteCerere(G2);
    cout<<endl<<G2<<endl;
    
    for(int j=0; j<H.getNrApartamente(); j++) {
        cout<<"\n Apartamentul "<<H.getApartamente()[j].getId()<<": ";
        for (int i = 0; i < 50; i++)

            cout << H.getApartamente()[j].getOcupat(i) << " ";
    }
    
    cout<<"\n\nSterg grup \n";
    
    H.stergeGrup(G1);
    
    
    
    for(int j=0; j<H.getNrApartamente(); j++) {
        
        cout<<"\n Apartamentul "<<H.getApartamente()[j].getId()<<": ";
        
        for (int i = 0; i < 50; i++)
            cout << H.getApartamente()[j].getOcupat(i) << " ";
    }
    cout<<endl;
    
    Grup K;
    cin>>K;
    H.citesteCerere(K);
    cout<<K;
    
    
    //H.citesteCerere(G);
    //cout<<G;


}

