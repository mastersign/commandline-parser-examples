import java.util.Locale;

public class Tool {

    public static void main(String[] argv) {
        Locale.setDefault(Locale.ROOT);

        var cmdLine = new CommandLine();

        // Befehlszeilenparser ausführen
        cmdLine.parse(argv);

        if (cmdLine.help()) {
            // Hilfetext ausgeben und beenden
            cmdLine.printHelp(System.out);
            return;
        }
        if (cmdLine.hasError()) {
            // Wenn Befehlszeilenparser Fehler erkannt hat,
            // Fehler ausgeben und mit Exit-Code 1 beenden
            System.err.println("Syntaxfehler beim Programmaufruf:");
            System.err.println(cmdLine.error());
            System.exit(1);
        }

        // Hauptprogramm
        System.out.println("Programm wird ausgeführt mit:");
        if (cmdLine.altMode()) {
            System.out.println("  Modus:  alternativ");
        } else {
            System.out.println("  Modus:  normal");
        }
        System.out.printf("  Speed:  %.1f\n", cmdLine.speed());
        System.out.printf("  Offset: %s\n", cmdLine.offset().toString());
        System.out.printf("  Input:  %s\n", cmdLine.inputFile());
    }
}