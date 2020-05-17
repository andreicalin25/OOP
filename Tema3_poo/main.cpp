#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <fstream>
using namespace std;


///CLASA ANIMALE__________________________________________________________________

class Animale {
protected:
    string denumire;

public:
    Animale();
    Animale(string);
    Animale(const Animale &A);
    ~Animale();

    friend istream& operator >> (istream &in, Animale &A);

    virtual void afisare() const = 0;
};


Animale :: Animale(){ }


Animale :: Animale(string name){
    denumire = name;
}


Animale :: Animale(const Animale &A){
    denumire = A.denumire;
}


Animale :: ~Animale() {
    denumire.erase();
}


istream& operator >>(istream &in, Animale& A){
    //cout<<"numele animalului: ";
    in>>A.denumire;
    return in;
}


///CLASA NEVERTEBRATE____________________________________________________________

class Nevertebrate : public Animale {

public:
    Nevertebrate();
    Nevertebrate(string);
    Nevertebrate(const Nevertebrate &N);
    ~Nevertebrate();

    //friend istream& operator >> (istream &in, Nevertebrate &N);
    void afisare() const;
};


Nevertebrate :: Nevertebrate() : Animale() { }


Nevertebrate :: Nevertebrate(string name) : Animale(name) {
    denumire = name;
}


Nevertebrate :: Nevertebrate(const Nevertebrate &N) : Animale(N){
    denumire = N.denumire;
}


Nevertebrate ::~Nevertebrate() { }


/*istream& operator >>(istream &in, Nevertebrate& N){
    cout<<"numele animalului: ";
    in>>N.denumire;
    return in;
}*/


void Nevertebrate :: afisare() const {
    cout<<"Numele nevertebratei este "<<denumire<<endl;
}


///CLASA VERTEBRATE______________________________________________________________

class Vertebrate : public Animale {
public:
    Vertebrate();
    Vertebrate(string);
    Vertebrate(const Vertebrate &V);
    ~Vertebrate();

    void afisare() const;
};


Vertebrate :: Vertebrate() : Animale() { }


Vertebrate :: Vertebrate(string name) : Animale(name) {
    denumire = name;
}


Vertebrate :: Vertebrate(const Vertebrate &V) : Animale(V){
    denumire = V.denumire;
}


Vertebrate ::~Vertebrate() { }


void Vertebrate :: afisare() const {
    cout<<"Numele vertebratei este "<<denumire<<endl;
}


///CLASA PASARI__________________________________________________________________

class Pasari : public Vertebrate {

public:
    Pasari();
    Pasari(string);
    Pasari(const Pasari &P);
    ~Pasari();

    void afisare() const ;
};


Pasari :: Pasari() { }


Pasari :: Pasari(string name) {
    denumire = name;
}


Pasari :: Pasari(const Pasari &P) {
    denumire = P.denumire;
}


Pasari ::~Pasari() { }


void Pasari :: afisare() const {
    cout<<"Numele pasarii este "<<denumire<<endl;
}


///CLASA REPTILE_________________________________________________________________

class Reptile : public Vertebrate {

public:
    Reptile();
    Reptile(string);
    Reptile(const Reptile &R);
    ~Reptile();

    void afisare() const ;
};


Reptile :: Reptile() { }


Reptile :: Reptile(string name) {
    denumire = name;
}


Reptile :: Reptile(const Reptile &R) {
    denumire = R.denumire;
}


Reptile ::~Reptile() { }


void Reptile :: afisare() const {
    cout<<"Numele reptilei este "<<denumire<<endl;
}


///CLASA PESTI___________________________________________________________________

class Pesti : public Vertebrate {
    bool pradator;
    double lungime;

public:
    Pesti();
    Pesti(string, bool, double);
    Pesti(const Pesti &P);
    ~Pesti();

    friend istream& operator >> (istream &in, Pesti &P);

    void afisare() const;
    bool getPradator() { return pradator; };
    double getLungime() { return lungime; };
};


Pesti :: Pesti() { }


Pesti :: Pesti(string name, bool pradator=0, double lungime=0) {
    denumire = name;
    pradator = pradator;
    lungime = lungime;
}


Pesti :: Pesti(const Pesti &P) {
    denumire = P.denumire;
}


Pesti ::~Pesti() { }

istream& operator >>(istream &in, Pesti& P){

    in >> dynamic_cast<Animale&>(P);

    cout<<"este pradator? (1-da, 0-nu): ";
    in >> P.pradator;
    cout<<"lungimea pestelui: ";
    in >> P.lungime;
    
    if(!in.good()){
        throw 1;
    }
        

    return in;
}

void Pesti :: afisare() const {
    if(pradator)
        cout<<"Numele pestelui este "<<denumire<<", este pradator iar lungimea sa este de "<<lungime<<"metrii\n";
    else
        cout<<"Numele pestelui este "<<denumire<<", nu este pradator iar lungimea sa este de "<<lungime<<"metrii\n";

}


///CLASA MAMIFERE________________________________________________________________

class Mamifere : public Vertebrate {

public:
    Mamifere();
    Mamifere(string);
    Mamifere(const Mamifere &M);
    ~Mamifere();

    void afisare() const ;
};


Mamifere :: Mamifere() { }


Mamifere :: Mamifere(string name) {
    denumire = name;
}


Mamifere :: Mamifere(const Mamifere &M) {
    denumire = M.denumire;
}


Mamifere ::~Mamifere() { }


void Mamifere :: afisare() const {
    cout<<"Numele mamiferei este "<<denumire<<endl;
}


