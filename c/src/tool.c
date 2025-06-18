#include <stdio.h>
#include <string.h>

// Hilfssymbole
#define TRUE              1
#define FALSE             0
#define OK                0
#define ERR               1

// Standardwerte
#define DEFAULT_SPEED     100.0
#define DEFAULT_OFFSET_X  0.0
#define DEFAULT_OFFSET_Y  0.0

// Variablen mit Standardwerten initialisieren
int help = FALSE;
int altMode = FALSE;
double speed = DEFAULT_SPEED;
double offsetX = DEFAULT_OFFSET_X;
double offsetY = DEFAULT_OFFSET_Y;
const char *inputFile = NULL;

void printHelp() {
  printf("Syntax: tool [-a] [-s <S>] [-o <X>,<Y>] <Eingabedatei>\n");
  printf("        tool -h | --help\n");
  printf("\n");
  printf("Ein Beispiel fuer ein Befehlszeilenprogramm\n");
  printf("\n");
  printf("Schalter:\n");
  printf("  -h, --help\n");
  printf("      Zeigt diese Hilfe an.\n");
  printf("  -a, --alt\n");
  printf("      Fuehrt das Programm im alternativen Modus aus.\n");
  printf("\n");
  printf("Optionen:\n");
  printf("  -s, --speed <S>\n");
  printf("      Gibt die Geschwindigkeit an.\n");
  printf("      Standard: %.1f\n", DEFAULT_SPEED);
  printf("  -o, --offset <X>,<Y>\n");
  printf("      Gibt den Offset fuer die Ausfuehrung in X- und Y-Richtung an.\n");
  printf("      Standard: %.1f,%.1f\n", DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
}

int matchKeyword(
    const char *arg,
    const char *shortName, const char *longName
) {
    return strcmp(arg, shortName) == 0
        || strcmp(arg, longName) == 0
            ? TRUE : FALSE;
}

int parseDoubleValue(
    const int argc, const char *argv[], const int index,
    const char *metaVar, double *value
) {
    if (index >= argc) {
        fprintf(stderr,
            "Syntaxfehler: Fehlendes Argument fuer %s\n",
            metaVar);
        return ERR;
    }
    int matches = sscanf(argv[index], "%lf", value);
    if (matches != 1) {
        fprintf(stderr,
            "Syntaxfehler: Fliesskommazahl fuer %s erwartet\n",
            metaVar);
        return ERR;
    }
    return OK;
}

int parseCliArguments(const int argc, const char *argv[]) {
    int error = FALSE;
    int i = 1;  // Pfad der ausfuehrbaren Datei ueberspringen
    while (i < argc) {
        if (matchKeyword(argv[i], "-h", "--help")) {
            help = TRUE;
            return OK; // Abkuerzung, wenn Hilfeschalter verwendet wird
        } else if (matchKeyword(argv[i], "-a", "--alt")) {
            // Schalter
            altMode = TRUE;
        } else if (matchKeyword(argv[i], "-s", "--speed")) {
            // Option mit einem Wert
            i++;
            if (parseDoubleValue(argc, argv, i, "<S>", &speed) != OK) {
                error = TRUE;
                break;
            }
        } else if (matchKeyword(argv[i], "-o", "--offset")) {
            // Option mit zwei Werten
            i++;
            if (parseDoubleValue(argc, argv, i, "<X>", &offsetX) != OK) {
                error = TRUE;
                break;
            }
            i++;
            if (parseDoubleValue(argc, argv, i, "<Y>", &offsetY) != OK) {
                error = TRUE;
                break;
            }
        } else {
            // Positionsargument(e)
            if (inputFile == NULL) {
                inputFile = argv[i];
            } else {
                fprintf(stderr,
                    "Syntaxfehler: Es kann nur eine Eingabedatei verarbeitet werden\n");
                error = TRUE;
                break;
            }
        }
        i++;
    }

    // Fehlererkennung
    if (inputFile == NULL) {
        fprintf(stderr,
            "Syntaxfehler: Es muss eine Eingabedatei angegeben werden\n");
        error = TRUE;
    }

    return error == TRUE ? ERR : OK;
}

int main(int argc, char *argv[]) {

    // Befehlszeilenparser ausführen
    int parseResult = parseCliArguments(argc, argv);

    if (help == TRUE) {
        // Hilfetext ausgeben und beenden
        printHelp();
        return OK;
    }

    if (parseResult != OK) {
        // Abbrechen wenn Parser Fehler erkannt hat
        return ERR;
    }

    // Hauptprogramm
    printf("Programm wird ausgefuehrt mit:\n");
    if (altMode == TRUE) {
        printf("  Modus: alternativ\n");
    } else {
        printf("  Modus: normal\n");
    }
    printf("  Speed:  %.1f\n", speed);
    printf("  Offset: (%.1f; %.1f)\n", offsetX, offsetY);
    printf("  Input:  %s\n", inputFile);
    return OK;
}
