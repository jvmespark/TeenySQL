
CPP_SOURCES = $(wildcard *.cpp ../src/compiler/*.cpp ../src/core/*.cpp ../src/engine/*.cpp ../src/compiler/types/*.cpp ../src/networking/*.cpp)
HEADERS = $(wildcard *.h ../src/compiler/*.h ../src/core/*.h ../src/engine/*.h ../src/networking/*.h)

build:
	g++ -std=c++17 -o teenySQL.exe -g ${CPP_SOURCES}
run:
	make build
	./teenySQL.exe
stats:
ifeq ($(OS),Windows_NT)
	$(info ERROR: 'cloc' not available on Windows)
else
	cloc ${CPP_SOURCES} ${HEADERS}
endif