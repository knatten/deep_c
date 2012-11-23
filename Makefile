#vim set noet
CFLAGS := -Wall -std=c99

	
phonebook.lib: phonebook.o
	ar r phonebook.lib phonebook.o

phonebook_test: phonebook_test.o phonebook.lib
	$(CC) -o phonebook_test phonebook_test.o phonebook.lib

test: phonebook_test
	./phonebook_test

phonebook_demo: phonebook_demo.o phonebook.lib
	$(CC) -o phonebook_demo phonebook_demo.o phonebook.lib

demo: phonebook_demo
	./phonebook_demo

clean:
	rm -f *.o *.lib phonebook_test
