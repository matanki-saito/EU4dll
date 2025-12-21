# EU4DLL

This dll makes it possible to display double-byte characters on Europa Universalis IV.

## Notice

- This project is **unofficial**.
- Windows and macOS are supported. The library works on Steam version.
- Linux support is experimental (not fully tested).
- Displaying very long tooltips can cause **CTD**. See [here](https://github.com/matanki-saito/EU4dll/issues/226).

## How to use

- Manual install
  1. Download latest release zipped file and unpack it.
  2. Put all files into the game directory.
  3. Subscribe multibyte mods from steam or add mods to paradox user directory in your documents folder.
  4. Enable mods on game luncher
  5. Play game. 👍

- Automatic install

  1. Download [Simple Installer](https://github.com/matanki-saito/SimpleInstaller)
  2. See [Install Guide (Japanese)](https://paradoxian-japan-mod.com/page-1295/)
  3. Enable mods on game luncher
  4. Play game. 👍

## Find bugs

If you find a bug, **create a issue** in this repository.

## Spec

### plugins/plugin.ini

#### ERROR_TEST

It is for the alert debug.

#### SEPARATE_CHARACTER_CODE_POINT

Change the character that connects the region name and the country name. See ISSUE-164

#### REVERSING_WORDS_BATTLE_OF_AREA

Change the words ordering.

- Battle of / xxx -> xxx / Battle of
- Siege of / xxx -> xxx / Siege of
- Occupation of xxx -> xxx / Occupation of

### Autoupdate

Plugin.dll and Plugin64.dll will be updated automatically. It requires an Internet connection at game run. If you do not need or play offline game, please DELETE "plugins/autoupdate.bat" file.

### Name order

Attaching Inverted Question Mark(¿) to dynasty, the first name and last name are reversed.

```paradox
1534.6.23 = {
  heir = {
    name = "Nobunaga"  # Nobunaga
    monarch_name = "Nobunaga"  # Nobunaga
    dynasty = "¿Oda"  # Oda
    birth_date = 1534.6.23
    death_date = 1582.6.21
    claim = 90
    adm = 5
    dip = 5
    mil = 6
  }
}
# Nobunaga Oda -> Oda Nobunaga
```

When you use this feature, please exclude Inverted Question Mark(¿) from all fonts.

## Building from Source

### macOS

Requirements:
- CMake 3.15 or later
- Xcode Command Line Tools
- Boost library

Build steps:
```bash
# Install dependencies (using Homebrew)
brew install cmake boost

# Clone the repository
git clone https://github.com/matanki-saito/EU4dll.git
cd EU4dll

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .

# The output will be Plugin64.dylib in the build/Plugin64 directory
```

Installation on macOS:
1. Build the library following the steps above
2. Copy `Plugin64.dylib` to your EU4 game directory
3. Use `DYLD_INSERT_LIBRARIES` environment variable to inject the library when launching EU4:
   ```bash
   DYLD_INSERT_LIBRARIES=/path/to/Plugin64.dylib /path/to/Europa\ Universalis\ IV.app/Contents/MacOS/eu4
   ```

**Note**: macOS System Integrity Protection (SIP) may prevent library injection. You may need to disable SIP or use other methods to load the library.

### Windows

Use the provided Visual Studio solution file `EU4JPS.sln` to build the project.

## Licence

MIT Licence

## Thanks

This dll was forked by the following project. Thank you so much.

[EU4CHS](https://bitbucket.org/kelashi/eu4chs/src/master/)
