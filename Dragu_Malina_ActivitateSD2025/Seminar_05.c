//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
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
//	Masina masina;
//	struct Nod* next;
//	struct Nod* prev;
//};
//typedef struct Nod Nod;
//
//struct ListaDubla
//{
//	Nod* first;
//	Nod* last;
//	int nrNoduri;
//};
//typedef struct ListaDubla ListaDubla;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
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
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasiniDeLaInceput(ListaDubla lista) 
//{
//	Nod* p = lista.first;
//	while (p)
//	{
//		afisareMasina(p->masina);
//		p = p->next;
//	}
//}
//
//void afisareListaMasiniDeLaSfarsit(ListaDubla lista) 
//{
//	Nod* p = lista.last;
//	while (p)
//	{
//		afisareMasina(p->masina);
//		p = p->prev;
//	}
//}
//
//void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) 
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->masina = masinaNoua; //shallow copy
//	nou->next = NULL;
//	nou->prev = lista->last;
//	if (lista->last)
//	{
//		lista->last->next = nou;
//	}
//	else
//	{
//		lista->first = nou;
//	}
//	lista->last = nou;
//	lista->nrNoduri++;
//}
//
//void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) 
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->masina = masinaNoua;
//	nou->next = lista->first;
//	nou->prev = NULL;
//	if (lista->first !=NULL)
//	{
//		lista->first->prev = nou;
//	}
//	else
//	{
//		lista->last = nou;
//	}
//	lista->first = nou;
//	lista->nrNoduri++;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) 
//{
//	FILE* f = fopen(numeFisier, "r");
//	ListaDubla lista;
//	lista.first = NULL;
//	lista.last = NULL;
//	lista.nrNoduri = 0;
//	while (!feof(f))
//	{
//		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocareLDMasini(ListaDubla* lista) 
//{
//	Nod* p = lista->first;
//	while (p)
//	{
//		Nod* aux = p;
//		p = p->next;
//		if (aux->masina.model)
//		{
//			free(aux->masina.model);
//		}
//		if (aux->masina.numeSofer)
//		{
//			free(aux->masina.numeSofer);
//		}
//		free(aux);
//	}
//	lista->first = NULL;
//	lista->last = NULL;
//	lista->nrNoduri = 0;
//}
//
//float calculeazaPretMediu(ListaDubla lista)
//{
//	if (lista.nrNoduri > 0)
//	{
//		float suma = 0;
//		Nod* p = lista.first;
//		while (p)
//		{
//			suma += p->masina.pret;
//			p = p->next;
//		}
//		return suma / lista.nrNoduri;
//	}
//	return 0;
//}
//
//void stergeMasinaDupaID(ListaDubla* lista, int id) 
//{
//	if (lista)
//	{
//		Nod* p = lista->first;
//		while (p && p->masina.id != id)
//		{
//			p = p->next;
//		}
//		if (p->masina.id == id)
//		{
//			if (p->prev == NULL)
//			{
//				Nod* aux = p->next;
//				lista->first = aux;
//				aux->prev = NULL;
//			}
//			else
//			{
//				if (p->next == NULL)
//				{
//					Nod* aux = p->prev;
//					aux->next = NULL;
//					p->prev = NULL;
//					lista->last = aux;
//				}
//				else
//				{
//					p->next->prev = p->prev;
//					p->prev->next = p->next;
//					p->next = NULL;
//					p->prev = NULL;
//				}
//			}
//		}
//		if (p->masina.model)
//		{
//			free(p->masina.model);
//		}
//		if (p->masina.numeSofer)
//		{
//			free(p->masina.numeSofer);
//		}
//		free(p);
//		lista->nrNoduri--;
//	}
//	return;
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla lista) 
//{
//	Nod* p = lista.first;
//	Nod* maxx = lista.first;
//	while (p)
//	{
//		if (p->masina.pret > maxx->masina.pret)
//		{
//			maxx = p;
//		}
//		p = p->next;
//	}
//	return maxx->masina.numeSofer;
//}
//
//int main() 
//{
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasiniDeLaInceput(lista);
//	printf("=========================================\n");
//	afisareListaMasiniDeLaSfarsit(lista);
//
//	//dezalocareLDMasini(&lista);
//	printf("\n=========================================\n");
//
//	printf("Pretul mediu al masinilor este: %.2f", calculeazaPretMediu(lista));
//	printf("\n=========================================\n");
//
//	//stergeMasinaDupaID(&lista, 5);
//	//afisareListaMasiniDeLaInceput(lista);
//	
//	printf("\n=========================================\n");
// 
//	printf("Numele soferului cu cea mai scumpa masina este: %s", getNumeSoferMasinaScumpa(lista));
//
//	return 0;
//}