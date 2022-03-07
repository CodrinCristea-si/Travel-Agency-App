#include <QMessageBox>
#include "GUI.h"

void MeniuAplicatie::initializare(){
    WidMeniu=new QWidget;
    WidCautareBara=new QWidget;
    WidCautare=new QWidget;
    WidButoaneMeniu=new QWidget;
    WidAfisare=new QWidget;
    WidMeniuStg=new QWidget;
    LyCautare=new QHBoxLayout;
    LyAfisare=new QVBoxLayout;
    LyMeniuButoane=new QVBoxLayout;
    LyMeniuButoaneCos=new QVBoxLayout;
    LyMeniu=new QHBoxLayout;
    DenLabCaut= new QLabel{"DENUMIRE:"};
    LineCautare=new QLineEdit;
    ButonCautare=new QPushButton{"&CAUTARE"};
    FormCautare=new QFormLayout;

    //modelLista=new ModelLista{cont.get_lista_repo(rep),this};
    ListaAfisare=new QListWidget;
    //ListaAfisare->setModel(reinterpret_cast<QAbstractItemModel *>(modelLista));

    LyMeniuStg=new QVBoxLayout;
    DenOfLabAf=new QLabel{"DENUMIRI OFERTE:"};
    ButonTabel=new QPushButton{"&AFISARE TABEL"};
    ButonCos=new QPushButton{"&GESTIONARE COS"};

    tabel=new QTableWidget;


    ///layout cautare
    WidCautareBara->setLayout(FormCautare);
    FormCautare->addRow(DenLabCaut,LineCautare);
    LyCautare->addWidget(WidCautareBara);
    LyCautare->addWidget(ButonCautare);
    LyCautare->addStretch();
    WidCautare->setLayout(LyCautare);

    ///layout afisare
    LyAfisare->addWidget(DenOfLabAf);
    LyAfisare->addWidget(ListaAfisare);
    LyAfisare->addStretch();
    WidAfisare->setLayout(LyAfisare);

    ///layout partea stanga
    LyMeniuStg->addWidget(WidCautare);
    LyMeniuStg->addWidget(WidAfisare);
    LyMeniuStg->addStretch();
    WidMeniuStg->setLayout(LyMeniuStg);

    ///layout butoane
    ButonAdauga=new QPushButton{"&Adauga"};
    ButonSterge=new QPushButton{"&Sterge"};
    ButonModifica=new QPushButton{"&Modifica"};
    ButonIesire=new QPushButton{"&Iesire"};
    ButonUndo=new QPushButton{"&UNDO"};
    ButonAdaugaCos=new QPushButton{"&ADAUGA IN COS"};
    ButonGenerareCos=new QPushButton{"&GENEREAZA COS"};
    ButonGolireCos=new QPushButton{"&GOLIRE COS"};
    ButonWriteCos=new QPushButton{"&COS CRUD"};
    ButonWriteCosV2=new QPushButton{"&COS CRUD V2"};
    ButonReadCos= new QPushButton{"&COS READ"};


    LyMeniuButoane->addStretch();
    LyMeniuButoane->addWidget(ButonAdauga);
    LyMeniuButoane->addWidget(ButonSterge);
    LyMeniuButoane->addWidget(ButonModifica);
    LyMeniuButoane->addWidget(ButonTabel);
    LyMeniuButoane->addWidget(ButonCos);
    LyMeniuButoane->addWidget(ButonUndo);
    LyMeniuButoane->addWidget(ButonIesire);
    LyMeniuButoane->addStretch();
    WidButoaneMeniu->setLayout(LyMeniuButoane);

    LyMeniuButoaneCos->addStretch();
    LyMeniuButoaneCos->addWidget(ButonAdaugaCos);
    LyMeniuButoaneCos->addWidget(ButonGolireCos);
    LyMeniuButoaneCos->addWidget(ButonGenerareCos);
    LyMeniuButoaneCos->addWidget(ButonWriteCos);
    LyMeniuButoaneCos->addWidget(ButonWriteCosV2);
    LyMeniuButoaneCos->addWidget(ButonReadCos);
    LyMeniuButoaneCos->addStretch();
    ///meniu
    WidMeniu->setLayout(LyMeniu);
    LyMeniu->addWidget(WidMeniuStg);
    LyMeniu->addWidget(WidButoaneMeniu);
    LyMeniu->addLayout(LyMeniuButoaneCos);
    //LyMeniu->addStretch();

    WidMeniu->show();
}

