#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <inttypes.h>

#define MAX_NAME_LEN 15
#define MAX_ENTRIES 30
#define number_t uint32_t

typedef
struct entry
{
    number_t number;
    char name[MAX_NAME_LEN];
} entry;

typedef
struct phonebook
{
    unsigned int size;
    entry entries[MAX_ENTRIES];
} phonebook;

typedef
enum { RES_OK, RES_PHONEBOOK_FULL, RES_NAME_TOO_LONG } result_t;

phonebook create_phonebook();
result_t add(phonebook* phonebook, number_t number, const char* name);
entry* get(phonebook* phonebook, number_t number);

#endif
