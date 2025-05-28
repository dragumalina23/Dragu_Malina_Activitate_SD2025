//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//struct Masina 
//{
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct Masina Masina;
//
//struct Nod
//{
//	Masina info;
//	struct Nod* st;
//	struct Nod* dr;
//};
//typedef struct Nod Nod;
//
//Masina citireMasinaFisier(FILE* f)
//{
//	char buffer[100];
//	char sep[3] = ",;\n";
//	Masina m;
//	char* aux;
//
//	fgets(buffer, 100, f);
//	m.id = atoi(strtok(buffer, sep));
//	m.nrUsi = atoi(strtok(NULL, sep));
//	m.pret = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	m.model = (char*)malloc(strlen(aux) + 1);
//	strcpy(m.model, aux);
//
//	aux = strtok(NULL, sep);
//	m.numeSofer = (char*)malloc(strlen(aux) + 1);
//	strcpy(m.numeSofer, aux);
//
//	m.serie = *strtok(NULL, sep);
//
//	return m;
//}
//
//void afisareMasina(Masina m)
//{
//	printf("\nId: %d\n", m.id);
//	printf("Nr usi: %d\n", m.nrUsi);
//	printf("Pret: %.2f\n", m.pret);
//	printf("Model: %s\n", m.model);
//	printf("Nume sofer: %s\n", m.numeSofer);
//	printf("Serie: %c\n", m.serie);
//}
//
//void afisareRSD(Nod* nod)
//{
//	if (nod != NULL)
//	{
//		afisareMasina(nod->info);
//		afisareRSD(nod->st);
//		afisareRSD(nod->dr);
//	}
//}
//
//void rotireDreapta(Nod** nod)
//{
//	Nod* aux = (*nod)->st;
//	(*nod)->st = aux->dr;
//	aux->dr = (*nod);
//	(*nod) = aux;
//}
//
//void rotireStanga(Nod** nod)
//{
//	Nod* aux = (*nod)->dr;
//	(*nod)->dr = aux->st;
//	aux->st = (*nod);
//	(*nod) = aux;
//}
//
//int calculeazaInaltimeArbore(Nod* nod)
//{
//	if (nod != NULL)
//	{
//		int inaltimeStanga = calculeazaInaltimeArbore(nod->st);
//		int inaltimeDreapta = calculeazaInaltimeArbore(nod->dr);
//
//		if (inaltimeStanga > inaltimeDreapta)
//		{
//			return 1 + inaltimeStanga;
//		}
//		else
//		{
//			return 1 + inaltimeDreapta;
//		}
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//int calculeazaGradAsimetrie(Nod* nod)
//{
//	int gradStanga = calculeazaInaltimeArbore(nod->st);
//	int gradDreapta = calculeazaInaltimeArbore(nod->dr);
//
//	return(gradStanga - gradDreapta);
//}
//
//void inserareNodInArbore(Nod** nod, Masina m)
//{
//	if ((*nod) != NULL)
//	{
//		if (m.id < (*nod)->info.id)
//		{
//			inserareNodInArbore(&(*nod)->st, m);
//		}
//		else if (m.id > (*nod)->info.id)
//		{
//			inserareNodInArbore(&(*nod)->dr, m);
//		}
//		if(calculeazaGradAsimetrie(*nod) == 2)
//		{
//			if (calculeazaGradAsimetrie((*nod)->st) == -1)
//			{
//				rotireStanga(&(*nod)->st);
//			}
//			rotireDreapta(nod);
//		}
//		else if (calculeazaGradAsimetrie(*nod) == -2)
//		{
//			if (calculeazaGradAsimetrie((*nod)->dr) == 1)
//			{
//				rotireDreapta(&(*nod)->dr);
//			}
//			rotireStanga(nod);
//		}
//	}
//	else
//	{
//		(*nod) = (Nod*)malloc(sizeof(Nod));
//		(*nod)->dr = NULL;
//		(*nod)->st = NULL;
//		(*nod)->info = m;
//	}
//}
//
//Nod* citesteArboreDinFisier(const char* numeFisier)
//{
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//
//	while (!feof(f))
//	{
//		inserareNodInArbore(&nod, citireMasinaFisier(f));
//	}
//
//	fclose(f);
//	return nod;
//}
//
//void dezalocareArbore(Nod** nod)
//{
//	if ((*nod) != NULL)
//	{
//		dezalocareArbore(&(*nod)->st);
//		dezalocareArbore(&(*nod)->dr);
//
//		free((*nod)->info.numeSofer);
//		free((*nod)->info.model);
//
//		free(*nod);
//	}
//	(*nod) = NULL;
//}
//
//float calculeazaPretulUnuiSofer(Nod* nod, const char* nume)
//{
//	if (nod == NULL)
//	{
//		return 0;
//	}
//
//	float suma = 0;
//	if (strcmp(nod->info.numeSofer, nume) == 0)
//	{
//		suma += nod->info.pret;
//	}
//
//	suma += calculeazaPretulUnuiSofer(nod->st, nume);
//	suma += calculeazaPretulUnuiSofer(nod->dr, nume);
//
//	return suma;
//}
//
//int main()
//{
//	Nod* nod = citesteArboreDinFisier("masini.txt");
//	//afisareRSD(nod);
//
//	float suma = calculeazaPretulUnuiSofer(nod, "Gheorghe");
//	printf("Suma masini: %.2f", suma);
//
//	dezalocareArbore(&nod);
//	return 0;
//}