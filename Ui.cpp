#include "Ui.h"
using std::cout;
using std::cin;
using std::string;
using std::endl;
void Ui::creeaza_meniu(const int nr) {
    cout<<"Elemente in cos "<<nr<<endl;
	cout << "Introduceti una dintre optiunile de mai jos:" << endl;
	cout << "1-pentru a adauga o oferta" << endl;
	cout << "2-pentru a sterge o oferta" << endl;
	cout << "3-pentru a modifica o oferta" << endl;
	cout << "4-pentru a cauta o oferta" << endl;
	cout << "5-pentru a afisa toate ofertele" << endl;
	cout << "6-pentru a filtra ofertele" << endl;
	cout << "7-pentru a sorta ofertele" << endl;
	cout << "8-pentru a accesa meniul de la cos" << endl;
    cout << "9-pentru a afisa lista de oferte dupa fiecare tip" << endl;
    cout << "10-pentru a aplica undo" << endl;
	cout << "0-pentru a iesi" << endl;
	cout << "Optiunea dumneavoastra :" << endl;
}
void Ui::creeaza_meniu_wish(const int nr){
    cout<<"Elemente in cos "<<nr<<endl;
    cout << "Introduceti una dintre optiunile de mai jos:" << endl;
    cout << "1-pentru a adauga o oferta in cos" << endl;
    cout << "2-pentru a sterge sterge tot cosul" << endl;
    cout << "3-pentru a afisa tot cosul" << endl;
    cout << "4-pentru a genera un cos" << endl;
    cout << "5-pentru a salva cosul intr-un fisier" << endl;
    cout << "0-pentru a iesi" << endl;
    cout << "Optiunea dumneavoastra :" << endl;
}
void Ui::meniu() {
    srand((unsigned)time(NULL));
    float probabilitate=rand()%100+1;
    cout<<probabilitate<< " si "<< probabilitate/(float)100<<endl;
    //ExceptionRepo rep{0};
	Repository rep;
	//RepositoryFile rep{"repo.txt"};
	Controller cont;
	Wishlist wish;
	cont.citeste_fisier_repo(rep,"repo.txt");
	while (true) {
	    try{
		string optiune1;
		this->creeaza_meniu(cont.get_numar_oferte(wish));
		cin >> optiune1;
        if(std::any_of(optiune1.begin(),optiune1.end(),[](char c){return !(c>='0'&&c<='9');})) cout<<"Optiune invalida!"<<endl;
        else {
            int optiune=stoi(optiune1);
            if (optiune == 1)this->adaugare_oferta(rep, cont);
            else if (optiune == 2)this->stergere_oferta(rep, cont);
            else if (optiune == 3)this->modificare_oferta(rep, cont);
            else if (optiune == 4)this->cautare_oferta(rep, cont);
            else if (optiune == 5)this->afisare_toate(cont.get_lista_repo(rep));
            else if (optiune == 6)this->filtrare_lista(rep, cont);
            else if (optiune == 7)this->sortare_lista(rep, cont);
            else if (optiune == 8)this->meniu_wishlist(wish,rep, cont);
            else if (optiune == 9)this->afiseaza_dictionar(rep, cont);
            else if (optiune == 10)this->do_undo(cont);
            else if (optiune == 0)break;
            else cout << "Optiune invalida" << endl;
        }
	    }catch(const ExceptieRepository& err){
	        cout<<err.get_mesaj_eroare()<<endl;
	    }
	}
    cont.salveaza_fisier_repo(rep,"repo.txt");
}
void Ui::adaugare_oferta(AbstractRepo& rep,Controller& cont){
	string denumire, destinatie, tip;
	string pret;
	cout << "Introduceti denumirea :" << endl;
	cin >> denumire;
	cout << "Introduceti destinatie :" << endl;
	cin >> destinatie;
	cout << "Introduceti tip :" << endl;
	cin >> tip;
	cout << "Introduceti pret :" << endl;
	cin >> pret;

	try {
		cont.validare(rep, denumire, destinatie, tip, pret);
		cont.adauga_in_lista(rep, denumire, destinatie, tip, stof(pret));
		cout << "Oferta adaugata cu succes" << endl;
	}
	catch (const ExceptieValidare& err) {
		cout<<err.get_mesaj_eroare()<<endl;
	}
	//return rep;
}

void Ui::stergere_oferta(AbstractRepo& rep, Controller& cont) {
	string denumire;
	cout << "Introduceti denumirea :" << endl;
	cin >> denumire;
	const int poz = cont.cauta_in_lista(rep, denumire);
		try {
			if (poz != -1) {
				const Oferta& of = cont.oferta_cu_poz(rep, poz);
				cont.validare(rep, denumire, of.get_destinatie(), of.get_tip(), std::to_string(of.get_pret()));
			}
			else cout << "Oferta nu exista" << endl;
		}
		catch (const ExceptieValidare& err) {
			if (err.get_cod() == 8) {
				cont.sterge_din_lista(rep, denumire);
				cout << "Oferta stearsa cu succes" << endl;
			}
			else cout<<err.get_mesaj_eroare()<<endl;
		}
		//return rep;
}

