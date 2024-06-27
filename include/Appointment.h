#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include"include/personnes.h"
#include<string>
#include<vector>
#include"Date.h"

using namespace std;


class Appointment
{
    friend class Rdv;
    friend class RendezVous;
    friend class Menu;
    public:
        Appointment(string nom, Date date, vector<string> pers);
        Appointment(const Appointment &a);
        Appointment();
        bool estPresent(string nom)const;
        void affichepersonnes()const;
private:
         string d_nom;
         Date d_date;
         vector<string> d_personnes;
         Appointment* d_suiv;
         Appointment* d_prec;
};

#endif // APPOINTMENT_H
