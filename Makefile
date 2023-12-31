ifndef lab
    # $(error "lab" variable is not defined. Please specify lab=<value> when running make.)
	lab=3
endif

LAB := lab_0$(lab)
EXE := lab_0$(lab)
TEST := lab_0$(lab)_test
CFLAGS := -Wall -DMEASURE_STACK
CURDIR := $(shell pwd)

.DEFAULT_GOAL := debug

.PHONY: default debug profile
default:
	cmake -B build -G Ninja -DBUILD_LAB=$(lab) -DCMAKE_CXX_FLAGS="$(CFLAGS) -O0" .
	cmake --build build
	ln -sf $(CURDIR)/build/$(LAB)/$(EXE) $(CURDIR)/build/main
	ln -sf $(CURDIR)/build/$(LAB)/$(TEST) $(CURDIR)/build/test

debug:
	cmake -B build -G Ninja -DBUILD_LAB=$(lab) -DCMAKE_CXX_FLAGS="$(CFLAGS) -O0 -g" -DCMAKE_EXE_LINKER_FLAGS="-g" .
	cmake --build build
	ln -f $(CURDIR)/build/$(LAB)/$(EXE) $(CURDIR)/build/main
	# ln -f $(CURDIR)/build/$(LAB)/$(TEST) $(CURDIR)/build/test

profile:
	cmake -B build -G Ninja -DBUILD_LAB=$(lab) -DCMAKE_CXX_FLAGS="$(CFLAGS) -O0 -pg" -DCMAKE_EXE_LINKER_FLAGS="-g" .
	cmake --build build
	ln -f $(CURDIR)/build/$(LAB)/$(EXE) $(CURDIR)/build/main
	ln -f $(CURDIR)/build/$(LAB)/$(TEST) $(CURDIR)/build/test
	cd build && ./main
	cd build && gprof main gmon.out | gprof2dot -s -w | dot -Tpdf -o output.pdf
	zathura build/output.pdf

.PHONY: run dbg test
run:
	@# Run from build directory, not from current (to not generate gmon.out
	@# here in case of profiling).
	cd build && ./main

test:
	@# Run from build directory, not from current (to not generate gmon.out
	@# here in case of profiling).
	cd build && ./test --gtest_color=yes

dbg:
	cgdb build/main

p:
	python lab_01/plot.py

.PHONY: clean
clean:
	rm -rf build
