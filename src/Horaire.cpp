#include "include/Horaire.h"

Horaire::Horaire(int heure , int minute ): d_heure{heure} , d_minute{minute} {}
Horaire::Horaire():  d_heure{} , d_minute{} {}
int Horaire::getheure()const{ return d_heure ;}
int Horaire::getminute()const{ return d_minute ;}

string Horaire::toString()const{
    string h=to_string(d_heure),m=to_string(d_minute);
    if(d_heure<10){
        h="0"+h;
    }
    if(d_minute<10){
        m="0"+m;
    }
    return h + ":"+ m;
}

bool operator==(Horaire const& h1,Horaire const& h2){
    if(h1.getheure()==h2.getheure()){
        if(h1.getminute()==h2.getminute())
            return 1;
        else
            return 0;
    }else
        return 0;

}

bool operator < (Horaire const& h1,Horaire const& h2){
    if(h1==h2){
        return false;
    }else{
        if(h1.getheure()==h2.getheure()){
            if(h1.getminute()<h2.getminute())
                return 1;
            else
                return 0;
        }else {
            if(h1.getheure()<h2.getheure())
                    return 1;
                else
                    return 0;

        }
    }
}

bool operator > (Horaire const& h1,Horaire const& h2){
    if(h1==h2){
        return false;
    }else{
        if(h1.getheure()==h2.getheure()){
            if(h1.getminute()>h2.getminute())
                return 1;
            else
                return 0;
        }else {
            if(h1.getheure()>h2.getheure())
                    return 1;
                else
                    return 0;

        }
    }
}
bool operator<=(Horaire const& h1,Horaire const& h2){
    if(h1==h2 || h1<h2){
        return true;
    }else{
        return false;
    }


}
