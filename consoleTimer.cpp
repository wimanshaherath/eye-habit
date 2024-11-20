#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <conio.h>

#include <Windows.h>


#define WIDTH 400
#define HEIGHT 200


void clearConsole() {
    std::cout << "\033[2J\033[H";
}

void setConsoleSize() 
{
//#ifdef _WIN32
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.right, r.top, WIDTH, HEIGHT, TRUE);
}

void setConsoleColor(int bgColor, int txtColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD wOldColorAttribute;
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;

    GetConsoleScreenBufferInfo(hConsole, &csbInfo);
    wOldColorAttribute = csbInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, bgColor << 4 | txtColor);
}

void Timer(int& seconds) 
{    
    while (seconds >= 0)
    {
        int min = seconds / 60;
        int remSec = seconds % 60;

        std::cout << min << ":" << remSec << std::endl;
        Beep(750, 300);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        clearConsole();
        --seconds;

    }
}

void getStatus(char &status)
{
    if (_kbhit) { // Check if a key press
        char key = _getch(); // Get the key pressed
        std::cout << key << std::endl;

        if (key == 'f' || key == 'F') {
            status = 'f';
        }
        else if (key == 'w' || key == 'W') {
            status = 'w';
        }
    }
}

void setTimer(std::string  msg) {

}

int main()
{
    char status = 'f';
    int seconds = -1;
    setConsoleSize();
    
    while (true) {
        //if (status == 'w') seconds = 10; // 20min to work
        //else if (status == 'f') seconds = 5; // 20 sec to rest

        
        //setConsoleColor(0, 7);
        if (seconds == -1 && status == 'w') {
            clearConsole();
            setConsoleColor(4, 7);
            std::cout << "You need to rest. If you start to rest press 'f'." << std::endl;
            getStatus(status);
            if (status == 'f') {
                seconds = 5;
                clearConsole();
                Timer(seconds);
            }
            else continue;
            
        }

        if (seconds == -1 && status == 'f') {
            clearConsole();
            setConsoleColor(2, 7);
            std::cout << "You can start work again. If you start to work press 'w'." << std::endl;
            getStatus(status);
            if (status == 'w') {
                seconds = 10;
                clearConsole();
                Timer(seconds);
            }
            else continue;
        }

    }

    return 0;
}
