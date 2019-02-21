# EU4DLL
This dll makes it possible to display double-byte characters on Europa Universalis IV.

## Notice
 - This project is **unofficial**.
 - macOS is not supported. I don't have those plans.
 - Only Steam version is supported.

## How to use
 1. Install DLL. I made an [simple installer](https://github.com/matanki-saito/SimpleInstaller).
 2. Subscribe to Any Lanugage Mod in Steam.
 3. Play game. 👍

## Find bugs
If you find a bug, **create a issue** in this repository. 
If possible, please write the issue report in English. However you can also create it in your language (Japanese, Korean, Chinese, Russian etc).

## Spec
### plugin.ini
TBD

### Autoupdate
Plugin.dll will be updated automatically. It requires an Internet connection at game run. If you do not need or play offline game, please DELETE "plugins/autoupdate.bat" file.

### Name order
Attaching Inverted Question Mark(¿) to dynasty, the first name and last name are reversed.

```
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
