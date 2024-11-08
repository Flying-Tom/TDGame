# TDGame

<p>
<a href="https://opensource.org/licenses/">
<img src="https://img.shields.io/badge/License-GPL%20v3-blue.svg" alt="GPLv3 License">
</a>
<a href="https://github.com/Flying-Tom/TDGame/releases/latest">
<img src="https://img.shields.io/github/release/Flying-Tom/TDGame" alt="Version">
</a>
<a href="https://github.com/Flying-Tom/TDGame/actions/workflows/release-windows.yml">
<img src="https://github.com/Flying-Tom/TDGame/actions/workflows/release-windows.yml/badge.svg" alt="Windows Release">
</a>
<a href="https://github.com/Flying-Tom/TDGame/actions/workflows/release-ubuntu.yml">
<img src="https://github.com/Flying-Tom/TDGame/actions/workflows/release-ubuntu.yml/badge.svg" alt="Ubuntu Release">
</a>
</p>

NJUCS 2021 年秋季学期《高级程序设计》课程项目：基于 Qt 实现的简单塔防小游戏，现有可供下载的 [Demo](https://github.com/Flying-Tom/TDGame/releases)

## 项目结构

采用了Qt的`Graphics View`框架

```mermaid
---
  config:
    class:
      hideEmptyMembersBox: true
---
classDiagram
  direction LR

  MainWindow <--> Game
  Game *-- Statistic
  Game *-- Map

  Map o-- Shop
  Map o-- Enemy
  Map o-- Tower

  GameItem <|-- Tower
  GameItem <|-- Enemy

  Tower --> InfoPanel
  Tower --> Bullet

  style MainWindow fill:#3647AD
  style Game fill:#008A7C
  style Statistic fill:#008A7C
  style Map fill:#008A7C
  style GameItem fill:#008A7C


  direction TB
  Tower <|-- GunTower
  Tower <|-- LaserTower
  Tower <|-- MissileTower
  Tower <|-- Bomb
  Tower <|-- Repeller
  Tower <|-- SawTooth
  Tower <|-- Shield

  direction TB
  Enemy <|-- BlackWarrior
  Enemy <|-- FallenWarrior
  Enemy <|-- Ghost
  Enemy <|-- CowardPlane
  Enemy <|-- Dragon
  Enemy <|-- RobotSoldier
  Enemy <|-- Shaman
  Enemy <|-- Spirit

```

4张地图，7种防御塔和8种敌人

- 游戏内`ESC`返回主菜单，`F5`暂停
- ~~游戏平衡做的稀巴烂 (仅为课设完成度)~~

## 游戏截图

|   |   |
|---|---|
|![level1.png](doc/figs/level1.png)|![level2.png](doc/figs/level2.png)|
|![level3.png](doc/figs/level3.png)|![level4.png](doc/figs/level4.png)|

## 编译环境

- Qt >= 5.12
- Ubuntu
  - `build-essential` & `cmake`
  - `qt5-default`, `qtmultimedia5-dev`
- Windows
  - [mingw](https://www.mingw-w64.org/)
