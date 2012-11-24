#include "phonebook.h"

#include <stdio.h>

int main(void)
{
	phonebook book = create_phonebook();
	add(&book, 922, "Anders");

	const char* name = getByNumber(&book, 922);
	printf("The owner of number 922 is %s\n",  name);

	number_t number = getByName(&book, "Anders");
	printf("Anders' number is %d\n", number);

	const char* errorName = getByNumber(&book, 1337);
	if (errorName == NULL)
	{
		printf("No one has number 1337\n");
	}

	number_t errorNumber = getByName(&book, "Charlotte");
	if (errorNumber == -1)
	{
		printf("Charlotte is not in the phonebook\n");
	}

	add(&book, 977, "Morten");

	printf("The contents of the phonebook are:\n");
	print(&book);

}
