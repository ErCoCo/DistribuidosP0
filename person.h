#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

class Person {
	private:
		std::string dni, ss, name;
		int age;

	public:
		Person() {
			dni = "";
			ss = "";
			name = "";
			age = 0;
		}

		void setDni(std::string _dni) {
			dni = _dni;
		}

		std::string getDni() {
			return dni;
		}

		void save(std::string file) {
			FILE* f = fopen(file.c_str(), "w");

			int dataLen = dni.length() + 1;
			fwrite(&dataLen, sizeof(int), 1, f);
			fwrite(dni.c_str(), dataLen, 1, f);

			fclose(f);
		}

		void load(std::string file) {
			FILE* f = fopen(file.c_str(), "r");

			int dataLen;
			char* input = nullptr;
			fread(&dataLen, sizeof(int), 1, f);
			input = new char[dataLen];
			fread(input, dataLen, 1, f);
			dni = std::string(input);
			delete[] input;

			fclose(f);
		}
};
