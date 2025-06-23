#include <string>
#include <iostream>
#include <format>
#include "cmdline.hpp"

cmdline::CliArguments cli_args;

int main(int argc, const char *argv[])
{
    // https://utf8everywhere.org/
    std::locale::global(std::locale("en_US.UTF-8"));

    // Befehlszeilenparser ausführen
    cmdline::parse(argc, argv, cli_args);

    if (cli_args.help)
    {
        // Hilfetext ausgeben und beenden
        cmdline::print_help();
        return 0;
    }

    if (cli_args.has_error())
    {
        // Wenn Befehlszeilenparser Fehler erkannt hat,
        // Fehler ausgeben und mit Exit-Code 1 beenden
        std::cerr
            << "Syntaxfehler beim Programmaufruf:" << std::endl
            << cli_args.error << std::endl;
        return 1;
    }

    // Hauptprogramm
    std::cout << "Programm wird ausgeführt mit:" << std::endl;
    if (cli_args.altMode)
    {
        std::cout << "  Modus: alternativ" << std::endl;
    }
    else
    {
        std::cout << "  Modus: normal" << std::endl;
    }
    std::cout
        << "  Speed:  " << std::format("{:.1f}", cli_args.speed) << std::endl
        << "  Offset: " << cli_args.offset << std::endl
        << "  Input:  " << cli_args.input_file << std::endl;
    return 0;
}
