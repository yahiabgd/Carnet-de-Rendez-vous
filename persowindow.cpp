#include "persowindow.h"
#include "src/customrdv.h"
#include "menu.h"
#include <iostream>


persoWindow::persoWindow(Personnes* prsns, QWidget *parent)
    : QWidget{parent}, d_personnes{nullptr}
{
    d_personnes = new Personnes(prsns);
    creeInterface();
}


void persoWindow::creeInterface(){
    //setGeometry(100,170,350,250);
    setMinimumSize(550,350);
    auto mainLayout = new QVBoxLayout{this};
    auto buttonLayout = new QHBoxLayout{};
    auto bajouter = new QPushButton{"Ajouter Personne"};
    connect(bajouter,QPushButton::clicked,this,&persoWindow::onAjouter);
    auto bmodifier = new QPushButton{"Modifier"};
    connect(bmodifier,QPushButton::clicked,this,&persoWindow::onModifier);
    auto bsupprimer = new QPushButton{"supprimer"};
    connect(bsupprimer,QPushButton::clicked,this,&persoWindow::onSupprimeClicked);


    filesTable = new QTableWidget(0, 4);
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    d_rowidx = 0;
    QList<QString> Name;
    QList<QString> Prenom;
    QList<QString> tel;
    QList<QString> email;
    QStringList labels;
    labels << "Nom"  << "Prenom" <<"Email"<< "Téléphone";
    QHeaderView* header = filesTable->horizontalHeader();
    filesTable->setHorizontalHeaderLabels(labels);
    header->setSectionResizeMode(QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    filesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    filesTable->setShowGrid(false);
    filesTable->resizeColumnsToContents();
    filesTable->resizeRowsToContents();
    int row = filesTable->rowCount();
    Personne* tmp = d_personnes->getTete();
    while (tmp)
    {
        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(tmp->d_nom)));
        filesTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tmp->d_prenom)));
        filesTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tmp->d_email)));
        filesTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(tmp->d_telephone)));
        tmp = tmp->d_suiv;
    }

    mainLayout->addWidget(filesTable);
   // mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(bajouter,0,Qt::AlignLeft |Qt::AlignTop);
    buttonLayout->addWidget(bmodifier,0,Qt::AlignLeft |Qt::AlignTop);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(bsupprimer,0,Qt::AlignRight |Qt::AlignTop);
    //mainLayout->addStretch(1);
    filesTable->selectRow(d_rowidx);
    filesTable->resizeColumnsToContents();
    filesTable->resizeRowsToContents();
    setStyleSheet("QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QDateTimeEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox { background-color: white; border: 1px solid #dcdcdc; color: black; border-radius: 3px;font-size: 14px;padding: 5px;} QComboBox::hover { background-color: lightgray; } QComboBox::pressed { background-color: gray; } QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;} QTableWidget {background-color: #f5f5f5;border: 1px solid #d7d7d7;gridline-color: #d7d7d7;} QTableWidget::item {padding: 5px;border: none; text-align: center;} QTableWidget::item:selected {background-color: #b5d5ff;} QHeaderView::section {background-color: #d7d7d7;color: #444444;padding: 5px;border: none;font-weight: bold;} QHeaderView::section:hover {background-color: #b5d5ff;} QScrollBar:vertical {background-color: #f5f5f5border: none;width: 10px;} QScrollBar::handle:vertical {background-color: #d7d7d7;border: none;border-radius: 5px;} QScrollBar::add-line:vertical {height: 0px;}QScrollBar::sub-line:vertical {height: 0px;}");

}

void persoWindow::onSupprimeClicked(){
    QItemSelectionModel *selectionModel = filesTable->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (!selectedRows.isEmpty()) {
        d_rowidx = selectedRows.first().row();
        // Use the rowIndex as needed
    }
    int idx= d_rowidx;
    emit deletePersonneSignal(idx);

}


void persoWindow::onValiderClicked()
{
    // Get the values from the input fields
    QString nom = nomchamp->text();
    QString prenom = prénomchamp->text();
    QString email = emailchamp->text();
    QString tel = telchamp->text();

    // Emit the addPersonneSignal signal with the values
    emit addPersonneSignal(nom, prenom, tel, email);
    Addpersonne->close();
    delete Addpersonne;
}

void persoWindow::onModifierClicked()
{
    // Get the values from the input fields
    QString nom = nomchamp->text();
    QString prenom = prénomchamp->text();
    QString email = emailchamp->text();
    QString tel = telchamp->text();
    int idx= d_rowidx;
    // Emit the addPersonneSignal signal with the values
    emit modifierPersonneSignal(idx,nom, prenom, tel, email);
    Modifierpersonne->close();
    delete Modifierpersonne;
}



