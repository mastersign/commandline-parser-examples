const util = require('node:util')
const { exit } = require('node:process')

// Definition von Standardwerten
const DEFAULT_ARG_SPEED = '100.0'
const DEFAULT_ARG_OFFSET = '0.0,0.0'

function printHelp() {
  console.log('Syntax: tool [-a] [-s <S>] [-o <X>,<Y>] <Eingabedatei>')
  console.log('        tool -h | --help')
  console.log('')
  console.log('Ein Beispiel für ein Befehlszeilenprogramm')
  console.log('')
  console.log('Schalter:')
  console.log('  -h, --help')
  console.log('      Zeigt diese Hilfe an.')
  console.log('  -a, --alt')
  console.log('      Führt das Programm im alternativen Modus aus.')
  console.log('')
  console.log('Optionen:')
  console.log('  -s, --speed <S>')
  console.log('      Gibt die Geschwindigkeit an.')
  console.log(`      Standard: ${DEFAULT_ARG_SPEED}`)
  console.log('  -o, --offset <X>,<Y>')
  console.log('      Gibt den Offset für die Ausführung in X- und Y-Richtung an.')
  console.log(`      Standard: ${DEFAULT_ARG_OFFSET}`)
}

function parseCliArguments() {

  // Definition der Schalter und Optionen
  const cliArguments = {
    options: {
      'help': { short: 'h', type: 'boolean' },
      'alt': { short: 'a', type: 'boolean' },
      'speed': { short: 's', type: 'string' },
      'offset': { short: 'o', type: 'string' },
    },
    allowPositionals: true,
  }

  // Ausführung des Befehlszeilenparsers
  const {
    values: options,
    positionals: inputFiles,
  } = util.parseArgs(cliArguments)

  // Ausgabe der Hilfe
  if (options.help) {
    printHelp()
    exit(0)
  }

  // Umwandlungen und Fehlererkennung
  const altMode = options.alt
  const speed = Number.parseFloat(options.speed ?? DEFAULT_ARG_SPEED)
  if (Number.isNaN(speed)) {
    console.error('Syntaxfehler: Option -s/--speed <S> erwartet Fließkommazahl')
    exit(1)
  }
  const offset = (options.offset ?? DEFAULT_ARG_OFFSET)
    .split(',').map(Number.parseFloat)
  if (offset.length != 2 ||
      Number.isNaN(offset[0]) ||
      Number.isNaN(offset[1])
  ) {
    console.error('Syntaxfehler: Option -o/--offset <X>,<Y> erwartet zwei Fließkommazahlen')
    exit(1)
  }
  const inputFile = inputFiles[0]
  if (inputFiles.length != 1) {
    console.error('Syntaxfehler: Eine Eingabedatei muss angegeben werden')
    exit(1)
  }

  return {
    altMode,
    speed,
    offsetX: offset[0],
    offsetY: offset[1],
    inputFile,
  }
}

const args = parseCliArguments()

// Hauptprogramm
console.log('Programm wird ausgeführt mit:')
if (args.altMode) {
  console.log('  Modus:  alternativ')
} else {
  console.log('  Modus:  normal')
}
console.log(`  Speed:  ${args.speed}`)
console.log(`  Offset: (${args.offsetX}; ${args.offsetY})`)
console.log(`  Input:  ${args.inputFile}`)
