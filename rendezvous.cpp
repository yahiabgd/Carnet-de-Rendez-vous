#include "rendezvous.h"


RendezVous::RendezVous(Rdv* rdvs,Personnes* prsns,QWidget *parent)
    : QWidget(parent),d_rdv{rdvs},d_personnes{prsns},d_prsninRdv{},PersoTable{nullptr}

{
    //d_rdv = new Rdv{rdvs};
    //d_personnes = new Personnes{prsns};
    creerInterface();
}

RendezVous::~RendezVous()
{
}

void RendezVous::creerInterface()
{
    // Création des widgets

    setMinimumSize(650,400);
    //setGeometry(800,170,600,400);

    auto mainLayout = new QVBoxLayout{this};
    d_rdvTable = new QTableWidget(0, 4);
    comboBox = new QComboBox;
    rechercheValue = new QLineEdit;
    auto bajouter = new QPushButton{"Ajouter RDV"};
    auto bmodifier = new QPushButton{"Modifier"};
    auto bsupprimer = new QPushButton{"Supprimer"};
    auto brecherche = new QPushButton{"Rechercher"};
    auto breset = new QPushButton{"Reset"};
    connect(brecherche,&QPushButton::clicked,this,&RendezVous::onRechercher);
    connect(breset,&QPushButton::clicked,this,&RendezVous::onReset);
    // Configuration des widgets
    QStringList labels;
    labels << "Intitulé"  << "Date" << "Horaire"<<"Nombres de personnes";
    d_rdvTable->setHorizontalHeaderLabels(labels);
    d_rdvTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    d_rdvTable->verticalHeader()->hide();
    d_rdvTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    d_rdvTable->setShowGrid(false);
    d_rdvTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    d_rdvTable->setSelectionMode(QAbstractItemView::SingleSelection);
    comboBox->addItem("Date");
    comboBox->addItem("Personne");
    comboBox->addItem("Mois");
    connect(comboBox,&QComboBox::activated,this,&RendezVous::onChangeFiltre);
    rechercheValue->setPlaceholderText("dd-MM-yyyy");

    // Configuration des layouts
    auto buttonLayout = new QHBoxLayout{};
    buttonLayout->addWidget(bajouter, 0, Qt::AlignLeft | Qt::AlignTop);
    buttonLayout->addWidget(bmodifier, 0, Qt::AlignLeft | Qt::AlignTop);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(bsupprimer, 0, Qt::AlignLeft | Qt::AlignTop);

    auto rechercheLayout = new QHBoxLayout{};
    rechercheLayout->addWidget(new QLabel("Filter par :"), 0, Qt::AlignLeft | Qt::AlignTop);
    rechercheLayout->addWidget(comboBox, 0, Qt::AlignLeft | Qt::AlignTop);
    rechercheLayout->addStretch(1);
    rechercheLayout->addWidget(rechercheValue, 0, Qt::AlignRight | Qt::AlignTop);
    rechercheLayout->addWidget(brecherche, 0, Qt::AlignRight | Qt::AlignTop);
    rechercheLayout->addWidget(breset, 0, Qt::AlignRight | Qt::AlignTop);



    mainLayout->addLayout(rechercheLayout);
    mainLayout->addWidget(d_rdvTable);
    //mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    Remplir();


    // Connexions des signaux et des slots
    connect(bajouter, &QPushButton::clicked, this, &RendezVous::onAjouter);
    connect(bmodifier, &QPushButton::clicked, this, &RendezVous::onModifier);
    connect(bsupprimer, &QPushButton::clicked, this, &RendezVous::onSupprimeClicked);

    //STYLE
    setStyleSheet("QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QDateTimeEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox { background-color: white; border: 1px solid #dcdcdc; color: black; border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox::hover { background-color: lightgray; } QComboBox::pressed { background-color: gray; } QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;} QTableWidget {background-color: #f5f5f5;border: 1px solid #d7d7d7;gridline-color: #d7d7d7;} QTableWidget::item {padding: 5px;border: none; text-align: center;} QTableWidget::item:selected {background-color: #b5d5ff;} QHeaderView::section {background-color: #d7d7d7;color: #444444;padding: 5px;border: none;font-weight: bold;} QHeaderView::section:hover {background-color: #b5d5ff;} QScrollBar:vertical {background-color: #f5f5f5border: none;width: 10px;} QScrollBar::handle:vertical {background-color: #d7d7d7;border: none;border-radius: 5px;} QScrollBar::add-line:vertical {height: 0px;}QScrollBar::sub-line:vertical {height: 0px;}");
}

