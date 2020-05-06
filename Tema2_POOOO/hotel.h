
using namespace std;

int COD = 1;

class Camera {
protected:
    int zile[365] = {0};

public:
    Camera() {};
    Camera(const Camera &c);
    ~Camera();

    virtual void setOcupat(int i, int b) = 0;
    virtual int getOcupat(int i) = 0;
};


Camera::Camera(const Camera &c) {
    for(int i=0; i<365; i++)
        zile[i] = c.zile[i];
}

Camera::~Camera() {
    for(int i=0; i<365; i++)
        zile[i] = 0;
}

//////////////////////////////////////////////////////////////////////////////


class Dubla : public Camera {
    int id;
    const static int nr_paturi = 2;

public:
    Dubla()  ;
    Dubla(const Dubla &d);
    ~Dubla() {};

    friend ostream & operator << (ostream &out, const Dubla &d);
    Dubla& operator=(const Dubla &a);

    void setOcupat(int i, int b);
    int getOcupat(int i);
    int getId();
};

Dubla::Dubla() {
    id = COD;
    COD++;
}

Dubla::Dubla(const Dubla &d){
    id = d.id;
    for(int i=0; i<365; i++)
        zile[i] = d.zile[i];
}

ostream & operator << (ostream &out, const Dubla &d){
    out<<"camera "<<d.id;
    return out;
}

Dubla& Dubla::operator = (const Dubla &d) {
    this->id = d.id;
    for(int i=0; i<365; i++)
        this->zile[i] = d.zile[i];

    return *this;
}

void Dubla::setOcupat(int i, int b) {
    zile[i] = b;
}

int Dubla::getOcupat(int i) {
    return zile[i];
}

int Dubla::getId() {
    return id;
}


/////////////////////////////////////////////////////////////////////////////


class Apartament : public Camera {
    int id;
    const static int nr_paturi = 4;

public:
    Apartament();
    Apartament(const Apartament &d);
    ~Apartament() {};

    friend ostream & operator << (ostream &out, const Apartament &a);
    Apartament& operator=(const Apartament &a);
    void setOcupat(int i, int b);
    int getOcupat(int i);
    int getId();
};

Apartament::Apartament(){
    id = COD;
    COD++;
}

Apartament::Apartament(const Apartament &a){
    id = a.id;
    for(int i=0; i<365; i++)
        zile[i] = a.zile[i];
}

ostream & operator << (ostream &out, const Apartament &a){
    out<<"apartamentul "<<a.id;
    return out;
}

Apartament& Apartament::operator = (const Apartament &a) {
    this->id = a.id;
    for(int i=0; i<365; i++)
        this->zile[i] = a.zile[i];

    return *this;
}

void Apartament::setOcupat(int i, int b) {
    zile[i] = b;
}

int Apartament::getOcupat(int i) {
    return zile[i];
}

int Apartament::getId() {
    return id;
}


///////////////////////////////////////////////////////////////////////


int CODSALA = 1;

class Sala {
    int id;
    bool sala_tip_scena;   //1=scena, 0=conferinte;
    bool proiector;
    int capacitate;
    int zile[365] = {0};

public:
    Sala();
    Sala(const Sala &s);
    ~Sala();

    friend istream & operator >> (istream &in, Sala &s);
    friend ostream & operator << (ostream &out, const Sala &s);
    Sala& operator=(const Sala &s);

    int getCapacitate() const;
    void setOcupat(int i, int b);
    int getOcupat(int i);
};

Sala::Sala() {
    id = CODSALA;
    CODSALA++;
    sala_tip_scena = 1;
    proiector = 1;
    capacitate = 20;
}

Sala::Sala(const Sala &s) {
    sala_tip_scena = s.sala_tip_scena;
    proiector = s.proiector;
    capacitate = s.capacitate;
    for(int i=0; i<365; i++)
        zile[i] = s.zile[i];
}

Sala::~Sala() {}

