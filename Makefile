BUILD_DIR = ./build
DEST_DIR = ./bin
DEST_EXE_NAME = cmake_tutorial.exe # linux下则把.exe去掉

all: build
	cd $(BUILD_DIR); make -j4
run:
	cd $(DEST_DIR); ./$(DEST_EXE_NAME)
clean:
	rm $(BUILD_DIR) -rf
build:
	mkdir $(BUILD_DIR); cd $(BUILD_DIR); cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" ..
install:
	cd $(BUILD_DIR); make install
test:
	cd $(BUILD_DIR); make test
