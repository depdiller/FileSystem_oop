#include <cstdio>
#include "FileSystem.h"

int main() {
    FILE *associatedFile;
    associatedFile = fopen("C:\\disk.txt", "wb+");
    if (associatedFile != nullptr) {
        System::FileSystem sys(associatedFile);
    }


}