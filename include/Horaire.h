#ifndef HORAIRE_H
#define HORAIRE_H
#include<string>
using namespace std;



class Horaire
{
    public:
        Horaire(int heure , int minute );
        Horaire();
        int getheure() const;
        int getminute()const;
        string toString()const;

    private:
        int d_heure ;
        int d_minute ;

};
bool operator==(Horaire const& h1,Horaire const& h2);
bool operator<(Horaire const& h1,Horaire const& h2);
bool operator<=(Horaire const& h1,Horaire const& h2);
bool operator>(Horaire const& h1,Horaire const& h2);
#endif // HORAIRE_H
