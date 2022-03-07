# include "utils.h"

bool compara_destinatie(const Oferta& of,const std::string& filt) {
	if (of.get_destinatie() == filt)return true;
	return false;
}

bool compara_pret(const Oferta& of, const std::string& filt) {
	if (of.get_pret() < stof(filt))return true;
	return false;
}
bool compara_oferta_destinatie(const Oferta& of, const Oferta& of1) {
	if (of.get_destinatie() > of1.get_destinatie())return true;
	return false;
}

bool compara_oferta_denumire(const Oferta& of, const Oferta& of1) {
	if (of.get_denumire() > of1.get_denumire())return true;
	return false;
}
bool compara_oferta_tip_si_pret(const Oferta& of, const Oferta& of1) {
	if (of.get_tip() > of1.get_tip())return true;
	else if (of.get_tip() == of1.get_tip() && of.get_pret() > of1.get_pret())return true;
	return false;
}