void RendezVous:: onAjouterPerso(){
    int row = PersoTable->rowCount();
    PersoTable->insertRow(row);
    Personne *p = d_personnes->getPersonne(d_prsnCombo->currentText().toStdString());
    PersoTable->setItem(row,0, new QTableWidgetItem(QString::fromStdString(p->d_nom)));
    PersoTable->setItem(row,1, new QTableWidgetItem(QString::fromStdString(p->d_prenom)));
    d_prsninRdv.push_back(p->d_nom);
}
void RendezVous::onSupprimeClicked(){
    QItemSelectionModel *selectionModel = d_rdvTable->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (!selectedRows.isEmpty()) {
        d_rowidx = selectedRows.first().row();
        // Use the rowIndex as needed
    }
    int idx= d_rowidx;
    emit deleteRendezVousSignal(idx);

}

void RendezVous:: onReset(){
    emit onResetSignal();
}

void RendezVous:: onDeletePerso(){
    QItemSelectionModel *selectionModel = PersoTable->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    int idx=0;
    if (!selectedRows.isEmpty()) {
        idx = selectedRows.first().row();
        // Use the rowIndex as needed
    }
    d_prsninRdv.erase(d_prsninRdv.begin()+idx);
    PersoTable->removeRow(idx);
}
void RendezVous::onValiderClicked()
{
    // Get the values from the input fields
    string nom = (nomrdvchamp->text()).toStdString();
    string hd = (hdrdvchamp->text()).toStdString();
    string hf = (hfrdvchamp->text()).toStdString();
    string date = (dateTimeEdit->text()).toStdString();
    // Emit the addPersonneSignal signal with the values
    emit addRendezVousSignal(nom, hd, hf, date,d_prsninRdv);
    AddrdvDialog->close();
    delete AddrdvDialog;
}
void RendezVous::onValiderModifClicked()
{
    string nom = (nomrdvchamp->text()).toStdString();
    string hd = (hdrdvchamp->text()).toStdString();
    string hf = (hfrdvchamp->text()).toStdString();
    string date = (dateTimeEdit->text()).toStdString();
    // Emit the addPersonneSignal signal with the values
    emit editRendezVousSignal(d_rowidx,nom, hd, hf, date,d_prsninRdv);
    AddrdvDialog->close();
    delete AddrdvDialog;
    d_rdvTable->selectRow(d_rowidx);
}
void RendezVous:: onAjouter(){

    d_prsninRdv.clear();

    AddrdvDialog = new QDialog();
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *nomrdvlayout = new QHBoxLayout;
    QHBoxLayout *datelayout = new QHBoxLayout;
    QHBoxLayout *horairelayout = new QHBoxLayout;
    QHBoxLayout *personnelayout = new QHBoxLayout;
    QHBoxLayout *tablelayout = new QHBoxLayout;
    QHBoxLayout *Buttonlayout = new QHBoxLayout;
    vlayout->addLayout(nomrdvlayout);
    vlayout->addLayout(datelayout);
    vlayout->addLayout(horairelayout);
    vlayout->addLayout(personnelayout);
    vlayout->addLayout(tablelayout);
    vlayout->addStretch(1);
    vlayout->addLayout(Buttonlayout);


    nomrdvlayout->addWidget(new QLabel{"Nom de rendez-vous: "},0,Qt::AlignLeft | Qt::AlignTop);
    nomrdvchamp =  new QLineEdit;
    nomrdvchamp->setPlaceholderText("Nom");
    nomrdvlayout->addWidget(nomrdvchamp);

    datelayout->addWidget(new QLabel{"Date : "},0,Qt::AlignLeft | Qt::AlignTop);
    QWidget *window = new QWidget;
    window->setWindowTitle("DateTime Picker Example");
    dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), window);
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setDisplayFormat("dd-MM-yyyy");
    datelayout->addWidget(dateTimeEdit);

    horairelayout->addWidget(new QLabel{"Heure début: "},0,Qt::AlignLeft | Qt::AlignTop);
    hdrdvchamp =  new QLineEdit;
    hdrdvchamp->setPlaceholderText("00:00");
    horairelayout->addWidget(hdrdvchamp);
    horairelayout->addWidget(new QLabel{"Heure fin: "},0,Qt::AlignLeft | Qt::AlignTop);
    hfrdvchamp =  new QLineEdit;
    hfrdvchamp->setPlaceholderText("00:00");
    horairelayout->addWidget(hfrdvchamp);






    personnelayout->addWidget(new QLabel{"personnes : "},0,Qt::AlignLeft | Qt::AlignTop);
    QAbstractButton *bajout = new QPushButton("+");
    QAbstractButton *bsup = new QPushButton("-");


    PersoTable = new QTableWidget(0, 2);
    QStringList labels;
    labels << "Nom"  << "Prénom" ;
    PersoTable->setHorizontalHeaderLabels(labels);
    PersoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    PersoTable->verticalHeader()->hide();
    PersoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    PersoTable->setShowGrid(false);
    tablelayout->addWidget(PersoTable);
    connect(bajout,&QPushButton::clicked,this,&RendezVous::onAjouterPerso);
    connect(bsup,&QPushButton::clicked,this,&RendezVous::onDeletePerso);

    d_prsnCombo = new QComboBox(this);
    Personne *tmp =d_personnes->getTete();
        while(tmp!=nullptr){
            d_prsnCombo->addItem(QString::fromStdString(tmp->d_nom));
            tmp=tmp->d_suiv;
        }
        personnelayout->addWidget(d_prsnCombo,0,Qt::AlignLeft | Qt::AlignTop);
        personnelayout->addStretch(1);
        personnelayout->addWidget(bajout,0,Qt::AlignLeft | Qt::AlignTop);
        personnelayout->addWidget(bsup,0,Qt::AlignLeft | Qt::AlignTop);

    //AddrdvDialog->setFixedSize(300,280);
    QAbstractButton *bExit = new QPushButton("Annuler");
    QAbstractButton *bValider = new QPushButton("valider");

    Buttonlayout->addWidget(bExit);
    Buttonlayout->addWidget(bValider);
    AddrdvDialog->setLayout(vlayout);
    AddrdvDialog->show();
    AddrdvDialog->connect(bExit,SIGNAL(clicked()),AddrdvDialog,SLOT(close()));
    AddrdvDialog->connect(bValider,&QPushButton::clicked,this,&RendezVous::onValiderClicked);

    //STYLE
    AddrdvDialog->setStyleSheet("QDialog {background-color: #f7f7f7;border: 1px solid #dcdcdc;border-radius: 5px;font-family: Arial, sans-serif;} QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QDateTimeEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox { background-color: white; border: 1px solid #dcdcdc; color: black; border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox::hover { background-color: lightgray; } QComboBox::pressed { background-color: gray; } QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;}");
}
// Remplissage de la table
void RendezVous::Remplir()
{
    QAbstractItemModel* model = d_rdvTable->model();
    model->removeRows(0, model->rowCount());
    Appointment* tmp = d_rdv->getTete();

    while (tmp)
    {
        int row = d_rdvTable->rowCount();
        d_rdvTable->insertRow(row);
        d_rdvTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(tmp->d_nom)));
        d_rdvTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tmp->d_date.toString())));
        d_rdvTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tmp->d_date.tostringHoraire())));
        d_rdvTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(tmp->d_personnes.size()))));
        tmp = tmp->d_suiv;
    }
}
void RendezVous::onRechercher()
{
    string r=(rechercheValue->text()).toStdString();
    string c=(comboBox->currentText()).toStdString();
    Rdv* rdv;
    cout<<c<<endl;
    if (c[0] == 'D')
    {
            int jour = std::stoi(r.substr(0, 2));
            int mois = std::stoi(r.substr(3, 5));
            int annee = std::stoi(r.substr(6, 10));
            Date D= Date(Horaire(10,12),Horaire(15,20),jour,mois,annee);
            rdv=d_rdv->afficheRdvDateDonnee(D) ;
            d_rdv = rdv;
            Remplir();
    }
    else if (c[0] == 'P')
    {
            rdv=d_rdv->afficheRdvPersonneDonnee(r) ;
            d_rdv = rdv;
            Remplir();
    }
    else if (c[0] == 'M')
    {
        int jour = std::stoi(r.substr(0, 2));
        int mois = std::stoi(r.substr(0, 2));
        int annee = std::stoi(r.substr(3, 7));
        Date D= Date(Horaire(10,12),Horaire(15,20),jour,mois,annee);
        rdv=d_rdv->afficheRdvMoisDonnee(D) ;
        d_rdv = rdv;
        Remplir();
    }


}
void RendezVous::onModifier(){
    d_prsninRdv.clear();

    QItemSelectionModel *selectionModel = d_rdvTable->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (!selectedRows.isEmpty()) {
        d_rowidx = selectedRows.first().row();
        // Use the rowIndex as needed
    }
    Appointment* a= d_rdv->getRdv(d_rowidx);

    AddrdvDialog = new QDialog();
    AddrdvDialog->setWindowTitle("Modifier un rendez-vous");
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *nomrdvlayout = new QHBoxLayout;
    QHBoxLayout *datelayout = new QHBoxLayout;
    QHBoxLayout *horairelayout = new QHBoxLayout;
    QHBoxLayout *personnelayout = new QHBoxLayout;
    QHBoxLayout *tablelayout = new QHBoxLayout;
    QHBoxLayout *Buttonlayout = new QHBoxLayout;
    vlayout->addLayout(nomrdvlayout);
    vlayout->addLayout(datelayout);
    vlayout->addLayout(horairelayout);
    vlayout->addLayout(personnelayout);
    vlayout->addLayout(tablelayout);
    vlayout->addStretch(1);
    vlayout->addLayout(Buttonlayout);


    nomrdvlayout->addWidget(new QLabel{"Nom de rendez-vous: "},0,Qt::AlignLeft | Qt::AlignTop);
    nomrdvchamp =  new QLineEdit;
    nomrdvlayout->addWidget(nomrdvchamp);

    datelayout->addWidget(new QLabel{"Date : "},0,Qt::AlignLeft | Qt::AlignTop);
    QWidget *window = new QWidget;
    window->setWindowTitle("DateTime Picker Example");
    dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), window);
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setDisplayFormat("dd-MM-yyyy");
    datelayout->addWidget(dateTimeEdit);

    horairelayout->addWidget(new QLabel{"Heure début: "},0,Qt::AlignLeft | Qt::AlignTop);
    hdrdvchamp =  new QLineEdit;
    horairelayout->addWidget(hdrdvchamp);
    horairelayout->addWidget(new QLabel{"Heure fin: "},0,Qt::AlignLeft | Qt::AlignTop);
    hfrdvchamp =  new QLineEdit;
    horairelayout->addWidget(hfrdvchamp);

    QString timeString =QString::fromStdString(a->d_date.toString());
    QTime time = QTime::fromString(timeString, "dd:MM:yyyy");
    dateTimeEdit->setTime(time);
    hdrdvchamp->setText(QString::fromStdString(a->d_date.tostringHDebut()));
    hfrdvchamp->setText(QString::fromStdString(a->d_date.tostringHFin()));
    nomrdvchamp->setText(QString::fromStdString(a->d_nom));
    d_prsninRdv=a->d_personnes;






    personnelayout->addWidget(new QLabel{"personnes : "},0,Qt::AlignLeft | Qt::AlignTop);
    QAbstractButton *bajout = new QPushButton("+");
    QAbstractButton *bsup = new QPushButton("-");


    PersoTable = new QTableWidget(0, 2);
    QStringList labels;
    labels << "Nom"  << "Prénom" ;
    PersoTable->setHorizontalHeaderLabels(labels);
    PersoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    PersoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    PersoTable->verticalHeader()->hide();
    PersoTable->setShowGrid(false);
    tablelayout->addWidget(PersoTable);
    connect(bajout,&QPushButton::clicked,this,&RendezVous::onAjouterPerso);
    connect(bsup,&QPushButton::clicked,this,&RendezVous::onDeletePerso);
    d_prsnCombo = new QComboBox(this);
    Personne *tmp =d_personnes->getTete();
        while(tmp!=nullptr){
            d_prsnCombo->addItem(QString::fromStdString(tmp->d_nom));
            tmp=tmp->d_suiv;
        }
        personnelayout->addWidget(d_prsnCombo,0,Qt::AlignLeft | Qt::AlignTop);
        personnelayout->addStretch(1);
        personnelayout->addWidget(bajout,0,Qt::AlignLeft | Qt::AlignTop);
        personnelayout->addWidget(bsup,0,Qt::AlignLeft | Qt::AlignTop);

    //AddrdvDialog->setFixedSize(300,280);
    QAbstractButton *bExit = new QPushButton("Annuler");
    QAbstractButton *bValider = new QPushButton("valider");


    //remplir la table des personnes présent
    for(int i =0 ;i<d_prsninRdv.size();i++){
        int row = PersoTable->rowCount();
        PersoTable->insertRow(row);
        Personne *p = d_personnes->getPersonne(d_prsninRdv[i]);
        PersoTable->setItem(row,0, new QTableWidgetItem(QString::fromStdString(p->d_nom)));
        PersoTable->setItem(row,1, new QTableWidgetItem(QString::fromStdString(p->d_prenom)));
    }

    Buttonlayout->addWidget(bExit);
    Buttonlayout->addWidget(bValider);
    AddrdvDialog->setLayout(vlayout);
    AddrdvDialog->show();
    AddrdvDialog->connect(bExit,SIGNAL(clicked()),AddrdvDialog,SLOT(close()));
    AddrdvDialog->connect(bValider,&QPushButton::clicked,this,&RendezVous::onValiderModifClicked);

    //STYLE
    AddrdvDialog->setStyleSheet("QDialog {background-color: #f7f7f7;border: 1px solid #dcdcdc;border-radius: 5px;font-family: Arial, sans-serif;} QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QDateTimeEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox { background-color: white; border: 1px solid #dcdcdc; color: black; border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox::hover { background-color: lightgray; } QComboBox::pressed { background-color: gray; } QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;}");



}

void RendezVous:: onSucces(string str){
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

    // connect the "OK" button to close the dialog
    connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // show the dialog
    dialog->exec();

    // clean up the dialog
    delete dialog;
}
void RendezVous:: onError(string str){
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

    // connect the "OK" button to close the dialog
    connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // show the dialog
    dialog->exec();

    // clean up the dialog
    delete dialog;
}

void RendezVous::onChangeFiltre(){
    string c = (comboBox->currentText()).toStdString();
    if(c[0]=='D'  ){
        rechercheValue->setPlaceholderText("dd-MM-yyyy");
        return;
    }
    if(c[0]=='M'){
        rechercheValue->setPlaceholderText("MM-yyyy");
        return;
    }
    if(c[0]== 'P'){
        rechercheValue->setPlaceholderText("Nom");
    }

}
