# download http://gnuwin32.sourceforge.net/downlinks/make.php
# or here: http://gnuwin32.sourceforge.net/packages/make.htm

ifeq ($(strip $(C)), Debug)
	CONFIGURATION = Debug
else
	CONFIGURATION = Release
endif

ifeq ($(strip $(A)), x64)
	ARCH = x64
	PLATFORM = x64
else
	ARCH = Win32
	PLATFORM = x86
endif

PROJECT_NAME = GameTrainer
PROJECT_VERSION = "1.2.3"
GENERATOR = "Visual Studio 16 2019"
TOOLCHAIN = msvc15

SOURCE_DIR = .
PROJECT_DIR = .
BIN_DIR_NAME = bin
OBJ_DIR_NAME = build
OBJ_DIR = ${OBJ_DIR_NAME}/${CONFIGURATION}-${ARCH}

run: clean configure build_all copy

clean:
	rm -rf ${BIN_DIR_NAME} ${OBJ_DIR_NAME}

configure:
	cmake \
	-B ${OBJ_DIR} \
	-S ${SOURCE_DIR} \
	-G ${GENERATOR} \
	-A ${ARCH} \
	-DMY_CONFIGURATION=${CONFIGURATION} \
	-DMY_PLATFORM=${PLATFORM} \
	-DMY_PROJECT_NAME=${PROJECT_NAME} \
	-DMY_PROJECT_VERSION=${PROJECT_VERSION} \
	-DMY_TOOLCHAIN=${TOOLCHAIN} \
	${PROJECT_DIR}

build_all:
	cmake \
	--build ${OBJ_DIR} \
	--config ${CONFIGURATION} \
	-j 8

copy:
	cp -r ./data/* ./bin/${CONFIGURATION}/*/
