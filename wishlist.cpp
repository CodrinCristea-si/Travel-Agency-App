#include "wishlist.h"

void Wishlist::salveaza(string nume_fisier){
    std::ofstream fout(nume_fisier);
    std::string cvs=".csv";
    std::string html=".html";
    if (nume_fisier.find(cvs)!=std::string::npos)
        for(const auto& of:lista){
            fout<<of.get_denumire()<<","<<of.get_destinatie()<<","<<of.get_tip()<<","<<of.get_pret()<<std::endl;
        }
    if(nume_fisier.find(html)!=std::string::npos)
        for(const auto& of:lista){
            fout<<of.get_denumire()<<" "<<of.get_destinatie()<<" "<<of.get_tip()<<" "<<of.get_pret()<<"<br>";
        }
    fout.close();
}