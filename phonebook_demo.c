#include "phonebook.h"

#include <stdio.h>

int main(void)
{
	phonebook book = create_phonebook();

	add(&book, 922, "Anders");
	const char* name = getByNumber(&book, 922);
	printf("The owner of number 922 is %s\n",  name);

	add(&book, 977, "Morten");
	number_t number = getByName(&book, "Morten");
	printf("Morten' number is %d\n", number);

	printf("The contents of the phonebook are:\n");
	print(&book);

	deleteByNumber(&book, 977);
	const char* errorName = getByNumber(&book, 977);
	if (errorName == NULL)
	{
		printf("No one has number 977\n");
	}

	deleteByName(&book, "Anders");
	number_t errorNumber = getByName(&book, "Anders");
	if (errorNumber == -1)
	{
		printf("Anders is not in the phonebook\n");
	}

}
