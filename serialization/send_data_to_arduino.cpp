#include <windows.h>
#include <iostream>
#include <string>
#include <cstdint>

int main() {
    // Data to send
    std::string name = "Andrea";
    uint8_t age = 24;
    uint8_t nameLen = static_cast<uint8_t>(name.size());

    // Open serial port (change COM3 to your Arduino's port)
    HANDLE hSerial = CreateFileA("\\\\.\\COM3", GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port\n";
        return 1;
    }

    // Configure serial port
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial state\n";
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial state\n";
        CloseHandle(hSerial);
        return 1;
    }

    // Send name length, name, and age
    DWORD bytesWritten;
    WriteFile(hSerial, &nameLen, 1, &bytesWritten, NULL);
    WriteFile(hSerial, name.c_str(), nameLen, &bytesWritten, NULL);
    WriteFile(hSerial, &age, 1, &bytesWritten, NULL);

    CloseHandle(hSerial);
    std::cout << "Data sent!\n";
    return 0;
}