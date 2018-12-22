# Age of Agatha
Age of Agatha is a project to create a medieval fantasy MMORPG.  This means there will be many races, magic, possibly early guns, and if we get to it then even steampunk airships.  Our focus is on actions and content.  We want to make sure there is depth to actions players can take to impact their world and decisions they can make.  This does not mean we are going to completely neglect world building or character development but rather that it is not our focus for development.

For more information please visit our [github pages.](https://kyrasuum.github.io/AgeOfAgatha/index.html)

### Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
```sh
$ git clone https://github.com/Kyrasuum/AgeOfAgatha.git
$ make clean
$ make
```
You should now have a directory called AgeOfAgatha created in the directory where your cmd was looking at.  Within this directory there will be a 'run.exe' this is the program executable.

### Prerequisites
What things you need to install the software and how to install them
```
opengl - should come with your graphics drivers
```

### Installing
A step by step series of examples that tell you how to get a development env running
```sh
$ git clone https://github.com/Kyrasuum/AgeOfAgatha.git
```
You should now have a directory called AgeOfAgatha created in the directory where your cmd was looking at.  The 'src' directory contains all the code for the AgeOfAgatha specificially.  'deps' contains any library dependencies which are precompiled into .dll's for your convenience.

To compile the program navigate your cmd to the root AgeOfAgatha Directory and use the following command:
```sh
$ make
```
This will create a 'run.exe' in the same directory which is the program executable.
If problems occur after edits to src, then a clean make will usually fix it which similarly with:
```sh
$ make clean
$ make
```

### Built With
* Makefile - the compiling automation
* G++ - the compiler
* Opengl - the graphics library
* FreeGlut, Glad - the modernized opengl library specifically used
* GLM - for mathematical matrix operations
* Wings3D - for 3D models

### Contributing
Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

### Versioning
Github is our version control, the master should have our latest working version.

### Authors
* ***Phillip Lorentz*** - Primary Contributor - [Github Account](https://github.com/Kyrasuum)

### License
This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

### Acknowledgments
* Hat tip to anyone under built with section
* Stackoverflow for general troubleshooting
* Kronos wiki websites for opengl queries
* Wings3D for providing an open source free for use 3d modelling software

### Final Word
We appreciate your support.
-Team of Age of Agatha
