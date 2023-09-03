ifndef lab
    # $(error "lab" variable is not defined. Please specify lab=<value> when running make.)
	lab=1
endif

LAB := lab_0$(lab)
EXE := lab_0$(lab)
CFLAGS := -Wall -Werror
CURDIR := $(shell pwd)

.DEFAULT_GOAL := debug

.PHONY: default debug profile
default:
	cmake -B build -G Ninja -DBUILD_LAB=$(lab) -DCMAKE_CXX_FLAGS="$(CFLAGS)" .
	cmake --build build
	ln -sf $(CURDIR)/build/$(LAB)/$(EXE) $(CURDIR)/build/main

debug:
	cmake -B build -G Ninja -DBUILD_LAB=$(lab) -DCMAKE_CXX_FLAGS="$(CFLAGS) -O0 -g" -DCMAKE_EXE_LINKER_FLAGS="-g" .
	cmake --build build
	ln -sf $(CURDIR)/build/$(LAB)/$(EXE) $(CURDIR)/build/main

profile:
	cmake -B build -G Ninja -DBUILD_LAB=$(lab) -DCMAKE_CXX_FLAGS="$(CFLAGS) -O0 -pg" -DCMAKE_EXE_LINKER_FLAGS="-g" .
	cmake --build build
	ln -sf $(CURDIR)/build/$(LAB)/$(EXE) $(CURDIR)/build/main
	cd build && ./main
	cd build && gprof main gmon.out | gprof2dot -s -w | dot -Tpdf -o output.pdf
	zathura build/output.pdf

.PHONY: run dbg
run:
	@# Run from build directory, not from current (to not generate gmon.out
	@# here in case of profiling).
	cd build && ./main

dbg:
	cgdb build/main

.PHONY: clean
clean:
	rm -rf build