istream & operator >> (istream &in, Sala &s) {
    in >> s.sala_tip_scena;
    in >> s.proiector;
    in >> s.capacitate;
    return in;
}

ostream & operator << (ostream &out, const Sala &s) {
    out<<"Sala numarul "<<s.id<<" are o capacitate de "<<s.capacitate<<" persoane;";
    if(s.sala_tip_scena)
        if(s.proiector)
            out<<"sala este de tip scena si are proiector.\n";
        else
            out<<"sala este de tip scena si nu are proiector. \n";
    else
    if(s.proiector)
        out<<"sala este de tip conferinta si are proiector.\n";
    else
        out<<"sala este de tip conferinta si nu are proiector. \n";
    return out;
}

Sala& Sala::operator = (const Sala &s) {
    this->id = s.id;
    this->proiector = s.proiector;
    this->capacitate = s.capacitate;
    for(int i=0; i<365; i++)
        this->zile[i] = s.zile[i];

    return *this;
}

int Sala::getCapacitate() const {
    return capacitate;
}

void Sala::setOcupat(int i, int b) {
    zile[i] = b;
}

int Sala::getOcupat(int i) {
    return zile[i];
}


///////////////////////////////////////////////////////////////////////


class Restaurant {
    int locuri;
    int zile[365] = {0};

public:
    Restaurant();
    ~Restaurant();

    void setNrLocuri(int k);
    int getLocuriLibere(int i);
    int getTotalLocuri() const;         //aveam eroare la H.restaurant.getTotalLocuri() si compilatorul a pus un const
};

Restaurant::Restaurant() {}

Restaurant::~Restaurant() {}

void Restaurant::setNrLocuri(int k) {
    locuri = k;
}

int Restaurant::getLocuriLibere(int i) {
    return locuri - zile[i];
}

int Restaurant::getTotalLocuri() const {
    return locuri;
}


////////////////////////////////////////////////////////////////////////////////////


class Hotel {
    string nume;
    int nr_camere;
    int nr_duble;
    int nr_apartamente;
    int capacitate_totala;
    int nr_sali;
    vector<Dubla> duble;
    vector<Apartament> apartamente;
    vector<Sala> sali;
    Restaurant restaurant;

public:
    Hotel();
    ~Hotel();

    friend istream & operator >> (istream &in, Hotel &H);
    friend ostream & operator << (ostream &out, const Hotel &H);
    Hotel& operator=(const Hotel &H);
    string getNume();
    int getNrCamere();
    int getNrDuble();
    int getNrApartamente();
    int getDubleLibere(int i);
    int getApartamenteLibere(int i);
    vector<Dubla> getDuble();
    vector<Apartament> getApartamente();


    void citesteCerere(Grup &G);
    int perioadaLibera(Grup &G);
    bool ziLibera(Grup &G, int zi);
    void rezervaPerioada(Grup &G, int inceput, int sfarsit);
    
    void stergeGrup(Grup &G);

    friend class Grup;
};

Hotel::Hotel() {
    nume = "";
    nr_camere = nr_duble = nr_apartamente = 0;
}

Hotel::~Hotel() {
    nume = "";
    nr_camere = nr_duble = nr_apartamente = 0;
    duble.clear();
    apartamente.clear();
}

istream & operator >> (istream &in, Hotel &H) {
    in >> H.nume;
    in >> H.nr_camere;
    in >> H.nr_duble;
    in >> H.nr_apartamente;

    for(int i=0; i<H.nr_duble; i++)
    {
        Dubla *d = new Dubla;
        H.duble.push_back(*d);

    }

    for(int i=0; i<H.nr_apartamente; i++)
    {
        Apartament *a = new Apartament;
        H.apartamente.push_back(*a);
    }

    H.capacitate_totala = 2*H.nr_duble + 4*H.nr_apartamente;

    int k;
    in >> k;
    H.restaurant.setNrLocuri(k);

    in >> H.nr_sali;

    for(int i=0; i<H.nr_sali; i++)
    {
        Sala s;
        in>>s;
        H.sali.push_back(s);
    }

    return in;
}


