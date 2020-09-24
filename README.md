# Tests for ex6 - summer course c++
## Usage
On your project directory, clone the tests using:
```$xslt
$ git clone https://github.com/yairfine/cpp-tests-ex6.git
```

Copy your `HashMap.hpp` file to the tests directory, using:
```$xslt
WINDOWS:  $ copy .\HashMap.hpp .\cpp-tests-ex6
LINUX:    $ cp HashMap.hpp ./cpp-tests-ex6
```

Move to the tests directory, using:
```$xslt
$ cd cpp-tests-ex6
```

Compile the tests, using:
```$ xslt
$ g++ tests.cpp -std=c++14 -o compiledTests
```

Run the tests, using:
```$ xslt
WINDOWS:  $ .\compiledTests.exe
LINUX:    $ ./compiledTests
```

## Valgrind
For running with Valgrind, **compile again** with `-DVAL` flag:
```$ xslt
$ g++ tests.cpp -std=c++14 -DVAL -o compiledTests
```
And run:
```$ xslt
$ valgrind --leak-check=full --track-origins=yes compiledTests
```

## Good luck!
![coding gif](https://media.giphy.com/media/iAKXyzgLVtKsU/giphy.gif)
