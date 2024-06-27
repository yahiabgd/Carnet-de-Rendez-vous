#include "include/Appointment.h"
#include<iostream>

Appointment::Appointment(string nom, Date date, vector<string> pers):
    d_nom{nom},
    d_date{date},
    d_personnes{pers},
    d_suiv{nullptr},
    d_prec{nullptr}
{}


Appointment::Appointment():
    d_nom{" "},
    d_date{},
    d_personnes{},
    d_suiv{nullptr},
    d_prec{nullptr}

{}
Appointment::Appointment(const Appointment &a){
    d_nom=a.d_nom;
    d_date=a.d_date;
    d_personnes=a.d_personnes;
    d_suiv=nullptr;
    d_prec=nullptr;
}

bool Appointment::estPresent(string nom)const{
    int i = 0;
    bool trouv=false;
    while (i<d_personnes.size() && !trouv){
        if (d_personnes[i]==nom){
            trouv=true;
        }
        i++;
    }
    return trouv;
}

void Appointment:: affichepersonnes()const{
    for(int i =0 ; i<d_personnes.size() ; i++){
        cout<< d_personnes[i]<<" | ";
    }
    cout <<endl;
}
