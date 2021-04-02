#include "xml.h"

int test1();
int test2();

int main() {
	int return_value = 0;
	return_value += test1();
	return_value += test2();
	return return_value;
}

int test1() {
	struct xml *xml = open_xml("test1.xml");
	open_tag(xml, "tag_test", 2, "provolone", "biscotto");
	close_tag(xml, "tag_test");
	close_xml(xml);
	
	printf("Test1 passed!\n");

	return 0;
}

int test2() {
	struct xml *xml = open_xml("test2.xml");
	open_tag(xml, "tag1", 0);
	open_tag(xml, "tag2", 4, "a", "b", "c", "d");
	inline_tag(xml, "inline_tag", "Test", 0);
	close_tag(xml, "tag2");
	open_tag(xml, "tag3", 0);
	write_str(xml, "Test2");
	close_tag(xml, "tag3");
	close_tag(xml, "tag1");
	close_xml(xml);

	printf("Test2 passed!\n");

	return 0;
}
