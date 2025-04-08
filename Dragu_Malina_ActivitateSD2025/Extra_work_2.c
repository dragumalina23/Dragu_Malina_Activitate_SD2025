#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Melodie
{
	int id;
	float durata; // in minute
	char gen; // R - rock, P - pop, J - jazz, T - rap
	char* titlu;
	int nrNote;
	float* noteObtinute; // rating de la diferite platforme
};
typedef struct Melodie Melodie;

Melodie citesteObiect(Melodie* m)
{
	printf("Introduceti id-ul: ");
	scanf("%d", &(m->id));

	printf("Introduceti durata (in minute): ");
	scanf("%f", &(m->durata));

	printf("Introduceti genul ( R - rock, P - pop, J - jazz, T - rap): ");
	scanf(" %c", &(m->gen));

	m->titlu = (char*)malloc(100);
	printf("Introduceti titlul: ");
	scanf(" %[^\n]", m->titlu);

	printf("Introduceti numarul de note obtinute: ");
	scanf("%d", &(m->nrNote));

	m->noteObtinute = (int*)malloc(m->nrNote * sizeof(int));
	printf("Introduceti notele obtinute: ");
	for (int i = 0; i < m->nrNote; i++)
	{
		scanf("%f", &(m->noteObtinute[i]));
	}

	return (*m);
}

void afisareMelodie(Melodie m)
{
	printf("====== Melodia %d ======\n", m.id);
	printf("Titlu: %s\n", m.titlu);
	printf("Durata: %.2f minute\n", m.durata);
	printf("Gen: %c\n", m.gen);
	printf("Note obtinute: ");
	for (int i = 0; i < m.nrNote; i++)
	{
		printf("%.2f ", m.noteObtinute[i]);
	}
	printf("\n\n");
}

float calculeazaNotaMedie(Melodie m)
{
	float suma = 0;
	for (int i = 0; i < m.nrNote; i++)
	{
		suma += m.noteObtinute[i];
	}
	if (suma)
	{
		return suma / m.nrNote;
	}
	return 0;
}

void stergeAnumiteNote(Melodie* m, float nota)
{
	// sterge toate notele egale cu parametrul primit
	for (int i = 0; i < m->nrNote; i++)
	{
		while (m->noteObtinute[i] == nota)
		{
			for (int j = i + 1; j < m->nrNote; j++)
			{
				m->noteObtinute[j - 1] = m->noteObtinute[j];
			}
			m->nrNote--;
			i--;
		}
	}
}

// Initializare obiect
Melodie initializareObiect(int id, float durata, char gen, char* titlu, int nrNote, float* noteObtinute)
{
	Melodie m;
	m.id = id;
	m.durata = durata;
	m.gen = gen;
	
	m.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy_s(m.titlu, strlen(titlu) + 1, titlu);

	m.nrNote = nrNote;
	m.noteObtinute = (float*)malloc(sizeof(float) * nrNote);
	for (int i = 0; i < nrNote; i++)
	{
		m.noteObtinute[i] = noteObtinute[i];
	}

	return m;
}

////=================== 2. Vectori ======================

//Realizati o functie care va creea un nou vector în care va copia dintr - un vector primit ca
//parametru obiectele care indeplinesc o anumita conditie.Stabiliti voi conditia in functie de
//un atribut sau doua atribute

Melodie* getMelodiiCuRatingMare(Melodie* album, int nrMelodii, float rating, int* nr)
{
	(*nr) = 0;
	for (int i = 0; i < nrMelodii; i++)
	{
		if (calculeazaNotaMedie(album[i]) >= rating)
		{
			(*nr)++;
		}
	}
	Melodie* aux = (Melodie*)malloc(sizeof(Melodie) * (*nr));

	int k = 0;
	for (int i = 0; i < nrMelodii; i++)
	{
		if (calculeazaNotaMedie(album[i]) >= rating)
		{
			aux[k] = initializareObiect(album[i].id, album[i].durata, album[i].gen, album[i].titlu, album[i].nrNote, album[i].noteObtinute);
			k++;
		}
	}

	return aux;
}

//Realizati o functie care muta intr - un nou vector obiectele care indeplinesc o alta conditie
//fata de cerinta precedenta

Melodie* getMelodiiDupaGen(Melodie* album, int nrMelodii, char gen, int* nr)
{
	(*nr) = 0;
	for (int i = 0; i < nrMelodii; i++)
	{
		if (album[i].gen == gen)
		{
			(*nr)++;
		}
	}

	Melodie* aux = (Melodie*)malloc(sizeof(Melodie) * (*nr));

	int k = 0;
	for (int i = 0; i < nrMelodii; i++)
	{
		if (album[i].gen == gen)
		{
			aux[k] = initializareObiect(album[i].id, album[i].durata, album[i].gen, album[i].titlu, album[i].nrNote, album[i].noteObtinute);
			k++;
		}
	}

	return aux;
}

//Realizati o functie care concateneaza doi vectori.
float* concatenareVectori(Melodie m1, Melodie m2)
{
	int nr = m1.nrNote + m2.nrNote;
	float* rezultat = (float*)malloc(sizeof(float) * nr);
	int i = 0;
	for (i = 0; i < m1.nrNote; i++)
	{
		rezultat[i] = m1.noteObtinute[i];
	}
	int j = 0;
	while (i < nr)
	{
		rezultat[i] = m2.noteObtinute[j];
		i++;
		j++;
	}

	return rezultat;
}


//Realizati o functie care afiseaza un vector cu obiecte
void afisareVectorMelodii(Melodie* m, int nrMelodii)
{
	for (int i = 0; i < nrMelodii; i++)
	{
		afisareMelodie((m[i]));
	}
}

int main()
{
	//Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre.
	int nrMelodii = 5;
	Melodie* album = (Melodie*)malloc(sizeof(Melodie) * nrMelodii);

	float note1[] = { 10,7,8,10 };
	float note2[] = { 5,2,4 };
	float note3[] = { 10,9,10,10,10 };
	float note4[] = { 3,6 };
	float note5[] = { 10,7,8 };

	Melodie m1 = initializareObiect(1, 3.5, 'R', "To Binge", 4, note1);
	Melodie m2 = initializareObiect(2, 4.6, 'J', "My way", 3, note2);
	Melodie m3 = initializareObiect(3, 2.9, 'P', "Song 2", 5, note3);
	Melodie m4 = initializareObiect(4, 3, 'P', "Obsessed", 2, note4);
	Melodie m5 = initializareObiect(5, 4.1, 'T', "My eyes", 3, note5);

	album[0] = m1;
	album[1] = m2;
	album[2] = m3;
	album[3] = m4;
	album[4] = m5;


	int nr = 0;
	//Melodie* rating = getMelodiiCuRatingMare(album, nrMelodii, 7.8, &nr);
	//afisareVectorMelodii(rating, nr);

	Melodie* melodiiGen = getMelodiiDupaGen(album, nrMelodii, 'P', &nr);
	afisareVectorMelodii(melodiiGen, nr);

	float* noteMelodii = concatenareVectori(m1, m2);
	printf("Concatenare vectori: ");
	for (int i = 0; i < m1.nrNote + m2.nrNote; i++)
	{
		printf("%.2f ", noteMelodii[i]);
	}

	free(m1.titlu);
	free(m1.noteObtinute);
	free(album);
	return 0;
}