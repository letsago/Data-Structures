# About

This file is markdown file. It is recommended you open this via: `markdown: open preview` in VSCode.

# Dependencies

This project now depends on googletest. Installation instructions below.

Once installed, `make` for the project will complain until the shell has environment variable `GTEST_DIR` and `PROJECT_DIR` set.

You make set it via the following command in terminal: 
>`export GTEST_DIR=~/gtest/build`

To avoid doing this repeatedly, you can modify your **workspace settings** in vscode with the following setting.
```json
		"terminal.integrated.env.linux": {
			"GTEST_DIR" : "~/gtest",
			"PROJECT_DIR" : "${workspaceFolder}"
		}
```

# Installing googletest

```bash
cd ~/
git clone https://github.com/google/googletest.git
mkdir -p ~/gtest/build
cd ~/gtest/build
cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/.. -DBUILD_SHARED_LIBS=OFF -DBUILD_GMOCK=OFF -DINSTALL_GTEST=ON ../../googletest/
make
make install
```

# Compiling the test

Run `make` from the `PROJECT_ROOT` folder.

If you wish you compile just one of them, just enter the folder you want to compile, but make does handle dependencies for you!

Should you only change a header file however, make sure you call: `make rebuild.`

# Running the test

Run `make run` from the `PROJECT_ROOT` folder.

To pass in arguments in the executable:

```Makefile
make run ARGS=--help
make run ARGS=--gtest_list_tests
make run ARGS="--check_for_leaks --gtest_filter=PigLatin*"
```
