#include "include/Personne.h"
Personne::Personne():
    d_nom{" "},
    d_prenom{" "},
    d_telephone{" " },
    d_email{" "},
    d_suiv{nullptr}
    {

    }

Personne::Personne(string nom,string prenom,string telephone,string email):
    d_nom{nom},
    d_prenom{prenom},
    d_telephone{telephone},
    d_email{email},
    d_suiv{nullptr}
{

}

string Personne::getnom()const{
    return d_nom;
}
Personne* Personne::getsuiv()const{
    return d_suiv;
}
