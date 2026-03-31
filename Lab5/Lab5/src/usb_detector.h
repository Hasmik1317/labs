#pragma once
#ifndef USB_DETECTOR_H
#define USB_DETECTOR_H

#include <string>
#include <vector>

class USBDetector {
public:
    // Հայտնաբերել միացված USB կրիչները
    static std::vector<std::string> getUSBDrives();

    // Ստուգել արդյոք տրված ուղին USB կրիչ է
    static bool isUSBDrive(const std::string& path);

    // Ստանալ USB կրիչի մասին տեղեկություն
    static std::string getDriveInfo(const std::string& path);
};

#endif

