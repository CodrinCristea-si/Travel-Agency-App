#include "GUI.h"
void Cos_GUI::initializare(){
     alocare();

    lyButoane->addStretch();
    lyButoane->addWidget(ButonAdauga);
    lyButoane->addWidget(ButonGolire);
    lyButoane->addWidget(ButonGenerare);
    lyButoane->addWidget(ButonWrite);
    lyButoane->addWidget(ButonWriteV2);
    lyButoane->addWidget(ButonRead);
    if (invizibil)lyButoane->addWidget(ButonAfisare);
    if (!invizibil)lyButoane->addWidget(ButonReAfisare);
    lyButoane->addWidget(ButonExporta);
    lyButoane->addWidget(ButonIesire);
    lyButoane->addStretch();

    lyCosTabel->addWidget(statusCos);
    lyCosTabel->addWidget(listaCos);

    lyDispTabel->addWidget(statusDisp);
    lyDispTabel->addWidget(listaDisp);

    lyTotal->addLayout(lyCosTabel);
    lyTotal->addLayout(lyButoane);
    if (!invizibil)lyTotal->addLayout(lyDispTabel);

    lyTotal->addStretch();
    widTotal->setLayout(lyTotal);
    widTotal->show();
}

void Cos_GUI::conectare(){
    cont.adauga_suspect(this);
    QObject::connect(ButonAfisare,&QPushButton::clicked,[&](){
        invizibil=false;
        widTotal->close();
        delete(widTotal);
        initializare();
        conectare();
        afisare_cos();
        afisare_disponibil();
    });

    QObject::connect(ButonReAfisare,&QPushButton::clicked,[&](){
        invizibil=true;
        widTotal->close();
        delete(widTotal);
        initializare();
        conectare();
        afisare_cos();
        afisare_disponibil();
    });

    QObject::connect(ButonAdauga,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de adaugare");
        //widTotal->close();
        adauga_cos();
        afisare_cos();
        if(!invizibil)afisare_disponibil();
    });

    QObject::connect(ButonGolire,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de golire");
        int btn=QMessageBox::warning(nullptr,"AVERTISMENT","Cosul va fi golit!\nSunteti sigur de aceasta operatiune?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes)cont.sterge_tot_wishlist(wish);
        afisare_cos();
        afisare_disponibil();
        //widTotal->close();
    });

    QObject::connect(ButonGenerare,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de generare");
        //widTotal->close();
        generare_cos();
        afisare_cos();
        afisare_disponibil();
    });

    QObject::connect(ButonExporta,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de export");
        exporta_cos();
        //widTotal->close();

    });

    QObject::connect(ButonIesire,&QPushButton::clicked,[&](){
        int btn=QMessageBox::warning(nullptr,"Iesire", "Fereastra se va inchide!\nSunteti sigura de aceasta operatiune",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes) {
            widTotal->close();
            delete(widTotal);
        }
    });

    QObject::connect(listaCos,&QListWidget::itemSelectionChanged,[&](){
        QString textul=listaCos->selectedItems().at(0)->text();
        string denumire=textul.toStdString();
        if(!denumire.empty())afisare_date(denumire);
    });


    QObject::connect(listaDisp,&QListWidget::itemSelectionChanged,[&](){
        //QString textul=listaDisp->selectedItems().at(0)->text();
        //string denumire=textul.toStdString();
        //if(!denumire.empty())afisare_date(denumire,true);
        //afisare_cos();
        //afisare_disponibil();
        auto selectie=listaDisp->selectedItems();
        if(!selectie.isEmpty()){
            auto select=selectie.at(0);
            QString textul=select->text();
            string denumire=textul.toStdString();
            if(cont.cauta_in_lista(rep,denumire)!=-1)
                afisare_date(denumire,true);
            else QMessageBox::critical(nullptr,"EROARE","Oferta nu mai exista in baza de date");
        }
    });

    QObject::connect(ButonWrite,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de export");
        auto* crud= new CosCRUDGUI{rep,cont,wish};
        //widTotal->close();

    });

    QObject::connect(ButonWriteV2,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de export");
        auto* crud= new CosV2CRUDGUI{rep,cont,wish};
        //widTotal->close();

    });

    QObject::connect(ButonRead,&QPushButton::clicked,[&](){
        //QMessageBox::information(nullptr, "Info", "acesta e butonul de export");
        auto* crud= new CosReadOnlyGUI{rep,cont,wish};
        //widTotal->close();

    });
}

