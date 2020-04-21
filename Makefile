# download http://gnuwin32.sourceforge.net/downlinks/make.php
# or here: http://gnuwin32.sourceforge.net/packages/make.htm

C ?=Release
ifeq ($(strip $(C)), Debug)
	CONFIGURATION = Debug
else
	CONFIGURATION = Release
endif

T ?=0
ifeq ($(strip $(T)),0)
	GT_ENABLE_TESTING=0
else
	GT_ENABLE_TESTING=1
endif

A ?=x64
ifeq ($(strip $(A)),x64)
	ARCH=x64
	PLATFORM = x64
else
	ARCH=Win32
	PLATFORM = x86
endif

A ?=latest
ifeq ($(strip $(AT)),latest)
	ALPINE_TAG = latest
else
	ALPINE_TAG = $(AT)
endif

UNAME := $(shell uname)
ifeq ($(findstring MINGW,$(UNAME)),MINGW)
    GENERATOR = "Visual Studio 16 2019"
    GENERATOR_PARAMS=-G ${GENERATOR} -A ${ARCH}
    GT_OS=win
else
    GENERATOR = "Unix Makefiles"
    GENERATOR_PARAMS=-G ${GENERATOR}
    GT_OS=unix
endif

PROJECT_NAME = GameTrainer
PROJECT_VERSION = "1.2.3"

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
	${GENERATOR_PARAMS} \
	-DGT_OS=${GT_OS} \
	-DGT_ENABLE_TESTING=${GT_ENABLE_TESTING} \
	-DCOVERAGE=${GT_ENABLE_TESTING} \
	-DGT_CONFIGURATION=${CONFIGURATION} \
	-DGT_PLATFORM=${PLATFORM} \
	-DGT_PROJECT_NAME=${PROJECT_NAME} \
	-DGT_PROJECT_VERSION=${PROJECT_VERSION} \
	-DGT_TOOLCHAIN=${TOOLCHAIN} \
	${PROJECT_DIR}

build_all:
	cmake \
	--build ${OBJ_DIR} \
	--config ${CONFIGURATION}

copy:
	cp -r ./app/resources/data/* ./bin/${CONFIGURATION}/*/

release:
	git tag $$(git tag -l | tail -n 1 | sed -E "s/^([0-9]+.[0-9]+.)[0-9]+$$/\1/")$$((1 + $$(git tag -l | tail -n 1 | tr "." "\\n" | tail -n 1)))
	git push origin $$(git tag -l | tail -n 1)

test: build_tests run_tests

build_env:
	docker build \
	--rm \
	--no-cache \
	--build-arg ALPINE_TAG=${ALPINE_TAG} \
	-f .ci/docker/env.Dockerfile \
	-t gt/env-alpine:${ALPINE_TAG} \
	.

build_tests:
	docker build \
	--rm \
	--no-cache \
	--build-arg ALPINE_TAG=${ALPINE_TAG} \
	-f .ci/docker/tests.Dockerfile \
	-t gt/tests-alpine:${ALPINE_TAG} \
	.

run_tests:
	docker run \
	--rm \
	--name gt__tests \
	gt/tests-alpine

