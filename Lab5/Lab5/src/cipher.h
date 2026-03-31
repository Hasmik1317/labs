#pragma once
#ifndef CIPHER_H
#define CIPHER_H

#include <vector>
#include <string>

// Պարզ XOR գաղտնագրում (միայն ANSI տեքստի համար)
class SimpleXORCipher {
private:
    std::string key;

public:
    SimpleXORCipher(const std::string& encryptionKey);

    // Տվյալների գաղտնագրում
    std::vector<char> encrypt(const std::vector<char>& data);

    // Տվյալների վերծանում
    std::vector<char> decrypt(const std::vector<char>& data);

    // Ֆայլի գաղտնագրում
    bool encryptFile(const std::string& inputPath, const std::string& outputPath);

    // Ֆայլի վերծանում
    bool decryptFile(const std::string& inputPath, const std::string& outputPath);
};

#endif

