# About

This file is markdown file. It is recommended you open this via the command: `markdown: open preview` in VSCode.

# Dependencies

This project now depends on googletest. Installation instructions below.

Once installed, `make` for the project will complain until the shell has environment variable `GTEST_DIR` and `PROJECT_DIR` set.

You make set it via the following command in terminal:
```bash
export GTEST_DIR=~/gtest/build
export PROJECT_DIR=/ *insert path to your project*
```

To avoid doing this each time you open a vscode terminal, you can modify your **workspace settings** in vscode with the following setting.
> Preferences: Open Workspace Settings
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
cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/.. -DBUILD_SHARED_LIBS=ON -DBUILD_GMOCK=OFF -DINSTALL_GTEST=ON ../../googletest/
make
make install
rm -rf ~/googletest
```

# Compiling the test
> `make`

Make handles all dependencies and won't do any more work than it needs to! That means if you change any files, it will only rebuild the necessary items.

## Compile Issues
If you run into build errors that you think are not caused by you, use `make rebuild`. This will clean, and then rebuild everything.

If you have renamed files, run `make fullclean` before calling `make`.

# Running the test

> `make run`

This will also build any changes!

## Memory Leak validation
> `make valgrind`

This will run your tests along with memory leak checks. `$(PROJECT_DIR)/outputs/valgrind.log` will contain the memory leak output. If you don't understand what this file is saying at any point, please ask me.
