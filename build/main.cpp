#include "../src/core/core.h"

int main(int argc, char *argv[]) {
    // call the interface
    switch(argc) {
        case 1:
            interface("");
            break;
        case 2:
            interface(argv[1]);
            break;
        default:
            std::cout<<"ERROR: incorrect format";
            break;
    }
    return 0;
}