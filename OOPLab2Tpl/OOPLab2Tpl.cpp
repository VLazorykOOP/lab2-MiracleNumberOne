#include <iostream>
#include <fstream>
#include <string>

int calculateExpression(int a, int b, int c, int d) {
    int result = 0;

    // Multiply a by 15 using bitwise shift operations
    int aBy15 = (a << 4) + a;

    // Multiply b by 312 using bitwise shift operations
    int bBy312 = (b << 8) - (b << 3);

    // Divide aBy15 by 64 using bitwise shift operations
    int aBy15Div64 = aBy15 >> 6;

    // Divide bBy312 by 64 using bitwise shift operations
    int bBy312Div64 = bBy312 >> 6;

    // Add aBy15Div64 and bBy312Div64
    int sum = aBy15Div64 + bBy312Div64;

    // Subtract c multiplied by 120
    int cMul120 = (c << 3) + (c << 5);
    sum -= cMul120;

    // Add d multiplied by 121
    int dMul121 = (d << 7) + d + (d << 4);
    sum += dMul121;

    result = sum;
    return result;
}

void encryptText(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile);
    std::ofstream fout(outputFile, std::ios::binary);

    if (!fin.is_open() || !fout.is_open()) {
        std::cout << "Failed to open files!" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(fin, line)) {
        // Add spaces to lines less than 32 characters
        if (line.length() < 32) {
            line.append(32 - line.length(), ' ');
        }

        for (int i = 0; i < line.length(); i++) {
            // Calculate the position of the character in the line (5 bits)
            int position = i + 1;

            // Calculate the ASCII character code (8 bits)
            int ascii = static_cast<int>(line[i]);

            // Calculate the parity bit (1 bit)
            int parity = 0;
            for (int j = 0; j < 8; j++) {
                parity ^= (ascii >> j) & 1;
            }

            // Combine the data into two bytes
            int byte1 = (lineNumber << 6) | (position << 1) | (ascii >> 7);
            int byte2 = ((ascii & 0x7F) << 1) | parity;

            // Write the two bytes to the output file
            fout.write(reinterpret_cast<const char*>(&byte1), sizeof(byte1));
            fout.write(reinterpret_cast<const char*>(&byte2), sizeof(byte2));
        }

        lineNumber++;
    }

    fin.close();
    fout.close();
}

void decryptText(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile, std::ios::binary);
    std::ofstream fout(outputFile);

    if (!fin.is_open() || !fout.is_open()) {
        std::cout << "Failed to open files!" << std::endl;
        return;
    }

    int lineNumber = 0;
    while (!fin.eof()) {
        int byte1;
        int byte2;

        // Read two bytes from the input file
        fin.read(reinterpret_cast<char*>(&byte1), sizeof(byte1));
        fin.read(reinterpret_cast<char*>(&byte2), sizeof(byte2));

        if (fin.eof()) {
            break;
        }

        // Extract data from the two bytes
        int lineNumber = byte1 >> 6;
        int position = (byte1 >> 1) & 0x1F;
        int ascii = ((byte1 & 0x01) << 7) | (byte2 >> 1);
        int parity = byte2 & 0x01;

        // Verify parity bit
        int computedParity = 0;
        for (int i = 0; i < 8; i++) {
            computedParity ^= (ascii >> i) & 1;
        }

        // If parity bit is correct, write the character to the output file
        if (parity == computedParity) {
            fout << static_cast<char>(ascii);
        } else {
            std::cout << "Parity bit verification failed. Skipping character." << std::endl;
        }
    }

    fin.close();
    fout.close();
}

void encodeBytes(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile, std::ios::binary);
    std::ofstream fout(outputFile, std::ios::binary);

    if (!fin.is_open() || !fout.is_open()) {
        std::cout << "Failed to open files!" << std::endl;
        return;
    }

    // Read bytes from input file into a vector
    std::vector<char> bytes;
    char byte;
    while (fin.get(byte)) {
        bytes.push_back(byte);
    }

    // Encode bytes
    for (int i = 0; i < bytes.size(); i++) {
        char encodedByte = 0;
        for (int j = 0; j < 8; j++) {
            // Get the j-th bit of the i-th byte
            char bit = (bytes[i] >> j) & 0x01;

            // Set the (j*8+i)-th bit of the encoded byte
            encodedByte |= (bit << (j * 8 + i));
        }
        fout.write(&encodedByte, sizeof(encodedByte));
    }

    fin.close();
    fout.close();
}