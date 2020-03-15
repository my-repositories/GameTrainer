# download http://gnuwin32.sourceforge.net/downlinks/make.php
# or here: http://gnuwin32.sourceforge.net/packages/make.htm

target = "GameTrainer"
generator = "Visual Studio 16 2019"
arch = "Win32" # Win32 || Win64
configuration = "Release"
ideName = "clion"

sourceDir = "."
projectDir = "."
objDirName = "build"
objDir = $(addprefix $(objDirName)\\\\,$(ideName))

build: clean compile link
build2:
	echo $(objDir)

clean:
	rm -rf bin ${objDirName}

compile:
	cmake -B $(objDir) -S $(sourceDir) -G ${generator} -A ${arch} ${projectDir}

link:
	cmake --build $(objDir) --target $(target) --config $(configuration) -j 8

copy:
	cp -r ./data/*.lua ./bin/clion/Release