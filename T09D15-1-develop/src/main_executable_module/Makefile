CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=
SOURCES=main_executable_module.c ../data_libs/data_io.c ../data_libs/data_sort.c ../data_libs/data_stat.c ../data_module/data_process.c ../yet_another_decision_module/decision.c
OBJECTS=$(SOURCES:.c=.o)
QUEST3=../../build/Quest_3
QUEST4=../../build/Quest_4
QUEST5=../../build/Quest_5
QUEST6=../../build/Quest_6

all: $(SOURCES) $(QUEST3)
$(QUEST3): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

build_with_macro: $(SOURCES) $(QUEST4)
$(QUEST4): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(QUEST4): CFLAGS += -D USE_MACROS

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(QUEST3) $(QUEST4) $(QUEST5) $(QUEST6) *.a *.o *.so $(OBJECTS)

rebuild:
	$(MAKE) clean
	$(MAKE) all

data_stat.a: ../data_libs/data_stat.o
	ar r $@ $<

build_with_static: $(SOURCES) $(QUEST5)
$(QUEST5): $(OBJECTS) data_stat.a
	$(CC) $(LDFLAGS) $(filter-out ../data_libs/data_stat.o,$(OBJECTS)) data_stat.a -o $@

data_process.so: ../data_module/data_process.o ../data_libs/data_stat.o
	$(CC) $(LDFLAGS) -shared $^ -o $@

build_with_dynamic: $(SOURCES) $(QUEST6)
$(QUEST6): $(OBJECTS) data_process.so
	$(CC) $(LDFLAGS) $(filter-out ../data_module/data_process.o,$(OBJECTS)) data_process.so -o $@