void Cos_GUI::alocare(){
    widTotal= new QWidget;
    lyTotal= new QHBoxLayout;

    lyButoane= new QVBoxLayout;
    lyCosTabel= new QVBoxLayout;
    lyDispTabel= new QVBoxLayout;

    ButonAdauga= new QPushButton{"&ADAUGA IN COS"};
    ButonGolire=new QPushButton{"&GOLIRE COS"};
    ButonGenerare=new QPushButton{"&GENERARE COS"};
    ButonAfisare=new QPushButton{"&AFISARE OFERTE DISPONIBILE"};
    ButonWrite=new QPushButton{"&COS CRUD"};
    ButonWriteV2=new QPushButton{"&COS CRUD V2"};
    ButonRead=new QPushButton{"&COS READ"};
    ButonReAfisare=new QPushButton{"&RESTRANGE TABEL"};;
    ButonExporta=new QPushButton{"&EXPORTA"};
    ButonIesire=new QPushButton{"&IESIRE COS"};

    statusCos= new QLabel{"OFERTE IN COS: "+ QString::number(cont.get_numar_oferte(wish))};
    statusDisp=new QLabel{"OFERTE DISPONIBILE: "+ QString::number(cont.get_numar_oferte(rep)-cont.get_numar_oferte(wish))};

    listaCos= new QListWidget;
    listaDisp= new QListWidget;
}

void Cos_GUI::afisare_cos() {
    statusCos->setText("OFERTE IN COS: "+ QString::number(cont.get_numar_oferte(wish)));
    listaCos->clear();
    vector<Oferta>& lista_afisare=cont.get_lista_repo(wish);
    for(const auto& el:lista_afisare){
        auto* item=new QListWidgetItem{QString::fromStdString(el.get_denumire())};
        listaCos->addItem(item);
    }
}

void Cos_GUI::afisare_disponibil() {
    listaDisp->clear();
    statusDisp->setText("OFERTE DISPONIBILE: "+ QString::number(cont.get_numar_oferte(rep)-cont.get_numar_oferte(wish)));
    vector<Oferta>& lista_repo=cont.get_lista_repo(rep);
    for(const auto& el:lista_repo){
        try{
            cont.validare(wish,el.get_denumire(),el.get_destinatie(),el.get_tip(),std::to_string(el.get_pret()));
            auto* item=new QListWidgetItem{QString::fromStdString(el.get_denumire())};
            listaDisp->addItem(item);
        }
        catch(const ExceptieValidare& err){
            continue;
        }
    }
}

void Cos_GUI::adauga_cos() {
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
         afisare_cos();
         afisare_disponibil();
     });

     QObject::connect(ButonSecundar,&QPushButton::clicked,[widAdauga](){
         widAdauga->close();
     });
}

void Cos_GUI::generare_cos(){
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
            afisare_cos();
            afisare_disponibil();

        });

        QObject::connect(ButonSecundar,&QPushButton::clicked,[widGen](){
            widGen->close();
        });
}

void Cos_GUI::exporta_cos(){
    auto* boxExp=new QLineEdit;

    auto* formExp=new QFormLayout;

    auto* widExp=new QWidget;
    auto* lyExp=new QVBoxLayout;

    auto* lyExpButoane=new QHBoxLayout;

    auto* ButonPrincipal= new QPushButton{"&EXPORTA CSV"};
    auto* ButonSecundar= new QPushButton{"&EXPORTA HTML"};
    auto* ButonRevocare= new QPushButton{"&REVOCARE"};

    lyExpButoane->addWidget(ButonPrincipal);
    lyExpButoane->addWidget(ButonSecundar);
    lyExpButoane->addWidget(ButonRevocare);
    lyExpButoane->addStretch();

    formExp->addRow("NUMELE FISIERULUI:",boxExp);

    lyExp->addLayout(formExp);
    lyExp->addLayout(lyExpButoane);
    widExp->setLayout(lyExp);

    widExp->show();

    QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,widExp,boxExp](){
        QString textul=boxExp->text();
        string nume=textul.toStdString();
        if(nume.empty())QMessageBox::critical(nullptr,"EROARE","Numele fisierului nu trebuie sa fie vid!");
        else{
            nume+=".csv";
            if(cont.get_numar_oferte(wish)==0)QMessageBox::critical(nullptr,"EROARE","Nu se poate exporta un cos gol!");
            else{
                cont.salveaza_fisier_wish(wish,nume);
                QMessageBox::information(nullptr,"Info","Cosul a fost salvat cu succes in "+QString::fromStdString(nume));
            }
        }
        widExp->close();
    });

    QObject::connect(ButonSecundar,&QPushButton::clicked,[&,widExp,boxExp](){
        QString textul=boxExp->text();
        string nume=textul.toStdString();
        if(nume.empty())QMessageBox::critical(nullptr,"EROARE","Numele fisierului nu trebuie sa fie vid!");
        else {
            nume += ".html";
            if (cont.get_numar_oferte(wish) == 0)
                QMessageBox::critical(nullptr, "EROARE", "Nu se poate exporta un cos gol!");
            else {
                cont.salveaza_fisier_wish(wish, nume);
                QMessageBox::information(nullptr, "Info",
                                         "Cosul a fost salvat cu succes in " + QString::fromStdString(nume));
            }
        }
        widExp->close();
    });

    QObject::connect(ButonRevocare,&QPushButton::clicked,[widExp](){
        widExp->close();
    });
}

