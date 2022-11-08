# rnbo-command-line

This is a little demo of how you might use RNBO in a command-line app. It's 
really hacked together, and only intended to be used for demonstration.

## Dependencies

First and foremost, you'll need RNBO and CMake.

You'll also need `libsndfile` for file I/O, available here http://www.mega-nerd.com/libsndfile.
I am not currently smart enough to figure out how to make this work in a nice and clean way
with CMake. If you are a smart and generous person, please don't hesitate to help me 
understand how to make this dependency less clunky. In the meantime, just download libsndfile
and configure/make it locally.

```
cd src
curl -o libsndfile.tar.gz http://www.mega-nerd.com/libsndfile/files/libsndfile-1.0.28.tar.gz
tar -xf libsndfile.tar.gz
rm -rf libsndfile.tar.gz
cd libsndfile-1.0.28 && ./configure && make
```

You'll only need to do this one time, of course, so that the library is available.

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

