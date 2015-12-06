#ifdef _MSC_VER  // je¿eli nie korzystacie z visual studio usunicie tego ifa
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Nie wiem na jakim poziomie z programowania jestescie, ale z materialem wam ostro polecieli, ja listy mialem dopiero w marcu (czyli drugi semestr) 
// Je¿eli nie mieliscie ¿adnego wprowadzenia do struktur danych, nie wiecie co to jest lista, zacznijcie od tego
struct DynamicList 
{
	float x, y, z;
	char char_string[36];
	struct DynamicList* next;
};

struct DynamicList* new_element_to_insert(float x_arg, float y_arg, float z_arg, char char_string_arg[36]) { // funkcja ktora alokuje pamiec pod nowy element w liscie
	struct DynamicList *element_to_add = malloc(sizeof *element_to_add); //http://stackoverflow.com/questions/2177391/allocating-memory-for-a-structure-in-c
	element_to_add->x = x_arg;
	element_to_add->y = y_arg;
	element_to_add->z = z_arg;
	strcpy(element_to_add->char_string, char_string_arg); //string copy
	element_to_add->next = NULL;
	return element_to_add;
}

void print(struct DynamicList* list, int number_of_printed_element) { // wypisywanie 
	for (int i = 0; i < number_of_printed_element; i++) {
		list = list->next;
	}
	printf("x=%f y=%f z=%f char_string=%s\n", list->x, list->y, list->z, list->char_string);
}

void clear(void) // usuwanie bufforu stdin http://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
{
	while (getchar() != '\n');
}

int main(void)
{
	int number_of_loaded_elements = 0; // licznik dla liczby elementow, normalnie powinien on znajdowac sie w strukturze/klasie ... ale wy mieliscie scisle okreslona liczbe pol w strukturze/klasie
	struct DynamicList *head = NULL; //glowa listy, nie mozna jej zmieniac, tzn nie mozna dac head=haed->next, bo wtedy straci siê pierwszy element w liscie, je¿eli by³a by to lista dwukierunkowa (a jest jedno, bo nie ma prev, jest tylko next), to wtedy mozna by bylo to zrobic, ale wtedy przesunelo by sie "poczatek listy"
	{
		struct DynamicList *temp_point_to_list; //tymczasowa zmienna, zeby nie zmieniac wartosci head 
		float temp_x, temp_y, temp_z;
		char temp_string[36] = { 2,3,4 };
		while (scanf("%f%f%f%[^\n]s", &temp_x, &temp_y, &temp_z, &temp_string) == 4) // JEST TO LE ZROBIONE, nie wiem jak zrobiæ tak hardcorowe formatowanie, mo¿na oczywiscie to reguralnymi wyra¿eniami (regex) zrobiæ, ale nie s¹dzê, ¿eby wam tak kaza³ zrobiæ goœciu, wykrzykuje siê na "E .:" (crtl+f zróbcie w pliku ¿eby to zobaczyæ) które jest gdzieœ na œrodku w pliku
			// Nie wiem w sumie jak to zrobiæ, mo¿e pobieraæ ca³¹ liniê (%[^\n]s) odrazu, potem atoi ¿eby 3 liczby x,y,z wy¿³obiæ, a reszta do stringa, ale tez to nie bêdzie ³adne
			// lub tez w sumie mozliwe, ze powinien ignorowac zle podane dane, to jest do szybkiego zrobienia
		{
			if (head == NULL) { // jezeli pierwsze przejscie, alokuj pierwszy element
				head = new_element_to_insert(temp_x, temp_y, temp_z, temp_string); //wywolanie funkcji ktora zwraca do glowy nowy element
			}
			else { // jezeli nie pierwsze przejscie, szukaj 
				temp_point_to_list = head; //tymczasowa zmienna przestawiona na glowe
				while (temp_point_to_list->next != NULL) //szukanie koncowego elementu
				{
					temp_point_to_list = temp_point_to_list->next;
				}
				temp_point_to_list->next = new_element_to_insert(temp_x, temp_y, temp_z, temp_string);//wywolanie funkcji ktora zwraca do koncowego elemntu->next nowy element, po wykonaniu tej funkcji, koncowy element przechodzi na przedkoncowy element, a nowy element jest koncowym elementem
			}
			number_of_loaded_elements++; //zwiekszenie licznika
		}
	}
	
	if (head == NULL) { // zabezpieczenie jezeli nie ma zadnych elementow
		printf("list is empty\n");
	}
	else {
		print(head, 0); // pierwszy element to jest 0
		print(head, number_of_loaded_elements - 1); //ostatni element to number_of_loaded_elements - 1
		printf("Do you want to print whole list? y or n\n");
		clear(); // czyszczenie buffora wlasna funkcja
		char one_character;;
		scanf("%c", &one_character);
		if (one_character == 'y') {
			for (int i = 0; i < number_of_loaded_elements; i++) {
				print(head, i);
			}
		}
	}
	return 0;
}