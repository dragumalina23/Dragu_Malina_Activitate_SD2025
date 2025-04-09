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
	struct Nod* next;
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

void afisareListaMasini(Nod* cap) 
{
	while (cap != NULL)
	{
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) 
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; // shallow copy
	nou->next = NULL;

	if (*cap)
	{
		Nod* p = *cap;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		(*cap) = nou;
	}

}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) 
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = (*cap);
	(*cap) = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier)
{
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		while (!feof(f))
		{
			//creem lista cu inserare la sfarsit
			adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));
		}
	}
	fclose(f);
	return cap;
}

void dezalocareListaMasini(Nod** cap) 
{
	while (*cap)
	{
		Nod* p = (*cap);
		(*cap) = (*cap)->next;
		if (p->info.model)
		{
			free(p->info.model);
		}
		if (p->info.numeSofer)
		{
			free(p->info.numeSofer);
		}
		free(p);
	}
}

float calculeazaPretMediu(Nod* cap) 
{
	float suma = 0;
	int contor = 0;
	while (cap)
	{
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	if (suma)
	{
		return suma / contor;
	}
	return 0;
}

void stergeMasiniDinSeria(Nod** cap, char serieCautata)
{
	while ((*cap) && (*cap)->info.serie == serieCautata)
	{
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		if (aux->info.numeSofer)
		{
			free(aux->info.numeSofer);
		}
		if (aux->info.model)
		{
			free(aux->info.model);
		}
		free(aux);
	}
	if ((*cap))
	{
		Nod* p = (*cap);
		while (p)
		{
			while (p->next && p->next->info.serie != serieCautata)
			{
				p = p->next;
			}
			if (p->next)
			{
				Nod* aux = p->next;
				p->next = aux->next;
				if (aux->info.numeSofer)
				{
					free(aux->info.numeSofer);
				}
				if (aux->info.model)
				{
					free(aux->info.model);
				}
				free(aux);
			}
			else
			{
				p = NULL;
			}
		}
	}
	

}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, char* numeSofer)
{
	float suma = 0;
	while (cap)
	{
		if (strcmp(cap->info.numeSofer, numeSofer) == 0)
		{
			suma += cap->info.pret;
		}
		cap = cap->next;
	}
	return suma;
}

//================= 5. Liste simple =====================

//1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista
//   are mai putine noduri decat index - ul dat, nu se realizeaza stergerea.

void stergeNodDupaPozitie(Nod** cap, int index)
{
	Nod* aux = *cap;
	int contor = 0;
	while (aux && aux->next && contor < (index - 2))
	{
		aux = aux->next;
		contor++;
	}
	if ((*cap) == aux)
	{
		(*cap) = (*cap)->next;
	}
	else
	{
		Nod* temp = aux->next;
		if (temp->next == NULL)
		{
			aux->next = NULL;
		}
		else
		{
			aux->next=temp->next;
		}
	}
	cap = aux;
}

// 2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel
// incat acestea a fie sortate crescator dupa un camp la alegerea voastra.

float gasestePretMinimSiPozitie(Nod* cap, int* poz)
{
	float pretMin = cap->info.pret;
	int aux = 0;
	while (cap)
	{
		if (cap->info.pret < pretMin)
		{
			pretMin = cap->info.pret;
			aux = (*poz);
		}
		cap = cap->next;
		(*poz)++;
	}

	(*poz) = aux;

	return pretMin;
}

void insereazaCrescatorDupaPret(Nod** cap)
{
	Nod* aux = *cap;
	Nod* temp = *cap;
	float pretMin = 0;
	int poz = 0;
	while (temp)
	{
		pretMin = gasestePretMinimSiPozitie(aux, &poz);
		while (temp)
		{
			if (temp->info.pret == pretMin)
			{
				adaugaMasinaInLista(&aux, temp->info);
				stergeNodDupaPozitie(&temp, poz);
			}
			temp = temp->next;
		}
		temp = temp->next;
	}

	(*cap) = aux;
}


int main()
{
	Nod* cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);

	//printf("\n\n\n\n\n");
	//stergeNodDupaPozitie(&cap, 1);
	//afisareListaMasini(cap);

	insereazaCrescatorDupaPret(&cap);
	afisareListaMasini(cap);
	return 0;
}