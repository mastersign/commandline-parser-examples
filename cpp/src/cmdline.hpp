#include <string>
#include <iostream>

namespace cmdline
{
    // Datenstruktur für 2-dimensionale Position
    struct Position
    {
        double x;
        double y;
    };

    std::ostream& operator<<(std::ostream& os, const Position& p);

    // Datenstruktur für Parser-Ergebnis
    struct CliArguments
    {
        std::string error;

        bool help;
        bool altMode;
        double speed;
        Position offset;
        std::string input_file;

        bool has_error();
    };

    // Standardwerte
    const static double DEFAULT_SPEED = 100.0;
    const static Position DEFAULT_OFFSET = { 0.0, 0.0 };

    // Hilfeausgabe
    void print_help();

    // Befehlszeilenparser
    void parse(const int argc, const char *argv[], CliArguments &target);
}
