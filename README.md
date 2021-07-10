# ColorPicker App
ColorPicker is a powerful screen color picker based on Qt's QColorDialog Class.

A colour picker and colour editor for web designers and digital artists, With Color Picker, identifying the colours, saving and editing is a quick and simple job.

Color Picker features include:

* Five formats of colour codes: HTML, HexRGBA, RGB, HSB/HSV, CMYK and their variations. Conversion of HTML, HEX and RGB colour codes into the corresponding colours.
* Colour picker for easy handling and greater precision.
* Colour list for saving and reusing the picked colour samples for each picked colour.
* Color preview widget
* Progressive color pattern generator 
* Support Switching three themes - System theme, Flat Light theme and Dark theme.

* More features soon..

# Requirements

* Qt5 or above

# Build instructions

For Linux, Windows and Mac. In all cases, you need a copy of the code:

```sh
git clone https://github.com/keshavbhatt/ColorPicker
```

## CLI method

These instructions perform an out-of-tree build, which is easier to manage.

```sh
mkdir build
cd build
qmake ../src
make
```

Assuming everything runs correctly, you can create an installation directory like so:

```sh
make INSTALL_ROOT=/path/to/installation install
```

This is useful when preparing to package ColorPicker for distribution.
If you just want to install it locally, leave out the `INSTALL_ROOT` parameter.

## GUI Method

* Open the `.pro` file in Qt creator
* Configure with one of your preferred toolkit version (Should be Qt5 or above)
* Once project is configured, Press Build or Run button to perform respective action

# Install and project status

 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

﻿**Stable and nightly Build on any [snapd](https://docs.snapcraft.io/installing-snapd) enabled Linux Distribution can be installed using:**

﻿[![color-picker](https://snapcraft.io//color-picker/badge.svg)](https://snapcraft.io/olivia) [![color-picker](https://snapcraft.io//color-picker/trending.svg?name=0)](https://snapcraft.io/color-picker)

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/color-picker)

    snap install color-picker

## AUR

You can install it from the AUR:

https://aur.archlinux.org/packages/colorpicker-keshavbhatt/


# Screenshot (could be old)
![ColorPicker Application for Linux Desktop](https://github.com/keshavbhatt/ColorPicker/blob/master/screenshots/1.jpg?raw=true)
![ColorPicker Application for Linux Settings dialog](https://github.com/keshavbhatt/ColorPicker/blob/master/screenshots/2.jpg?raw=true)
![ColorPicker Application for Linux Shade dialog](https://github.com/keshavbhatt/ColorPicker/blob/master/screenshots/3.jpg?raw=true)
