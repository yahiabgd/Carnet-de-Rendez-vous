#include "include/Date.h"
#include<iostream>
using namespace std;

Date::Date(Horaire hd,Horaire hf,int j,int m,int a):h_debut{hd},h_fin{hf},d_jours{j},d_mois{m},d_annee{a}{}
Date::Date():
    h_debut{},
    h_fin{},
    d_jours{},
    d_mois{},
    d_annee{}
{

}
int Date::getJours() const{return d_jours;}
int Date::getMois() const{return d_mois;}
int Date::getAnnee() const{return d_annee;}
Horaire Date::getHDebut() const{return h_debut;}
Horaire Date::getHFin() const{return h_fin;}
string Date:: tostringHDebut() const{
    return h_debut.toString();
}
string Date:: tostringHFin() const{
    return h_fin.toString();
}

string Date:: tostringHoraire()const{
    return h_debut.toString() +" - "+ h_fin.toString();
}



bool Date::sameDay(Date date)const{
    if (date.d_annee==d_annee && date.d_mois==d_mois && date.d_jours==d_jours ){
        return true;
    }else{
        return false;
    }
}
bool Date:: sameMonth(Date date)const{
    if (date.d_annee==d_annee && date.d_mois==d_mois){
        return true;
    }else{
        return false;
    }
}

bool operator< (Date const& d1,Date const& d2) {

        if(d1.getAnnee()==d2.getAnnee())
        {
            if(d1.getMois()==d2.getMois())
            {
                if(d1.getJours()==d2.getJours())
                {
                    if(d1.getHDebut()== d2.getHDebut())
                    {
                        return 0;
                    }
                    else
                    {
                      return (d1.getHDebut()<d2.getHDebut());
                    }
                }
                else
                {
                    return (d1.getJours()<d2.getJours());
                }
            }
            else
            {
                return (d1.getMois()<d2.getMois());
            }
        }
        else
        {
            return (d1.getAnnee()<d2.getAnnee());
        }
    }

bool operator> (Date const& d1,Date const& d2){
    if(d1.getAnnee()==d2.getAnnee())
        {
            if(d1.getMois()==d2.getMois())
            {
                if(d1.getJours()==d2.getJours())
                {
                    if(d1.getHDebut()== d2.getHDebut())
                    {
                        return 0;
                    }
                    else
                    {
                      return (d1.getHDebut()>d2.getHDebut());
                    }
                }
                else
                {
                    return (d1.getJours()>d2.getJours());
                }
            }
            else
            {
                return (d1.getMois()>d2.getMois());
            }
        }
        else
        {
            return (d1.getAnnee()>d2.getAnnee());
        }
}

bool operator == (Date const& d1,Date const& d2){
    if((d1.getAnnee() == d2.getAnnee())
       &&(d1.getMois() == d2.getMois())
       &&(d1.getJours() == d2.getJours())
       &&((d1.getHDebut()<d2.getHFin())&&(d2.getHFin()<=d1.getHFin())
       || (d2.getHDebut()<d1.getHFin())&&(d1.getHFin()<= d2.getHFin()) ) ){
            return true;
       }else{
            return false;
       }

}
 bool operator!= (Date const& d1,Date const& d2){
    return !(d1==d2);
 }
ostream& operator<<(ostream& os, const Date& date) {
    os << date.getJours()<<'/'<<date.getMois()<<'/'<<date.getAnnee();
    return os;
}
string Date::toString() const
{
    string a;
    a = to_string(d_jours) + "/" + to_string(d_mois) + "/" + to_string(d_annee);
    return a;
}
