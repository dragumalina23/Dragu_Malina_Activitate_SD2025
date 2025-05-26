#include<stdio.h>
#include<malloc.h>

struct Masina
{
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};

struct Masina initializare(int id, int nrKm, const char* model, float pret, char tipMotor)
{
	struct Masina m;
	m.id = id;
	m.nrKm = nrKm;
	m.model = (char*)malloc(strlen(model) + 1);
	strcpy(m.model, model);
	m.pret = pret;
	m.tipMotor = tipMotor;
	return m;
}

void afisare(struct Masina m)
{
	printf("Id: %d, nr km: %d, model: %s, pret: %f, tip motor: %c", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
}

void afisareVector(struct Masina* vector, int nrElemente)
{
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
		printf("\n");
	}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int(*nrElementeCopiate))
{
	struct Masina* vectorNou = NULL;

	if (vector != NULL && (*nrElementeCopiate) > 0)
	{
		if ((*nrElementeCopiate) > nrElemente)
			(*nrElementeCopiate) = nrElemente;
		vectorNou = malloc(sizeof(struct Masina) * (*nrElementeCopiate));

		for (int i = 0; i < (*nrElementeCopiate); i++)
			vectorNou[i] = initializare(vector[i].id, vector[i].nrKm, vector[i].model, vector[i].pret, vector[i].tipMotor);

	}
	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente)
{
	for (int i = 0; i < (*nrElemente); i++)
	{
		if ((*vector)[i].model != NULL)
		{
			free((*vector)[i].model); // dereferentiere + deplasare + dereferentiere + afisare
		}
	}
	free(*vector);
	(*vector) = NULL;
	(*nrElemente) = 0;
}

//parametrul prag poate fi modificat in functie de 
// tipul atributului ales pentru a indeplini o conditie
//este creat un nou vector cu elementele care indeplinesc acea conditie

void copiazaMasiniIeftine(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune)
{
	(*dimensiune) = 0;

	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret < prag)
		{
			(*dimensiune)++;
		}
	}
	int k = 0;
	*vectorNou = malloc(sizeof(struct Masina) * (*dimensiune));
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret < prag)
		{
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
			strcpy_s((*vectorNou)[k].model, (strlen(vector[i].model) + 1), vector[i].model);
			k++;
		}
	}
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie)
{
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}



int main()
{
	int n = 3;
	struct Masina* vec;
	vec = malloc(sizeof(struct Masina) * n);

	vec[0] = initializare(10, 10000, "Logan", 10000.5, 'd');
	vec[1] = initializare(11, 20000, "Passat", 18000.5, 'b');
	vec[2] = initializare(12, 15000, "CyberTruck", 85000.0, 'e');

	int nrElemCopiate = 5;

	afisareVector(vec, n);
	struct Masina* vecnou = copiazaPrimeleNElemente(vec, n, &nrElemCopiate);

	printf("Elemente copiate: \n");
	afisareVector(vecnou, nrElemCopiate);

	dezalocare(&vecnou, &nrElemCopiate);

	printf("Masini ieftine: \n");

	copiazaMasiniIeftine(vec, n, 19000, &vecnou, &nrElemCopiate);
	afisareVector(vecnou, nrElemCopiate);

	dezalocare(&vecnou, &nrElemCopiate);
	dezalocare(&vec, &n);

	return 0;
}