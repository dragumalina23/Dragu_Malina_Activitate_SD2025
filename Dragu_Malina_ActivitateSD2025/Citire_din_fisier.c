#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Masina
{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct Masina Masina;

Masina citireMasinaFisier(FILE* file)
{
	Masina m;
	char buffer[100];
	char sep[4] = ",\n";

	fgets(buffer, 100, file);
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));

	char* aux;
	aux = strtok(NULL, sep);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m.model, aux);

	aux = strtok(NULL, sep);
	m.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m.numeSofer, aux);

	m.serie = strtok(NULL, sep)[0];

	return m;
}

void afisareMasina(Masina m)
{
	printf("Id: %d\n", m.id);
	printf("Numar usi: %d\n", m.nrUsi);
	printf("Pret: %.2f\n", m.pret);
	printf("Model: %s\n", m.model);
	printf("Nume sofer: %s\n", m.numeSofer);
	printf("Serie: %c\n\n", m.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini)
{
	for (int i = 0; i < nrMasini; i++)
	{
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua)
{
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++)
	{
		aux[i] = (*masini)[i];
	}
	aux[(*nrMasini)] = masinaNoua;
	free(*masini);
	(*masini) = aux;
	(*nrMasini)++;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite)
{
	FILE* f = fopen(numeFisier, "r");
	Masina* masini = NULL;
	(*nrMasiniCitite) = 0;

	while (!feof(f))
	{
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(f));
	}
	fclose(f);
	return masini;
}

void dezalocareVectoriMasini(Masina** vector, int* nrMasini)
{
	for (int i = 0; i < (*nrMasini); i++)
	{
		if ((*vector)[i].model != NULL)
		{
			free((*vector)[i].model);
		}
		if ((*vector)[i].numeSofer != NULL)
		{
			free((*vector)[i].numeSofer);
		}
	}
	free(*vector);
	(*vector) = NULL;
	(*nrMasini) = 0;
}

int main()
{
	int nrMasini = 0;
	Masina* masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);
	dezalocareVectoriMasini(&masini, &nrMasini);

	return 0;
}