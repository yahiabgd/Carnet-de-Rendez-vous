#include"include/personnes.h"
#include<iostream>
using namespace std;

Personnes::Personnes():
    d_tete{nullptr}
    {}
Personnes::Personnes(const Personnes *p)
{
    Personne *tmp = p->d_tete,*prec;
    d_tete= new Personne(*tmp);
    prec = d_tete;
    tmp = tmp->d_suiv;
    while(tmp!=nullptr){
        Personne *newPersonne = new Personne(*tmp);
        prec->d_suiv=newPersonne;
        //newPersonnes->addPersonne(newPersonne);
        tmp=tmp->d_suiv;
        prec=newPersonne;
    }
    //d_tete=newPersonnes->getTete();
}
Personne* Personnes::getTete()const{
    return d_tete;
}

void Personnes::vider(){
    Personne *tmp = d_tete;
    while(d_tete!= nullptr){
        d_tete=d_tete->d_suiv;
        delete tmp;
        tmp=d_tete;
    }
}


void Personnes::addPersonne(Personne *p){
    Personne* q;
    Personne* pre;
    pre=d_tete;
    q=d_tete;
    while( q != nullptr && q->d_nom < p->d_nom){
        pre=q;
        q=q->d_suiv;
    }
    if(d_tete==q){
        p->d_suiv=d_tete;
        d_tete=p;
    }else{
        p->d_suiv=q;
        pre->d_suiv=p;
    }

}

void Personnes::deletePersonne(string nom){
    Personne* c= d_tete , *prec = nullptr ;
    while (c != nullptr && c->d_nom != nom){
        prec = c ;
        c = c->d_suiv ;
    }
    if (c == d_tete){
        c=c->d_suiv;
        delete d_tete;
        d_tete=c;
        return;
    }
    if (c!=nullptr){
        Personne* next = c->d_suiv ;
        delete c ;
        prec->d_suiv = next ;

    }

}

void Personnes::deletePersonne(int idx){

    Personne* c = d_tete, *prec = nullptr;
    while (c != nullptr && c != getPersonne(idx)){
        prec = c;
        c = c->d_suiv;
    }

    if (c == d_tete){
        c = c->d_suiv;
        delete d_tete;
        d_tete = c;
        return;
    }
    if (c != nullptr){
        Personne* next = c->d_suiv;
        delete c;
        prec->d_suiv = next;
    }

}



void Personnes::modifierTel(string nom, string tel){
    Personne* c= d_tete ;
    while (c != nullptr && c->d_nom != nom){
        c = c->d_suiv ;
    }
    if (c!=nullptr){
        c->d_telephone = tel ;
    }
    else
        return ;
}

void Personnes::modifierEmail(string nom, string Email){
    Personne* c= d_tete ;
    while (c != nullptr && c->d_nom != nom){
        c = c->d_suiv ;
    }
    if (c!=nullptr){
        c->d_email = Email ;
    }
    else
        return ;
}
void Personnes::afficheListe()const{
    Personne *tmp =d_tete;
    while(tmp!=nullptr){
        cout<<tmp->d_nom<<" -> ";
        tmp=tmp->d_suiv;
    }
    cout<<"nullptr"<<endl;
}

int Personnes::nombrePersonne()const{
    Personne *tmp=d_tete;
    int nb=0;
    while(tmp!=nullptr){
        nb++;
        tmp=tmp->d_suiv;
    }
    return nb;
}
Personne* Personnes::getPersonne(string nom)const{
    Personne *tmp = d_tete;
    while(tmp!=nullptr && tmp->d_nom != nom){
        tmp=tmp->d_suiv;
    }
    return tmp;
}
Personne* Personnes::getPersonne(int idx)const{
    Personne *tmp = d_tete;
    int tmpidx=0;
    while(tmp!=nullptr && tmpidx != idx){
        tmp=tmp->d_suiv;
        tmpidx++;
    }
    return tmp;
}
void Personnes::modifierPersonne(int idx,string nom, string prenom,string tel,string Email)
{
    Personne *p = getPersonne(idx);
    p->d_email=Email;
    p->d_nom=nom;
    p->d_prenom=prenom;
    p->d_telephone=tel;
}
