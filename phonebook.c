#include "phonebook.h"

#include <string.h>

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

entry* get(phonebook* phonebook, number_t number)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        if (phonebook->entries[i].number == number)
        {
            return &phonebook->entries[i];
        }
    }
    return NULL;
}