void Ui::modificare_oferta(AbstractRepo& rep,Controller& cont) {
	string denumire;
	cout << "Introduceti denumirea: " << endl;
	cin >> denumire;
	const int poz = cont.cauta_in_lista(rep, denumire);
	if (poz != -1) {
		cout << "Ce ati dori sa modificati?" << endl;
		cout << "1-denumirea" << endl;
		cout << "2-destinatia" << endl;
		cout << "3-tip" << endl;
		cout << "4-pret" << endl;
		cout << "Optiunea dumneavoastra :" << endl;
		int optiune;
		cin >> optiune;
		if (optiune == 1) {
			string denumire_nou;
			cout << "Introduceti denumirea noua ";
			cin >> denumire_nou;
			const Oferta& of = cont.oferta_cu_poz(rep, poz);
			try {
				cont.validare(rep, denumire_nou, of.get_destinatie(), of.get_tip(), std::to_string(of.get_pret()));
				cont.modifica(rep, denumire, optiune, denumire_nou);
				cout << "Oferta modificata cu succes" << endl;
			}
			catch (const ExceptieValidare& err) {
                cout<<err.get_mesaj_eroare()<<endl;
			}
		}
		else if (optiune == 2) {
			string destinatie_nou;
			cout << "Introduceti destinatia noua ";
			cin >> destinatie_nou;
			const Oferta& of = cont.oferta_cu_poz(rep, poz);
			try {
				cont.validare(rep, of.get_denumire(), destinatie_nou, of.get_tip(), std::to_string(of.get_pret()));
			}
			catch (const ExceptieValidare& err) {
				if (err.get_cod() == 8) {
					cont.modifica(rep, denumire, optiune, destinatie_nou);
					cout << "Oferta modificata cu succes" << endl;
				}
				else cout<<err.get_mesaj_eroare()<<endl;

			}
		}
		else if (optiune == 3) {
			string tip_nou;
			cout << "Introduceti tipul nou ";
			cin >> tip_nou;
			const Oferta& of = cont.oferta_cu_poz(rep, poz);
			try {
				cont.validare(rep, of.get_denumire(), of.get_denumire(),tip_nou, std::to_string(of.get_pret()));
			}
			catch (const ExceptieValidare& err) {
                if (err.get_cod() == 8) {
				    cont.modifica(rep, denumire, optiune, tip_nou);
				    cout << "Oferta modificata cu succes" << endl;
				}
                else cout<<err.get_mesaj_eroare()<<endl;
			}
		}
		else if (optiune == 4) {
			string pret_nou;
			cout << "Introduceti pretul nou ";
			cin >> pret_nou;
			const Oferta& of = cont.oferta_cu_poz(rep, poz);
			try {
				cont.validare(rep, of.get_denumire(), of.get_denumire(), of.get_destinatie(), pret_nou);
			}
			catch (const ExceptieValidare& err) {
                if (err.get_cod() == 8) {
				    cont.modifica(rep, denumire, optiune, pret_nou);
				    cout << "Oferta modificata cu succes" << endl;
				}
                else cout<<err.get_mesaj_eroare()<<endl;
			}
		}
	}
	else cout << "Oferta nu exista" << endl;
	//return rep;
}

void Ui::afiseaza_oferta(const Oferta& of) {
	cout << "Oferta cu denumirea " << of.get_denumire() << " destinatia " << of.get_destinatie() << " tipul " << of.get_tip() << " si pretul " << of.get_pret() << endl;
}

void Ui::afisare_toate(vector<Oferta>& rep) {
	cout << "Sunt introduse " << rep.size() << " oferte " << endl;
	for (const auto& of:rep)
	{
		this->afiseaza_oferta(of);
	}
}
void Ui::cautare_oferta(AbstractRepo& rep,Controller& cont) {
	string denumire;
	cout<< "Introduceti denumirea ofertei: " << endl;
	cin >> denumire;
	const int poz = cont.cauta_in_lista(rep, denumire);
	if (poz != -1)afiseaza_oferta(cont.oferta_cu_poz(rep, poz));
	else cout << "Oferta nu exista" << endl;
}

void Ui::filtrare_lista(AbstractRepo& rep, const Controller& cont){
	string filtrare;
	int optiune;
	cout << "Faceti filtru dupa :\n1- destinatie\n2- pret\nOptiunea: " << endl;
	cin >> optiune;
	cout << "Introduceti filtrul :" << endl;
	cin >> filtrare;
	if (optiune == 1) {
		vector<Oferta> filt = cont.filtru(rep, filtrare, compara_destinatie);
		this->afisare_toate(filt);
	}
	else if (optiune == 2) {
        vector<Oferta> filt = cont.filtru(rep, filtrare, compara_pret);
		this->afisare_toate(filt);
	}
	else cout << "Optiune invalida" << endl;
}

