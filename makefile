build:
	gcc -o main main.c validate_read.c structure.c

test:
	gcc -o test xml_test/test_xml.c validate_read.c structure.c

test_1:
	gcc -o test_1 xml_test/test_xml_part_1.c validate_read.c structure.c

test_2:
	gcc -o test_2 xml_test/test_xml_part_2.c validate_read.c structure.c

clear_test:
	rm test

clear_test_1:
	rm test_1

clear_test_2:
	rm test_2

christophe:
	gcc -o christophe christophe.c