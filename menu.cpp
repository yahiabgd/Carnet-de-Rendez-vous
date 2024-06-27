#include "menu.h"

Menu::Menu(Rdv *rdv,Personnes *prsn,QWidget *parent)
    : QWidget(parent),d_rdv{rdv},d_personnes{prsn},d_prsnw{nullptr},d_rdvw{nullptr}
{
  creeInterface();
}

void Menu::creeInterface(){
    auto LayoutP = new QVBoxLayout {this};
    setMinimumSize(350,300);
    auto LabelMenu = new QLabel{"Carnet Rendez-Vous"};
    LabelMenu->setStyleSheet("font-size:25px");
    auto bRendezVous = new QPushButton("Rendez Vous");
    auto bPersonnes = new QPushButton("Personnes");
    auto bQuitter = new QPushButton("Quitter");
    connect(bQuitter,QPushButton::clicked,this,&Menu::onQuitter);
    connect(bRendezVous,QPushButton::clicked,this,&Menu::onRdv);
    connect(bPersonnes,QPushButton::clicked,this,&Menu::onPersonne);
    bRendezVous->setMinimumSize(200,50);
    bPersonnes->setMinimumSize(200,50);
    bQuitter->setMinimumSize(200,50);
    LayoutP->addWidget(LabelMenu,0,Qt::AlignHCenter |Qt::AlignTop);
    LayoutP->addWidget(bRendezVous,0,Qt::AlignHCenter |Qt::AlignTop);
    LayoutP->addWidget(bPersonnes,0,Qt::AlignHCenter|Qt::AlignTop);
    LayoutP->addWidget(bQuitter,0,Qt::AlignHCenter|Qt::AlignTop);



    //STYLE
    setStyleSheet("QPushButton {"
                   "background-color: #0088cc; /* Couleur de fond */"
                   "color: white; /* Couleur de texte */"
                   "font-size: 16px; /* Taille de la police */"
                   "padding: 8px 16px; /* Remplissage du bouton */"
                   "border-radius: 4px; /* Rayon des coins */"
                   "border: none; /* Pas de bordure */    }"

               "QPushButton:hover {"
                   "background-color: #006699; /* Couleur de fond lors du survol */}"

               "QPushButton:pressed {"
                   "background-color: #2e6735; /* Couleur de fond lors du clic */"
               "}");




}


void Menu::onQuitter(){
    close();
}

void  Menu::onPersonne(){
    if(d_personnes ==nullptr)
    {
        d_personnes = new Personnes{};
    }
    if(d_prsnw!= nullptr)
        d_prsnw->close();
    d_prsnw =  new persoWindow(d_personnes) ;
    d_prsnw->show();
    connect(d_prsnw, &persoWindow::addPersonneSignal, this, &Menu::addPersonne);
    connect(d_prsnw, &persoWindow::modifierPersonneSignal, this, &Menu::modifierPersonne);
    connect(d_prsnw, &persoWindow::deletePersonneSignal, this, &Menu::suprimerPersonne);

}

