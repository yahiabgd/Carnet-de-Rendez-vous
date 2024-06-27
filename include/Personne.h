#ifndef PERSONNE_H
#define PERSONNE_H
#include<string>
using namespace std;

class Personne
{
    friend class Personnes;
    friend class Rdv;
    friend class persoWindow;
    friend class RendezVous;
    public:
        Personne();
        Personne(string nom,string prenom,string telephone,string email);
        string getnom()const;
        Personne* getsuiv()const;
        /////
        /*
        void setTel(string tel);
        void setEmail(string email);*/
    private:
        string d_nom,d_prenom,d_telephone,d_email;
        Personne* d_suiv;
};

#endif // PERSONNE_H
