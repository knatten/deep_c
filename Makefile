#vim set noet
CFLAGS := -Wall -std=c99

	
test: phonebook_test.o phonebook.o
	$(CC) -o phonebook_test phonebook_test.o phonebook.o
	./phonebook_test

clean:
	rm -f *.o phonebook_test
