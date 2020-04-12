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

install:
	.\\.ci\\install-testing-deps.bat

clean:
	rm -rf ${BIN_DIR_NAME} ${OBJ_DIR_NAME}

configure:
	cmake \
	-B ${OBJ_DIR} \
	-S ${SOURCE_DIR} \
	-G ${GENERATOR} \
	-A ${ARCH} \
	-DGT_CONFIGURATION=${CONFIGURATION} \
	-DGT_PLATFORM=${PLATFORM} \
	-DGT_PROJECT_NAME=${PROJECT_NAME} \
	-DGT_PROJECT_VERSION=${PROJECT_VERSION} \
	-DGT_TOOLCHAIN=${TOOLCHAIN} \
	${PROJECT_DIR}

build_all:
	cmake \
	--build ${OBJ_DIR} \
	--config ${CONFIGURATION} \
	-j 8

copy:
	cp -r ./app/resources/data/* ./bin/${CONFIGURATION}/*/

release:
	git tag $$(git tag -l | tail -n 1 | sed -E "s/^([0-9]+.[0-9]+.)[0-9]+$$/\1/")$$((1 + $$(git tag -l | tail -n 1 | tr "." "\\n" | tail -n 1)))
	git push origin $$(git tag -l | tail -n 1)
