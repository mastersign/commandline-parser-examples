import java.io.PrintStream;

/**
 * Der Befehlszeilenparser.
 */
class CommandLine {

    // Standardwerte
    public static final double DEFAULT_SPEED = 100.0;
    public static final Position DEFAULT_OFFSET = new Position(0.0, 0.0);

    // Variablen
    private String _error = null;
    private boolean _help = false;
    private boolean _altMode = false;
    private double _speed = DEFAULT_SPEED;
    private Position _offset = new Position(DEFAULT_OFFSET);
    private String _inputFile = null;

    public String error() { return _error; }

    public boolean hasError() { return _error != null; }

    public boolean help() { return _help; }

    public boolean altMode() { return _altMode; }

    public double speed() { return _speed; }

    public Position offset() { return new Position(_offset); }

    public String inputFile() { return _inputFile; }

    public void printHelp(PrintStream s) {
        s.println("Syntax: tool [-a] [-s <S>] [-o <X> <Y>] <Eingabedatei>");
        s.println("        tool -h | --help");
        s.println();
        s.println("Ein Beispiel für ein Befehlszeilenprogramm");
        s.println();
        s.println("Schalter:");
        s.println("  -h, --help");
        s.println("      Zeigt diese Hilfe an.");
        s.println("  -a, --alt");
        s.println("      Führt das Programm im alternativen Modus aus.");
        s.println();
        s.println("Optionen:");
        s.println("  -s, --speed <S>");
        s.println("      Gibt die Geschwindigkeit an.");
        s.printf("      Standard: %.1f\n", DEFAULT_SPEED);
        s.println("  -o, --offset <X> <Y>");
        s.println("      Gibt den Offset für die Ausführung in X- und Y-Richtung an.");
        s.printf("      Standard: %s\n", DEFAULT_OFFSET);
    }

    public void parse(String[] argv) {
        try {
            parseInternal(argv);
        } catch (CommandLineException e) {
            _error = e.getMessage();
        }
    }

    private void parseInternal(String[] argv) throws CommandLineException {
        var i = 1; // Pfad zur ausführbaren Datei überspringen
        while (i < argv.length)
        {
            switch (argv[i])
            {
                case "-h":
                case "--help":
                    _help = true;
                    break;
                case "-a":
                case "--alt":
                    // Schalter
                    _altMode = true;
                    break;
                case "-s":
                case "--speed":
                    // Option mit einem Wert
                    _speed = parseDouble(argv, ++i, "<S>");
                    break;
                case "-o":
                case "--offset":
                    // Option mit zwei Werten
                    _offset.x = parseDouble(argv, ++i, "<X>");
                    _offset.y = parseDouble(argv, ++i, "<Y>");
                    break;
                default:
                    // Positionsargument
                    if (_inputFile == null)
                        _inputFile = argv[i];
                    else
                        throw new CommandLineException(
                            "Kann nur eine Eingabedatei verarbeiten.");
                    break;
            }
            i++;
        }
        if (_help) return;

        // Fehlererkennung
        if (_inputFile == null)
        {
            throw new CommandLineException(
                "Eine Eingabedatei muss angegeben werden.");
        }
    }

    private double parseDouble(String[] argv, int i, String metavar)
            throws CommandLineException {
        if (i >= argv.length)
        {
            throw new CommandLineException(
                "Argument für " + metavar + " fehlt.");
        }
        try {
            return Double.parseDouble(argv[i]);
        } catch (NumberFormatException e) {
            throw new CommandLineException(
                "Erwartet Fließkommazahl für " + metavar + ".");
        }
    }
}