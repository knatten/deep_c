#vim set noet
CFLAGS := -Wall -std=c99

	
phonebook.lib: phonebook.o
	ar r phonebook.lib phonebook.o

test: phonebook_test.o phonebook.lib
	$(CC) -o phonebook_test phonebook_test.o phonebook.lib
	./phonebook_test

clean:
	rm -f *.o *.lib phonebook_test
