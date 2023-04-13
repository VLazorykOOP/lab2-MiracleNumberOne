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