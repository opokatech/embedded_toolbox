all:
	@echo "Targets:"
	@echo " build     - build and run tests"
	@echo " run_tests - as above, but rebuild everything"
	@echo " clean     - removes created files and directories"

.PHONY: build
build:
	@cmake -S . -B build
	@cmake --build build && ./build/bin/tests
	@rm -f compile_commands.json
	@ln -s build/compile_commands.json


.PHONY: run_tests
run_tests:
	@rm -rf build
	@mkdir build && cd build && cmake .. && make && ./bin/tests


.PHONY: clean
clean:
	@rm -rf build
	@rm -f compile_commands.json
