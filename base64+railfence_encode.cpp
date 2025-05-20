#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

string base64_encode(const string &in) {
    string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        out.push_back(base64_chars[(val << 8) >> (valb + 8) & 0x3F]);
    }
    while (out.size() % 4 != 0) {
        out.push_back('=');
    }
    return out;
}

string railfence_encrypt(const string &text) {
    string row1, row2;
    for (int i = 0; i < text.size(); ++i) {
        if (i % 2 == 0) {
            row1 += text[i];
        } else {
            row2 += text[i];
        }
    }
    return row1 + row2;
}

int main() {
    string input;
    cout << "Enter text to encrypt: ";
    getline(cin, input);
    string b64 = base64_encode(input);
    string encrypted = railfence_encrypt(b64);
    cout << "Encrypted result: " << encrypted << endl;
    return 0;
}
