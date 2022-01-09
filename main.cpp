#include <cstdio>
#include "FileSystem.h"
template<class T>
int getNum(T &a);

int main() {
    FILE *associatedFile;
    associatedFile = fopen("C:\\disk.txt", "wb+");
    if (associatedFile != nullptr) {
        System::FileSystem sys(associatedFile);
        int choice;
        while (true) {
            std::cout << "\n\n";
            std::cout << "Choose options: " << std::endl
                      << "0. Exit" << std::endl
                      << "1. pwd" << std::endl
                      << "2. cd" << std::endl
                      << "3. create dir in current directory" << std::endl
                      << "4. create file in current directory"<< std::endl
                      << "5. move dir from current directory" << std::endl
                      << "6. move file from current directory" << std::endl
                      << "7. copy dir from current directory" << std::endl
                      << "8. copy file from current directory" << std::endl
                      << "9. delete dir from current directory" << std::endl
                      << "10. delete file from current directory" << std::endl
                      << "11. write to file" << std::endl
                      << "12. edit file" << std::endl
                      << "13. cat file" << std::endl
                      << "14. info about system" << std::endl
                      << "15. print current user" << std::endl;
            // if (getNum(choice) == 1)
            std::cin >> choice;
            if (choice == 0)
                break;
            switch (choice) {
                case 1: {
                    std::cout << "Current dir: " << sys.getPwd();
                }
                    break;
                case 2: {
                    std::string path;
                    std::cout << "Enter dir to go to: ";
                    std::cin >> path;
                    try {
                        sys.setCurrDir(path);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 3: {
                    std::string dirname;
                    std::cout << "Enter name of new dir: ";
                    std::cin >> dirname;
                    try {
                        sys.createDir(dirname);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 4: {
                    std::string filename;
                    std::cout << "Enter name of new file: ";
                    std::cin >> filename;
                    try {
                        sys.createFile(filename, sys.controlVirtualMem());
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 5: {
                    std::string dirname;
                    std::string path;
                    std::cout << "Enter name of dir from current directory you want to move: ";
                    std::cin >> dirname;
                    std::cout << "Enter path to move to: ";
                    std::cin >> path;
                    try {
                        sys.moveDir(dirname, path);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 6: {
                    std::string filename;
                    std::string path;
                    std::cout << "Enter name of file from current directory you want to move: ";
                    std::cin >> filename;
                    std::cout << "Enter path to move to: ";
                    std::cin >> path;
                    try {
                        sys.moveFile(filename, path);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 7: {
                    std::string dirname;
                    std::string path;
                    std::cout << "Enter name of dir from current directory you want to copy: ";
                    std::cin >> dirname;
                    std::cout << "Enter path to copy to: ";
                    std::cin >> path;
                    try {
                        sys.copyDir(dirname, path);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 8: {
                    std::string filename;
                    std::string path;
                    std::cout << "Enter name of file from current directory you want to copy: ";
                    std::cin >> filename;
                    std::cout << "Enter path to copy to: ";
                    std::cin >> path;
                    try {
                        sys.copyFile(filename, path);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 9: {
                    std::string dirname;
                    std::cout << "Enter name of dir from current directory you want to delete: ";
                    std::cin >> dirname;
                    try {
                        sys.deleteDir(dirname);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 10: {
                    std::string filename;
                    std::cout << "Enter name of file from current directory you want to delete: ";
                    std::cin >> filename;
                    try {
                        sys.deleteFile(filename);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 11: {
                    std::string filePath;
                    std::string data;
                    std::cout << "Enter path to file: ";
                    std::cin >> filePath;
                    std::cout << "Enter data: ";
                    std::cin >> data;
                    try {
                        sys.writeToFile(filePath, data);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 12: {
                    std::string filePath;
                    std::string toAdd;
                    std::cout << "Enter path to file: ";
                    std::cin >> filePath;
                    std::cout << "Enter data to add to file: ";
                    std::cin >> toAdd;
                    try {
                        sys.editFile(filePath, toAdd);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 13: {
                    std::string filePath;
                    std::cout << "Enter path to file: ";
                    std::cin >> filePath;
                    try {
                        sys.catFile(filePath);
                    }
                    catch (std::invalid_argument &msg) {
                        std::cout << msg.what() << std::endl;
                    }
                }
                    break;
                case 14: {
                    std::cout << sys.infoSystem();
                }
                    break;
                case 15: {
                    std::cout << sys.getCurrUser()->getName();
                }
                    break;
                default : {
                    std::cout << "Invalid type option. Try again.";
                }
            }
        }
        return 0;
    }
    else {
        std::cout << "Cannot open file" << std::endl;
    }
}
template<typename T>
int getNum(T &a) {
    int indic;
    do {
        std::cin >> a;
        indic = 1;
        if (std::cin.eof())
            indic = -1;
        if (!std::cin.good()) {
            std::cout << "Incorrect input. Try again" << std::endl;
            indic = 0;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    } while (indic == 0);
    return indic < 0 ? -1 : 1;
}
