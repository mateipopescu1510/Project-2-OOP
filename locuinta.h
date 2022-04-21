#pragma once
/*
-Locuință (string numeClient, int suprafataUtila, float discount)
-Apartament (int etaj) : Locuinta
-Casa (int suprafataCurte) : Locuinta
La clasa Locuinta se va adauga metoda virtuala pura CalculChirie (X,Y) cu X = valoare standard chirie/mp(intreg),
Y=1 daca se ia in considerare discountul si 0 daca nu se ia in considerare.
Metoda va fi adaugata in clasa Apartament dupa formula X*suprafataUtila*(1-Y*discount/100.0),
respectiv in clasa Casa dupa formula X*(suprafataUtila + 0.2*suprafataCurte) * (1-Y*discount/100.0).
Metodele vor fi testate prin parcurgerea unui vector de pointeri la Locuinta *,
incarcat cu obiecte de tip Apartament si Casa.
Se defineste clasa AgentieImobiliara continand un vector de pointeri la obiecte de tip Locuinta alocat dinamic.
Se va supraincarca operatorul >> pentru a citi locuintele agentiei si operatorul << pentru afisarea lor.
*/
#include <vector>

class Locuinta
{
public:
    Locuinta()
    {
        suprafataUtila = 0;
        discount = 0.0;
        numeClient = "";
        Y = 0;
    }
    Locuinta(int s, float d, std::string n, int y)
    {
        suprafataUtila = s;
        discount = d;
        numeClient = n;
        Y = y;
    }
    Locuinta(const Locuinta &L)
    {
        suprafataUtila = L.suprafataUtila;
        discount = L.discount;
        numeClient = L.numeClient;
        Y = L.Y;
    }
    ~Locuinta() {}
    virtual float CalculChirie() = 0;
    static void setX()
    {
        std::cout << "Introduceti valoarea standard pentru chirie: ";
        std::cin >> X;
    }
    static int getX()
    {
        return X;
    }
    void operator=(const Locuinta &L)
    {
        suprafataUtila = L.suprafataUtila;
        discount = L.discount;
        numeClient = L.numeClient;
    }

    friend std::istream &operator>>(std::istream &, Locuinta &);
    friend std::ostream &operator<<(std::ostream &, const Locuinta &);

protected:
    static int X; // valoarea standard
    int Y;        // daca se aplica discout sau nu
    std::string numeClient;
    int suprafataUtila;
    float discount;
};
int Locuinta::X = 0;

class Apartament : public Locuinta
{
public:
    Apartament()
    {
        etaj = -1;
    }
    Apartament(int s, float d, std::string n, int y, int e)
        : Locuinta(s, d, n, y)
    {
        etaj = e;
    }
    Apartament(const Apartament &A) : Locuinta(A)
    {
        etaj = A.etaj;
    }
    ~Apartament() {}

    float CalculChirie()
    {
        return X * suprafataUtila * (1 - Y * discount / 100.0);
    }

    void operator=(const Apartament &A)
    {
        etaj = A.etaj;
        const Locuinta &Lref = A;
        this->Locuinta::operator=(Lref);
    }
    friend std::istream &operator>>(std::istream &, Apartament &);
    friend std::ostream &operator<<(std::ostream &, const Apartament &);

private:
    int etaj;
};

class Casa : public Locuinta
{
public:
    Casa()
    {

        suprafataCurte = 0;
    }
    Casa(int s, float d, std::string n, int y, int sc)
        : Locuinta(s, d, n, y)
    {
        suprafataCurte = sc;
    }
    Casa(const Casa &C) : Locuinta(C)
    {
        suprafataCurte = C.suprafataCurte;
    }
    ~Casa() {}
    float CalculChirie()
    {
        return X * (suprafataUtila + 0.2 * suprafataCurte) * (1 - Y * discount / 100.0);
    }

    void operator=(const Casa &C)
    {
        suprafataCurte = C.suprafataCurte;
        const Locuinta &Lref = C;
        this->Locuinta::operator=(Lref);
    }
    friend std::istream &operator>>(std::istream &, Casa &);
    friend std::ostream &operator<<(std::ostream &, const Casa &);

private:
    int suprafataCurte;
};

class AgentieImobiliara
{
public:
    AgentieImobiliara()
    {
        V.push_back(new Casa(99, 15, "Popescu Calin", 1, 400));
        V.push_back(new Apartament(57, 30, "Anghel Anica", 0, 5));
    }
    AgentieImobiliara(std::vector<Locuinta *> V)
    {
        this->V = V;
    }
    AgentieImobiliara(const AgentieImobiliara &agentie)
    {
        V = agentie.V;
    }
    ~AgentieImobiliara()
    {
        V.clear();
    }
    void operator=(const AgentieImobiliara &agentie)
    {
        V = agentie.V;
    }
    friend std::istream &operator>>(std::istream &, AgentieImobiliara &);
    friend std::ostream &operator<<(std::ostream &, const AgentieImobiliara &);
    void adaugaLocuinta(Locuinta *L)
    {
        V.push_back(L);
    }
    void stergereLocuinta(int);

private:
    std::vector<Locuinta *> V;
};
