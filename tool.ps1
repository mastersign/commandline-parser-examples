<#
.SYNOPSIS
  Ein Beispiel für ein Befehlszeilenprogramm

.DESCRIPTION
  Hier könnte eine ausführliche Beschreibung für das Programm stehen.

.PARAMETER AlternativeMode
  Führt das Programm im alternativen Modus aus.

.PARAMETER Speed
  Gibt die Geschwindigkeit an.

.PARAMETER Offset
  Gib den Offset für die Ausführung in X- und Y-Richtung an.
  Erwartet ein Array mit zwei Fließkommzahlen.

.PARAMETER InputFile
  Ein Pfad zur Datei mit Eingabedaten.

.NOTES
  Version:        1.0
  Author:         Tobias Kiertscher
  Creation Date:  2025-06-17

.LINK
  https://honest-devhead.com/posts/commandline-3
#>

param (
    [switch]$AlternativeMode,

    [double]$Speed = 100.0,

    [double[]]$Offset = @(0.0, 0.0),

    [Parameter(Mandatory=$true, Position=0)]
    [string]$InputFile
)

# Fehlererkennung
if ($Offset.Count -ne 2) {
    Write-Error "Der Parameter -Offset erwartet ein Array mit genau zwei Werten."
    exit 1
}

# Hauptprogramm
Write-Output "Programm wird ausgeführt mit:"
if ($AlternativeMode) {
    Write-Output "  Modus: alternativ"
} else {
    Write-Output "  Modus: normal"
}
Write-Output "  Speed:  $Speed"
Write-Output "  Offset: ($($Offset[0]); $($Offset[1]))"
Write-Output "  Input:  $InputFile"
