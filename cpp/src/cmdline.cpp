#include <format>
#include "cmdline.hpp"

std::ostream& cmdline::operator<<(std::ostream& os, const Position& p)
{
    os
        << "("
        << std::format("{:.1f}", p.x)
        << "; "
        << std::format("{:.1f}", p.y)
        << ")";
    return os;
}

bool cmdline::CliArguments::has_error()
{
    return !error.empty();
}

void cmdline::print_help()
{
    std::cout
        << "Syntax: tool [-a] [-s <S>] [-o <X> <Y>] <Eingabedatei>" << std::endl
        << "        tool -h | --help" << std::endl
        << std::endl
        << "Ein Beispiel für ein Befehlszeilenprogramm" << std::endl
        << std::endl
        << "Schalter:" << std::endl
        << "  -h, --help" << std::endl
        << "      Zeigt diese Hilfe an." << std::endl
        << "  -a, --alt" << std::endl
        << "      Führt das Programm im alternativen Modus aus." << std::endl
        << std::endl
        << "Optionen:" << std::endl
        << "  -s, --speed <S>" << std::endl
        << "      Gibt die Geschwindigkeit an." << std::endl
        << "      Standard: "
            << std::format("{:.1f}", DEFAULT_SPEED)
            << std::endl
        << "  -o, --offset <X> <Y>" << std::endl
        << "      Gibt den Offset für die Ausführung in X- und Y-Richtung an." << std::endl
        << "      Standard: "
            << std::format("{:.1f}", DEFAULT_OFFSET.x)
            << " "
            << std::format("{:.1f}", DEFAULT_OFFSET.y)
            << std::endl;
}

void cmdline::parse(const int argc, const char *argv[], CliArguments &target)
{
    // Ergebnisfelder mit Standardwerten initialisieren
    target.error.clear();
    target.help = false;
    target.altMode = false;
    target.speed = DEFAULT_SPEED;
    target.offset = DEFAULT_OFFSET;
    target.input_file.clear();

    int i;
    std::string arg;

    // Wertumwandlung in Lambda mit Closure über Argumente, Schleifenvariable und Ergebnis
    auto parse_double = [&](const char* metaVar, double *value) -> bool
    {
        i++; // verschiebt die Position in der Schleife um eins
        if (i >= argc) {
            target.error = std::format("Fehlendes Argument für {0}", metaVar);
            return false;
        }
        std::string s = argv[i];
        try 
        {
            *value = std::stod(s);
        }
        catch (std::invalid_argument) 
        {
            target.error = std::format("Fließkommazahl für {0} erwartet", metaVar);
            return false;
        }
        catch (std::out_of_range)
        {
            target.error = std::format("Wert für {0} ist zu groß oder zu klein", metaVar);
            return false;
        }
        return true;
    };

    // Schleife über Argumente
    for (i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            target.help = true;
            return; // Abkürzung, wenn Hilfeschalter verwendet wird
        }
        else if (arg == "-a" || arg == "--alt")
        {
            // Schalter
            target.altMode = true;
        }
        else if (arg == "-s" || arg == "--speed")
        {
            // Option mit einem Wert
            if (!parse_double("<S>", &target.speed)) return;
        }
        else if (arg == "-o" || arg == "--offset")
        {
            // Option mit zwei Werten
            if (!parse_double("<X>", &target.offset.x)) return;
            if (!parse_double("<Y>", &target.offset.y)) return;
        }
        else
        {
            // Positionsargument(e)
            if (target.input_file.empty())
            {
                target.input_file = arg;
            }
            else
            {
                target.error = "Es kann nur eine Eingabedatei verarbeitet werden";
                return;
            }
        }
    }

    // Fehlererkennung
    if (target.input_file.empty())
    {
        target.error = "Es muss eine Eingabedatei angegeben werden";
        return;
    }
}
