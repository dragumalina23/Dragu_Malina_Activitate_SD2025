//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina 
//{
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Nod
//{
//	Masina info;
//	struct Nod* dr;
//	struct Nod* st;
//};
//typedef struct Nod Nod;
//
//Masina citireMasinaDinFisier(FILE* file) 
//{
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret= atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) 
//{
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//
//void adaugaMasinaInArbore(Nod** nod, Masina masinaNoua) {
//	if ((*nod) != NULL)
//	{
//		if (masinaNoua.id > (*nod)->info.id) {
//			adaugaMasinaInArbore(&(*nod)->dr, masinaNoua);
//		}
//		else if (masinaNoua.id < (*nod)->info.id)
//			adaugaMasinaInArbore(&(*nod)->st, masinaNoua);
//	}
//	else {
//		(*nod) = (Nod*)malloc(sizeof(Nod));
//		(*nod)->info = masinaNoua;
//		(*nod)->dr = NULL;
//		(*nod)->st = NULL;
//	}
//
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier) 
//{
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while (!feof(f)) {
//		adaugaMasinaInArbore(&nod, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return nod;
//}
//
//
//void afisareMasiniDinArbore(/*arbore de masini*/) 
//{
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//}
//
//void afisarePreOrdine(Nod* rad)
//{
//	if (rad != NULL)
//	{
//		afisareMasina(rad->info);
//		afisarePreOrdine(rad->st);
//		afisarePreOrdine(rad->dr);
//	}
//}
//
//void afisareInOrdine(Nod* rad)
//{
//	if (rad != NULL)
//	{
//		afisareInOrdine(rad->st);
//		afisareMasina(rad->info);
//		afisareInOrdine(rad->dr);
//	}
//}
//
//void dezalocareArboreDeMasini(/*arbore de masini*/) 
//{
//	//sunt dezalocate toate masinile si arborele de elemente
//}
//
//Masina getMasinaByID(Nod * rad, int id) 
//{
//	Masina m;
//	m.id = -1;
//	if (rad != NULL)
//	{
//		if (id < rad->info.id)
//		{
//			return getMasinaByID(rad->st, id);
//		}
//		else if (id > rad->info.id)
//		{
//			return getMasinaByID(rad->dr, id);
//		}
//		else
//		{
//			return rad->info;
//		}
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod* rad) 
//{
//	int nrNoduri = 0;
//	if (rad != NULL)
//	{
//		nrNoduri += determinaNumarNoduri(rad->st);
//		nrNoduri += determinaNumarNoduri(rad->dr);
//		nrNoduri++;
//	}
//	return nrNoduri;
//}
//
//int calculeazaInaltimeArbore(/*arbore de masini*/) 
//{
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	return 0;
//}
//
//float calculeazaPretTotal(/*arbore de masini*/) 
//{
//	//calculeaza pretul tuturor masinilor din arbore.
//	return 0;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) 
//{
//	//calculeaza pretul tuturor masinilor unui sofer.
//	return 0;
//}
//
//int main() 
//{
//	Nod* rad = citireArboreDeMasiniDinFisier("masini.txt");
//	afisarePreOrdine(rad);
//	printf("========================================\n");
//	afisareMasina(getMasinaByID(rad, 5));
//	printf("========================================\n");
//	printf("Nr noduri: %d", determinaNumarNoduri(rad));
//	return 0;
//}