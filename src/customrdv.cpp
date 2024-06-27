#include "customrdv.h"

customrdv::customrdv(QString name,QString date,QString horaire,QString pnb):Name{name},Date{date},Horaire{horaire},Pnb{pnb}
{
}
QString customrdv::getName() const
{
    return Name;
}
QString customrdv::getDate() const
{
    return Date;
}
QString customrdv::getHoraire() const
{
    return Horaire;
}
QString customrdv::getPnb() const
{
    return Pnb;
}
