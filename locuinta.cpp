#include <iostream>
#include <string>
#include "locuinta.h"
using namespace std;

istream &operator>>(istream &in, Locuinta &L)
{
    cout << "suprafataUtila: ";
    in >> L.suprafataUtila;
    cout << "Se aplica discount?(1 sau 0): ";
    in >> L.Y;
    if (L.Y == 1)
    {
        cout << "discount: ";
        in >> L.discount;
    }
    cout << "numeClient: ";
    in.get();
    getline(in, L.numeClient);
    return in;
}

ostream &operator<<(ostream &out, const Locuinta &L)
{
    out << "suprafataUtila: " << L.suprafataUtila << " mp\n";
    if (L.Y == 1)
        out << "discount: " << L.discount << " %\n";
    else
        out << "Nu se aplica discount pentru aceasta locuinta!\n";
    out << "numeClient: " << L.numeClient << "\n";
    return out;
}

istream &operator>>(istream &in, Apartament &A)
{
    Locuinta &Lref = A;
    in >> Lref;
    cout << "etaj: ";
    in >> A.etaj;
    return in;
}

ostream &operator<<(ostream &out, const Apartament &A)
{
    const Locuinta &Lref = A;
    Apartament Ac(A);
    out << Lref << "etaj: " << A.etaj << "\n";
    out << "Chirie: " << Ac.CalculChirie() << " lei\n";
    return out;
}

istream &operator>>(istream &in, Casa &C)
{
    Locuinta &Lref = C;
    in >> Lref;
    cout << "suprafataCurte: ";
    in >> C.suprafataCurte;
    return in;
}

ostream &operator<<(ostream &out, const Casa &C)
{
    const Locuinta &Lref = C;
    Casa Cc(C);
    out << Lref << "suprafataCurte: " << C.suprafataCurte << " mp\n";
    out << "Chirie: " << Cc.CalculChirie() << " lei\n";
    return out;
}

istream &operator>>(istream &in, AgentieImobiliara &agentie)
{
    int nrLocuinte;
    string tipLocuinta;
    cout << "Introduceti numarul de locuinte: ";
    in >> nrLocuinte;
    in.get();
    for (int nr = 0; nr < nrLocuinte; nr++)
    {
        int corect = 0;
        while (!corect)
        {
            cout << "Tip de locuinta? (Apartament sau Casa): ";
            getline(in, tipLocuinta);
            if (tipLocuinta == "Apartament")
            {
                Apartament *A = new Apartament;
                cout << "\nIntroduceti informatii despre apartament:\n";
                in >> *A;
                cout << endl;
                agentie.V.push_back(A);
                corect = 1;
            }
            else if (tipLocuinta == "Casa")
            {
                Casa *C = new Casa;
                cout << "\nIntroduceti informatii despre casa:\n";
                in >> *C;
                cout << endl;
                agentie.V.push_back(C);
                corect = 1;
            }
            else
            {
                cout << "Alegere invalida.\n";
            }
            in.get();
        }
    }
    return in;
}

ostream &operator<<(ostream &out, const AgentieImobiliara &agentie)
{
    for (int i = 0; i < agentie.V.size(); i++)
    {
        cout << "Locuinta nr " << i << ": \n\n";
        if (dynamic_cast<Apartament *>(agentie.V[i]))
        {
            Apartament *A = dynamic_cast<Apartament *>(agentie.V[i]);
            out << *A << endl;
        }
        if (dynamic_cast<Casa *>(agentie.V[i]))
        {
            Casa *C = dynamic_cast<Casa *>(agentie.V[i]);
            out << *C << endl;
        }
    }
    return out;
}

void AgentieImobiliara::stergereLocuinta(int i)
{
    if (i > V.size() || i < 0)
    {
        cout << "Locuinta nu exista!\n";
    }
    else
    {
        V.erase(V.begin() + i);
        cout << "Locuinta nr " << i << " a fost stearsa!\n";
    }
}