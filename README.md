# FM Librarian

**Now available as an in-browser utility:** [https://sg4e.github.io/FM-Librarian/](https://sg4e.github.io/FM-Librarian/)

A program that reads PS1 memory card images that contain *Yu-Gi-Oh! Forbidden Memories* save data and prints a list of obtained cards in the Library. All cards in the Library are included: owned, fusion-summoned, and ritual-summoned. The ideal way to track a Forbidden Memories 100% playthrough!

By sg4e.

[![Build status](https://ci.appveyor.com/api/projects/status/u34atpv4g7rcliin/branch/master?svg=true)](https://ci.appveyor.com/project/sg4e/fm-librarian/branch/master)

Releases built for Windows, Linux, and MacOS. Code works on any platform with a C compiler.

## Usage
The simplest way of using FM Librarian (on Windows):
1. Download the latest release
1. Extract
1. Copy your memory card image to the extracted directory where `librarian.exe` is. Your memory card file should end in `.SAVERAM`, `.mcr`, or `.gme`, or else it won't be recognized
1. Double-click on `run.bat`
1. A list of card ids that you've obtained in the library will be printed to `cards.txt`

**Note:** You **must** open the in-game "Library" menu and then save each time you want to use your memory card with this program. FM is lazy about keeping the library up-to-date, and does not update all your obtained cards, rituals, and fusions in the library until you open the "Library" menu. Your emulator may not flush the save data to the file until you close the ROM.

## Tested memory card formats
* Raw memory card dump
* Bizhawk (`.SAVERAM`)

FM Librarian should work with any emulator that accurately saves memory card data. If your memory card image is exactly 128KB, it will likely work. Some Bizhawk versions create 256KB card images, which are also supported. FM Librarian expects that the first block of the memory card contains the FM data, but you can specify an alternative block on the command line.

## Command-line usage
```
./librarian (options) [memory card image file] [output file]
```
Run `./librarian --help` for more info.

## Compiling
FM Librarian is a simple C program. Platform-specific code is avoided. Simply compile `librarian.c` on any platform with a C compiler.
