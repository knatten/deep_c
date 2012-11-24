#include "phonebook.h"

#include <string.h>
#include <stdio.h>

phonebook create_phonebook()
{
    phonebook book;
    book.size = 0;
    return book;
}

result_t add(phonebook* phonebook, number_t number, const char* name)
{
    if (MAX_ENTRIES <= phonebook->size)
    {
        return RES_PHONEBOOK_FULL;
    }
    if (strlen(name) > MAX_NAME_LEN)
    {
        return RES_NAME_TOO_LONG;
    }
    entry ent;
    ent.number = number;
    strcpy(ent.name, name);
    phonebook->entries[phonebook->size] = ent;
    phonebook->size++;
    return RES_OK;
}

const char* getByNumber(phonebook* phonebook, number_t number)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        entry* entr = &phonebook->entries[i];
        if (entr->number == number)
        {
            return entr->name;
        }
    }
    return NULL;
}

number_t getByName(phonebook* phonebook, const char* name)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        entry* entr = &phonebook->entries[i];
        if (!strcmp(entr->name, name))
        {
            return entr->number;
        }
    }
    return -1;
}

void print(phonebook* phonebook)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        entry* entr = &phonebook->entries[i];
        printf("%s: %d\n", entr->name, entr->number);
    }
    
}
