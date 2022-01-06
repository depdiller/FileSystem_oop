#include <iostream>
#include <cstdio>
#include "FileSystem.h"

int main() {
    FILE *associatedFile;
    associatedFile = fopen("C:\\disk.txt", "a+");
    if (associatedFile != nullptr) {
        System::FileSystem system(associatedFile);
    }
}