void  Menu::onRdv(){
    if(d_rdv ==nullptr)
    {
        d_rdv = new Rdv{};
    }
    if(d_rdvw!= nullptr)
        d_rdvw->close();
    d_rdvw =  new RendezVous(d_rdv,d_personnes);
    connect(d_rdvw, &RendezVous::addRendezVousSignal, this, &Menu::addRdv);
    connect(d_rdvw, &RendezVous::editRendezVousSignal, this, &Menu::editRdv);
    connect(d_rdvw, &RendezVous::deleteRendezVousSignal, this, &Menu::deleteRdv);
    connect(d_rdvw, &RendezVous::onResetSignal, this, &Menu::onRdv);
    d_rdvw->show();

}
void Menu::addPersonne(const QString& nom, const QString& prenom, const QString& tel, const QString& email)
{
    std::string nomStr = nom.toStdString();
    std::string prenomStr = prenom.toStdString();
    std::string emailStr = email.toStdString();
    std::string telStr = tel.toStdString();
    Personne *Prsn = new Personne(nomStr,prenomStr,telStr,emailStr);
    d_personnes->addPersonne(Prsn);
    onSucces("La personne est ajouté");
    onPersonne();
}
void Menu::addRdv(string nom, string hd, string hf, string date, vector<string> d_prsninRdv)
{
    int jour = std::stoi(date.substr(0, 2));
    int mois = std::stoi(date.substr(3, 5));
    int annee = std::stoi(date.substr(6, 10));

    int dh  = std::stoi(hd.substr(0, 2));
    int dmin= std::stoi(hd.substr(3, 5));
    int fh= std::stoi(hf.substr(0, 2));
    int fmin= std::stoi(hf.substr(3, 5));

    Date d= Date(Horaire(dh,dmin),Horaire(fh,fmin),jour,mois,annee);

    Appointment* app = new Appointment(nom,d,d_prsninRdv);
    if(d_rdv->personnesLibre(app)){
        d_rdv->addRdv(app);
        onSucces("Le rendez-vous est ajouté");
    }else{
        onError("il y a des personnes occupé");
    }

    onRdv();
}
void Menu::editRdv(int idx,string nom, string hd, string hf, string date, vector<string> d_prsninRdv)
{
    int jour = std::stoi(date.substr(0, 2));
    int mois = std::stoi(date.substr(3, 5));
    int annee = std::stoi(date.substr(6, 10));

    int dh  = std::stoi(hd.substr(0, 2));
    int dmin= std::stoi(hd.substr(3, 5));
    int fh= std::stoi(hf.substr(0, 2));
    int fmin= std::stoi(hf.substr(3, 5));

    Date d= Date(Horaire(dh,dmin),Horaire(fh,fmin),jour,mois,annee);

    Appointment* app = d_rdv->getRdv(idx);
    app->d_date=d;
    app->d_nom=nom;
    app->d_personnes=d_prsninRdv;
    onSucces("Le rendez-vous est modifié");
    onRdv();
}
void Menu::modifierPersonne(int idx,const QString& nom, const QString& prenom, const QString& tel, const QString& email)
{
    std::string nomStr = nom.toStdString();
    std::string prenomStr = prenom.toStdString();
    std::string emailStr = email.toStdString();
    std::string telStr = tel.toStdString();
    d_personnes->modifierPersonne(idx,nomStr,prenomStr,telStr,emailStr);
    onSucces("La personne est modifié");
    onPersonne();
}
void Menu::suprimerPersonne(int idx)
{
    d_personnes->deletePersonne(idx);
    onSucces("La personne est supprimé");
    onPersonne();
}
void Menu::deleteRdv(int idx)
{
    d_rdv->deleteRdv(idx);
    onSucces("Le rendez-vous est supprimé");
    onRdv();
}

void Menu:: onSucces(string str){
    QDialog* dialog = new QDialog{};

    // set the dialog title
    dialog->setWindowTitle("Success");

    // create a label for the message
    QLabel* label = new QLabel(dialog);
    label->setText(QString::fromStdString(str));

    // create an "OK" button
    QPushButton* okButton = new QPushButton(dialog);
    okButton->setText("OK");

    // create a vertical layout for the dialog
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);
    layout->addWidget(okButton);
    label->setStyleSheet("QLabel {"
                           "font-size: 18px;"
                           "}");
    okButton->setStyleSheet("QDialog {background-color: #f7f7f7;border: 1px solid #dcdcdc;border-radius: 5px;font-family: Arial, sans-serif;} QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QDateTimeEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox { background-color: white; border: 1px solid #dcdcdc; color: black; border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox::hover { background-color: lightgray; } QComboBox::pressed { background-color: gray; } QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;}");
    // connect the "OK" button to close the dialog
    connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // show the dialog
    dialog->exec();

    // clean up the dialog
    delete dialog;
}
void Menu:: onError(string str){
    QDialog* dialog = new QDialog{};

    // set the dialog title
    dialog->setWindowTitle("Erreur");

    // create a label for the message
    QLabel* label = new QLabel(dialog);
    label->setText(QString::fromStdString(str));

    // create an "OK" button
    QPushButton* okButton = new QPushButton(dialog);
    okButton->setText("OK");

    // create a vertical layout for the dialog
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);
    layout->addWidget(okButton);
    label->setStyleSheet("QLabel {"
                           "font-size: 18px;"
                           "}");
    okButton->setStyleSheet("QDialog {background-color: #f7f7f7;border: 1px solid #dcdcdc;border-radius: 5px;font-family: Arial, sans-serif;} QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QDateTimeEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox { background-color: white; border: 1px solid #dcdcdc; color: black; border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox::hover { background-color: lightgray; } QComboBox::pressed { background-color: gray; } QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;}");

    // connect the "OK" button to close the dialog
    connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // show the dialog
    dialog->exec();

    // clean up the dialog
    delete dialog;
}
