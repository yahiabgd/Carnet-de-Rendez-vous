#ifndef RDV_H
#define RDV_H
#include<string>
#include"Appointment.h"
#include"Date.h"
using namespace std;


class Rdv{
public:
    Rdv();
    ~Rdv();
    Appointment* getTete()const;
    Rdv(const Rdv *r);
    void addRdv(Appointment* rdv);
    Appointment* getRdv(string nom);
    Appointment* getRdv(int idx);
    void deleteRdv(string nom);
    void deleteRdv(int idx);
    //void modifierDate(string nom, int year =  ); // struct problem
    void ajouterPersonne(string nom_rdv,string nom_per);
    Rdv* afficheRdvDateDonnee(const Date& date);
    Rdv* afficheRdvMoisDonnee(const Date& date);
    Rdv* afficheRdvPersonneDonnee(const string nom);
    bool personneLibre(string nom, Date date)const;
    bool personnesLibre(Appointment* a)const;
    void afficheRdv(string nom)const;
    void affiche()const;
    Appointment chercherRdv(string nom);


private:
    Appointment *d_tete;

};

#endif // RDV_H