void MeniuAplicatie::conectare(){
    cont.adauga_suspect(this);
    QObject::connect(ButonAdauga,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr,"Info","Acesta e butonul de adaugare");
        //adaugare();
        //CasutaLineEdit2Butoane casuta{"&STERGE",*this};
        //Casuta4LineEdit adauga{2,"&ADAUGA","\0",*this};
        adaugare();
        //qDebug()<<"gata adaugarea\n";
        //cont.citeste_fisier_repo(rep,"repo.txt");
        //qDebug()<<"nr of tot"<<QString::number(cont.get_numar_oferte(rep));
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonSterge,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr,"Info","Acesta e butonul de stergere");
        //casutaStergeModifica("&Stergere");
        sterge();
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonModifica,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr,"Info","Acesta e butonul de modificare");
        //casutaStergeModifica("&Modficare");
        modifica();
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonCautare,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr,"Info","Acesta e butonul de cautare");
        QString textul=LineCautare->text();
        string denumire=textul.toStdString();
        const int poz = cont.cauta_in_lista(rep, denumire);
        if(poz==-1) {QMessageBox::critical(nullptr,"Eroare","Oferta inexistenta!");
            //widTotal->close();
             }
        else{
            casuta_cautare_coloana(denumire);
            //widTotal->close();
        }
        LineCautare->setText("");
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonTabel,&QPushButton::clicked,[&](){
        afisare_totala();
    });

    QObject::connect(ButonCos,&QPushButton::clicked,[&](){
        auto* cos=new Cos_GUI{rep,cont,wish};
    });

    QObject::connect(ButonAdaugaCos,&QPushButton::clicked,[&](){
        adauga_cos();
        afisare(cont.get_lista_repo(rep));
    });

    QObject::connect(ButonGenerareCos,&QPushButton::clicked,[&](){
        generare_cos();
        afisare(cont.get_lista_repo(rep));
    });

    QObject::connect(ButonGolireCos,&QPushButton::clicked,[&](){
        int btn=QMessageBox::warning(nullptr,"AVERTISMENT","Cosul va fi golit!\nSunteti sigur de aceasta operatiune?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes){
            cont.sterge_tot_wishlist(wish);
        }
    });

    QObject::connect(ButonWriteCos,&QPushButton::clicked,[&](){
        auto* cos=new CosCRUDGUI{rep,cont,wish};
    });

    QObject::connect(ButonWriteCosV2,&QPushButton::clicked,[&](){
        auto* cos=new CosV2CRUDGUI{rep,cont,wish};
    });

    QObject::connect(ButonReadCos,&QPushButton::clicked,[&](){
        auto* cos=new CosReadOnlyGUI{rep,cont,wish};
    });

    QObject::connect(ButonUndo,&QPushButton::clicked,[&](){
        try{
            cont.undo();
            QMessageBox::information(nullptr,"INFO","Undo realizat cu succes");
        }
        catch (const ExceptieRepository& err){
            QMessageBox::critical(nullptr,"EROARE",QString::fromStdString(err.get_mesaj_eroare()));
        }
        afisare(cont.get_lista_repo(rep));
    });
    QObject::connect(ButonIesire,&QPushButton::clicked,[&](){
        int btn=QMessageBox::warning(nullptr,"Iesire","Aplicatia se va inchide!\n"
                                              "Esti sigur ca vrei sa iesi?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes)exit(0);
    });


    QObject::connect(ListaAfisare,&QListWidget::itemSelectionChanged,[&](){
        //auto selectie=ListaAfisare->selectionModel()->selectedIndexes();
        auto selectie=ListaAfisare->selectedItems();
        if(!selectie.isEmpty()){
            //if(ultim!= nullptr)ultim->setBackground(Qt::white);
            auto select=selectie.at(0);
            //auto poz =select.row();
            select->setBackground(Qt::darkGreen);
            //auto textul=modelLista->index(poz,0).data(Qt::DisplayRole);
            //string denumire=textul.toString().toStdString();
            string denumire=select->text().toStdString();
            casuta_cautare_coloana(denumire,true);
            //ListaAfisare->selectionModel()->clearSelection();
            //ultim=select;
            //select->setBackground(Qt::white);
        }
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

}


void MeniuAplicatie::afisare(vector<Oferta>&lista_oferte){
    ListaAfisare->clear();
    //ListaAfisare->model()->removeRows(0, ListaAfisare->model()->rowCount());
    //vector<Oferta>lista_oferte=cont.get_lista_repo(rep);
    for(const auto& el: lista_oferte){
        //modelLista->insertRow(modelLista->rowCount());
        //QModelIndex index= modelLista->index(modelLista->rowCount()-1);
        //modelLista->setData(index,QString::fromStdString(el.get_denumire()));
        auto* item= new QListWidgetItem{QString::fromStdString(el.get_denumire()),ListaAfisare};
        //auto *item= new QListWidgetItem(QString::fromStdString(el.get_denumire()), MeniuAplicatie::ListaAfisare);
    }
}

void MeniuAplicatie::adaugare() {
    //auto* textDenumire=new QLabel{"DENUMIRE"};
    //auto* textDestinatie=new QLabel{"DESTINATIE"};
    //auto* textTip=new QLabel{"TIP"};
    //auto* textPret=new QLabel{"PRET"};

    auto* boxDenumire=new QLineEdit;
    auto* boxDestinatie=new QLineEdit;
    auto* boxTip=new QLineEdit;
    auto* boxPret=new QLineEdit;

    auto* ButonPrincipal=new QPushButton{"&ADAUGA"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    auto* widButoane=new QWidget;
    auto* widText=new QWidget;
    auto* widAdaugare=new QWidget;

    auto* lyText=new QFormLayout;
    auto* lyButoane=new QHBoxLayout;
    auto* lyAdaugare=new QVBoxLayout;

    ///layout texte de colectat
    lyText->addRow("DENUMIRE:",boxDenumire);
    lyText->addRow("DESTINATIE:",boxDestinatie);
    lyText->addRow("TIP:",boxTip);
    lyText->addRow("PRET:",boxPret);
    widText->setLayout(lyText);

    ///layout butoane
    lyButoane->addWidget(ButonPrincipal);
    lyButoane->addWidget(ButonRevocare);
    widButoane->setLayout(lyButoane);

    ///layout principal
    lyAdaugare->addWidget(widText);
    lyAdaugare->addWidget(widButoane);
    widAdaugare->setLayout(lyAdaugare);
    widAdaugare->show();

    //qDebug()<<"adauga conectare\n";
    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,boxDenumire,boxDestinatie,boxPret,boxTip,widAdaugare](){
        //cont.citeste_fisier_repo(rep,"repo.txt");
        //qDebug()<<"click x1\n";
        QLineEdit* texDenumire=boxDenumire;
        //qDebug()<<"click x2\n";
        QString text=texDenumire->text();
        //qDebug()<<"click x3\n";
        string denumire=text.toStdString();
        text=boxDestinatie->text();
        string destinatie=text.toStdString();
        text=boxTip->text();
        string tip=text.toStdString();
        text=boxPret->text();
        string pret=text.toStdString();
        //qDebug()<<QString::fromStdString(denumire)<<" "<<QString::fromStdString(destinatie)<<" "<<QString::fromStdString(tip)<<" "<<QString::fromStdString(pret)<<"\n";
        //cout<<denumire<<" "<<destinatie<<" "<<tip<<" "<<pret<<endl;
        try{
            cont.validare(rep,denumire,destinatie,tip,pret);
            cont.adauga_in_lista(rep,denumire,destinatie,tip,stof(pret));
            QMessageBox::information(nullptr,"Info","Oferta adaugata cu succes");
            //cont.salveaza_fisier_repo(rep,"repo.txt");
        }
        catch(const ExceptieValidare& err){
            QMessageBox::critical(nullptr,"Eroare",QString::fromStdString(err.get_mesaj_eroare()));
        }
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
        widAdaugare->close();
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[this,widAdaugare](){
        QMessageBox::information(nullptr,"Info","hai pa");
        //QCloseEvent();
        widAdaugare->close();
        //return 0;
    });
    //qDebug()<<boxDenumire->text();
}

void MeniuAplicatie::sterge(){
    auto* textDenumire=new QLabel{"DENUMIRE"};
    auto* boxDenumire=new QLineEdit;

    auto* lyText=new QFormLayout;
    auto* lyButoane=new QHBoxLayout;
    auto* lyTotal=new QVBoxLayout;

    auto* widButoane=new QWidget;
    auto* widText=new QWidget;
    auto* widTotal=new QWidget;


    auto* ButonPrincipal=new QPushButton{"&STERGE"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    ///layout denumire
    widText->setLayout(lyText);
    lyText->addRow("DENUMIRE:",boxDenumire);

    ///layout butoane
    widButoane->setLayout(lyButoane);
    lyButoane->addWidget(ButonPrincipal);
    lyButoane->addWidget(ButonRevocare);
    lyButoane->addStretch();

    ///layout principal
    widTotal->setLayout(lyTotal);
    lyTotal->addWidget(widText);
    lyTotal->addWidget(widButoane);
    lyTotal->addStretch();

    widTotal->show();

    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,boxDenumire,widTotal](){
        int btn=QMessageBox::warning(nullptr,"Sterge","Oferta va fi stearsa!\nSunteti sigur de aceasta operatiune?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes){
            QString textul=boxDenumire->text();
            string denumire=textul.toStdString();
            const int poz = cont.cauta_in_lista(rep, denumire);
            try {
                if (poz != -1) {
                    const Oferta& of = cont.oferta_cu_poz(rep, poz);
                    cont.validare(rep, denumire, of.get_destinatie(), of.get_tip(), std::to_string(of.get_pret()));
                }
                else QMessageBox::critical(nullptr,"Eroare","Oferta inexistenta!");
            }
            catch (const ExceptieValidare& err) {
                if (err.get_cod() == 8) {
                    cont.sterge_din_lista(rep, denumire);
                    //cout << "Oferta stearsa cu succes" << endl;
                    QMessageBox::information(nullptr,"Info","Oferta stearga cu succes");
                }
                else QMessageBox::critical(nullptr,"Eroare",QString::fromStdString(err.get_mesaj_eroare()));
            }
            widTotal->close();
        }
        else{
            widTotal->close();
        }
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[this,widTotal](){
        //QMessageBox::information(nullptr,"Info","hai pa");
        //QCloseEvent();
        widTotal->close();
        //return 0;
    });
}
void MeniuAplicatie::modifica(){
    auto* textDenumire=new QLabel{"DENUMIRE"};
    auto* boxDenumire=new QLineEdit;

    auto* lyText=new QFormLayout;
    auto* lyButoane=new QHBoxLayout;
    auto* lyTotal=new QVBoxLayout;

    auto* widButoane=new QWidget;
    auto* widText=new QWidget;
    auto* widTotal=new QWidget;


    auto* ButonPrincipal=new QPushButton{"&MODIFICA"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    ///layout denumire
    widText->setLayout(lyText);
    lyText->addRow(textDenumire,boxDenumire);

    ///layout butoane
    widButoane->setLayout(lyButoane);
    lyButoane->addWidget(ButonPrincipal);
    lyButoane->addWidget(ButonRevocare);
    lyButoane->addStretch();

    ///layout principal
    widTotal->setLayout(lyTotal);
    lyTotal->addWidget(widText);
    lyTotal->addWidget(widButoane);
    lyTotal->addStretch();

    widTotal->show();

    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,boxDenumire,widTotal](){
        QString textul=boxDenumire->text();
        string denumire=textul.toStdString();
        const int poz = cont.cauta_in_lista(rep, denumire);
        if(poz==-1) {QMessageBox::critical(nullptr,"Eroare","Oferta inexistenta!");
            widTotal->close();}
        else{
            modificare_casuta(denumire);
            widTotal->close();
        }
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[this,widTotal](){
        //QMessageBox::information(nullptr,"Info","hai pa");
        //QCloseEvent();
        widTotal->close();
        //return 0;
    });
}

void MeniuAplicatie::modificare_casuta(string denumire){
    auto* boxDenumire=new QLineEdit;
    auto* boxDestinatie=new QLineEdit;
    auto* boxTip=new QLineEdit;
    auto* boxPret=new QLineEdit;

    auto* ButonPrincipal=new QPushButton{"&SALVEAZA"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    auto* widButoane=new QWidget;
    auto* widText=new QWidget;
    auto* widTotal=new QWidget;

    auto* lyText=new QFormLayout;
    auto* lyButoane=new QHBoxLayout;
    auto* lyTotal=new QVBoxLayout;

    ///layout texte de colectat
    lyText->addRow("DENUMIRE:",boxDenumire);
    lyText->addRow("DESTINATIE:",boxDestinatie);
    lyText->addRow("TIP:",boxTip);
    lyText->addRow("PRET:",boxPret);
    widText->setLayout(lyText);

    ///layout butoane
    lyButoane->addWidget(ButonPrincipal);
    lyButoane->addWidget(ButonRevocare);
    widButoane->setLayout(lyButoane);

    ///layout principal
    lyTotal->addWidget(widText);
    lyTotal->addWidget(widButoane);
    widTotal->setLayout(lyTotal);

    Oferta& of=cont.oferta_cu_poz(rep, cont.cauta_in_lista(rep,denumire));
    boxDenumire->setText(QString::fromStdString(of.get_denumire()));
    boxDestinatie->setText(QString::fromStdString(of.get_destinatie()));
    boxTip->setText(QString::fromStdString(of.get_tip()));
    boxPret->setText(QString::number(of.get_pret()));

    widTotal->show();

    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,boxDenumire,boxDestinatie,boxPret,boxTip,widTotal,denumire](){
        int btn=QMessageBox::warning(nullptr,"Sterge","Oferta va fi modificata!\nSunteti sigur de aceasta operatiune?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes) {
            QString text = boxDenumire->text();
            string denumire_noua = text.toStdString();
            text = boxDestinatie->text();
            string destinatie = text.toStdString();
            text = boxTip->text();
            string tip = text.toStdString();
            text = boxPret->text();
            string pret = text.toStdString();
            try {
                cont.validare(rep, denumire_noua, destinatie, tip, pret);
                if (denumire_noua!=denumire)throw ExceptieValidare(8,"Oferta Existenta");
            }
            catch (const ExceptieValidare &err) {
                if (err.get_cod() != 8)
                    QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.get_mesaj_eroare()));
                else {
                    bool ok=false;
                    if(denumire_noua!=denumire){
                        cont.modifica(rep, denumire, 1, denumire_noua);
                        ok=true;
                    }
                    string den= !ok ? denumire : denumire_noua ;
                    if(destinatie!=cont.oferta_cu_poz(rep,cont.cauta_in_lista(rep,den)).get_destinatie())cont.modifica(rep, den, 2, destinatie);
                    if(tip!=cont.oferta_cu_poz(rep,cont.cauta_in_lista(rep,den)).get_tip())cont.modifica(rep, den, 3, tip);
                    if(stof(pret)!=cont.oferta_cu_poz(rep,cont.cauta_in_lista(rep,den)).get_pret())cont.modifica(rep, den, 4, pret);
                    //cont.sterge_din_lista(rep,denumire);
                    //cont.adauga_in_lista(rep,denumire_noua,destinatie,tip, stof(pret));
                    QMessageBox::information(nullptr, "Info", "Oferta salvata cu succes");
                }
            }
            widTotal->close();
        }
        else widTotal->close();
        afisare(cont.get_lista_repo(rep));
        //afisare_totala();
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[this,widTotal](){
        //QMessageBox::information(nullptr,"Info","hai pa");
        //QCloseEvent();
        widTotal->close();
        //return 0;
    });
}

