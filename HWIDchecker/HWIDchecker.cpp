#include <iostream>
#include <string>
#include <Windows.h>
// мы подключили библеотеки для работы нашей консольной программы
void ClearConsole() {
    system("cls"); // Очистка консоли (работает на Windows)
}

std::string GetHWID(const std::string& drivePath) { // получаем данные об hwid
    std::string hwid;
    char volumeName[MAX_PATH + 1] = { 0 };
    char fileSystemName[MAX_PATH + 1] = { 0 };
    DWORD serialNumber = 0;
    DWORD maxComponentLen = 0;
    DWORD fileSystemFlags = 0;

    if (GetVolumeInformationA(drivePath.c_str(), volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName))) {
        hwid = std::to_string(serialNumber);
    }

    return hwid;
}

void PrintMenu() { // простенькое меню
    std::cout << "-------------menu------------\n";
    std::cout << "1. Check ur hwid\n";
    std::cout << "2. Exit\n";
    std::cout << "-------------menu------------\n";
}

void CheckHWID() { // здесь мы получаем ввывод нашей буквы диска и сам hwid
    ClearConsole(); // Очищаем консоль перед выводом результата
    char drives[255];
    if (GetLogicalDriveStringsA(sizeof(drives), drives)) {
        char* drive = drives;
        while (*drive) {
            std::string drivePath = std::string(1, *drive) + ":\\";
            std::string hwid = GetHWID(drivePath);
            std::cout << "Drive: " << drivePath << " HWID: " << hwid << std::endl;

            drive += 4;
        }
    }
    std::cout << "Press Enter to back..."; // пользователь должен нажать Enter чтобы вернуться к меню выбора
    std::cin.ignore();
    std::cin.get(); // Ждем, пока пользователь нажмет Enter
}

int main() {
    int choice;

    do {
        ClearConsole(); // Очищаем консоль
        PrintMenu();
        std::cout << "Enter your choice: "; // вывод надписи (введите ваш выбор)
        std::cin >> choice; // cюда запишеться выбор пользователя

        switch (choice) { // здесь же если пользователь выбрал один, сработает первый кейс, если два, идентично первому 
        case 1: // первый кейс если пользователь выбрал первый пункт (1)
            CheckHWID();
            break;
        case 2: // второй кейс если пользователь выбрал второй пункт (2)
            std::cout << "Exiting the program.\n";
            return 0; // Закрываем программу
        default:
            std::cout << "Invalid choice. Please enter 1 or 2.\n"; // если пользователь написал в консоль неверную цифру
        }

    } while (choice != 2);

    return 0;
}
