#include "rendezvous.h"
#include"menu.h"
#include <iostream>
#include"include/personnes.h"
#include"include/Personne.h"
#include"include/Rdv.h"
#include"include/Appointment.h"
#include"include/Date.h"
#include"include/Horaire.h"

#include <QApplication>

using namespace std;

Personnes* creerListePer(string name){
    Personnes* ListP =new Personnes();
    string nom,prenom,telephone,email;
    Personne *p;
    for(int i=4 ;i>=0;i--){
        nom=name+std::to_string(i);
        email="yahia.chiah@uha.fr";
        prenom="yahia";
        telephone="0654814888";
        Personne *p= new Personne(nom,prenom,telephone,email);
        ListP->addPersonne(p);
    }
    email="yahia.chiah@uha.fr";
    prenom="yahia";
    telephone="0654814888";
    nom=name+"15";
    p = new Personne(nom,prenom,telephone,email);
    ListP->addPersonne(p);
    //ListP->vider();
    return ListP;
}

vector<string> creerListeNom(string name){
    vector<string> pers;
    for (int i =0 ; i<5 ; i++){
        pers.push_back(name+std::to_string(i));
    }
    return pers;
}


void testListPer(){
    Personnes* ListP =creerListePer("chiah");
    ListP->afficheListe();
}
void testDate(){
    Date d1 =Date(Horaire(10,06),Horaire(12,20),30,03,2023);
    Date d2 =Date(Horaire(10,15),Horaire(12,20),30,01,2023);
    cout<<(d2==d1)<<endl;
    cout<<(d2<d1)<<endl;
    //cout<<"same = "<<(d1.sameDay(d2));
}
/*
Rdv* testRdv(){
    Rdv *r = new Rdv();

    vector<string> ListP =creerListeNom("Golli");
    Date d1 =Date(Horaire(10,06),Horaire(12,20),30,03,2023);
    Appointment *a = new Appointment("cours sport",d1,ListP);
    r->addRdv(a);

    d1 =Date(Horaire(10,06),Horaire(12,20),30,04,2023);
    ListP =  creerListeNom("chiah");
    a = new Appointment("cours foot",d1,ListP);
    r->addRdv(a);

    d1 =Date(Horaire(10,15),Horaire(12,20),30,03,2023);
    ListP =  creerListeNom("anis");
    a = new Appointment("cours anglais",d1,ListP);
    r->addRdv(a);


    d1 =Date(Horaire(10,16),Horaire(12,21),30,3,2023);
    a = new Appointment("cours new",d1,ListP);
    r->addRdv(a);
    r->affiche();
    r->ajouterPersonne("cours foot","anis");

    Rdv rDate = r->afficheRdvPersonneDonnee("anis");

    r->affiche();
    cout<<"=========================="<<endl;
    rDate.affiche();
    cout<< "fin";

    return r;
}
*/
int main(int argc, char *argv[])
{
    Rdv *r = new Rdv();
    Personnes* p = new Personnes();
    p->addPersonne(new Personne("chiah","yahia","0783305020","yahia.chiah@uha.fr"));
    p->addPersonne(new Personne("golli","rami","0783305020","rami.golli@uha.fr"));
    p->addPersonne(new Personne("reghis","sonia","0783305020","sonia.reghis@uha.fr"));
    p->addPersonne(new Personne("zeghlouche","anis","0783305020","anis.zeghlouche@uha.fr"));
    p->addPersonne(new Personne("ben","mizda","0783305020","yahia.ben@uha.fr"));
    //testDate();
    QApplication a(argc, argv);

    Menu w{r,p};
    w.show();
    return a.exec();

}
