build:
	gcc -o main main.c validate_read.c structure.c

test:
	gcc -o test xml_test/test_xml.c validate_read.c structure.c

#faire test pour la partie 1

#faire test pour la partie 2

clear_test:
	rm test