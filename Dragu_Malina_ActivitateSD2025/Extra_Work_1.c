//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////=================== 1. Structura si functii ======================
//
////Sa se construiască un articol care să conțină cele două litere. M-D
////Articolul trebuie să aibă logica.Articolul trebuie sa fie un substantiv.Articolul trebuie sa aibă
////cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.
//
//struct Melodie
//{
//	int id;
//	float durata; // in minute
//	char gen; // R - rock, P - pop, J - jazz, T - rap
//	char* titlu;
//	int nrNote;
//	float* noteObtinute; // rating de la diferite platforme
//};
//typedef struct Melodie Melodie;
//
////Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de voi.
//// Funcția returnează obiectul citit.
//
//Melodie citesteObiect(Melodie* m)
//{
//	printf("Introduceti id-ul: ");
//	scanf("%d", &(m->id));
//
//	printf("Introduceti durata (in minute): ");
//	scanf("%f", &(m->durata));
//
//	printf("Introduceti genul ( R - rock, P - pop, J - jazz, T - rap): ");
//	scanf(" %c", &(m->gen));
//
//	m->titlu = (char*)malloc(100);
//	printf("Introduceti titlul: ");
//	scanf(" %[^\n]", m->titlu);
//
//	printf("Introduceti numarul de note obtinute: ");
//	scanf("%d", &(m->nrNote));
//	
//	m->noteObtinute = (int*)malloc(m->nrNote * sizeof(int));
//	printf("Introduceti notele obtinute: ");
//	for (int i = 0; i < m->nrNote; i++)
//	{
//		scanf("%f", &(m->noteObtinute[i]));
//	}
//
//	return (*m);
//}
//
////Realizați o funcție care afișează un obiect de tipul creat.Afișarea se face la console, și sunt
////afișate toate informațiile.
//
//void afisareMelodie(Melodie m)
//{
//	printf("====== Melodia %d ======\n", m.id);
//	printf("Titlu: %s\n", m.titlu);
//	printf("Durata: %.2f minute\n", m.durata);
//	printf("Gen: %c\n", m.gen);
//	printf("Note obtinute: ");
//	for (int i = 0; i < m.nrNote; i++)
//	{
//		printf("%.2f ", m.noteObtinute[i]);
//	}
//	printf("\n\n");
//}
//
////Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o
////medie sau o suma, un maxim, un minim...sau orice altceva)
//
//float calculeazaNotaMedie(Melodie m)
//{
//	float suma = 0;
//	for (int i = 0; i < m.nrNote; i++)
//	{
//		suma += m.noteObtinute[i];
//	}
//	if (suma)
//	{
//		return suma / m.nrNote;
//	}
//	return 0;
//}
//
////Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.
////noua valoare este primita ca parametru.
//
//void stergeAnumiteNote(Melodie* m, float nota)
//{
//	// sterge toate notele egale cu parametrul primit
//	for (int i = 0; i < m->nrNote; i++)
//	{
//		while (m->noteObtinute[i] == nota)
//		{
//			for (int j = i + 1; j < m->nrNote; j++)
//			{
//				m->noteObtinute[j - 1] = m->noteObtinute[j];
//			}
//			m->nrNote--;
//			i--;
//		}
//	}
//}
//
//int main()
//{
//
//	Melodie m;
//	citesteObiect(&m);
//	afisareMelodie(m);
//	float medie = calculeazaNotaMedie(m);
//	printf("Nota medie pentru melodia %d este: %.2f", m.id, medie);
//	stergeAnumiteNote(&m, 10);
//	afisareMelodie(m);
//
//
//	return 0;
//}