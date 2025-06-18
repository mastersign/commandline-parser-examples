using System.Globalization;
using static System.FormattableString;

// Befehlszeilenparser ausführen
var cmdLine = new CommandLine();

if (cmdLine.Help)
{
    // Hilfetext ausgeben und beenden
    PrintHelp();
    return 0;
}
if (cmdLine.HasError)
{
    // Wenn Befehlszeilenparser Fehler erkannt hat,
    // Fehler ausgeben und mit Exit-Code 1 beenden
    Console.Error.WriteLine("Syntaxfehler beim Programmaufruf:");
    Console.Error.WriteLine(cmdLine.ErrorMessage);
    return 1;
}

// Hauptprogramm
Console.WriteLine("Programm wird ausgeführt mit:");
Console.WriteLine($"  Modus: {(cmdLine.AltMode ? "alternativ" : "normal")}");
Console.WriteLine($"  Speed:  {cmdLine.Speed}");
Console.WriteLine($"  Offset: {cmdLine.Offset}");
Console.WriteLine($"  Input:  {cmdLine.InputFile}");
return 0;

// Funktionen

static void PrintHelp() => Console.WriteLine(Invariant(
    $"""
    Syntax: tool [-a] [-s <S>] [-o <X> <Y>] <Eingabedatei>
            tool -h | --help

    Ein Beispiel für ein Befehlszeilenprogramm')

    Schalter:
      -h, --help
          Zeigt diese Hilfe an.
      -a, --alt
          Führt das Programm im alternativen Modus aus.

    Optionen:
      -s, --speed <S>
          Gibt die Geschwindigkeit an.
          Standard: {CommandLine.DEFAULT_SPEED:0.0}
      -o, --offset <X> <Y>
          Gibt den Offset für die Ausführung in X- und Y-Richtung an.
          Standard: {CommandLine.DEFAULT_OFFSET.X:0.0} {CommandLine.DEFAULT_OFFSET.Y:0.0}
    """));

// Typen

/// <summary>
/// Beschreibt eine 2-dimensionale Position.
/// </summary>
struct Position
{
    public double X;
    public double Y;

    public override readonly string ToString() => Invariant($"({X:0.0}; {Y:0.0})");
}

/// <summary>
/// Der Befehlszeilenparser.
/// </summary>
class CommandLine
{
    // Standardwerte
    public const double DEFAULT_SPEED = 100.0;
    public static Position DEFAULT_OFFSET = new() { X = 0.0, Y = 0.0 };

    private readonly string[] argv;

    public bool Help { get; private set; }
    public bool AltMode { get; private set; }
    private double speed = DEFAULT_SPEED;
    private Position offset = DEFAULT_OFFSET;
    public string? InputFile { get; private set; }
    public string? ErrorMessage { get; private set; }

    public double Speed => speed;
    public Position Offset => offset;
    public bool HasError => ErrorMessage is not null;

    public CommandLine(string[]? argv = null)
    {
        this.argv = argv ?? Environment.GetCommandLineArgs();
        Parse();
    }

    private void Parse()
    {
        var i = 1; // Pfad zur ausführbaren Datei überspringen
        while (i < argv.Length)
        {
            switch (argv[i])
            {
                case "-h" or "--help":
                    Help = true;
                    break;
                case "-a" or "--alt":
                    // Schalter
                    AltMode = true;
                    break;
                case "-s" or "--speed":
                    // Option mit einem Wert
                    if (!ParseDouble(++i, "<S>", out speed)) break;
                    break;
                case "-o" or "--offset":
                    // Option mit zwei Werten
                    if (!ParseDouble(++i, "<X>", out offset.X)) break;
                    if (!ParseDouble(++i, "<Y>", out offset.Y)) break;
                    break;
                default:
                    // Positionsargument
                    if (InputFile is null)
                        InputFile = argv[i];
                    else
                        ErrorMessage = "Kann nur eine Eingabedatei verarbeiten.";
                    break;
            }
            if (ErrorMessage is not null) return;
            i++;
        }

        // Fehlererkennung
        if (InputFile is null)
        {
            ErrorMessage = "Eine Eingabedatei muss angegeben werden.";
        }
    }

    private bool ParseDouble(int i, string metavar, out double value)
    {
        if (i >= argv.Length)
        {
            value = 0.0;
            ErrorMessage = $"Argument für {metavar} fehlt.";
            return false;
        }
        if (!double.TryParse(argv[i],
            NumberStyles.Float, CultureInfo.InvariantCulture,
            out value))
        {
            ErrorMessage = $"Erwartet Fließkommazahl für {metavar}.";
            return false;
        }
        return true;
    }
}
