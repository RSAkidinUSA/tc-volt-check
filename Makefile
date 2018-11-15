APP = tc_sim.app
CPPFLAGS += -Wall -Werror -DTC_SIM
CC = g++

.PHONY: clean

all: clean build

build: $(APP)

$(APP): tc_sim.o tc_volt.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $(LDFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf $(APP) *.o
