// Simple logger test file


#include "simplelogger.h"


int main() {

    LOG_ERROR << "test";
    LOG_WARNING<< "test";
    LOG_INFO << "test";
    LOG_DEBUG << "test";

    return 0;
}
