# Roomba Implementation

Hello and welcome to this README! This documents my implementation of Roomba in C++.

## How to run

```bash
git clone https://flashhire@dev.azure.com/flashhire/PatrickYu/_git/PatrickYu
cd PatrickYu/Roomba
source ~/References/tools/setup.sh
# To run all automated tests
make run
# To execute step-by-step visualizations
make
./outputs/roomba_runner.out ./Test/raw/big.room
```

## Directory Structure

Note that each project folder has a `makefile` and `makefile.exp` used for code compilation.
All test cases were written using [GoogleTest](https://github.com/google/googletest) framework.
Memory leak checks were done via Valgrind.

### Directories
* /
    * Builds program
    * Runs all tests cases within GTest framework
* /execute
    * Builds program
    * Runs step-by-step Room and Roomba visualizations
* /Src
    * Builds library
    * Contains implementation of room environment, Roomba hardware and sensors, and Roomba traversal algorithm
* /Test
    * /raw
        * Contains raw room files
    * Builds library
    * Contains all test cases

## Known issues
- [ ] Roomba visualization outside initial grid dimensions on the left hand and upper sides

## Completed Ideas
- [x] Room Representation
- [x] Roomba Movement
- [x] Roomba Rotation
- [x] Roomba Cleaning
- [x] Roomba Breadth-first Exploration
- [x] One Action per Visualization Implementation
- [x] Room Visualization of Roomba Traversal
- [x] Roomba Visualization of Roomba Traversal 
- [x] Roomba with 4 Sensors (one per direction)
- [x] Accounted for Rotation in Graph Traversal Cost 

## Potential future work
- [ ] Minimal number of visits to every space 
- [ ] More adversarial test cases
- [ ] Noise model for sensor
- [ ] Sensor telling maximum distance to wall
- [ ] 1D sensor
- [ ] Detect known room on 2nd pass
- [ ] Noise model for motors
- [ ] Levels of dirtiness in the room
- [ ] Moving objects in the room
- [ ] Charging stations

**Thanks for reading me and have a lovely day!**
