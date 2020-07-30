# Toolkit-examples
This repository contains examples that shows how to use components of the c3d kernel.
Also there are wrappers over the MFC and Qt GUI libraries in the platform directory.

## Build:
* Put the **C3D Toolkit** libraries in the ***toolkit-examples/c3d-libs*** directory. 
  You may request **C3D Toolkit** libraries on [https://c3dlabs.com](https://c3dlabs.com)  
* If you want to use **Qt GUI** library download and install it from [qt.io/download](https://www.qt.io/download) and 
  define environment variable ***Qt5_Dir***.
* Install CMake 3.14 version and higher.
* Generate the project using CMake and build it.

## Examples list:  
* param_cube/  
The example shows how to make a parametric cube using C3D Solver component and to visualize it using C3D Vision component.  
![alt text](param_cube/screenshots/preview.png?raw=true "example preview")
* vision_widgets/  
The example shows how to make the handlers for change or move geometry of the scene using C3D Vision component.  
![alt text](vision_widgets/screenshots/preview.png?raw=true "example preview")
