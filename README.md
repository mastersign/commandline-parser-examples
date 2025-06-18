# Command Line Parser Examples

Diese Projekt enthält Beispiele für einfache Befehlszeilenparser
in verschiedenen Programmiersprachen.

## Motivation

Die Beispiele sollen als Vorlage für das Parsen von
Befehlszeilenargumenten dienen.
Sie sind am besten geeignet, wenn zusätzliche Abhängigkeiten
für ein kleines Befehlszeilenprogramm oder Skript vermieden werden sollen.

Näheres in dem zugehörigen Blog-Beitrag
[Einen einfachen Befehlszeilenparser implementieren](https://honest-devhead.com/posts/commandline-3).

## Beispiel Befehlszeilenprogramm

Das Programm das durch die Beispiele implementiert wird ist:

```plain
tool [-a|--alt] [-s|--speed <S>] [-o|--offset <X> <Y>] <Eingabedatei>
tool -h | --help
```

In einigen Implementierungen erwartet die Option `-o`/`--offset`
ihre Werte `<X>` und `<Y>` auch als kommasparierte Liste `<X>,<Y>`.

Das PowerShell-Skript `tool.ps1` hat weitere Besonderheiten,
die dem Blog-Beitrag entnommen werden können.

## Lizenz

Public Domain