void Ui::sortare_lista(AbstractRepo& rep,const Controller& cont) {
	int optiune,rev;
	cout << "Faceti sortare dupa :\n1- denumire\n2- destinatie\n3-tip+pret\nOptiunea: " << endl;
	cin >> optiune;
	cout << "Ordinea :\n0- crescator\n1- descrescator\nOptiunea: " << endl;
	cin >> rev;
	if (optiune == 1) {
		vector<Oferta> sorta = cont.sortare(rep, rev, compara_oferta_denumire);
		this->afisare_toate(sorta);
	}
	else if (optiune == 2) {
        vector<Oferta> sorta = cont.sortare(rep, rev, compara_oferta_destinatie);
		this->afisare_toate(sorta);
	}
	else if (optiune == 3) {
        vector<Oferta> sorta = cont.sortare(rep, rev, compara_oferta_tip_si_pret);
		this->afisare_toate(sorta);
	}
	else cout << "Optiune invalida" << endl;
}
void Ui::meniu_wishlist(Wishlist& wish,AbstractRepo& rep,Controller& cont){
    while (true) {
        string optiune1;
        creeaza_meniu_wish(cont.get_numar_oferte(wish));
        cin >> optiune1;
        if(std::any_of(optiune1.begin(),optiune1.end(),[](char c){return !(c>='0'&&c<+'9');})) cout<<"Optiune invalida!"<<endl;
        else {
            int optiune=stoi(optiune1);
            if (optiune == 1)this->adauga_wishlist(wish,rep, cont);
            else if (optiune == 2)this->sterge_tot_wish(wish, cont);
            else if (optiune == 3)this->afiseaza_wishlist(wish, cont);
            else if (optiune == 4)this->genereaza_wish(wish,rep, cont);
            else if (optiune == 5)this->salveaza_wish_fisier(wish,cont);
            else if (optiune == 0)break;
            else cout << "Optiune invalida" << endl;
        }
    }
}
void Ui::adauga_wishlist(Wishlist& wish,AbstractRepo& rep,Controller& cont){
    string denumire;
    cout<<"Introduceti denumire ofertei: ";
    cin>>denumire;
    try {
        const int poz=cont.cauta_in_lista(rep,denumire);
        Oferta& of=cont.oferta_cu_poz(rep,poz);
        cont.validare(wish, denumire, of.get_destinatie(), of.get_tip(), std::to_string(of.get_pret()));
        cont.adauga_oferta_in_wishlist(wish,of);
        cout << "Oferta adaugata cu succes" << endl;
    }
    catch (const ExceptieValidare& err) {
        cout<<err.get_mesaj_eroare()<<endl;
    }catch (const ExceptieRepository& err) {
		err.get_mesaj_eroare();
        cout<<"Oferta inexistenta"<<endl;
    }

}

void Ui::sterge_tot_wish(Wishlist& wish,Controller& cont){
    cont.sterge_tot_wishlist(wish);
    cout<<"Cos sters cu succes"<<endl;
}

void Ui::afiseaza_wishlist(Wishlist& wish,Controller& cont){
    afisare_toate(cont.get_lista_repo(wish));
}
void Ui::genereaza_wish(Wishlist& wish,AbstractRepo& rep,Controller& cont){
    cont.sterge_tot_wishlist(wish);
    int nr_of;
    cout<<"Introduceti numarul de oferte: ";
    cin>>nr_of;
    if(nr_of>cont.get_numar_oferte(rep)) cout<<"Numarul este prea mare";
    else if(nr_of<=0) cout<<"Numarul este prea mic";
    else{
    cont.genereaza_wishlist(wish,rep,nr_of);
    cout<<"Oferte generate si adaugate cu succes"<<endl;}
}
void Ui::salveaza_wish_fisier(Wishlist& wish,Controller& cont){
    string fisier;
    cout<<"Introduceti numele fisierului : "<<endl;
    cin>>fisier;
    cont.salveaza_fisier_wish(wish,fisier);
    cout<<"Date salvate cu succes"<<endl;
}

void Ui::afiseaza_dictionar(AbstractRepo& rep,Controller& cont){
    std::map<string,std::pair<string,int>> lista=cont.dictionar(rep);
    for ( const auto& [cheie,val]:lista){
        cout << "Oferta cu tipul " << cheie<< " este de tipul "<<val.first<<" si apare de "<<val.second<<" ori"<<endl;
    }
}

void Ui::do_undo(Controller& cont){
    try{
        cont.undo();
        cout<<"Undo aplicat cu succes"<<endl;
    }
    catch(const ExceptieRepository& err){
        cout<<err.get_mesaj_eroare()<<endl;
    }
}