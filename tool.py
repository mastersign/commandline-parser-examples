from argparse import ArgumentParser

# Definition der Befehlszeilenargumente
arg_parser = ArgumentParser(
    prog="tool",
    description="Ein Beispiel für ein Befehlszeilenprogramm")
arg_parser.add_argument("-a", "--alt", action="store_true", dest="alt_mode",
                        help="Führt das Programm im alternativen Modus aus")
arg_parser.add_argument("-s", "--speed", type=float,
                        metavar="S", default=100.0,
                        help="Gibt die Geschwindigkeit an")
arg_parser.add_argument("-o", "--offset", nargs=2, type=float,
                        metavar=("X", "Y"), default=[0.0, 0.0],
                        help="Gibt den Offset für die Ausführung in X- und Y-Richtung an.")
arg_parser.add_argument("input_file",
                        metavar="Eingabedatei",
                        help="Ein Pfad zur Eingabedatei.")

# Ausführung des Befehlszeilenparsers mit Abbruch bei Fehler
args = arg_parser.parse_args()

# Hauptprogramm
print("Programm wird ausgeführt mit:")
if args.alt_mode:
    print("  Modus:  alternativ")
else:
    print("  Modus: normal")
print(f"  Speed:  {args.speed}")
print(f"  Offset: ({args.offset[0]}; {args.offset[1]})")
print(f"  Input:  {args.input_file}")
