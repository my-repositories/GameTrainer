# download http://gnuwin32.sourceforge.net/downlinks/make.php
# or here: http://gnuwin32.sourceforge.net/packages/make.htm

ifeq ($(strip $(C)), Debug)
	CONFIGURATION = Debug
else
	CONFIGURATION = Release
endif

ifeq ($(strip $(A)), x86)
	ARCH = Win32
else
	ARCH = x64
endif

TARGET = GameTrainer
GENERATOR = "Visual Studio 16 2019"

IDE_NAME = clion

SOURCE_DIR = .
PROJECT_DIR = .
BIN_DIR_NAME = bin
OBJ_DIR_NAME = build
OBJ_DIR = ${OBJ_DIR_NAME}/${IDE_NAME}/${CONFIGURATION}-${ARCH}

build: clean compile link

clean:
	rm -rf ${BIN_DIR_NAME} ${OBJ_DIR_NAME}

compile:
	cmake -B ${OBJ_DIR} -S ${SOURCE_DIR} -G ${GENERATOR} -A ${ARCH} -DCONFIGURATION=${CONFIGURATION} ${PROJECT_DIR}

link:
	cmake --build ${OBJ_DIR} --target ${TARGET} --config ${CONFIGURATION} -j 8

copy:
	cp -r ./data/* ./bin/clion/Release-Win32