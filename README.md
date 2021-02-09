# Restaurant food order serving
In this project, we have tried to mimic a random day at a restaurant. The restaurant has a chef and two waiters. The idea over here is to exercise most of the concepts learnt as part of the C++ udacity nano-degree course work. The current working rules of this project are as follows:
* The restaurant is open only for specific period of time. This is currently hardcoded to be around 1000 milli seconds. In order to prevent worker burnout, the waiter will block on taking new orders when the number of pending orders hit a limit. Currently, that limit is also hardcoded and set to 10.
* During the time, the "restaurant" is open for business, a random number of customers can walk in and place an order. The order can be for dine-in or take-out. Due to the current pandemic, the two options are rolled into one and no differentiation is made. The customer randomly makes a menu order. Each order has a preparation time associated with it. Each customer can make only one order from the menu.

### Planned future updates
* The customer can query on the possible wait time till their order can get served. This is subject to change.
* There are only limited number of tables. There is no restriction on the number of persons/table.
* If no table is available, and if the customer waits till a table becomes available.
* After the meal is served, the customer eats for a random amount of time. The random time limit is anywhere between 4-6 seconds.
* A meal prepared in the kitchen consists of multiple dishes. A dish can either be an entree or main course. A meal is the plating of all the dishes along with the garnish. Here, it is assumed there are multiple cooks who prepare a specific dish. The dish is finally arranged and garnished by the chef. The delivery of the prepared meal is then served to the specific table by the multiple waiters. We would be using multi-threading for the preparation of the various components that make a dish.

## Dependencies for Running Locally
* cmake >= 3.11.3
    * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* clang/clang++ >= 10.0
    * All OSes

## Basic Build Instructions
1. Clone this repo.
### Linux/Mac
1. Make a build directory in the top level directory: `mkdir build && cd build`
1. Compile: `cmake .. && make`
1. Run it: `./restaurantFoodPrep <menuFileName>`.

## Testing the implementation
There is an example Menufile that can be used to check the program.
`./restaurantFoodPrep ../data/Menu.txt`

## Rubric points addressed
### Loops, Functions, I/O
| Rubric point  | Location |
| ------------- | ------------- |
| The project demonstrates an understanding of C++ functions and control structures.  |   Yes, check all the files
| The project reads data from a file and process the data, or the program writes data to a file.  | [Menu](src/Menu.cpp)
The project accepts user input and processes the input.  |   [Main](src/Main.cpp)

### Object Oriented Programming
| Rubric point  | Location |
| ------------- | ------------- |
| The project uses Object Oriented Programming techniques.  | Yes, check all the files
| Classes use appropriate access specifiers for class members. | Yes, check all the files
| Class constructors utilize member initialization lists. | [Menu](src/Menu.h)
| Classes encapsulate behavior. | Yes, check all the files

### Memory Management
| Rubric point  | Location |
| ------------- | ------------- |
| The project makes use of references in function declarations. | Yes
| The project uses destructors appropriately. | [ThreadSafeCout](src/ThreadSafe.h)
| The project uses move semantics to move data, instead of copying it, where possible. | Yes, check all the files.
| The project uses smart pointers instead of raw pointers. | Yes, check all the files.

### Concurrency
| Rubric point  | Location |
| ------------- | ------------- |
| The project uses multithreading. | [Restaurant](src/Restaurant.cpp),  and [Main](src/Main.cpp)
| The project uses multiple threads in the execution. | [Main](src/Main.cpp)
| A promise and future is used in the project. | [Main](src/Main.cpp)
| A mutex or lock is used in the project. | [Restaurant](src/Restaurant.cpp), [ThreadSafeCout](src/ThreadSafe.h), and [Main](src/Main.cpp)
| A condition variable is used in the project. | [Restaurant](src/Restaurant.cpp)