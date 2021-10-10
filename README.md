# GameOfLife University Project

[Game of Life!](https://sv.wikipedia.org/wiki/Game_of_Life) is a zero-player game, simulating cells on screen as live or dead according to an initial configuration. This code has been copied to Github from my Bitbucket repository [GameOfLife!](https://bitbucket.org/eli6/gameoflife/src/master/) and if you are interested, it's better to download the project directly from the Bitbucket link since some links to external projects are broken here on GitHub.

My contribution was writing the test suite for the application together with another student. The tests can be found in the "tests" folder and run according to the description below.

<img width="811" alt="Skärmavbild 2021-10-10 kl  16 03 33" src="https://user-images.githubusercontent.com/11839563/136699026-0fdabe5d-b634-43eb-a69b-a1f8246567b0.png">

# Tests and Documentation for Game Of Life.

Fork of GameOfLife project adding tests and documentation for the project. This main page is the same as the Bitbucket README to avoid duplicating the information there.

Doxygen files for generation of documentation are in folder "docs". Test files are in the folder "test". The other folders contain the code for GameOfLife.

## Requirements

No specific requirements

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

Run the executable GameOfLife-test in cmake-build-debug folder (or compile with GameOfLife-test-configuration) to run the tests.

## FAQ

Ask questions about this amazing Doxygen documentation and we will answer you!

## Authors

* **Fredrik Arhusiander**
* **Elin Fritiofsson**
