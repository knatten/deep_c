CFLAGS := -Wall -std=c99

phonebook_test: phonebook_test.o

test: phonebook_test
	./phonebook_test

clean:
	rm -f *.o phonebook_test
