#include "tc_sim.h"

#include <fstream>
#include <stdlib.h>
#include <time.h>

serial Serial;
extern Adafruit_MAX31856 max;
std::ifstream inFile;

int main (int argc, char **argv) {
	if (argc >= 2) {
		cout << "1\n";
		max.setSrc((char *)argv[1]);
		cout << "2\n";
	} else {
		max.setSrc(NULL);
	}
	setup();
	while (1) {
		loop();
	}
	return 0;
}

/* Thermocouple functions */

Adafruit_MAX31856::Adafruit_MAX31856(int pin_cs, int pin_di, int pin_do, int pin_clk) {

}

void Adafruit_MAX31856::setSrc(char *filename) {
	inFile.close();
	if (filename) {
		strncpy(src, filename, FILE_NAME_MAX - 1);
		inFile.open(src, std::ifstream::in);
	}
	srand(time(NULL));
}

void Adafruit_MAX31856::begin(void) {
	cout << "Began" << endl;
}

uint8_t Adafruit_MAX31856::readFault(void) {
	return 0;
}

void Adafruit_MAX31856::setThermocoupleType(int t) {

}

/* 1 in RAND_FREQ times the value will be random */
#define RAND_START_FREQ	10
#define RAND_STOP_FREQ	4

float Adafruit_MAX31856::readThermocoupleTemperature(void) {
	static bool useRandom = false;
	float f;
	char junk;
	if (inFile) {
		/* read in next value from file */
		inFile >> f;
		
		/* if bad value skip it */
		while (inFile.fail()) { 
			inFile.clear();
			inFile >> junk;
			/* If file ends restart */
			if (inFile.eof()) { 
				inFile.clear();
				inFile.close();
				inFile.open(src, std::ifstream::in);
			}
			inFile >> f;
		}

		/* Randomly set it to a random value */
		if (useRandom) {
			f = frand();
			if (!(rand() % RAND_STOP_FREQ)) {
				useRandom = false;
			}
		} else if (!(rand() % RAND_START_FREQ)) {
			useRandom = true;
		}
		
		
	} else {
		cout << "Not OK\n";
		f = frand();
	}
	return f;
}

/* Serial functions */

void serial::begin(int t) {

}

void serial::println(float f) {
	cout << f << endl;
}

void serial::println(const char *c) {
	cout << c << endl;
}