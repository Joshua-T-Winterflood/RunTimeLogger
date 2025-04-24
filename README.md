# RunTimeLogger

## Description
This is a small Project which provides a simple Usage pattern to benchmark applications and parts of a bigger system. The RunTimeLogger class logs the runtime of custom parts of an application into the console and into a LogFile located in the log directory.

## Requirements
- CMake see also CMakeLists.txt
- C++ Compiler, Currently Built for Clang

## Usage
In order to build the project with Cmake the following command from the top-level directory :
```
mkdir build
mkdir log
cd build
cmake ..
make 
```
You can then run the project with :
```
./RunTimeLogger
```
Note that you will be prompted for a Name of the LogFile when running the project.

Note that for the correct usage the log directory needs to be in the same directory as the build directory.

## Contributing & Future Work
The RunTimeLogger currently has some minor concurrency issues and needs to be extended in a way such that the overhead of deploying the RunTimeLogger onto an application doesn`t impact the runtime of the application. This RunTimeLogger is meant for rough estimations as to where the most of the runtime is spent rather than measuring exact runtimes.

If you have any deeper knowledge on how to resolve these concurrency issues feel free to create a PR, I`d be more than glad to review it.
