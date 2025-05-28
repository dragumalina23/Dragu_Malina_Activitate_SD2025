//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
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
//struct Stiva
//{
//	Masina info;
//	struct Stiva* next;
//};
//typedef struct Stiva Stiva;
//
//Masina citireMasinaDinFisier(FILE* f)
//{
//	char buffer[100];
//	char sep[3] = ",;\n";
//	char* aux;
//	Masina m;
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
//	return m;
//}
//
//void afisareMasina(Masina masina) 
//{
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi: %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//
//void pushStack(Stiva** stiva, Masina m)
//{
//	Stiva* aux = (Stiva*)malloc(sizeof(Stiva));
//	aux->info = m;
//	aux->next = (*stiva);
//	(*stiva) = aux;
//}
//
//Masina popStack(Stiva** stiva)
//{
//	Masina m;
//	m.id = -1;
//	if ((*stiva) != NULL)
//	{
//		Stiva* aux = (*stiva);
//		m = (*stiva)->info;
//		(*stiva) = (*stiva)->next;
//		free(aux);
//	}
//	return m;
//}
//
//Stiva* citireMasiniInStiva(const char* numeFisier)
//{
//	FILE* f = fopen(numeFisier, "r");
//	Stiva* s = NULL;
//
//	while (!feof(f))
//	{
//		pushStack(&s, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return s;
//}
//
//unsigned int isEmptyStack(Stiva* s)
//{
//	return s == NULL;
//}
//
//void afisareStiva(Stiva* s)
//{
//	while (s != NULL)
//	{
//		afisareMasina(s->info);
//		s = s->next;
//	}
//}
//
//void dezalocareStiva(Stiva** s)
//{
//	while (!isEmptyStack(*s))
//	{
//		Masina m = popStack(s);
//		free(m.model);
//		free(m.numeSofer);
//	}
//}
//
//struct Nod
//{
//	Masina info;
//	struct Nod* next;
//	struct Nod* prev;
//};
//typedef struct Nod Nod;
//
//struct Coada
//{
//	Nod* first;
//	Nod* last;
//};
//typedef struct Coada Coada;
//
//void enqueue(Coada* coada, Masina masina)
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masina;
//	nou->prev = NULL;
//	nou->next = coada->first;
//	
//	if (coada->first == NULL)
//	{
//		coada->first = nou;
//		coada->last = nou;
//	}
//	else
//	{
//		coada->first->prev = nou;
//		coada->first = nou;
//	}
//}
//
//Masina dequeue(Coada* coada)
//{
//	Masina m;
//	if (coada->last == NULL)
//	{
//		m.id = -1;
//		return m;
//	}
//	else
//	{
//		m = coada->last->info;
//		if (coada->last->prev == NULL)
//		{
//			coada->last = NULL;
//			coada->first = NULL;
//		}
//		else
//		{
//			coada->last->prev->next = NULL;
//			coada->last = coada->last->prev;
//		}
//	}
//	return m;
//}
//
//Coada citireCoadaMasiniFisier(const char* numeFisier)
//{
//	FILE* f = fopen(numeFisier, "r");
//	Coada cap;
//	cap.first = NULL;
//	cap.last = NULL;
//
//	while (!feof(f))
//	{
//		enqueue(&cap, citireMasinaDinFisier(f));
//	}
//
//	fclose(f);
//	return cap;
//}
//
//void afisareCoada(Coada coada)
//{
//	while (coada.last != NULL)
//	{
//		afisareMasina(coada.last->info);
//		coada.last = coada.last->prev;
//	}
//}
//
//void dezalocareCoadaDeMasini(Coada* coada) 
//{
//	while (coada->first != NULL)
//	{
//		Masina m = dequeue(coada);
//		free(m.numeSofer);
//		free(m.model);
//	}
//	coada->first = NULL;
//	coada->last = NULL;
//}
//
//int main()
//{
//	//Stiva* s = citireMasiniInStiva("masini_sortate.txt");
//	//afisareStiva(s);
//
//	Coada c = citireCoadaMasiniFisier("masini_sortate.txt");
//	afisareCoada(c);
//
//	dezalocareCoadaDeMasini(&c);
//	//dezalocareStiva(&s);
// 	return 0;
//}