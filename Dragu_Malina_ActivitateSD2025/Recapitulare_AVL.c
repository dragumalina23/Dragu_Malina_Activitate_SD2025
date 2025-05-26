#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
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

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int calculeazaInaltimeArbore(Nod * nod)
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

int calculeazaGradAsimetrie(Nod* nod)
{
	int gradStanga = calculeazaInaltimeArbore(nod->stanga);
	int gradDreapta = calculeazaInaltimeArbore(nod->dreapta);

	return (gradStanga - gradDreapta);
}

void rotireLaDreapta(Nod** nod)
{
	Nod* aux = (*nod)->stanga;
	(*nod)->stanga = aux->dreapta;
	aux->dreapta = (*nod);
	(*nod) = aux;
}

void rotireLaStanga(Nod** nod)
{
	Nod* aux = (*nod)->dreapta;
	(*nod)->dreapta = aux->stanga;
	aux->stanga = (*nod);
	(*nod) = aux;
}

void adaugaMasinaInArbore(Nod** nod, Masina masinaNoua)
{
	if ((*nod) != NULL)
	{
		if (masinaNoua.id > (*nod)->info.id)
		{
			adaugaMasinaInArbore(&(*nod)->stanga, masinaNoua);

		}
		else if (masinaNoua.id < (*nod)->info.id)
		{
			adaugaMasinaInArbore(&(*nod)->dreapta, masinaNoua);

		}

		if (calculeazaGradAsimetrie(*nod) == 2)
		{
			if (calculeazaGradAsimetrie((*nod)->stanga) == -1)
			{
				rotireLaStanga(&(*nod)->stanga);
			}
			rotireLaDreapta(nod);
		}
		else if (calculeazaGradAsimetrie(*nod) == -2)
		{
			if (calculeazaGradAsimetrie((*nod)->dreapta) == 1)
			{
				rotireLaDreapta(&(*nod)->dreapta);
			}
			rotireLaStanga(nod);
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
	Nod* aux = NULL;

	while (!feof(f))
	{
		adaugaMasinaInArbore(&aux, citireMasinaDinFisier(f));
	}

	fclose(f);
	return aux;
}

void afisareMasiniDinArboreRSD(Nod* nod) 
{
	if (nod != NULL)
	{
		afisareMasina(nod->info);
		afisareMasiniDinArboreRSD(nod->stanga);
		afisareMasiniDinArboreRSD(nod->dreapta);
	}
}

void dezalocareArboreDeMasini(Nod** nod) 
{
	if ((*nod) != NULL)
	{
		dezalocareArboreDeMasini(&(*nod)->stanga);
		dezalocareArboreDeMasini(&(*nod)->dreapta);

		free((*nod)->info.model);
		free((*nod)->info.numeSofer);
		
		free(*nod);
	}
	(*nod) = NULL;
}

Masina getMasinaByID(Nod* nod, int id)
{
	Masina m;
	m.id = -1;

	if (nod != NULL)
	{
		if (nod->info.id == id)
		{
			m = nod->info;
		}
		else
		{
			if (nod->info.id < id)
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

int determinaNumarNoduri(Nod* nod)
{
	if (nod == NULL)
		return 0;

	return 1 + determinaNumarNoduri(nod->stanga) + determinaNumarNoduri(nod->dreapta);
}


float calculeazaPretTotal(Nod* nod)
{
	if (nod == NULL)
		return 0;

	return nod->info.pret + calculeazaPretTotal(nod->stanga) + calculeazaPretTotal(nod->dreapta);
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
	//afisareMasiniDinArboreRSD(nod);

	Masina masina = getMasinaByID(nod, 3);
	printf("\n===========Masina cautata: ===========\n");
	afisareMasina(masina);

	int nrNoduri = determinaNumarNoduri(nod);
	printf("\n=========== Nr. noduri: %d ===========\n", nrNoduri);

	float pretTotal = calculeazaPretTotal(nod);
	printf("\n=========== Pret total: %.2f ===========\n", pretTotal);

	float pretTotalSofer = calculeazaPretulMasinilorUnuiSofer(nod, "Gigel");
	printf("\n=========== Pret total pentru Gigel: %.2f ===========\n", pretTotalSofer);

	dezalocareArboreDeMasini(&nod);
	return 0;
}