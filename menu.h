#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QWidget>
#include"include/Rdv.h"
#include "rendezvous.h"
#include "persowindow.h"
#include "QBoxLayout"
#include<QDialog>
#include<QLabel>
#include<QIcon>
#include<QPushButton>
class Menu :public QWidget
{
    Q_OBJECT

public slots:
    void addPersonne(const QString& nom, const QString& prenom, const QString& tel, const QString& email);
    void modifierPersonne(int idx,const QString& nom, const QString& prenom, const QString& tel, const QString& email);
    void suprimerPersonne(int idx);
    void addRdv(string nom, string hd, string hf, string date, vector<string> d_prsninRdv);
    void editRdv(int idx,string nom, string hd, string hf, string date, vector<string> d_prsninRdv);
    void deleteRdv(int idx);
public:
    void creeInterface();
    Menu(Rdv *rdv=nullptr,Personnes *prsn=nullptr,QWidget *parent = nullptr);
    void onQuitter();
    void onPersonne();
    void onRdv();
private:
    void onSucces(string str);
    void onError(string str);
    Rdv *d_rdv;
    Personnes *d_personnes;
    persoWindow *d_prsnw;
    RendezVous *d_rdvw;
};

#endif // MENU_H
