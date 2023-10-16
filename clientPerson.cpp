#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operations.h"
#include "person.h"

int main() {
	Person p1 = Person();

	p1.setDni("123456X");
	p1.save("personPepito.txt");
}
