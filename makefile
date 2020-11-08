build:
	gcc -o main main.c validate_read.c structure.c

test:
	gcc -o test xml_test/test_xml.c validate_read.c structure.c

clear_test:
	rm test