///CLASA ATLAS___________________________________________________________________

template <class Type>
class AtlasZoologic {
    int nr_animale = 0;
    list <Animale*> animale;

public:
    AtlasZoologic();
    ~AtlasZoologic() ;

    int getNumarAnimale();

    void afisare();
    void operator +=(Type &crt);
};


template<class Type>
AtlasZoologic<Type> :: AtlasZoologic() { }


template<class Type>
AtlasZoologic<Type> :: ~AtlasZoologic() { }


template <class Type>
void AtlasZoologic<Type> ::afisare()  {

    cout<<"\nAtlasul de "<< typeid(Type).name() <<" contine: \n";

    list<Animale*>::iterator it;

    for(it = animale.begin(); it!=animale.end(); it++)
    {
        //cout<< typeid(*it).name()<<" ";
        (*it)->afisare();
    }
}


template<class Type>
void AtlasZoologic<Type>::operator +=(Type &crt) {

    //cout<<"In atlas intra un "<< typeid(&crt).name()<<" \n";

    animale.push_back(&crt);
    nr_animale++;
}


template <class Type>
int AtlasZoologic<Type>:: getNumarAnimale() {
    return nr_animale;
}


///SPECIALIZARE PESTI__________________________________________________________________________________

template <>
class AtlasZoologic <Pesti> {
    int nr_animale = 0;
    list <Pesti*> animale;

public:
    AtlasZoologic();
    ~AtlasZoologic() ;

    int getNumarAnimale();

    const int getNrPradatoriMari();

    void afisare();
    void operator +=(Pesti &crt);
};


AtlasZoologic<Pesti> :: AtlasZoologic() { }


AtlasZoologic<Pesti> :: ~AtlasZoologic() { }


void AtlasZoologic<Pesti> ::afisare()  {

    cout<<"\nAtlasul de "<< typeid(Pesti).name() <<" contine: \n";

    list<Pesti*>::iterator it;

    for(it = animale.begin(); it!=animale.end(); it++)
    {
        //cout<< typeid(*it).name()<<" ";
        (*it)->afisare();
    }
}


void AtlasZoologic<Pesti>::operator +=(Pesti &crt) {

    //cout<<"In atlas intra un "<< typeid(&crt).name()<<" \n";

    animale.push_back(&crt);
    nr_animale++;
}


int AtlasZoologic<Pesti>:: getNumarAnimale() {
    return nr_animale;
}


const int AtlasZoologic<Pesti>:: getNrPradatoriMari() {

    int nr = 0;

    list<Pesti*>::iterator it;

    for(it = animale.begin(); it != animale.end(); it++)
        if((*it)->getPradator() && (*it)->getLungime() > 1.0)
            nr++;

    return nr;

}



///MAIN__________________________________________________________________________________________

int main()
{

    ifstream f("animale.txt");

    AtlasZoologic<Nevertebrate> atlas_nevertebrate;
    AtlasZoologic<Pesti> atlas_pesti;
    AtlasZoologic<Reptile> atlas_reptile;
    AtlasZoologic<Pasari> atlas_pasari;
    AtlasZoologic<Mamifere> atlas_mamifere;


    bool continuam = true;

    while(continuam){

        char choice;

        cout<<"\nCe actiune doriti sa executati?\n"
              "A-adaugare animal;\n"
              "N-numar total animale\n"
              "T-total atlase\n"
              "P-numar pesti pradatori mari\n"
              "S-stop program\n";

        cin>>choice;

        switch (choice) {

            case 'A': {
                
                        int animal_choice;
                
                        //cout << "Ce animal doriti sa introduceti? "
                        //        "(0-nevertebrata, 1-peste, 2-reptila, 3-pasare, 4-mamifera) \n";

                        f >> animal_choice;


                        switch (animal_choice) {
                                
                            case 0: {
                                Nevertebrate *ob = new Nevertebrate;
                                f >> *ob;
    
                                atlas_nevertebrate += *ob;
                                break;
                            }
                                
                            case 1: {
                                Pesti *ob = new Pesti;
                                
                                try {
                                    f >> *ob;
                                }
                                
                                catch(...) {
                                    cout<<"\nCitire peste esuata\n";
                                    return 0;
                                }
                                
                                atlas_pesti += *ob;
                                break;
                            }
                                
                            case 2: {
                                Reptile *ob = new Reptile;
                                f >> *ob;
                                atlas_reptile += *ob;
                                break;
                            }
                                
                            case 3: {
                                Pasari *ob = new Pasari;
                                f >> *ob;
                                atlas_pasari += *ob;
                                break;
                            }
                                
                            case 4: {
                                Mamifere *ob = new Mamifere;
                                f >> *ob;
                                atlas_mamifere += *ob;
                                break;
                            }
                        }
                break;}


            case 'N': {

                        int sum=0;
                        sum += atlas_nevertebrate.getNumarAnimale();
                        sum += atlas_pesti.getNumarAnimale();
                        sum += atlas_reptile.getNumarAnimale();
                        sum += atlas_pasari.getNumarAnimale();
                        sum += atlas_mamifere.getNumarAnimale();

                        cout<<sum<<endl;

                break;
            }


            case 'T': {

                        atlas_nevertebrate.afisare();
                        atlas_pesti.afisare();
                        atlas_reptile.afisare();
                        atlas_pasari.afisare();
                        atlas_mamifere.afisare();

                 break;
            }


            case 'P': {
                cout<<atlas_pesti.getNrPradatoriMari()<<endl;
                break;
            }


            case 'S' : {
                continuam = false;
                break;
            }


        }
    }



}


