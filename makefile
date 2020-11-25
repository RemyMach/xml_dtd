build:
	gcc -o main main.c validate_read.c structure.c christophe.c

# Test validité fichier xml

test_x:
	gcc -o xml xml_test/test_xml.c validate_read.c structure.c

test_1_x:
	gcc -o xml_1 xml_test/test_xml_part_1.c validate_read.c structure.c

test_2_x:
	gcc -o xml_2 xml_test/test_xml_part_2.c validate_read.c structure.c

clear_test_x:
	rm xml

clear_test_1_x:
	rm xml_1

clear_test_2_x:
	rm xml_2

# Test correspondance dtd et xml MAC

test_d:
	gcc -o dtd DTD_test/test_xml_dtd.c validate_read.c structure.c christophe.c

test_1_d:
	gcc -o dtd_1 DTD_test/test_xml_dtd_part_1.c validate_read.c structure.c christophe.c

test_2_d:
	gcc -o dtd_2 DTD_test/test_xml_dtd_part_2.c validate_read.c structure.c christophe.c

clear_test_d:
	rm dtd

clear_test_1_d:
	rm dtd_1

clear_test_2_d:
	rm dtd_2

# Test correspondance dtd et xml Linux

linux_test_d:
	gcc -o linux_dtd DTD_test/test_xml_dtd.c validate_read.c structure.c christophe.c

linux_test_1_d:
	gcc -o linux_dtd_1 DTD_test/test_xml_dtd_part_1.c validate_read.c structure.c christophe.c

linux_test_2_d:
	gcc -o linux_dtd_2 DTD_test/test_xml_dtd_part_2.c validate_read.c structure.c christophe.c

linux_clear_test_d:
	rm linux_dtd

linux_clear_test_1_d:
	rm linux_dtd_1

linux_clear_test_2_d:
	rm linux_dtd_2

# partie christophe parsing DTD

christophe:
	gcc -o christophe christophe.c validate_read.c structure.c

clear_christophe:
	rm christophe