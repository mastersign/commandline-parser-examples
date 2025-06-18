#include <string>
#include <iostream>
#include <format>

namespace cmdline
{
    // Datenstruktur für 2-dimensionale Position
    struct Position
    {
        double x;
        double y;
    };

    std::ostream& operator<<(std::ostream& os, const Position& p)
    {
        os
            << "("
            << std::format("{:.1f}", p.x)
            << "; "
            << std::format("{:.1f}", p.y)
            << ")";
        return os;
    }

    // Standardwerte
    const static double DEFAULT_SPEED = 100.0;
    const static Position DEFAULT_OFFSET = { 0.0, 0.0 };

    // Datenstruktur für Parser-Ergebnis
    struct CliArguments
    {
        std::string error;

        bool help;
        bool altMode;
        double speed;
        Position offset;
        std::string inputFile;

        bool hasError() { return error.length() > 0; }
    };

    void printHelp()
    {
        std::cout
            << "Syntax: tool [-a] [-s <S>] [-o <X> <Y>] <Eingabedatei>" << std::endl
            << "        tool -h | --help" << std::endl
            << "" << std::endl
            << "Ein Beispiel für ein Befehlszeilenprogramm" << std::endl
            << "" << std::endl
            << "Schalter:" << std::endl
            << "  -h, --help" << std::endl
            << "      Zeigt diese Hilfe an." << std::endl
            << "  -a, --alt" << std::endl
            << "      Führt das Programm im alternativen Modus aus." << std::endl
            << "" << std::endl
            << "Optionen:" << std::endl
            << "  -s, --speed <S>" << std::endl
            << "      Gibt die Geschwindigkeit an." << std::endl
            << "      Standard: " << std::format("{:.1f}", DEFAULT_SPEED) << std::endl
            << "  -o, --offset <X> <Y>" << std::endl
            << "      Gibt den Offset für die Ausführung in X- und Y-Richtung an." << std::endl
            << "      Standard: "
                << std::format("{:.1f}", DEFAULT_OFFSET.x)
                << " "
                << std::format("{:.1f}", DEFAULT_OFFSET.y)
                << std::endl;
    }

    // Befehlszeilenparser
    void parse(const int argc, const char *argv[], CliArguments &target)
    {
        // Ergebnisfelder mit Standardwerten initialisieren
        target.error.clear();
        target.help = true;
        target.altMode = false;
        target.speed = DEFAULT_SPEED;
        target.offset = DEFAULT_OFFSET;
        target.inputFile.clear();

        int i = 1; // Pfad der ausführbaren Datei überspringen
        while (i < argc)
        {
            // TODO Schlüsselworterkennung
            i++;
        }

        // Fehlererkennung
    }
}