#include "phonebook.h"

#include <stdio.h>

int main(void)
{
	phonebook book = create_phonebook();
	add(&book, 922, "Anders");

	entry* e1 = getByNumber(&book, 922);
	printf("The owner of number 922 is %s\n",  e1->name);

	entry* e2 = getByName(&book, "Anders");
	printf("Anders' number is %d\n", e2->number);

	entry* error = getByNumber(&book, 1337);
	if (error == NULL)
	{
		printf("No one has number 1337");
	}
}
