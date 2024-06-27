#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include"Horaire.h"
#include<ostream>
using namespace std;
class Date
{
public:
    Date(Horaire hd,Horaire hf,int j,int m,int a);
    Date();
    int getJours() const;
    int getMois() const;
    int getAnnee() const;
    Horaire getHDebut() const;
    Horaire getHFin() const;
    bool sameDay(Date date)const;
    bool sameMonth(Date date)const;
    string toString() const;
    string tostringHDebut() const;
    string tostringHFin() const;
    string tostringHoraire()const;

private:
    int d_jours;
    int d_mois;
    int d_annee;
    Horaire h_debut;
    Horaire h_fin;
};
    bool operator< (Date const& d1,Date const& d2);
    bool operator> (Date const& d1,Date const& d2);
    bool operator== (Date const& d1,Date const& d2);
    bool operator!= (Date const& d1,Date const& d2);
    ostream& operator<<(ostream& os, const Date& date);



#endif // HEADER_H_INCLUDED
