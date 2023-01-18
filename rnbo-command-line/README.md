# rnbo-command-line

This is a little demo of how you might use RNBO in a command-line app. It's 
really hacked together, and only intended to be used for demonstration.

## Dependencies

First and foremost, you'll need RNBO and CMake. This code also depends on a 
third party library called libsndfile, and huge thanks to @rmpowell77 for adding
that dependency to CMakeLists so that we don't have to download and build it as
a separate step. So if you've got RNBO and CMake you can skip ahead to Directions.

## Directions

This example is currently pretty limited in what it can do. It processes a stereo file
called "anton.aif" in the src directory, producing a stereo output file called
"anton-out.aif".

1. Make a Max patch with stereo inputs and stereo outputs.
2. Export that patch into `src`
3. Make a directory in `src` called `build`
4. `cd build && cmake ..`
5. `cmake --build .`
6. This will put an executable `RNBOCommandLine` in `src`. Run this thing to do the thing.

