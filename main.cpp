#include <iostream>
#include <cmath>
using namespace std;

class Numar_Complex
{
    double re, im;

public:
    
    Numar_Complex();
    Numar_Complex(const Numar_Complex &ob);
    ~Numar_Complex();
    void set(double re, double im);
    double get_re();
    double get_im();
    friend istream & operator >> (istream &in, Numar_Complex &z);
    friend ostream & operator << (ostream &out, const Numar_Complex &z);
    double modul(const Numar_Complex &z);
    friend Numar_Complex operator+ (const Numar_Complex &z1, const Numar_Complex &z2);
    friend Numar_Complex operator* (const Numar_Complex &z1, const Numar_Complex &z2);
    friend Numar_Complex operator/ (const Numar_Complex &z1, const Numar_Complex &z2);

    
    friend class Matrice_Complexa;
};


Numar_Complex :: Numar_Complex()
{
    re=0;
    im=0;
}


Numar_Complex :: Numar_Complex(const Numar_Complex &ob)
{
    re=ob.re;
    im=ob.im;
}


Numar_Complex :: ~Numar_Complex() {}


void Numar_Complex :: set(double re, double im)
{
    re=re;
    im=im;
}


double Numar_Complex :: get_re()
{
    return re;
}


double Numar_Complex :: get_im()
{
    return im;
}


istream & operator >> (istream &in, Numar_Complex &z)
{
    cout<< "Parte reala: ";
    in>> z.re;
    
    cout<< "Parte imaginara: ";
    in>> z.im;
    
    return in;
}


ostream & operator << (ostream &out, const Numar_Complex &z)
{
    out<< z.re;
    if (z.im < 0)
        out<< z.im<<"i";                ///afisarea nu am facut-o exact in forma din enunt
    else
        out<< "+"<<z.im<<"i";           ///asa mi se pare mai lizibil si mai natural
    
    return out;
}


double Numar_Complex :: modul(const Numar_Complex &z)
{
    return sqrt(z.re*z.re + z.im*z.im);
}


Numar_Complex operator+ (const Numar_Complex &z1, const Numar_Complex &z2)
{
    Numar_Complex suma;
    
    suma.re = z1.re + z2.re;
    suma.im = z1.im + z2.im;
    
    return suma;
}


Numar_Complex operator* (const Numar_Complex &z1, const Numar_Complex &z2)
{
    Numar_Complex produs;
    
    produs.re = (z1.re * z2.re) - (z1.im * z2.im) ;
    produs.im = (z1.re * z2.im) + (z1.im * z2.re) ;
    
    return produs;
}


Numar_Complex operator/ (const Numar_Complex &z1, const Numar_Complex &z2)
{
    Numar_Complex raport;

    Numar_Complex aux;
    aux.re= z2.re;
    aux.im= -z2.im;

    Numar_Complex numitor;
    numitor.re = (z1.re * aux.re) - (z1.im * aux.im) ;
    numitor.im = (z1.re * aux.im) + (z1.im * aux.re) ;

    double numarator;
    numarator = z2.re * z2.re - z2.im *z2.im;

    raport.re = numitor.re / numarator;
    raport.im = numitor.im / numarator;

    return raport;
}


class Matrice_Complexa
{
    int linii, coloane;
    Numar_Complex M[100][100];

public:
    
    Matrice_Complexa (Numar_Complex k, int linii, int coloane);
    Matrice_Complexa();
    Matrice_Complexa(const Matrice_Complexa &ob);
    ~Matrice_Complexa();
    Matrice_Complexa(const Numar_Complex &z);
    friend istream & operator >> (istream &in, Matrice_Complexa &A);
    friend ostream & operator << (ostream &out, const Matrice_Complexa &A);
    Matrice_Complexa operator+ (const Matrice_Complexa &A);
    Matrice_Complexa operator* (const Matrice_Complexa &A);

    Matrice_Complexa &operator[](int i) { return reinterpret_cast<Matrice_Complexa &>(this->M[i]); }   ///nu stiu exact ce se intampla
                                    /// in linia asta de cod, dar aveam o eroare, am cautat pe net, am copiat aici bucata de cod gasita
                                    /// acolo, am adaptat-o la problema mea si a disparut eroarea :)

};


Matrice_Complexa :: Matrice_Complexa(Numar_Complex k, int linii, int coloane)
{
    for(int i=0; i<linii; i++)
        for(int j=0; j<coloane; j++)
            M[i][j].re = k.re, M[i][j].im = k.im;

}


Matrice_Complexa :: Matrice_Complexa()
{
    linii = 1;
    coloane = 1;
    M[0][0].re = 0;
    M[0][0].im = 0;
}


Matrice_Complexa :: Matrice_Complexa(const Matrice_Complexa &ob)
{
    linii = ob.linii;
    coloane = ob.coloane;

    for(int i=0; i<linii; i++)
        for(int j=0; j<coloane; j++)
            M[i][j].re = ob.M[i][j].re, M[i][j].im = ob.M[i][j].im;
}


Matrice_Complexa ::~Matrice_Complexa()
{
    linii = 0;
    coloane = 0;
}


Matrice_Complexa::Matrice_Complexa(const Numar_Complex &z) {
}


istream & operator >> (istream &in, Matrice_Complexa &A)
{
    cout<< "Numar linii: ";
    in>> A.linii;
    cout<< "Numar coloane: ";
    in>> A.coloane;

    for(int i=0; i < A.linii; i++)
        for(int j=0; j < A.coloane; j++)
        {
            cout<< "Elementul A[" << i << "][" << j << "]: ";
            in>> A.M[i][j];
        }

    return in;
}


ostream & operator << (ostream &out, const Matrice_Complexa &A)
{
    for(int i=0; i < A.linii; i++)
    {
        for (int j = 0; j < A.coloane; j++)
            {out << A.M[i][j];   out<< "    ";}
        out << endl;
    }

    return out;
}


Matrice_Complexa Matrice_Complexa :: operator+ (const Matrice_Complexa &A)
{
    if (linii != A.linii  ||  coloane != A.coloane)
        cout<<"Matricele nu pot fi insumate";
    else
    {
        Matrice_Complexa suma;

        suma.linii = linii;
        suma.coloane = coloane;

        for(int i=0; i < linii; i++)
            for(int j=0; j < coloane; j++)
                suma[i][j] = M[i][j] + A.M[i][j];

        return suma;
    }
    
}


Matrice_Complexa Matrice_Complexa :: operator* (const Matrice_Complexa &A)
{
    if (coloane != A.linii)
        cout<<"Matricele nu pot fi inmultite";
    else
    {
        Matrice_Complexa produs;

        produs.linii = linii;
        produs.coloane = A.coloane;

        for(int i=0; i < linii; i++)
            for(int k=0; k < A.coloane; k++)
                for(int j=0; j < coloane; j++)
                    produs[i][k] = produs[i][k] + M[i][j] * A.M[j][k];

        return produs;
    }
    
}


int main()
{
    Numar_Complex z1, z2;
    cout<<"z1: \n";
    cin>>z1;
    cout<<"z2: \n";
    cin>>z2;
    cout<<"z1="<<z1<<"     z2="<<z2<<endl;
    cout<<"z1+z2 = "<<z1+z2<<endl;
    cout<<"z1*z2 = "<<z1*z2<<endl;


    Matrice_Complexa A, B;
    cout<<"\n Prima matrice \n";
    cin>>A;
    cout<<A;
    cout<<"A doua matrice \n";
    cin>>B;
    cout<<B;
    cout<<"suma: \n";
    cout<<A+B;
    cout<<"produsul: \n";
    cout<<A*B;

}
