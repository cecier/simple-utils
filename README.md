# simple-utils

Small and simple C++ utilities.

## Features

* `simple_vector` — simple dynamic array
* `simple_logger` — simple logging utility
* `simple_counter` — simple file counter

## Requirements

* C++23
* CMake 3.24+

## Usage

Include the headers you need:

```cpp
#include "simplevector.h"
#include "simplelogger.h"
#include "simple_counter.h"
```

### Vector

```cpp
ss::Vector<int> vector;

vector.PushBack(10);
vector.PushBack(20);

LOG_INFO << vector[0];
```

### Logger

```cpp
LOG_DEBUG << "Debug message";
LOG_INFO << "Info message";
LOG_WARNING << "Warning message";
LOG_ERROR << "Error message";
```

### Counter

```cpp
sscount::FileChecker checker("example.txt");
```

## License

See [LICENSE](LICENSE).
