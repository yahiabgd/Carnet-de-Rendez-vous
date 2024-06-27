#ifndef PERSONNES_H_INCLUDED
#define PERSONNES_H_INCLUDED
#include<string>
#include"Personne.h"
using namespace std;

class Personnes{
    friend class Rdv;
    friend class persoWindow;
    public:
        Personnes();
        Personnes(const Personnes *p);
        Personne* getTete()const;
        void vider();
        void addPersonne(Personne *p);
        void deletePersonne(string nom);
        void deletePersonne(int idx);
        void modifierTel(string nom, string tel);
        void modifierEmail(string nom, string Email);
        Personne* getPersonne(string nom)const;
        Personne* getPersonne(int idx)const;
        void modifierPersonne(int idx,string nom, string prenom,string tel,string Email);
        int nombrePersonne()const;
        void afficheListe()const;
    private:
        Personne* d_tete;
};


#endif // PERSONNES_H_INCLUDED
