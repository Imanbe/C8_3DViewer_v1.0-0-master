#include "parser.h"

int main() {
    data_t obj = {};
    const char* filename = "/opt/goinfre/marcelit/C8_3DViewer_v1.0-0-master/src/machine.obj";
    Parsing(filename, &obj);
    return 0;
}