void MeniuAplicatie::casuta_cautare_coloana(string& denumire,bool cu_modificare){
    auto* boxDenumire=new QLineEdit;
    auto* boxDestinatie=new QLineEdit;
    auto* boxTip=new QLineEdit;
    auto* boxPret=new QLineEdit;

    auto* ButonPrincipal=new QPushButton{"&SALVEAZA"};
    auto* ButonSecundar=new QPushButton{"&STERGE"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    auto* widButoane=new QWidget;
    auto* widText=new QWidget;
    auto* widTotal=new QWidget;

    auto* lyText=new QFormLayout;
    auto* lyButoane=new QHBoxLayout;
    auto* lyTotal=new QVBoxLayout;

    ///layout texte de colectat
    lyText->addRow("DENUMIRE:",boxDenumire);
    lyText->addRow("DESTINATIE:",boxDestinatie);
    lyText->addRow("TIP:",boxTip);
    lyText->addRow("PRET:",boxPret);
    widText->setLayout(lyText);

    ///layout butoane
    if(cu_modificare) {
        lyButoane->addWidget(ButonPrincipal);
        lyButoane->addWidget(ButonSecundar);
        lyButoane->addWidget(ButonRevocare);
        widButoane->setLayout(lyButoane);
    }
    ///layout principal
    lyTotal->addWidget(widText);
    if(cu_modificare)lyTotal->addWidget(widButoane);
    widTotal->setLayout(lyTotal);

    Oferta& of=cont.oferta_cu_poz(rep, cont.cauta_in_lista(rep,denumire));
    boxDenumire->setText(QString::fromStdString(of.get_denumire()));
    boxDestinatie->setText(QString::fromStdString(of.get_destinatie()));
    boxTip->setText(QString::fromStdString(of.get_tip()));
    boxPret->setText(QString::number(of.get_pret()));

    widTotal->show();
    if(cu_modificare) {
    QObject::connect(ButonPrincipal, &QPushButton::clicked,
                     [&, boxDenumire, boxDestinatie, boxPret, boxTip, widTotal, denumire]() {
                         int btn = QMessageBox::warning(nullptr, "Sterge",
                                                        "Oferta va fi modificata!\nSunteti sigur de aceasta operatiune?",
                                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                         if (btn == QMessageBox::Yes) {
                             QString text = boxDenumire->text();
                             string denumire_noua = text.toStdString();
                             text = boxDestinatie->text();
                             string destinatie = text.toStdString();
                             text = boxTip->text();
                             string tip = text.toStdString();
                             text = boxPret->text();
                             string pret = text.toStdString();
                             try {
                                 cont.validare(rep, denumire_noua, destinatie, tip, pret);
                                 if (denumire_noua != denumire)throw ExceptieValidare(8, "Oferta Existenta");
                             }
                             catch (const ExceptieValidare &err) {
                                 if (err.get_cod() != 8)
                                     QMessageBox::critical(nullptr, "Eroare",
                                                           QString::fromStdString(err.get_mesaj_eroare()));
                                 else {
                                     //cont.modifica(rep, denumire, 1, denumire_noua);
                                     //cont.modifica(rep, denumire_noua, 2, destinatie);
                                     //cont.modifica(rep, denumire_noua, 3, tip);
                                     //cont.modifica(rep, denumire_noua, 4, pret);
                                     bool ok = false;
                                     if (denumire_noua != denumire) {
                                         cont.modifica(rep, denumire, 1, denumire_noua);
                                         ok = true;
                                     }
                                     string den = !ok ? denumire : denumire_noua;
                                     if (destinatie !=
                                         cont.oferta_cu_poz(rep, cont.cauta_in_lista(rep, den)).get_destinatie())
                                         cont.modifica(rep, den, 2, destinatie);
                                     if (tip != cont.oferta_cu_poz(rep, cont.cauta_in_lista(rep, den)).get_tip())
                                         cont.modifica(rep, den, 3, tip);
                                     if (stof(pret) !=
                                         cont.oferta_cu_poz(rep, cont.cauta_in_lista(rep, den)).get_pret())
                                         cont.modifica(rep, den, 4, pret);
                                     //cont.sterge_din_lista(rep,denumire);
                                     //cont.adauga_in_lista(rep,denumire_noua,destinatie,tip, stof(pret));
                                     QMessageBox::information(nullptr, "Info", "Oferta salvata cu succes");
                                 }
                             }
                             //qDebug()<<"Nr of mod "<<QString::number(cont.get_numar_oferte(rep));
                             widTotal->close();
                         } else widTotal->close();
                         afisare(cont.get_lista_repo(rep));
                         //cont.salveaza_fisier_repo(rep,"repo.txt");
                     });

    QObject::connect(ButonSecundar, &QPushButton::clicked, [&, boxDenumire, widTotal]() {
        int btn = QMessageBox::warning(nullptr, "Sterge", "Oferta va fi stearsa!\nSunteti sigur de aceasta operatiune?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (btn == QMessageBox::Yes) {
            QString textul = boxDenumire->text();
            string denumire = textul.toStdString();
            const int poz = cont.cauta_in_lista(rep, denumire);
            try {
                if (poz != -1) {
                    const Oferta &of = cont.oferta_cu_poz(rep, poz);
                    cont.validare(rep, denumire, of.get_destinatie(), of.get_tip(), std::to_string(of.get_pret()));
                } else QMessageBox::critical(nullptr, "Eroare", "Oferta inexistenta!");
            }
            catch (const ExceptieValidare &err) {
                if (err.get_cod() == 8) {
                    cont.sterge_din_lista(rep, denumire);
                    //cout << "Oferta stearsa cu succes" << endl;
                    QMessageBox::information(nullptr, "Info", "Oferta stearga cu succes");
                } else QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.get_mesaj_eroare()));
            }
            widTotal->close();
        } else {
            widTotal->close();
        }
        afisare(cont.get_lista_repo(rep));
        //cont.salveaza_fisier_repo(rep,"repo.txt");
    });

    QObject::connect(ButonRevocare, &QPushButton::clicked, [this, widTotal]() {
        //QMessageBox::information(nullptr,"Info","hai pa");
        //QCloseEvent();
        widTotal->close();
        //return 0;
    });
}
}
void MeniuAplicatie::afisare_totala(){
    auto* widTotal=new QWidget;
    auto* lyTotal=new QVBoxLayout;

    auto* widButoane=new QWidget;
    auto *lyButoane=new QHBoxLayout;

    auto* widTabel=new QWidget;

    auto* ButonReincarcare=new QPushButton{"&REINCARCARE"};
    auto* ButonFiltrare=new QPushButton{"&FILTRARE"};
    auto* ButonSortare=new QPushButton{"&SORTARE"};
    auto* ButonIesireTabel=new QPushButton{"&INCHIDE"};

    lyButoane->addStretch();
    lyButoane->addWidget(ButonReincarcare);
    lyButoane->addWidget(ButonFiltrare);
    lyButoane->addWidget(ButonSortare);
    lyButoane->addWidget(ButonIesireTabel);
    lyButoane->addStretch();
    widButoane->setLayout(lyButoane);

    lyTotal->addWidget(widButoane);
    lyTotal->addWidget(tabel);
    //lyTotal->addStretch();
    widTotal->setLayout(lyTotal);

    afisare_tabel(cont.get_lista_repo(rep),tabel);

    widTotal->show();

    QObject::connect(ButonIesireTabel,&QPushButton::clicked,[&,widTotal](){
        int btn=QMessageBox::warning(nullptr,"Iesire","Tabelul se va inchide!\n"
                                                      "Esti sigur ca vrei sa iesi?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes)widTotal->close();
    });

    QObject::connect(ButonReincarcare,&QPushButton::clicked,[&](){
        afisare_tabel(cont.get_lista_repo(rep),tabel);
    });

    QObject::connect(ButonFiltrare,&QPushButton::clicked,[&](){
        filtrare();
    });

    QObject::connect(ButonSortare,&QPushButton::clicked,[&](){
        sortare();
    });
}

void MeniuAplicatie::filtrare(){

    auto* widButoane=new QWidget;
    auto* lyButoane=new QVBoxLayout;

    auto* ButonFiltrareDestinatie=new QPushButton{"&FILTRARE DUPA DESTINATIE"};
    auto* ButonFiltrareTip=new QPushButton{"&FILTRARE DUPA TIP"};
    auto* ButonFiltrarePret=new QPushButton{"&FILTRARE DUPA PRET"};
    auto* ButonAnulare=new QPushButton{"&ANULARE FILTRU"};

    lyButoane->addWidget(ButonFiltrareDestinatie);
    lyButoane->addWidget(ButonFiltrareTip);
    lyButoane->addWidget(ButonFiltrarePret);
    lyButoane->addWidget(ButonAnulare);
    lyButoane->addStretch();
    widButoane->setLayout(lyButoane);

    widButoane->show();

    QObject::connect(ButonFiltrareDestinatie,&QPushButton::clicked,[&,widButoane](){
        filtrare_destinatie();
        widButoane->close();
    });

    QObject::connect(ButonFiltrareTip,&QPushButton::clicked,[&,widButoane](){
        filtrare_tip();
        widButoane->close();
    });

    QObject::connect(ButonFiltrarePret,&QPushButton::clicked,[&,widButoane](){
        filtrare_pret();
        widButoane->close();
    });

    QObject::connect(ButonAnulare,&QPushButton::clicked,[&,widButoane](){
        afisare_tabel(cont.get_lista_repo(rep),tabel);
        widButoane->close();
    });
}

void MeniuAplicatie::filtrare_destinatie(){

    auto* widDestinatieCasuta=new QWidget;

    auto* boxDestinatie=new QLineEdit;
    auto* formDestinatie=new QFormLayout;

    auto *lyButoane=new QHBoxLayout;
    auto *widButoane=new QWidget;
    auto* ButonFiltrare=new QPushButton{"&FILTREAZA"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    auto* lyTotal=new QVBoxLayout;
    auto* widTotal=new QWidget;

    formDestinatie->addRow("DESTINATIE :", boxDestinatie);
    widDestinatieCasuta->setLayout(formDestinatie);

    lyButoane->addWidget(ButonFiltrare);
    lyButoane->addWidget(ButonRevocare);
    lyButoane->addStretch();
    widButoane->setLayout(lyButoane);

    lyTotal->addWidget(widDestinatieCasuta);
    lyTotal->addWidget(widButoane);
    lyTotal->addStretch();
    widTotal->setLayout(lyTotal);

    widTotal->show();

    QObject::connect(ButonFiltrare,&QPushButton::clicked,[&,boxDestinatie,widTotal](){
        QString text=boxDestinatie->text();
        string filtrare_text=text.toStdString();
        vector<Oferta>lista_afisare=cont.filtru(rep, filtrare_text, compara_destinatie);
        if(lista_afisare.empty()) QMessageBox::critical(nullptr,"EROARE","Nu exista oferte care sa corespunda filtrarii respective!");
        else afisare_tabel(lista_afisare,tabel);
        widTotal->close();
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[&,widTotal](){
        widTotal->close();
    });
}

void MeniuAplicatie::filtrare_tip(){

    auto* widTipCasuta=new QWidget;

    auto* boxTip=new QLineEdit;
    auto* formTip=new QFormLayout;

    auto *lyButoane=new QHBoxLayout;
    auto *widButoane=new QWidget;
    auto* ButonFiltrare=new QPushButton{"&FILTREAZA"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    auto* lyTotal=new QVBoxLayout;
    auto* widTotal=new QWidget;

    formTip->addRow("TIP :", boxTip);
    widTipCasuta->setLayout(formTip);

    lyButoane->addWidget(ButonFiltrare);
    lyButoane->addWidget(ButonRevocare);
    lyButoane->addStretch();
    widButoane->setLayout(lyButoane);

    lyTotal->addWidget(widTipCasuta);
    lyTotal->addWidget(widButoane);
    lyTotal->addStretch();
    widTotal->setLayout(lyTotal);

    widTotal->show();

    QObject::connect(ButonFiltrare,&QPushButton::clicked,[&,boxTip,widTotal](){
        QString text=boxTip->text();
        string filtrare_text=text.toStdString();
        auto lista_oferte=cont.get_lista_repo(rep);
        vector<Oferta>lista_afisare;
        for (const auto& el: lista_oferte ){
            if (el.get_tip()==filtrare_text)
                lista_afisare.push_back(el);
        }
        if(lista_afisare.empty()) QMessageBox::critical(nullptr,"EROARE","Nu exista oferte care sa corespunda filtrarii respective!");
        else afisare_tabel(lista_afisare,tabel);
        widTotal->close();
    });
    QObject::connect(ButonRevocare,&QPushButton::clicked,[&,widTotal](){
        widTotal->close();
    });
}

void MeniuAplicatie::filtrare_pret(){

    auto* widPretCasuta=new QWidget;
    auto* lyPretCasuta=new QHBoxLayout;

    auto* spinPret=new QSpinBox;
    auto* sliderPret=new QSlider{Qt::Horizontal};

    auto *lyButoane=new QHBoxLayout;
    auto *widButoane=new QWidget;
    auto* ButonFiltrare=new QPushButton{"&FILTREAZA"};
    auto* ButonRevocare=new QPushButton{"&REVOCARE"};

    auto* lyTotal=new QVBoxLayout;
    auto* widTotal=new QWidget;

    lyPretCasuta->addWidget(spinPret);
    lyPretCasuta->addWidget(sliderPret);
    lyPretCasuta->addStretch();
    widPretCasuta->setLayout(lyPretCasuta);

    lyButoane->addWidget(ButonFiltrare);
    lyButoane->addWidget(ButonRevocare);
    lyButoane->addStretch();
    widButoane->setLayout(lyButoane);

    lyTotal->addWidget(widPretCasuta);
    lyTotal->addWidget(widButoane);
    lyTotal->addStretch();
    widTotal->setLayout(lyTotal);

    spinPret->setRange(0,500);
    sliderPret->setRange(0,500);

    widTotal->show();

    QObject::connect(spinPret,&QSpinBox::valueChanged,sliderPret,&QSlider::setValue);

    QObject::connect(sliderPret,&QSlider::valueChanged,spinPret,&QSpinBox::setValue);

    QObject::connect(ButonFiltrare,&QPushButton::clicked,[&,spinPret,widTotal](){
        QString text=spinPret->text();
        string filtrare_text=text.toStdString();
        auto lista_afisare=cont.filtru(rep,filtrare_text,compara_pret);
        if(lista_afisare.empty()) QMessageBox::critical(nullptr,"EROARE","Nu exista oferte care sa corespunda filtrarii respective!");
        else afisare_tabel(lista_afisare,tabel);
        widTotal->close();
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[&,widTotal](){
        widTotal->close();
    });
}

void MeniuAplicatie::afisare_tabel(vector<Oferta>lista_oferte,QTableWidget* tabel){

    auto* titluArt=new QTableWidgetItem("Nr art.");
    auto* titluDenumire=new QTableWidgetItem("DENUMIRE");
    auto* titluDestinatie=new QTableWidgetItem("DESTINATIE");
    auto* titluTip=new QTableWidgetItem("TIP");
    auto* titluPret=new QTableWidgetItem("PRET");

    tabel->setColumnCount(5);
    tabel->setRowCount((int)lista_oferte.size()+1);
    tabel->clear();
    tabel->setItem(0,0,titluArt);
    tabel->setItem(0,1,titluDenumire);
    tabel->setItem(0,2,titluDestinatie);
    tabel->setItem(0,3,titluTip);
    tabel->setItem(0,4,titluPret);
    int poz_lin=1;
    for (const auto& el: lista_oferte){
        tabel->setItem(poz_lin,0,new QTableWidgetItem(QString::number(poz_lin)));
        tabel->setItem(poz_lin,1,new QTableWidgetItem(QString::fromStdString(el.get_denumire())));
        tabel->setItem(poz_lin,2,new QTableWidgetItem(QString::fromStdString(el.get_destinatie())));
        tabel->setItem(poz_lin,3,new QTableWidgetItem(QString::fromStdString(el.get_tip())));
        tabel->setItem(poz_lin,4,new QTableWidgetItem(QString::number(el.get_pret())));
        poz_lin++;
    }
    tabel->removeColumn(0);
}

void MeniuAplicatie::sortare(){

    auto* widButoane=new QWidget;
    auto* lyButoane=new QVBoxLayout;

    auto* ButonSortareDenumire=new QPushButton{"&SORTARE DUPA DENUMIRE"};
    auto* ButonSortareDestinatie=new QPushButton{"&SORTARE DUPA DESTINATIE"};
    auto* ButonSortareTipPret=new QPushButton{"&SORTARE DUPA TIP+PRET"};
    auto* ButonAnulare=new QPushButton{"&ANULARE SORTARE"};

    lyButoane->addWidget(ButonSortareDenumire);
    lyButoane->addWidget(ButonSortareDestinatie);
    lyButoane->addWidget(ButonSortareTipPret);
    lyButoane->addWidget(ButonAnulare);
    lyButoane->addStretch();
    widButoane->setLayout(lyButoane);

    widButoane->show();

    QObject::connect(ButonSortareDenumire,&QPushButton::clicked,[&,widButoane](){
        int btn=QMessageBox::information(nullptr,"INFO","Doriti o sortare crescatoare?", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes)
            afisare_tabel(cont.sortare(rep,false,compara_oferta_denumire),tabel);
        else
            afisare_tabel(cont.sortare(rep,true,compara_oferta_denumire),tabel);
        widButoane->close();
    });

    QObject::connect(ButonSortareDestinatie,&QPushButton::clicked,[&,widButoane](){
        int btn=QMessageBox::information(nullptr,"INFO","Doriti o sortare crescatoare?", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes)
            afisare_tabel(cont.sortare(rep,false,compara_oferta_destinatie),tabel);
        else
            afisare_tabel(cont.sortare(rep,true,compara_oferta_destinatie),tabel);
        widButoane->close();
    });

    QObject::connect(ButonSortareTipPret,&QPushButton::clicked,[&,widButoane](){
        int btn=QMessageBox::information(nullptr,"INFO","Doriti o sortare crescatoare?", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes)
            afisare_tabel(cont.sortare(rep,false,compara_oferta_tip_si_pret),tabel);
        else
            afisare_tabel(cont.sortare(rep,true,compara_oferta_tip_si_pret),tabel);
        widButoane->close();
    });

    QObject::connect(ButonAnulare,&QPushButton::clicked,[&,widButoane](){
        afisare_tabel(cont.get_lista_repo(rep),tabel);
        widButoane->close();
    });
}

void  MeniuAplicatie::adauga_cos() {
    auto* boxDenumire=new QLineEdit;

    auto* formDenumire=new QFormLayout;

    auto* widAdauga=new QWidget;
    auto* lyAdauga=new QVBoxLayout;

    auto* lyAdButoane=new QHBoxLayout;

    auto* ButonPrincipal= new QPushButton{"&ADAUGA"};
    auto* ButonSecundar= new QPushButton{"&REVOCARE"};

    lyAdButoane->addWidget(ButonPrincipal);
    lyAdButoane->addWidget(ButonSecundar);
    lyAdButoane->addStretch();

    formDenumire->addRow("DENUMIRE:",boxDenumire);

    lyAdauga->addLayout(formDenumire);
    lyAdauga->addLayout(lyAdButoane);
    widAdauga->setLayout(lyAdauga);

    widAdauga->show();

    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,boxDenumire,widAdauga](){
        QString textul=boxDenumire->text();
        string denumire=textul.toStdString();
        try{
            int poz= cont.cauta_in_lista(rep,denumire);
            if(poz==-1) throw ExceptieValidare{9,"Oferta inexistenta!"};
            Oferta & of=cont.oferta_cu_poz(rep,poz);
            cont.validare(wish,of.get_denumire(),of.get_destinatie(),of.get_tip(), std::to_string(of.get_pret()));
            cont.adauga_oferta_in_wishlist(wish,of);
            QMessageBox::information(nullptr,"INFO","Oferta adaugata in cos cu succes");
        }
        catch(const ExceptieValidare& err){
            QMessageBox::critical(nullptr,"EROARE",QString::fromStdString(err.get_mesaj_eroare()));
        }
        widAdauga->close();
        afisare(cont.get_lista_repo(rep));
    });

    QObject::connect(ButonSecundar,&QPushButton::clicked,[widAdauga](){
        widAdauga->close();
    });
}

void MeniuAplicatie::generare_cos(){
    auto* boxNr=new QLineEdit;

    auto* formNr=new QFormLayout;

    auto* widGen=new QWidget;
    auto* lyGen=new QVBoxLayout;

    auto* lyGenButoane=new QHBoxLayout;

    auto* ButonPrincipal= new QPushButton{"&GENEREAZA"};
    auto* ButonSecundar= new QPushButton{"&REVOCARE"};

    lyGenButoane->addWidget(ButonPrincipal);
    lyGenButoane->addWidget(ButonSecundar);
    lyGenButoane->addStretch();

    formNr->addRow("NR. OFERTE:",boxNr);

    lyGen->addLayout(formNr);
    lyGen->addLayout(lyGenButoane);
    widGen->setLayout(lyGen);

    widGen->show();

    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,widGen,boxNr](){
        QString textul=boxNr->text();
        string nr=textul.toStdString();
        try{
            if(stoi(nr)>cont.get_numar_oferte(rep))throw ExceptieValidare{9,"Numar insuficent de oferte!"};
            cont.sterge_tot_wishlist(wish);
            cont.genereaza_wishlist(wish,rep,stoi(nr));
            QMessageBox::information(nullptr,"Info","Cos generat cu succes");
        }
        catch(const ExceptieValidare& err){
            QMessageBox::critical(nullptr,"EROARE",QString::fromStdString(err.get_mesaj_eroare()));
        }
        widGen->close();
        afisare(cont.get_lista_repo(rep));

    });

    QObject::connect(ButonSecundar,&QPushButton::clicked,[widGen](){
        widGen->close();
    });
}