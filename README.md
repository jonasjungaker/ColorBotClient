# ColorBotClient
A client for the color bot game written by Rasmus Ahlbäck (link to be added)

## Installation
To configure and compile the project follow the instructions below. 

### Requirements
For compiling the project you need to have installed a recent Python installation. If you want to run the binary in debug-mode then you also need to have installed the Python Debug symbols and Debug binaries, this is done through the installer. 

Your system also needs to have a fairly recent installation of OpenGL, Windows usually has this preinstalled. 

For every other dependancy, these will be compiled together with the rest of the project if you are using CMake and `recurse-submodules` with git. 

### Compile with CMake
Clone the repository with the command:

`git clone --recurse-submodules https://github.com/jonasjungaker/ColorBotClient`

and configure the repository with cmake (for an out-of-tree build):

`cmake -S . -B build`

and then compile the project with:

`cmake --build build --config Release`

You will find the comiled binary in a folder found at `build/bin/Release/client.exe` when compiling for a Windows target. 

## Usage
Start the compiled binary to start the client, you need to have a routable address to the game server and write this in the host configuration window. When you are connected to the server, you choose a path to a bot written in Python and matchmake on the server. 

## Contribution
Copyright Jonas Jungåker 2024
