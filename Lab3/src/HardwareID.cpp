#include "HardwareID.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

// Linux-ի համար հրամանների արդյունքը կարդալու ֆունկցիա
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    if (!result.empty() && result.back() == '\n') result.pop_back();
    return result;
}

std::string HardwareID::combineAndHash(const std::string& data) {
    unsigned long hash = 5381;
    for (char c : data) {
        hash = ((hash << 5) + hash) + c;
    }
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << hash;
    return ss.str();
}

HardwareID::HardwareID() {
    // Linux-ի իրական տվյալների ստացում
    cpuId = exec("lscpu | grep 'Model name' | cut -d ':' -f 2 | xargs");
    motherboardId = exec("cat /sys/class/dmi/id/product_uuid 2>/dev/null || echo 'UUID-PROTECTED'");
    macAddress = exec("cat /sys/class/net/$(ls /sys/class/net | grep -v lo | head -n 1)/address");
}

std::string HardwareID::getMachineID() {
    std::string combined = cpuId + "|" + motherboardId + "|" + macAddress;
    return combineAndHash(combined);
}
