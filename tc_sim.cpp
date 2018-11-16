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
		cout << "Usage: " << argv[0] << " datafile" << endl;
		return 1;
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

/* how often to start random */
#define RAND_START_FREQ	10
/* How long to stay random */
#define RAND_STOP_FREQ	4
/* How frequently to stay random for a longer interval */
#define RAND_LONG_NUM	4
/* How long to stay random for long interval */
#define RAND_CYCLES_MAX	100

float Adafruit_MAX31856::readThermocoupleTemperature(void) {
	static bool useRandom = false;
	static float avg = 0;
	static int count = 0, randCount = 0, randCycles = 0;
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
			f = vrand(avg);
			if (randCount == RAND_LONG_NUM - 1) {
				if (++randCycles >= RAND_CYCLES_MAX) {
					useRandom = false;
				}
			} else if (!(rand() % RAND_STOP_FREQ)) {
				useRandom = false;
			}
		} else if (!(rand() % RAND_START_FREQ)) {
			useRandom = true;
			randCount++;
			randCount %= RAND_LONG_NUM;
			randCycles = 0;
		} else {
			count++;
			avg = avg + (f - avg) / count;
		}
		
		
	} else {
		cout << "Not OK\n";
		f = vrand(0);
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

/* frand function */
float vrand(float x) {
	float y = frand();
	return (x - (0.0620762 * log(-1 + 1/y)));
}