void Cos_GUI::afisare_date(string& denumire,bool cu_modificare){
    auto* boxDenumire=new QLineEdit;
    auto* boxDestinatie=new QLineEdit;
    auto* boxTip=new QLineEdit;
    auto* boxPret=new QLineEdit;

    auto* lyDate=new QFormLayout;
    auto* widDate=new QWidget;

    auto* lyBut=new QHBoxLayout;
    auto* ButonPrincipal=new QPushButton{"&ADAUGA IN COS"};
    auto* ButonSecundar=new QPushButton{"&REVOCARE"};

    auto* lyTot=new QVBoxLayout;

    lyDate->addRow("DENUMIRE:",boxDenumire);
    lyDate->addRow("DESTINATIE:",boxDestinatie);
    lyDate->addRow("TIP:",boxTip);
    lyDate->addRow("PRET:",boxPret);
    lyTot->addLayout(lyDate);
    if(cu_modificare){

        lyBut->addWidget(ButonPrincipal);
        lyBut->addWidget(ButonSecundar);
        lyTot->addLayout(lyBut);
    }

    widDate->setLayout(lyTot);

    Oferta& of=cont.oferta_cu_poz(rep,cont.cauta_in_lista(rep,denumire));

    boxDenumire->setText(QString::fromStdString(of.get_denumire()));
    boxDestinatie->setText(QString::fromStdString(of.get_destinatie()));
    boxTip->setText(QString::fromStdString(of.get_tip()));
    boxPret->setText(QString::number(of.get_pret()));

    widDate->show();

    if(cu_modificare){

        QObject::connect(ButonPrincipal,&QPushButton::clicked,[&,boxDenumire,widDate](){
            QString textul=boxDenumire->text();
            string denumire=textul.toStdString();
            cont.adauga_oferta_in_wishlist(wish,cont.oferta_cu_poz(rep,cont.cauta_in_lista(rep,denumire)));
            widDate->close();
            afisare_cos();
            afisare_disponibil();
        });

        QObject::connect(ButonSecundar,&QPushButton::clicked,[&,widDate](){
            widDate->close();
        });
    }
}

void CosCRUDGUI::initializare() {
    mainWid= new QWidget;
    mainLy= new QHBoxLayout;

    butLy= new QVBoxLayout;
    butGol= new QPushButton{"&Golire cos"};
    butGen= new QPushButton{"&Generare cos"};;

    model=new ModelLista{cont.get_lista_repo(wish), nullptr};
    lista= new QListView{};
    lista->setModel(model);

    butLy->addStretch();
    butLy->addWidget(butGol);
    butLy->addWidget(butGen);
    butLy->addStretch();

    mainLy->addWidget(lista);
    mainLy->addLayout(butLy);
    mainWid->setLayout(mainLy);

    mainWid->show();
}

void CosCRUDGUI::conectare() {

    cont.adauga_suspect(this);

    QObject::connect(butGol,&QPushButton::clicked,[&](){
        int btn=QMessageBox::warning(nullptr,"AVERTISMENT","Cosul va fi golit!\nSunteti sigur de aceasta operatiune?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes){
            cont.sterge_tot_wishlist(wish);
            //afisare_cos();
            model->set_Oferte(cont.get_lista_repo(wish));
        }
    });

    QObject::connect(butGen,&QPushButton::clicked,[&](){
        generare_cos();
        //afisare_cos();
    });
}

