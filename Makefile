#vim set noet
CFLAGS := -Wall -std=c99

	
libphonebook.a: phonebook.o
	ar r libphonebook.a phonebook.o

phonebook_test: phonebook_test.o libphonebook.a
	$(CC) -o phonebook_test phonebook_test.o libphonebook.a

test: phonebook_test
	./phonebook_test

phonebook_demo: phonebook_demo.o libphonebook.a
	$(CC) -o phonebook_demo phonebook_demo.o libphonebook.a

demo: phonebook_demo
	./phonebook_demo

clean:
	rm -f *.o *.a phonebook_test
