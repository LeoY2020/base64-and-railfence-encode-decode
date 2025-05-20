#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

string base64_decode(const string &in) {
    vector<int> T(256, -1);
    for (int i = 0; i < 64; ++i) {
        T[base64_chars[i]] = i;
    }
    string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    return out;
}

string railfence_decrypt(const string &cipher) {
    int len = cipher.length();
    int len1 = (len + 1) / 2;
    string row1 = cipher.substr(0, len1);
    string row2 = cipher.substr(len1);
    string result;
    for (int i = 0; i < row2.size(); ++i) {
        result += row1[i];
        result += row2[i];
    }
    if (row1.size() > row2.size()) {
        result += row1.back();
    }
    return result;
}

int main() {
    string input;
    cout << "Enter text to decrypt: ";
    getline(cin, input);
    string rail_decrypted = railfence_decrypt(input);
    string decrypted = base64_decode(rail_decrypted);
    cout << "Decrypted result: " << decrypted << endl;
    return 0;
}