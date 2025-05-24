#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina 
{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod
{
	Masina info;
	struct Nod* dreapta;
	struct Nod* stanga;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) 
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) 
{
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(Nod** nod, Masina masinaNoua) 
{
	if ((*nod) != NULL)
	{
		if (masinaNoua.id > (*nod)->info.id)
		{
			adaugaMasinaInArbore(&(*nod)->dreapta, masinaNoua);
		}
		else if (masinaNoua.id < (*nod)->info.id)
		{
			adaugaMasinaInArbore(&(*nod)->stanga, masinaNoua);
		}
	}
	else
	{
		(*nod) = (Nod*)malloc(sizeof(Nod));
		(*nod)->dreapta = NULL;
		(*nod)->stanga = NULL;
		(*nod)->info = masinaNoua;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) 
{
	FILE* f = fopen(numeFisier, "r");
	Nod* nod = NULL;

	while (!feof(f))
	{
		adaugaMasinaInArbore(&nod, citireMasinaDinFisier(f));
	}

	fclose(f);
	return nod;
}

// parcurgere RSD / SRD / SDR

void afisareArboreRSD(Nod* nod) 
{
	if (nod != NULL)
	{
		afisareMasina(nod->info);
		afisareArboreRSD(nod->stanga);
		afisareArboreRSD(nod->dreapta);
	}
}

void afisareArboreSRD(Nod* nod)
{
	if (nod != NULL)
	{	
		afisareArboreRSD(nod->stanga);
		afisareMasina(nod->info);
		afisareArboreRSD(nod->dreapta);
	}
}

void afisareArboreSDR(Nod* nod)
{
	if (nod != NULL)
	{
		afisareArboreRSD(nod->stanga);
		afisareArboreRSD(nod->dreapta);
		afisareMasina(nod->info);
	}
}

void dezalocareArboreDeMasini(Nod* nod) 
{
	if (nod != NULL)
	{
		dezalocareArboreDeMasini(nod->stanga);
		dezalocareArboreDeMasini(nod->dreapta);

		free(nod->info.model);
		free(nod->info.numeSofer);
		
		free(nod);
	}
	nod = NULL;
}

Masina getMasinaByID(Nod* nod, int id) 
{
	Masina m;

	if (nod != NULL)
	{
		if (nod->info.id == id)
		{
			m = nod->info;
		}
		else
		{
			if (nod->info.id > id)
			{
				m = getMasinaByID(nod->stanga, id);
			}
			else
			{
				m = getMasinaByID(nod->dreapta, id);
			}
		}
	}

	return m;
}

int determinaNumarNoduri(Nod* nod, int nrNoduri) 
{
	if (nod != NULL)
	{
		nrNoduri++;
		if (nod->dreapta != NULL)
		{
			nrNoduri = determinaNumarNoduri(nod->dreapta, nrNoduri);
		}
		if (nod->stanga != NULL)
		{
			nrNoduri = determinaNumarNoduri(nod->stanga, nrNoduri);
		}
	}
	return nrNoduri;
}

int calculeazaInaltimeArbore(Nod* nod) 
{
	if (nod != NULL)
	{
		int inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
		int inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);

		if (inaltimeStanga > inaltimeDreapta)
		{
			return 1 + inaltimeStanga;
		}
		else
		{
			return 1 + inaltimeDreapta;
		}
	}
	else
	{
		return 0;
	}
}

float calculeazaPretTotal(Nod* nod, float pretTotal) 
{
	if (nod != NULL)
	{
		pretTotal += nod->info.pret;
		if (nod->dreapta != NULL)
		{
			pretTotal = calculeazaPretTotal(nod->dreapta, pretTotal);
		}
		if (nod->stanga != NULL)
		{
			pretTotal = calculeazaPretTotal(nod->stanga, pretTotal);
		}
	}

	return pretTotal;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* nod, const char* numeSofer) 
{
	if (nod == NULL)
	{
		return 0;
	}

	float suma = 0;
	if (strcmp(nod->info.numeSofer, numeSofer) == 0)
	{
		suma += nod->info.pret;
	}

	suma += calculeazaPretulMasinilorUnuiSofer(nod->stanga, numeSofer);
	suma += calculeazaPretulMasinilorUnuiSofer(nod->dreapta, numeSofer);

	return suma;
}

int main() 
{
	Nod* nod = citireArboreDeMasiniDinFisier("masini.txt");
	//afisareArboreRSD(nod);

	//dezalocareArboreDeMasini(nod);
	Masina m = getMasinaByID(nod, 3);
	afisareMasina(m);

	int nrNoduri = determinaNumarNoduri(nod, 0);
	printf("\nNumar noduri: %d\n", nrNoduri);

	float pretTotal = calculeazaPretTotal(nod, 0);
	printf("\nPret total: %.2f\n", pretTotal);

	float pretSofer = calculeazaPretulMasinilorUnuiSofer(nod, "Gheorghe");
	printf("\nPret total: %.2f\n", pretSofer);

	int inaltime = calculeazaInaltimeArbore(nod);
	printf("\nInaltime arbore: %d\n", inaltime);

	
	return 0;
}