void CosCRUDGUI::generare_cos(){
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
        //afisare_cos();
        model->set_Oferte(cont.get_lista_repo(wish));
    });

    QObject::connect(ButonSecundar,&QPushButton::clicked,[widGen](){
        widGen->close();
    });
}

void CosCRUDGUI::afisare_cos() {
    /*
    lista->clear();
    vector<Oferta>& lista_afisare=cont.get_lista_repo(wish);
    for(const auto& el:lista_afisare){
        auto* item=new QListWidgetItem{QString::fromStdString(el.get_denumire())};
        lista->addItem(item);
    }
    */
    model->removeRows(0, model->rowCount());
    vector<Oferta>& lista_afisare=cont.get_lista_repo(wish);
    int poz=0;
    for(const auto& el:lista_afisare){
        model->insertRow(model->rowCount());
        auto index=model->index(poz);
        model->setData(index,QString::fromStdString(el.get_denumire()));
        poz++;
    }
}

void CosReadOnlyGUI::paintEvent(QPaintEvent *ev) {
    srand(time(NULL));
    QPainter p{this};
    //p.drawLine(0,0,width(),height());
        int poz = 0;
    //qDebug()<<"dim paint "<<QString::number(width())<<" "<<QString::number(height())<<"\n";
        for (auto &el:cont.get_lista_repo(wish)) {
            p.drawRect(lista[poz].get_X(), lista[poz].get_Y(), lista[poz].get_lung(),lista[poz].get_lat());
            p.drawText(lista[poz].get_X() + lista[poz].get_lung() / 2, lista[poz].get_Y() + lista[poz].get_lat() / 2,
                       QString::fromStdString(el.get_denumire()));
            poz++;
            //qDebug()<<QString::fromStdString(el.get_denumire())<<" "<<QString::number(lista[poz].get_X())<<" "<<QString::number(lista[poz].get_Y())<<" "<<QString::number(lista[poz].get_X()+lista[poz].get_lung())<<" "<<QString::number(lista[poz].get_Y()+lista[poz].get_lat())<<"\n";
        }

}

vector<Figuri> CosReadOnlyGUI::calculeaza() {
    vector<Figuri> lista_fig;
    int creat=1;
    int max=cont.get_numar_oferte(wish);
    while(lista_fig.size()<=max)
    {
        //qDebug()<<"dim cal "<<QString::number(width())<<" "<<QString::number(height())<<"\n";
        int inceputX=rand()%width();
        int inceputY=rand()%height();
        int lung=rand()%((width()-inceputX));
        int lat=rand()%((height()-inceputY));
        Figuri fig{inceputX,inceputY,lung,lat};
        if(fara_coliziuni(lista_fig,fig)){
            lista_fig.push_back(fig);
            creat++;
        }
    }
    return lista_fig;
}

bool CosReadOnlyGUI::fara_coliziuni(vector<Figuri> &lista, Figuri &fig) {
    bool bun=true;
    for(auto& el:lista){
        ///daca unul din pct figurii se afla in alta figura existenta
        if((fig.get_Y()>el.get_Y()&&fig.get_Y()<el.get_Y()+el.get_lat()) &&
                (fig.get_X()>el.get_X() && fig.get_X()< el.get_X()+el.get_lung())) bun=false;//pct stg-sus se afla in alta figura
        if((fig.get_Y()+fig.get_lat()>el.get_Y()&&fig.get_Y()+fig.get_lat()<el.get_Y()+el.get_lat()) &&
                (fig.get_X()>el.get_X() && fig.get_X()< el.get_X()+el.get_lung())) bun=false;//pct pct stg-jos se afla in alta figura
        if((fig.get_X()+fig.get_lung()>el.get_X() && fig.get_X()+fig.get_lung()< el.get_X()+el.get_lung()) &&
                (fig.get_Y()>el.get_Y()&&fig.get_Y()<el.get_Y()+el.get_lat()) )bun=false;//pct pct dr-sus se afla in alta figura
        if((fig.get_X()+fig.get_lung()>el.get_X() && fig.get_X()+fig.get_lung()< el.get_X()+el.get_lung()) &&
                (fig.get_Y()+fig.get_lat()>el.get_Y()&&fig.get_Y()+fig.get_lat()<el.get_Y()+el.get_lat()) )bun=false;//pct pct dr-jos se afla in alta figura

        ///daca pct unei figuri existente se afla in figura noua
        if((el.get_Y()>fig.get_Y()&&el.get_Y()<fig.get_Y()+fig.get_lat()) &&
                (el.get_X()>fig.get_X() && el.get_X()< fig.get_X()+fig.get_lung())) bun=false;//pct stg-sus se afla in alta figura
        if((el.get_Y()+el.get_lat()>fig.get_Y()&&el.get_Y()+el.get_lat()<fig.get_Y()+fig.get_lat()) &&
                (el.get_X()>fig.get_X() && el.get_X()< fig.get_X()+fig.get_lung())) bun=false;//pct pct stg-jos se afla in alta figura
        if((el.get_X()+el.get_lung()>fig.get_X() && el.get_X()+el.get_lung()< fig.get_X()+fig.get_lung()) &&
                (el.get_Y()>fig.get_Y()&&el.get_Y()<fig.get_Y()+fig.get_lat()) )bun=false;//pct pct dr-sus se afla in alta figura
        if((el.get_X()+el.get_lung()>fig.get_X() && el.get_X()+el.get_lung()< fig.get_X()+fig.get_lung()) &&
                (el.get_Y()+el.get_lat()>fig.get_Y()&&el.get_Y()+el.get_lat()<fig.get_Y()+fig.get_lat()) )bun=false;//pct pct dr-jos se afla in alta figura

        /// intersectia dintre figuri
        /* de adaugat */
        if( (fig.get_X()>el.get_X() && fig.get_X()<el.get_X()+el.get_lung()) && (el.get_Y()>fig.get_Y() && el.get_Y()<fig.get_Y()+fig.get_lat())) bun=false; //fig intersecteaza vertical alta figura
        if( (el.get_X()>fig.get_X() && el.get_X()<fig.get_X()+fig.get_lung()) && (fig.get_Y()>el.get_Y() && fig.get_Y()<el.get_Y()+el.get_lat())) bun=false; //fig intersecteaza orizontal alta figura
        if(!bun) break;
    }
    return bun;
}

