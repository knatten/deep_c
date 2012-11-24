#include "phonebook.h"

#include <string.h>
#include <stdio.h>
#include <limits.h>


size_t indexByNumber(phonebook* phonebook, number_t number)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        entry* entr = &phonebook->entries[i];
        if (entr->number == number)
        {
            return i;
        }
    }
    return SIZE_MAX;
}

size_t indexByName(phonebook* phonebook, const char* name)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        entry* entr = &phonebook->entries[i];
        if (!strcmp(entr->name, name))
        {
            return i;
        }
    }
    return SIZE_MAX;
}

void deleteByIndex(phonebook* phonebook, size_t index)
{
    for (size_t i = index; i < phonebook->size-1; ++i)
    {
        phonebook->entries[i] = phonebook->entries[i+1];
    }
    phonebook->size--;
}

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

result_t deleteByNumber(phonebook* phonebook, number_t number)
{
    size_t index = indexByNumber(phonebook, number);
    if (index == SIZE_MAX)
    {
        return RES_NOT_FOUND;
    }
    deleteByIndex(phonebook, index);
    return RES_OK;
}

result_t deleteByName(phonebook* phonebook, const char* name)
{
    size_t index = indexByName(phonebook, name);
    if (index == SIZE_MAX)
    {
        return RES_NOT_FOUND;
    }
    deleteByIndex(phonebook, index);
    return RES_OK;
}

const char* getByNumber(phonebook* phonebook, number_t number)
{
    size_t index = indexByNumber(phonebook, number);
    if (index == SIZE_MAX)
    {
        return NULL;
    }
    return phonebook->entries[index].name;
}

number_t getByName(phonebook* phonebook, const char* name)
{
    size_t index = indexByName(phonebook, name);
    if (index == SIZE_MAX)
    {
        return -1;
    }
    return phonebook->entries[index].number;
}

void print(phonebook* phonebook)
{
    for (size_t i = 0; i < phonebook->size; ++i)
    {
        entry* entr = &phonebook->entries[i];
        printf("%s: %d\n", entr->name, entr->number);
    }
    
}
