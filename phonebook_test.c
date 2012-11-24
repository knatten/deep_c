#include "phonebook.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


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

phonebook book_with_two_entries()
{
    phonebook book = create_phonebook();
    result_t result = add(&book, 909, "Charlotte");
    assert(result == RES_OK);
    result = add(&book, 922, "Anders");
    assert(result == RES_OK);
    return book;
}

void entries_can_be_looked_up_by_number()
{
    phonebook book = book_with_two_entries();

    const char* anders = getByNumber(&book, 922);
    assert(anders && "Expected to not get null when looking up a known entry");
    assertStrEquals("Anders", anders);
}

void entries_can_be_looked_up_by_name()
{
    phonebook book = book_with_two_entries();

    number_t anders = getByName(&book, "Anders");
    assert(anders != -1 && "Expected to not get null when looking up a known entry");
    assertEquals(922, anders);
}

void non_existing_entries_return_null()
{
    phonebook book = book_with_two_entries();
    assert(getByNumber(&book, 42) == NULL);
    assert(getByName(&book, "Bob") == -1);
}

void when_deleting_an_entry_by_number_it_is_no_longer_there()
{
    phonebook book = book_with_two_entries();
    assert(deleteByNumber(&book, 922) == RES_OK);
    assert(getByNumber(&book, 922) == NULL && "Expected 922 Anders to have been deleted"); 
    assert(book.size == 1 && "Expected size to decrement");
    assertStrEquals(getByNumber(&book, 909), "Charlotte");
}

void when_deleting_an_entry_by_name_it_is_no_longer_there()
{
    phonebook book = book_with_two_entries();
    assert(deleteByName(&book, "Anders") == RES_OK);
    assert(getByName(&book, "Anders") == -1 && "Expected 922 Anders to have been deleted"); 
    assert(book.size == 1 && "Expected size to decrement");
    assert(getByName(&book, "Charlotte") == 909);
}

void when_deleting_a_non_existing_entry_by_number_an_error_is_returned()
{
    phonebook book = book_with_two_entries();
    assert(deleteByNumber(&book, 123) == RES_NOT_FOUND);
}

void when_deleting_a_non_existing_entry_by_name_an_error_is_returned()
{
    phonebook book = book_with_two_entries();
    assert(deleteByName(&book, "Bob") == RES_NOT_FOUND);
}

int main(void)
{
    a_new_phonebook_is_empty();
    when_adding_an_entry_the_size_is_incremented();
    adding_is_allowed_until_book_is_full();
    adding_is_not_allowed_if_name_is_too_long();
    entries_can_be_looked_up_by_number();
    entries_can_be_looked_up_by_name();
    non_existing_entries_return_null();
    when_deleting_an_entry_by_number_it_is_no_longer_there();
    when_deleting_a_non_existing_entry_by_number_an_error_is_returned();
    when_deleting_an_entry_by_name_it_is_no_longer_there();
    when_deleting_a_non_existing_entry_by_name_an_error_is_returned();
    printf("All tests passed\n");
    return 0;
}
