# TDGame

<p><a href="https://opensource.org/licenses/"></a><img src="https://img.shields.io/badge/License-GPL%20v3-blue.svg" alt="GPLv3 License"><a href="https://t.me/BrokenTom"></a><img src="https://badge.fury.io/gh/tterb%2FHyde.svg" alt="Version"> <a href="https://github.com/Flying-Tom/TDGame/actions/workflows/release-windows.yml"></a><img src="https://github.com/Flying-Tom/TDGame/actions/workflows/release-windows.yml/badge.svg" alt="Windows Release"> <a href="https://github.com/Flying-Tom/TDGame/actions/workflows/release-ubuntu.yml"></a><img src="https://github.com/Flying-Tom/TDGame/actions/workflows/release-ubuntu.yml/badge.svg" alt="Ubuntu Release"></p>

The course project of "Advanced Programming" in the fall semester of 2021: A simple tower defense game based on the Qt library

[Demos](https://github.com/Flying-Tom/TDGame/releases) built with Github Actions are available for download

## Project structure

![](doc/figs/MainWindow.png)

Using Qt's Graphics View framework

- The blue box, the `MainWindow` , represents the main window interface of the application

- The green box indicates that the current class is a custom base class inherited from Qt, and the black box is its corresponding subclass.

- `Tower` and `Enemy` are derived classes that inherit from `GameItem` (which abstracts the common features of towers and enemies to a greater extent)

- The green arrow indicates that the pointed end is a member of the other end, which is a parent-child relationship at the drawing level or at the object organization level (similar to aggregation)

> For more specific design and game content (unit introduction and implementation functions, etc.), please refer to the specific experimental report `doc/report.pdf`

## Game screenshot

4 maps, 7 types of towers and 8 types of enemies

- In-game `ESC` returns to the main menu, `F5` pauses
- <s>The game balance is sloppy (the enemy too strong or the tower too strong)</s>
- There are some designs with strong personal style that are not very recommended

![](doc/figs/level1.png)

![](doc/figs/level2.png)

![](doc/figs/level3.png)

![](doc/figs/level4.png)

## Compiler Environment

Qt &gt;= 5.12

Ubuntu

```
apt update
apt install cmake make g++ qt5-default qtmultimedia5-dev
```

Windows

- mingw Qt5.12