void CosV2CRUDGUI::initializare() {
    mainWid= new QWidget;
    mainLy= new QHBoxLayout;

    butLy= new QVBoxLayout;
    butGol= new QPushButton{"&Golire cos"};
    butGen= new QPushButton{"&Generare cos"};;

    tabel= new QTableWidget;

    butLy->addStretch();
    butLy->addWidget(butGol);
    butLy->addWidget(butGen);
    butLy->addStretch();

    mainLy->addWidget(tabel);
    mainLy->addLayout(butLy);
    mainWid->setLayout(mainLy);

    mainWid->show();
}

void CosV2CRUDGUI::conectare() {

    cont.adauga_suspect(this);

    QObject::connect(butGol,&QPushButton::clicked,[&](){
        int btn=QMessageBox::warning(nullptr,"AVERTISMENT","Cosul va fi golit!\nSunteti sigur de aceasta operatiune?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(btn==QMessageBox::Yes){
            cont.sterge_tot_wishlist(wish);
            afisare_cos();
            //model->set_Oferte(cont.get_lista_repo(wish));
        }
    });

    QObject::connect(butGen,&QPushButton::clicked,[&](){
        generare_cos();
        //afisare_cos();
    });
}

void CosV2CRUDGUI::generare_cos(){
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
        afisare_cos();
        //model->set_Oferte(cont.get_lista_repo(wish));
    });

    QObject::connect(ButonSecundar,&QPushButton::clicked,[widGen](){
        widGen->close();
    });
}

void CosV2CRUDGUI::afisare_cos() {
    auto lista_oferte=cont.get_lista_repo(wish);
    tabel->clear();
    tabel->setColumnCount(4);
    tabel->setRowCount((int)lista_oferte.size());
    int poz_lin=0;
    for (const auto& el: lista_oferte){
        tabel->setItem(poz_lin,0,new QTableWidgetItem(QString::fromStdString(el.get_denumire())));
        tabel->setItem(poz_lin,1,new QTableWidgetItem(QString::fromStdString(el.get_destinatie())));
        tabel->setItem(poz_lin,2,new QTableWidgetItem(QString::fromStdString(el.get_tip())));
        tabel->setItem(poz_lin,3,new QTableWidgetItem(QString::number(el.get_pret())));
        poz_lin++;
    }
    //tabel->removeColumn(0);
    /*
    model->removeRows(0, model->rowCount());
    vector<Oferta>& lista_afisare=cont.get_lista_repo(wish);
    int poz=0;
    for(const auto& el:lista_afisare){
        model->insertRow(model->rowCount());
        auto index=model->index(poz);
        model->setData(index,QString::fromStdString(el.get_denumire()));
        poz++;
    }
     */
}