#!/bin/bash

# getopt nutzen, um Argumente zu prüfen und zu normalisieren
opts=$(getopt -o has:o: --long help,alt,speed:,offset: -n'tool' -- "$@")
if [ $? -ne 0 ]; then
    >&2 echo "Ungültige Syntax"
    exit 1
fi
# originale Befehlszeilenargumente durch normalisierte ersetzen
eval set -- "$opts"

# Variablen initialisieren
help=false
alt_mode=false
speed=100
offset=(0 0)
input_file=''

# Schleife für Schalter und Optionen
while ! [ $# -eq 0 ]; do
  case "$1" in
    -h | --help)
      help=true
      ;;
    -a | --alt)
      alt_mode=true
      ;;
    -s | --speed)
      shift
      speed="$1"
      ;;
    -o | --offset)
      # kommaseparierte Argumente in Array auftrennen
      shift
      IFS=',' read -r -a offset <<< "$1"
      ;;
    --)
      # Abbruchkriterium, angefügt von getopt
      shift
      break
      ;;
  esac
  shift
done

# Positionsargumente übertragen
if [ "$#" -eq 1 ]; then
  input_file="$1"
fi

# Hilfeausgabe
if [ "$help" = true ]; then
  echo "Syntax: tool [-a] [-s <S>] [-o <X>,<Y>] <Eingabedatei>"
  echo "        tool -h | --help"
  echo ""
  echo "Schalter:"
  echo "  -h, --help"
  echo "      Zeigt diese Hilfe an."
  echo "  -a, --alt"
  echo "      Führt das Programm im alternativen Modus aus."
  echo ""
  echo "Optionen:"
  echo "  -s, --speed <S>"
  echo "      Gibt die Geschwindigkeit an."
  echo "      Standard: 100.0"
  echo "  -o, --offset <X>,<Y>"
  echo "      Gibt den Offset für die Ausführung in X- und Y-Richtung an."
  echo "      Standard: 0.0,0.0"
  exit 0
fi

# Fehlererkennung
if ! [ "${#offset[@]}" -eq 2 ]; then
  >&2 echo "Syntaxfehler: Zwei Argumente für -o/--offset <X>,<Y> erwartet"
  exit 1
fi
if [ -z "$input_file" ]; then
  >&2 echo "Eine Eingabedatei muss angegeben werden"
  exit 1
fi

# Hauptprogramm
echo "Programm wird ausgeführt mit:"
if [ "$alt_mode" = true ]; then
    echo "  Modus:  alternativ"
else
    echo "  Modus:  normal"
fi
echo "  Speed:  $speed"
echo "  Offset: (${offset[0]}; ${offset[1]})"
echo "  Input:  $input_file"