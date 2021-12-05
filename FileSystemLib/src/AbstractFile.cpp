//
// Created by stani on 30.11.2021.
//

#include "AbstractFile.h"
#include <iostream>

namespace System {
   AbstractFile::AbstractFile(unsigned int owner, unsigned char permissions[2]) {
       for (int i = 0; i < 2; ++i) {
           if (permissions[i] < 48 || permissions[i] > 55) {
               throw std::invalid_argument("invalid argument in constructor");
           }
       }
       this->permissions = new Permissions();
   }


}