#include <string>
#include <iostream>
#include "cmdline.hpp"

cmdline::CliArguments cliArgs;

int main(int argc, const char *argv[])
{
    // https://utf8everywhere.org/
    // https://en.cppreference.com/w/cpp/locale/locale.html
    std::locale::global(std::locale("en_US.UTF-8"));

    // Befehlszeilenparser ausführen
    cmdline::parse(argc, argv, cliArgs);

    if (cliArgs.help)
    {
        // Hilfetext ausgeben und beenden
        cmdline::printHelp();
        return 0;
    }

    if (cliArgs.hasError())
    {
        // Wenn Befehlszeilenparser Fehler erkannt hat,
        // Fehler ausgeben und mit Exit-Code 1 beenden
        std::cerr
            << "Syntaxfehler beim Programmaufruf:" << std::endl
            << cliArgs.error << std::endl;
        return 1;
    }

    // Hauptprogramm
    std::cout << "Programm wird ausgeführt mit:" << std::endl;
    if (cliArgs.altMode)
    {
        std::cout << "  Modus: alternativ" << std::endl;
    }
    else
    {
        std::cout << "  Modus: normal" << std::endl;
    }
    std::cout
        << "  Speed:  " << cliArgs.speed << std::endl
        << "  Offset: " << cliArgs.offset << std::endl
        << "  Input:  " << cliArgs.inputFile << std::endl;
    return 0;
}
