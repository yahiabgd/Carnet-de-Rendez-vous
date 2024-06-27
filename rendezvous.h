#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H
#include<QComboBox>
#include "include/Rdv.h"
#include <QWidget>
#include <QTableWidget>
#include "include/personnes.h"
#include<QBoxLayout>
#include<QPushButton>
#include<QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include "src/customrdv.h"
#include<QDialog>
#include<QLineEdit>
#include<QCalendarWidget>
#include<QDate>
#include<QDateTimeEdit>
#include<iostream>
class RendezVous : public QWidget
{
    Q_OBJECT

public:
    RendezVous(Rdv* rdvs,Personnes* prsns,QWidget *parent = nullptr);
    void creerInterface();
    ~RendezVous();
    void onAjouterPerso();
    void onDeletePerso();
    void onValiderClicked();
    void onValiderModifClicked();
    void onSupprimeClicked();
    void Remplir();
    void onRechercher();
signals:
    void onResetSignal();
    void deleteRendezVousSignal(int idx);
    void editRendezVousSignal(int d_rowidx,string nom, string hd, string hf, string date, vector<string> d_prsninRdv);
    void addRendezVousSignal(string nom, string hd, string hf, string date, vector<string> d_prsninRdv);
private:
    void onSucces(string str);
    void onError(string str);
    QDialog *AddrdvDialog;
    QComboBox *d_prsnCombo ;
    QComboBox *comboBox;
    QLineEdit *rechercheValue;
    QDateTimeEdit *dateTimeEdit;
    QLineEdit* nomrdvchamp;
    QLineEdit* hdrdvchamp;
    QLineEdit* hfrdvchamp;
    QTableWidget *PersoTable;
    QTableWidget *d_rdvTable;
    Rdv *d_rdv;
    int d_rowidx;
    vector<string> d_prsninRdv;
    Personnes* d_personnes;
    void onAjouter();
    void onModifier();
    void onReset();
signals:
    void deletePersonneSignal(int idx);
private slots:
    void onChangeFiltre();

};
#endif // RENDEZVOUS_H
