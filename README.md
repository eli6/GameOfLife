# Tests and Documentation for Game Of Life.

Doxygen files for generation of documentation are in folder "docs". Test files are in the folder "test". The other folders contain the code for GameOfLife.

## Requirements

To run the tests you need to have an environmental variable called ``$TOOLS_INCLUDE`` configured, that contains the file "catch.hpp".


## Getting Started

###Read Documentation

Clone the repo, first enter folder "docs"

```
cd docs
```
Then, from the docs folder: generate the Doxygen code, enter the html folder and open the index.html file to see it, this can be shortened to the following command:

```
doxygen Doxyfile && cd html && open index.html
```

Now you can read everything about GameOfLife!

###Run tests
The file "src/main.cpp" is commented out in CMakeLists.txt, so the Catch tests will run automatically.

## FAQ

Ask questions about this amazing Doxygen documentation!

## Authors

* **Fredrik Arhusiander**
* **Elin Fritiofsson**
