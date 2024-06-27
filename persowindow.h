#ifndef PERSOWINDOW_H
#define PERSOWINDOW_H
#include <QWidget>
#include<QBoxLayout>
#include<QPushButton>
#include<QComboBox>
#include<QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include<QDialog>
#include<QLineEdit>
#include <QStandardItemModel>
#include "include/personnes.h"


class persoWindow : public QWidget
{
    Q_OBJECT
public:
    persoWindow(Personnes* prsns, QWidget *parent = nullptr);
    void creeInterface();
    void onAjouter();
    void onModifier();
signals:
    void addPersonneSignal(const QString& nom, const QString& prenom, const QString& tel, const QString& email);
    void modifierPersonneSignal(int idx,const QString& nom, const QString& prenom, const QString& tel, const QString& email);
    void deletePersonneSignal(int idx);
private slots:
    void onValiderClicked();
    void onModifierClicked();
    void onSupprimeClicked();
private:

    Personnes *d_personnes;
    QLineEdit *nomchamp;
    QLineEdit *prénomchamp;
    QLineEdit *telchamp;
    QLineEdit *emailchamp;
    QDialog *Addpersonne;
    QDialog *Modifierpersonne;
    int d_rowidx;
    QTableWidget* filesTable;
    QComboBox* d_prsn;
};


#endif // PERSOWINDOW_H
