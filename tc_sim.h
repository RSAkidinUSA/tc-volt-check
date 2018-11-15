#include <stdint.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

#define MAX31856_FAULT_CJRANGE	0x01
#define MAX31856_FAULT_TCRANGE	0x02
#define MAX31856_FAULT_CJHIGH	0x04
#define MAX31856_FAULT_CJLOW	0x08
#define MAX31856_FAULT_TCHIGH	0x10
#define MAX31856_FAULT_TCLOW	0x20
#define MAX31856_FAULT_OVUV		0x40
#define MAX31856_FAULT_OPEN		0x80

#define MAX31856_TCTYPE_K		0x01

#define FILE_NAME_MAX	64

#define delay(a) usleep(a * 1000)

/* random float generation */
#define LO -100.00
#define HI 100.00
#define frand() LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)))

class Adafruit_MAX31856 {
	char src[FILE_NAME_MAX];
public:
	uint8_t readFault(void);
	void begin(void);
	void setThermocoupleType(int t);
	float readThermocoupleTemperature(void);
	void setSrc(char *filename);
	Adafruit_MAX31856(int pin_cs, int pin_di, int pin_do, int pin_clk);
};

class serial {

public:
	void begin(int t);
	void println(float f);
	void println(const char *c);
};

/* Functions */
void setup();
void loop();