void persoWindow:: onAjouter(){
    Addpersonne = new QDialog();
    Addpersonne->setWindowTitle("Ajouter une personne");
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *nomrdvlayout = new QHBoxLayout;
    QHBoxLayout *prenomlayout = new QHBoxLayout;
    QHBoxLayout *tellayout = new QHBoxLayout;
    QHBoxLayout *emaillayout = new QHBoxLayout;
    QHBoxLayout *Buttonlayout = new QHBoxLayout;
    vlayout->addLayout(nomrdvlayout);
    vlayout->addLayout(prenomlayout);
    vlayout->addLayout(tellayout);
    vlayout->addLayout(emaillayout);
    vlayout->addStretch(1);
    vlayout->addLayout(Buttonlayout);
    nomchamp = new QLineEdit(this);
    prénomchamp = new QLineEdit(this);
    telchamp = new QLineEdit(this);
    emailchamp = new QLineEdit(this);
    nomrdvlayout->addWidget(new QLabel{"Nom : "},0,Qt::AlignLeft | Qt::AlignTop);
    nomrdvlayout->addWidget(nomchamp);
    prenomlayout->addWidget(new QLabel{"Prénom : "},0,Qt::AlignLeft | Qt::AlignTop);
    prenomlayout->addWidget(prénomchamp);
    tellayout->addWidget(new QLabel{"Téléphone : "},0,Qt::AlignLeft | Qt::AlignTop);
    tellayout->addWidget(telchamp);
    emaillayout->addWidget(new QLabel{"E_mail : "},0,Qt::AlignLeft | Qt::AlignTop);
    emaillayout->addWidget(emailchamp);



    //Addrdv->setFixedSize(300,280);
    QAbstractButton *bExit = new QPushButton("Annuler");
    QAbstractButton *bValider = new QPushButton("Valider");

    Buttonlayout->addWidget(bExit);
    Buttonlayout->addWidget(bValider);
    Addpersonne->setLayout(vlayout);
    Addpersonne->show();
    Addpersonne->connect(bExit,SIGNAL(clicked()),Addpersonne,SLOT(close()));
    connect(bValider, &QPushButton::clicked, this, &persoWindow::onValiderClicked);

    // Définir les styles
    Addpersonne->setStyleSheet("QDialog {background-color: #f7f7f7;border: 1px solid #dcdcdc;border-radius: 5px;font-family: Arial, sans-serif;} QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;}");

}
void persoWindow:: onModifier(){
    QItemSelectionModel *selectionModel = filesTable->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (!selectedRows.isEmpty()) {
        d_rowidx = selectedRows.first().row();
        // Use the rowIndex as needed
    }
    Personne* p= d_personnes->getPersonne(d_rowidx);
    Modifierpersonne = new QDialog();
    Modifierpersonne->setWindowTitle("Modifier une personne");
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *nomrdvlayout = new QHBoxLayout;
    QHBoxLayout *prenomlayout = new QHBoxLayout;
    QHBoxLayout *tellayout = new QHBoxLayout;
    QHBoxLayout *emaillayout = new QHBoxLayout;
    QHBoxLayout *Buttonlayout = new QHBoxLayout;
    vlayout->addLayout(nomrdvlayout);
    vlayout->addLayout(prenomlayout);
    vlayout->addLayout(tellayout);
    vlayout->addLayout(emaillayout);
    vlayout->addStretch(1);
    vlayout->addLayout(Buttonlayout);
    nomchamp = new QLineEdit(this);
    prénomchamp = new QLineEdit(this);
    telchamp = new QLineEdit(this);
    emailchamp = new QLineEdit(this);
    nomchamp->setText(QString::fromStdString(p->d_nom));
    prénomchamp->setText(QString::fromStdString(p->d_prenom));
    telchamp->setText(QString::fromStdString(p->d_telephone));
    emailchamp->setText(QString::fromStdString(p->d_email));
    nomrdvlayout->addWidget(new QLabel{"Nom : "},0,Qt::AlignLeft | Qt::AlignTop);
    nomrdvlayout->addWidget(nomchamp);
    prenomlayout->addWidget(new QLabel{"Prénom : "},0,Qt::AlignLeft | Qt::AlignTop);
    prenomlayout->addWidget(prénomchamp);
    tellayout->addWidget(new QLabel{"Téléphone : "},0,Qt::AlignLeft | Qt::AlignTop);
    tellayout->addWidget(telchamp);
    emaillayout->addWidget(new QLabel{"E_mail : "},0,Qt::AlignLeft | Qt::AlignTop);
    emaillayout->addWidget(emailchamp);



    //Addrdv->setFixedSize(300,280);
    QAbstractButton *bExit = new QPushButton("Annuler");
    QAbstractButton *bValider = new QPushButton("Valider");

    Buttonlayout->addWidget(bExit);
    Buttonlayout->addWidget(bValider);
    Modifierpersonne->setLayout(vlayout);
    Modifierpersonne->show();
    Modifierpersonne->connect(bExit,SIGNAL(clicked()),Modifierpersonne,SLOT(close()));
    connect(bValider, &QPushButton::clicked, this, &persoWindow::onModifierClicked);

    // Définir les styles
    Modifierpersonne->setStyleSheet("QDialog {background-color: #f7f7f7;border: 1px solid #dcdcdc;border-radius: 5px;font-family: Arial, sans-serif;} QLabel {color: #2b2b2b;font-size: 16px;font-weight: bold;} QLineEdit {border: 1px solid #dcdcdc;border-radius: 3px;font-size: 14px;padding: 5px;} QPushButton {background-color: #0088cc;border: none;border-radius: 3px;color: #fff;font-size: 14px;padding: 8px 16px;} QPushButton:hover {background-color: #006699;cursor: pointer;}");

}


