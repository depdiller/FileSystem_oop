//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_USER_H
#define FILESYSTEM_USER_H

class User {
private:
    unsigned int userId;
    string name;
    string key;
public:
    User();
    changeKey();
};

#endif //FILESYSTEM_USER_H
