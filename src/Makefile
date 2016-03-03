APP=qstreamlines
PRO=$(APP).pro

all: help

help:
	@echo make [ clean app run ]

app:
	mkdir -p build && cd build && qmake ../$(PRO) -r -spec linux-g++ CONFIG+=release && make -j4

clean:
	-rm -rf build

run:
	./build/$(APP) ../examples/swirl.json

