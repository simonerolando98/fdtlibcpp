# ADT Template Library
This library aims to provide a comprehensive interface, similar to C++'s STL, for
many Abstract Data Types. The collection will expand every once in a while.
All ADTs will be provided as simple C++ include files, in order to facilitate the use
and integration within ongoing projects.

## 1. Requirements
Any **C++20** compliant compilers shold work. It is recommended to use CMake if you need
to test the ADTs before usage. If you need to run tests, feel free to clone the repository
using the command ```git clone --recurse https://github.com/simonerolando98/fdtlibcpp.git```
in order to clone te Goole Test library included as submodule of the repository.<br><br>
**WARNING:** to use CMake in order to generate projects for your IDEs, you need to clone
using the ```git clone --recurse``` command, otherwise project generation will fail due to
missing files.

## 2. Installation
Run ```git clone https://github.com/simonerolando98/fdtlibcpp.git``` directly into your
project folder. The git repository provides a ```CMakeLists.txt``` for every subfolder containing
any source or header file. It is not required to generate a CMake project or to use CMake to build
any of the header files.

## 3. Contribution
Please feel free to comment and submit issues and bug reports on this GitHub repo. This project is made merely for fun and, maybe, as a **already built** alternative to many other ADT template libraries.<br><br>
**DISCLAIMER:** by no means I pretend to be a C++ all-rounder, which means that constructive criticism is well accepted. This obviously means that any **MEAN** or **INEDUCATED** comment will not be tollerated and will be immediately removed.
<br><br>
Anyway, any **constructive criticism** is encouraged, especially if it can improve my C++ knowledge.

## 4. Disclaimers
This library will start as a **poorly documented C++ code**. Every function in every ADT class possesses a **Doxygen XML-style comment block**, meaning that sometimes in the (possibly near) future, it'll be populated and **HTML/PDF/Tex documentation will be uploaded to this GitHub repo** in order to keep the understanding of the library as simple as possible.
