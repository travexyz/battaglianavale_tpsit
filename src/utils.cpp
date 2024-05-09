#include <iostream>
#include <thread>
#include <chrono>

// https://stackoverflow.com/a/16884718
void scriviConEffetto(std::string stringa, unsigned int ritardo = 10)
{
    // for-each loop
    for (const auto carattere : stringa)
    {
        std::cout << carattere << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(ritardo));
    }
    std::cout << std::endl;
}

// https://stackoverflow.com/a/52895729
void clearScreen()
{
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
    system("clear");
#endif
}