ostream & operator << (ostream &out, const Hotel &H) {
    out<<"Hotelul se numeste "<<H.nume<<".\n";

    out<<"Acesta are "<<H.nr_camere<<" camere, dintre care "<<H.nr_duble<<" sunt duble iar "
       <<H.nr_apartamente<<" sunt apartamente de 4 persoane.\n";

    out<<"Capacitatea totala de cazare este de "<<H.capacitate_totala<<" de persoane. \n";

    out<<"Capacitatea totala a restaurantului este de "<<H.restaurant.getTotalLocuri()<<" de persoane.\n";

    out<<"Hotelul dispune de "<<H.nr_sali<<" sali de conferinta; capacitatea acestora este de ";
    for(int i=0; i<H.nr_sali; i++)
        out<<H.sali[i].getCapacitate()<<" ";
    out<<"persoane.";


    out<<endl;

    return out;
}

Hotel& Hotel::operator=(const Hotel &H){
    this->nume = H.nume;
    this->nr_camere = H.nr_camere;
    this->nr_duble = H.nr_duble;
    this->nr_apartamente = H.nr_apartamente;
    this->capacitate_totala = H.capacitate_totala;
    this->duble = H.duble;
    this->apartamente = H.apartamente;
    this->nr_sali = H.nr_sali;
    this->sali = H.sali;
    this->restaurant = H.restaurant;

    return *this;
}

string Hotel:: getNume() {
    return nume;
}

int Hotel:: getNrCamere() {
    return nr_camere;
}

int Hotel:: getNrDuble() {
    return nr_duble;
}

int Hotel:: getNrApartamente(){
    return nr_apartamente;
}

int Hotel::getDubleLibere(int zi) {

    int s=0;

    for(int i=0; i<getNrDuble(); i++)
        if(duble[i].getOcupat(zi) == 0)
            s++;

    return s;
}

int Hotel::getApartamenteLibere(int zi) {

    int s=0;

    for(int i=0; i<getNrApartamente(); i++)
        if(apartamente[i].getOcupat(zi) == 0)
            s++;

    return s;
}

vector<Dubla> Hotel:: getDuble(){
    return duble;
}

vector<Apartament> Hotel:: getApartamente(){
    return apartamente;
}

void Hotel::citesteCerere(Grup &G) {

    int data_checkin = perioadaLibera(G);

    if(data_checkin != -1)
    {
        G.setCheckIn(data_checkin);

        //for(int i=0; i< G.getPerioada()+data_checkin ; i++)
        rezervaPerioada(G, data_checkin, data_checkin + G.getPerioada() );
    }
    else
        cout<<"Nu exista o perioada pentru grupul dumneavoastra.";

}


int Hotel::perioadaLibera(Grup &G) {

    cout<<endl<<"perioada "<<G.getPerioada()<<endl;

    for(int i=0; i<100 - G.getPerioada(); i++)
    {
        bool okay = true;

        for(int j=i; j< G.getPerioada(); j++)
        {cout<<"ziua "<<j<<" este libera: ";

            if(ziLibera(G, j) == false)
            {okay = false;
                break;
            }
        }

        if(okay)
        {cout<<"\n data check in: "<<i<<" "; return i;}
    }

    return -1;
}


bool Hotel::ziLibera(Grup &G, int zi) {

    int spatiu = 0;

    for (int i = 0; i < getNrDuble() ; i++)
        if(duble[i].getOcupat(zi) == 0)
            spatiu+=2;


    for (int i=0; i < getNrApartamente() ; i++)
        if(apartamente[i].getOcupat(zi) == 0)
            spatiu+=4;

    if(spatiu < G.getNrPersoane())
    {   cout<<"false\n"; return false;}

    //if(G.getNrMicDejun() < restaurant.getLocuriLibere(zi))
    //    return false;

    cout<<"spatiu: "<<spatiu<<" true\n";
    return true;
}

