# EU4DLL

This dll makes it possible to display double-byte characters on Europa Universalis IV.

## Notice

- This project is **unofficial**.
- Windows is supported and dll only works on Steam.
- macOS is not supported. I don't have those plans.
- Linux is not supported.

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

## Licence

MIT Licence

## Thanks

This dll was forked by the following project. Thank you so much.

[EU4CHS](https://bitbucket.org/kelashi/eu4chs/src/master/)
