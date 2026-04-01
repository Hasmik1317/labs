#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. RLE Encode ֆունկցիա (Տեղերը փոխված)
string rle_encode(string data) {
    string output = "";
    int n = data.length();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && data[i] == data[i + 1]) {
            count++;
            i++;
        }
        // Սկզբում ավելացնում ենք Տառը, հետո Քանակը
        output += data[i];           // ASCII տառը (օր. 65)
        output += (char)count;      // Քանակը (օր. 4)
    }
    return output;
}

// 2. RLE Decode ֆունկցիա (Տեղերը փոխված)
string rle_decode(string data) {
    string output = "";
    for (int i = 0; i < data.length(); i += 2) {
        char ch = data[i];                  // Ստանում ենք տառը
        int count = (unsigned char)data[i + 1]; // Ստանում ենք քանակը
        for (int j = 0; j < count; j++) {
            output += ch;
        }
    }
    return output;
}

int main() {
    string input;
    cout << "Enter text to compress: ";
    cin >> input;

    cout << "\nOriginal: " << input << " (Size: " << input.length() << ")" << endl;

    // Սեղմում
    string encoded = rle_encode(input);

    cout << "Encoded Data [ASCII | Count]: ";
    for (int i = 0; i < encoded.length(); i += 2) {
        // Տպում ենք [Տառի կոդը - Քանակը]
        cout << "[" << (int)(unsigned char)encoded[i] << " " << (int)(unsigned char)encoded[i + 1] << "] ";
    }
    cout << "\nEncoded Size: " << encoded.length() << " bytes" << endl;

    // Վերականգնում
    string decoded = rle_decode(encoded);
    cout << "\nDecoded text: " << decoded << endl;

    if (decoded == input)
        cout << "RESULT: Correct" << endl;
    else
        cout << "RESULT: Error" << endl;

    return 0;
}
