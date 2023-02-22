# OpenGl-Template
This is a template repository for graphics, using ImGui and OpenGL.  
Is only tested on Linux.

# Dependencies
- OpenGl3
- GLFW (http://www.glfw.org):
  - Linux:
    - apt-get install libglfw-dev
  - Mac OS X:
    - brew install glfw
  - MSYS2:
    - pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw

# Compile
To compile on linux you will need [premake5](https://premake.github.io/).
```sh
premake5 gmake2
make
```
# Running
The binaries will be in *bin/* just run them.
```sh
./bin/Debug/OpenGLTemplate/OpenGLTemplate
```
