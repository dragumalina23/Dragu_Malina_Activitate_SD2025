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

struct Stiva
{
	Masina info;
	struct Striva* next;
};
typedef struct Stiva Stiva;

void pushStack(Stiva** nod, Masina masina)
{
	Stiva* aux = (Stiva*)malloc(sizeof(Stiva));
	aux->info = masina;
	aux->next = (*nod);
	(*nod) = aux;
}

Masina popStack(Stiva** nod)
{
	Masina m;
	if ((*nod) != NULL)
	{
		//Stiva* aux = (*nod);
		m = (*nod)->info;
		(*nod) = (*nod)->next;
		//free(aux);
	}
	else
	{
		m.id = -1;
	}
	return m;
}

unsigned char isEmptyStack(Stiva* nod)
{
	return nod == NULL;
}

Stiva* citireStackMasiniDinFisier(const char* numeFisier) 
{
	FILE* f = fopen(numeFisier, "r");
	Stiva* nod = NULL;

	while (!feof(f))
	{
		pushStack(&nod, citireMasinaDinFisier(f));
	}

	fclose(f);
	return nod;
}

void dezalocareStivaDeMasini(Stiva** nod) 
{
	while (!isEmptyStack(*nod))
	{
		Masina m = popStack(nod);
		free(m.model);
		free(m.numeSofer);
	}
}

int size(Stiva* nod) 
{
	int size = 0;
	while (nod != NULL)
	{
		size++;
		nod = nod->next;
	}
	return size;
}

struct Nod
{
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct Coada
{
	Nod* first;
	Nod* last;
};
typedef struct Coada Coada;

void enqueue(Coada* coada, Masina masina)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masina;
	nou->prev = NULL;
	nou->next = coada->first;
	if (coada->first == NULL)
	{
		coada->first = nou;
		coada->last = nou;
	}
	else
	{
		coada->first->prev = nou;
		coada->first = nou;
	}
}

Masina dequeue(Coada * coada) 
{
	if (coada->last == NULL)
	{
		Masina m;
		m.id = -1;
		return m;
	}
	else
	{
		Masina m = coada->last->info;
		if (coada->last->prev == NULL)
		{
			coada->first = NULL;
			coada->last = NULL;
		}
		else
		{
			Nod* ultim = coada->last;
			coada->last = ultim->prev;
			ultim->prev->next = NULL;
			free(ultim);
		}
		return m;
	}
}

Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) 
{
	FILE* f = fopen(numeFisier, "r");
	Coada cap;
	cap.first = NULL;
	cap.last = NULL;

	while (!feof(f))
	{
		enqueue(&cap, citireMasinaDinFisier(f));
	}
	
	fclose(f);
	return cap;

}

void dezalocareCoadaDeMasini(Coada* coada) 
{
	while (coada->first != NULL)
	{
		Masina m = dequeue(coada);
		free(m.numeSofer);
		free(m.model);
	}
	coada->first = NULL;
	coada->last = NULL;
}


//metode de procesare
Masina getMasinaByID(Stiva* stiva, int id)
{
	Masina m;
	m.id = -1;

	while (m.id != id && !isEmptyStack(stiva))
	{
		m = popStack(&stiva);
	}
	return m;
}

float calculeazaPretTotal(Coada coada)
{
	float pretTotal = 0;

	while (coada.first != NULL)
	{
		pretTotal += coada.first->info.pret;
		coada.first = coada.first->next;
	}

	return pretTotal;
}

int main() 
{
	Stiva* s = citireStackMasiniDinFisier("masini.txt");
	Masina m = popStack(&s);
	afisareMasina(m);

	printf("Size of stack: %d", size(s));


	Coada c = citireCoadaDeMasiniDinFisier("masini.txt");
	afisareMasina(dequeue(&c));

	afisareMasina(getMasinaByID(s, 3));


	printf("Pret total: %.2f", calculeazaPretTotal(c));

	dezalocareCoadaDeMasini(&c);
	dezalocareStivaDeMasini(&s);

	return 0;
}