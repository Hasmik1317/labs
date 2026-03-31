#include "usb_detector.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <fileapi.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

// 1. Ստանալ բոլոր USB սարքերը
std::vector<std::string> USBDetector::getUSBDrives() {
    std::vector<std::string> usbDrives;
#ifdef _WIN32
    DWORD drives = GetLogicalDrives();
    for (int i = 0; i < 26; i++) {
        if (drives & (1 << i)) {
            char rootPath[4] = { char('A' + i), ':', '\\', '\0' };
            UINT driveType = GetDriveTypeA(rootPath);
            if (driveType == DRIVE_REMOVABLE) {
                std::string drive(1, 'A' + i);
                drive += ":\\";
                usbDrives.push_back(drive);
            }
        }
    }
#else
    // Linux/Kali տարբերակ
    const char* baseDir = "/media/kali";
    DIR* dir = opendir(baseDir);
    if (dir) {
        struct dirent* ent;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                usbDrives.push_back(std::string(baseDir) + "/" + ent->d_name);
            }
        }
        closedir(dir);
    }
#endif
    return usbDrives;
}

// 2. Ստուգել՝ արդյոք տվյալ ուղին USB է
bool USBDetector::isUSBDrive(const std::string& path) {
#ifdef _WIN32
    if (path.length() >= 2 && path[1] == ':') {
        std::string root = path.substr(0, 3);
        UINT driveType = GetDriveTypeA(root.c_str());
        return (driveType == DRIVE_REMOVABLE);
    }
#else
    struct stat s;
    if (stat(path.c_str(), &s) == 0) {
        return S_ISDIR(s.st_mode);
    }
#endif
    return false;
}

// 3. Ստանալ տեղեկություն սարքի մասին (Սա էր բացակայում)
std::string USBDetector::getDriveInfo(const std::string& path) {
    char buffer[512] = { 0 };
#ifdef _WIN32
    if (path.length() >= 2 && path[1] == ':') {
        std::string root = path.substr(0, 3);
        DWORD serialNumber;
        char volName[256];
        if (GetVolumeInformationA(root.c_str(), volName, sizeof(volName), &serialNumber, NULL, NULL, NULL, 0)) {
            sprintf(buffer, "Drive: %s\nVolume Name: %s\nSerial: %08X", path.c_str(), volName, serialNumber);
            return std::string(buffer);
        }
    }
#endif
    // Linux-ում պարզապես վերադարձնում ենք ուղին
    snprintf(buffer, sizeof(buffer), "Drive: %s (Linux USB Mount)", path.c_str());
    return std::string(buffer);
}