void Hotel::rezervaPerioada(Grup &G, int inceput, int sfarsit) {

    int nr_persoane = G.getNrPersoane();
    cout<<"nr persoane "<<nr_persoane<<" in ziua "<<inceput<<endl;

    int a_crt = 0;
    int d_crt = 0;

    int pers_crt = 0;

    for(int i=0; i<getNrCamere() && nr_persoane > 0; i++)
    {
        if(nr_persoane > 2 && getApartamenteLibere(inceput) > 0)
        {
            while (apartamente[a_crt].getOcupat(inceput) != 0)
                a_crt++;

            
            ///ocup apartamentul
            
            for(int zi=inceput; zi<sfarsit; zi++)
                apartamente[a_crt].setOcupat(zi, G.getId() );

            
            
            int apartament_dat = apartamente[a_crt].getId();    //apartament_dat = id-ul apartamentului ocupat
            cout<<"apartament dat "<<apartament_dat<<endl;

            a_crt++;                                            //cresc pozitia apartamentului curent
            cout<<"a crt"<<a_crt<<endl;



                    for( int j=0; j<4 && pers_crt < G.getNrPersoane(); j++)         //atribui camera ocupata participantilor
                    {G.grup[pers_crt].setNrCamera(apartament_dat, G.grup[pers_crt]);

                        cout<<"pers crt "<<pers_crt<<" numita: "<<G.grup[pers_crt].getNume()<<" "<<G.grup[pers_crt].getNrCamera()<<" "<<G.grup[pers_crt].vreaMicDejun()<<endl;

                        pers_crt++;
                    }



            nr_persoane -=4;
            cout<<"nr persoane "<<nr_persoane<<endl;
        }



        if((nr_persoane <= 2 && nr_persoane > 0) || (getApartamenteLibere(inceput) == 0 && nr_persoane>0))
        {
            while (duble[d_crt].getOcupat(inceput) != 0)
            {
                d_crt++;
            }

            
            
            
            //ocup camera
            for(int zi=inceput; zi<sfarsit; zi++)
                duble[d_crt].setOcupat(zi, G.getId() );



            int camera_data = duble[d_crt].getId();
            cout<<"dubla data "<<camera_data<<endl;

            d_crt++;
            cout<<"d crt"<<d_crt<<endl;



                    for(int j = 0; j<2 && pers_crt < G.getNrPersoane(); j++)  //atribui camera ocupata participantilor
                    {G.grup[pers_crt].setNrCamera(camera_data, G.grup[pers_crt]);

                        cout<<"pers crt "<<pers_crt<<" numita: "<<G.grup[pers_crt].getNume()<<" "<<G.grup[pers_crt].getNrCamera()<<" "<<G.grup[pers_crt].vreaMicDejun()<<endl;

                        pers_crt++;
                    }



            nr_persoane -= 2;

            cout<<"nr persoane "<<nr_persoane<<endl;

        }

    }
}




void Hotel:: stergeGrup(Grup &G) {
    
    for (int i=0; i<G.getNrPersoane(); i++)
    {
        int camera = G.grup[i].getNrCamera();
        cout<<camera;
        
        if(camera < getNrDuble() )
        {
            cout<<" "<<camera-1<<endl;
            camera--;
            for(int zi = G.getCheckIn();  zi < G.getCheckIn() + G.getPerioada();  zi++)
            {
                cout<<"ziua "<<zi<<endl;
                duble[camera].setOcupat(zi, 0);
                
            }
                
        }
        else
        {
            camera = camera - getNrDuble();
            cout<<" "<<camera-1<<endl;
            
            camera--;
            for(int zi = G.getCheckIn();  zi < G.getCheckIn() + G.getPerioada();  zi++)
            {
                cout<<"ziua "<<zi<<" apartamentul "<<getApartamente()[camera].getId()<<endl;
                
                apartamente[camera].setOcupat(zi, 0);
                cout<<"ocupat? "<<getApartamente()[camera].getOcupat(zi)<<endl;

    
            }
        }
    }
    
}
