#include "include/Rdv.h"
#include"include/personnes.h"
#include<iostream>
using namespace std;

Rdv::Rdv():
    d_tete{nullptr}
    {}

Rdv::~Rdv(){
    Appointment *tmp = d_tete;
    while(d_tete!=nullptr){
        d_tete=d_tete->d_suiv;
        delete tmp;
        tmp=d_tete;
    }
}

Rdv::Rdv(const Rdv *r)
{
    Appointment *tmp = r->d_tete,*prec;
    d_tete = new Appointment(*tmp);
    prec=d_tete;
    tmp = tmp->d_suiv;
    while(tmp!=nullptr){
        Appointment *newApp = new Appointment(*tmp);
        prec->d_suiv=newApp;
        newApp->d_prec=prec;
        //newRdv->addRdv(newApp);
        prec=newApp;
        tmp=tmp->d_suiv;
    }

}
Appointment* Rdv :: getTete()const{
    return d_tete;
}
bool Rdv::personneLibre(string nom, Date date)const{
    Appointment *tmp = d_tete;
    while(tmp != nullptr && tmp->d_date!= date){
        tmp=tmp->d_suiv;
    }
    if(tmp == nullptr){
        cout<<"persone libre ///////"<< endl;
        return true;
    }

    while (tmp!= nullptr && tmp->d_date == date ){
        if(tmp->estPresent(nom)){
            cout<<"persone pas libre ///////"<<endl;
            return false;
        }
        tmp=tmp->d_suiv;
    }
    cout<<"persone libre ///////"<<endl;
    return true;
}
bool Rdv::personnesLibre(Appointment *a)const{
    Appointment *tmp = d_tete;
    while(tmp != nullptr && tmp->d_date!= a->d_date){
        tmp=tmp->d_suiv;
    }
    if(tmp == nullptr){
        cout <<"personnes libre \n";
        return true;
    }
    //Personne* pers = a->d_personnes->d_tete;
    while (tmp!= nullptr && tmp->d_date == a->d_date ){
        int i =0;
        while(i<a->d_personnes.size()){
            if(tmp->estPresent(a->d_personnes[i])){
                cout <<"personnes pas libre \n";
                return false;
            }
            //pers=pers->d_suiv;
            i++;
        }
        //pers = a->d_personnes->d_tete;
        tmp=tmp->d_suiv;
    }
    cout <<"personnes libre \n";
    return true;
}

void Rdv ::addRdv(Appointment* rdv){
    cout<<"add rendez vous \n";
    if(!personnesLibre(rdv)){
        return; //on peut pas ajouter un rendez-vous
    }
    if(d_tete==nullptr){
        d_tete = rdv;
        return;
    }
    Appointment *prec =nullptr, *cur=d_tete;
    while(cur!=nullptr && cur->d_date < rdv->d_date){
        prec=cur;
        cur=cur->d_suiv;
    }
    if(prec == nullptr){
        rdv->d_suiv=d_tete;
        d_tete->d_prec=rdv;
        d_tete=rdv;
        return;
    }
    if (cur != nullptr){
        rdv->d_suiv=cur;
        cur->d_prec= rdv;
    }
    prec->d_suiv=rdv;
    rdv->d_prec=prec;

}
void Rdv::deleteRdv(string nom){
    Appointment * prec =nullptr,*cur=d_tete;
    if(d_tete==nullptr)
        return;
    while(cur != nullptr && cur->d_nom != nom){
        prec=cur;
        cur=cur->d_suiv;
    }
    if(cur == nullptr)
        return;
    if(prec ==nullptr){
        Appointment*ele =d_tete;
        if (d_tete->d_suiv!=nullptr){
            d_tete=d_tete->d_suiv;
            d_tete->d_prec=nullptr;
        }else{
            d_tete=nullptr;
        }
        delete ele;

    }

}
void Rdv::deleteRdv(int idx){
    Appointment * prec =nullptr,*cur=d_tete;
    if(d_tete==nullptr)
        return;
    int i=0;
    while(cur != nullptr && i != idx){
        prec=cur;
        cur=cur->d_suiv;
        i++;
    }
    if(cur == nullptr)
        return;
    if(prec ==nullptr){
        Appointment*ele =d_tete;
        if (d_tete->d_suiv!=nullptr){
            d_tete=d_tete->d_suiv;
            d_tete->d_prec=nullptr;
        }else{
            d_tete=nullptr;
        }
        delete ele;

    }

}

void Rdv::affiche()const{
    Appointment * tmp =d_tete;
    cout << "affiche Rendez vous :  \n";
    if (tmp==nullptr){
        cout<<"Vide";
        return;
    }
    while (tmp != nullptr){
        cout << tmp->d_nom <<" | "<<tmp->d_date<<endl;
        tmp->affichepersonnes();
        tmp=tmp->d_suiv;
    }
}

Appointment* Rdv::getRdv(string nom){
    Appointment *tmp = d_tete;
    while(tmp != nullptr && tmp->d_nom != nom){
        tmp=tmp->d_suiv;
    }
    return tmp;
}
Appointment* Rdv::getRdv(int idx){
    Appointment *tmp = d_tete;
    int i = 0;
    while(tmp != nullptr && i<idx){
        tmp=tmp->d_suiv;
        i++;
    }
    return tmp;

}

void Rdv::ajouterPersonne(string nom_rdv,string nom_per){
    Appointment* tmp = getRdv(nom_rdv);
    if (tmp == nullptr){
        return;
    }
    if(personneLibre(nom_per,tmp->d_date)){
        tmp->d_personnes.push_back(nom_per);
    }
}

Rdv* Rdv::afficheRdvDateDonnee(const Date& date){
    Rdv* listeRdv = new Rdv();
    Appointment *tmp =d_tete;
    while(tmp!=nullptr && (!date.sameDay(tmp->d_date))){

        tmp=tmp->d_suiv;
    }
    while(tmp!=nullptr && date.sameDay(tmp->d_date)){
        Appointment* ele = new Appointment(*tmp);
        listeRdv->addRdv(ele);
        tmp=tmp->d_suiv;
    }
    return listeRdv;
}


Rdv* Rdv:: afficheRdvPersonneDonnee(const string nom){
    Rdv* listeRdv = new Rdv();
    Appointment *tmp =d_tete;
    while(tmp!=nullptr){
        if(tmp->estPresent(nom)){
            Appointment* ele = new Appointment(*tmp);
            listeRdv->addRdv(ele);
        }
        tmp=tmp->d_suiv;
    }
    return listeRdv;
}

Rdv* Rdv::afficheRdvMoisDonnee(const Date& date){
    Rdv* listeRdv = new Rdv();
    Appointment *tmp =d_tete;
    while(tmp!=nullptr && (!date.sameMonth(tmp->d_date))){
        tmp=tmp->d_suiv;
    }
    while(tmp!=nullptr && date.sameMonth(tmp->d_date)){
        Appointment* ele = new Appointment(*tmp);
        listeRdv->addRdv(ele);
        tmp=tmp->d_suiv;
    }
    return listeRdv;
}






