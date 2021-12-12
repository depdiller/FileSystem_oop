#include <iostream>
#include "FileSystemLib/src/FileSystem.h"
#include <cstdio>

int main() {
    FILE *associatedFile;
    associatedFile = fopen("C:\\disk.txt", "a+");
    if (associatedFile != nullptr) {
        System::FileSystem system = System::FileSystem(associatedFile);

    }
}