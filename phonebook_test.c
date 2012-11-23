#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

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

void assertStrEquals(const char* s1, const char* s2)
{
    if (strcmp(s1, s2))
    {
        printf("Strings are not equal:\ns1:%s\ns2:%s\n", s1, s2);
        assert(0);
    }
}

void assertEquals(int i1, int i2)
{
    if (i1 != i2)
    {
        printf("Ints are not equal:\ni1:%d\ni2:%d\n", i1, i2);
        assert(0);
    }
}

void a_new_phonebook_is_empty()
{
    phonebook book = create_phonebook();
    assert(book.size == 0 );
}

void when_adding_an_entry_the_size_is_incremented()
{
    phonebook book = create_phonebook();
    result_t result = add(&book, 42, "_");
    assert(result == RES_OK);
    assert(book.size == 1);
}

void adding_is_allowed_until_book_is_full()
{
    phonebook book = create_phonebook();
    for(size_t i = 0; i < MAX_ENTRIES; ++i)
    {
        result_t result = add(&book, 42, "_");
        assert(result == RES_OK && "Expected to be allowed to add to a non-null phonebook");
    }
    result_t result = add(&book, 42, "_");
    assert(result ==  RES_PHONEBOOK_FULL && "Expected to not be allowed to add to a full phonebook");
}

void adding_is_not_allowed_if_name_is_too_long()
{
    phonebook book = create_phonebook();
    result_t result  = add(&book, 42, "David Robert Hayward-Jones");
    assert(result == RES_NAME_TOO_LONG);
}

void entries_can_be_looked_up_by_number()
{
    phonebook book = create_phonebook();
    result_t result = add(&book, 909, "Charlotte");
    assert(result == RES_OK);
    result = add(&book, 922, "Anders");
    assert(result == RES_OK);

    entry* anders = get(&book, 922);
    assert(anders && "Expected to not get null when looking up a known entry");
    assertStrEquals("Anders", anders->name);
    assertEquals(922, anders->number);
}

void non_existing_entries_return_null()
{
    phonebook book = create_phonebook();
    entry* entr = get(&book, 42);
    assert(entr == NULL);
}

int main(void)
{
    a_new_phonebook_is_empty();
    when_adding_an_entry_the_size_is_incremented();
    adding_is_allowed_until_book_is_full();
    adding_is_not_allowed_if_name_is_too_long();
    entries_can_be_looked_up_by_number();
    non_existing_entries_return_null();
    printf("All tests passed\n");
    return 0;
}