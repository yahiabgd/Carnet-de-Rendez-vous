#ifndef CUSTOMRDV_H
#define CUSTOMRDV_H
#include <QString>

class customrdv
{
public:
    customrdv(QString name,QString date,QString horaire,QString pnb);
    QString getName() const;
    QString getDate() const;
    QString getHoraire() const;
    QString getPnb() const;
private:
    QString Name;
    QString Date;
    QString Horaire;
    QString Pnb;
};

#endif // CUSTOMRDV_H
