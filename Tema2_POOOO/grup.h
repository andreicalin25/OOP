
using namespace std;

class Persoana {
    string nume_prenume;
    bool mic_dejun;
    int camera;

public:

    Persoana();
    Persoana(const Persoana &p);
    ~Persoana();

    friend istream & operator >> (istream &in, Persoana &p);
    friend ostream & operator << (ostream &out, const Persoana &p);
    Persoana& operator=(const Persoana &p);


    bool vreaMicDejun();
    void setNrCamera(int k, Persoana &p);
    int getNrCamera();
    
    string getNume();
};

Persoana::Persoana() {
    nume_prenume = "";
    mic_dejun = 0;
    //camera = -2;
}

Persoana::Persoana(const Persoana &p) {
    nume_prenume = p.nume_prenume;
    mic_dejun = p.mic_dejun;
    camera = p.camera;
}

Persoana::~Persoana(){}

istream & operator >> (istream &in, Persoana &p) {
    //cout<<"\nIntroduceti datele participantului in formatul nume_prenume1_prenume2: ";
    in>> p.nume_prenume;

    //cout<<"Introduceti 1 daca "<<p.nume_prenume<<" doreste mic dejun la restaurant, sau 0 altfel: ";
    in>> p.mic_dejun;

    return in;
}

ostream & operator << (ostream &out, const Persoana &p) {
    out<< p.nume_prenume;

    if (p.mic_dejun)
        out<< ": doreste mic dejun la restaurant";
    else
        out<< ": nu doreste mic dejun la restaurant";

    out<<" si este cazat la camera "<<p.camera<<";";

    return out;
}

Persoana& Persoana::operator=(const Persoana &p)
{
    this->nume_prenume = p.nume_prenume;
    this->camera = p.camera;
    this->mic_dejun = p.mic_dejun;
    return *this;
}

bool Persoana::vreaMicDejun() {
    return mic_dejun;
}

void Persoana::setNrCamera(int k, Persoana &p) {
    camera = k;
}

int Persoana::getNrCamera() {
    return camera;
}

string Persoana::getNume() {
    return nume_prenume;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cod = 1;

class Grup {
    int id;
    vector<Persoana> grup;
    int nr_persoane;
    int perioada;
    int sala;
    int check_in;

public:
    Grup();
    Grup(const Grup &G);
    ~Grup();

    friend istream & operator >> (istream &in, Grup &G);
    friend ostream & operator << (ostream &out, const Grup &G);
    Grup& operator=(const Grup &G);

    int getNrPersoane();
    int getPerioada();
    int getNrMicDejun();
    int getTipSala();
    int getId();

    void setCheckIn(int k);
    int getCheckIn();

    friend class Hotel;
};

Grup::Grup() {
    perioada = 0;
    sala = 0;
}

Grup::Grup(const Grup &G) {
    grup = G.grup;
    perioada = G.perioada;
    sala = G.sala;
}

Grup::~Grup() {
    grup.clear();
}

istream & operator >> (istream &in, Grup &G) {
    G.id = cod;
    cod++;

    //cout<<"\nIntroduceti numarul de zile pentru care doriti o rezervare: ";
    in >> G.perioada;
    
    try {
        if (G.perioada>10)
            throw 'M';
        
        if (G.perioada<1)
            throw 'm';
    }
    
     catch (char x) {
         if (x == 'M')
             cout<<"\nPerioada este prea mare,";
         
         if (x == 'm')
             cout<<"\nPerioada este prea mica,";
         
         cout<<" va rugam reintroduceti o perioada de cazare intre 1 si 10 zile: ";
         cin>>G.perioada;
    }

    //cout<<"\nIntroduceti 1 daca sala de conferinte dorita este de tip scena, 0 altfel: ";
    in >> G.sala;

    //cout<<"\nIntroduceti numarul de persoane ale grupului: ";
    in >> G.nr_persoane;

    for(int i=0; i<G.nr_persoane; i++)
    {
        Persoana p;
        in>>p;
        G.grup.push_back(p);
    }

    return in;
}

ostream & operator << (ostream &out, const Grup &G) {
    out<<"Grupul are codul "<<G.id<<";\n";

    out<<"Grupul va fi cazat timp de "<<G.perioada<<" zile, incepand cu ziua "<<G.check_in<<";\n";

    if(G.sala)
        out<<"grupul nu doreste sala de conferinte tip scena;\n";
    else
        out<<"grupul doreste sala de conferinte tip scena;\n";

    out<<"Grupul este alcatuit din urmatoarele "<<G.nr_persoane<<" persoane:\n";

    for(int i=0; i<G.nr_persoane; i++)
        out<<G.grup[i]<<endl;

    return out;
}

Grup& Grup::operator=(const Grup &G)
{
    this->id = G.id;
    this->nr_persoane = G.nr_persoane;
    this->check_in = G.check_in;
    this->perioada = G.perioada;
    this->sala = G.sala;
    this->grup = G.grup;
    return *this;
}

int Grup::getNrPersoane() {
    return grup.size();
}

int Grup::getNrMicDejun() {
    int s=0;
    
    for(int i=0; i< nr_persoane; i++)
        if (grup[i].vreaMicDejun())
            s++;

    return s;
}

int Grup::getPerioada() {
    return perioada;
}

int Grup::getTipSala() {
    return sala;
}

int Grup::getId() {
    return id;
}

void Grup::setCheckIn(int k) {
    check_in = k;
}

int Grup::getCheckIn() {
    return check_in;
}
