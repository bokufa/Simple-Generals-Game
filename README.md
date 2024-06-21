# Generals 游戏复刻（基于终端）

这是一个用 C++ 编写的复刻 Generals 游戏的项目。目前实现了单人游戏模式，后续计划发布 GUI 版本和联网多人游戏版本。

## 游戏简介

Generals 是一款策略游戏，玩家通过控制军队和资源来扩展领土和战斗敌人。本项目旨在重新实现这款经典游戏的核心功能，并逐步扩展为更多的游戏模式和功能。

## 功能特性

- 单人游戏模式：目前支持基于终端的单人游戏体验。
- 将来的计划：
  - GUI 版本：提供更友好的用户界面和交互。
  - 联网多人游戏：实现与其他玩家的在线对战功能。

## 安装与运行

### 克隆项目

首先，克隆项目到本地计算机：

```bash
git clone https://github.com/bokufa/Simple-Generals-Game.git
cd Simple-Generals-Game-version0.1
```
可以直接点击Generals.exe运行游戏。
若想修改源代码后运行，请参照如下步骤
### 编译与运行
使用 C++ 编译器编译代码，并运行游戏：

```bash
g++ main.cpp -lpdcurses -o Generals
```

## 使用说明
### 游戏规则：
#### 游戏中的 1 turn 就是 现实中的 1s。开局时，你会有一个自己的王城（标有王冠），王城每 1 turn 会造出 1 个兵。每个格子上面的数字代表这个格子上有多少个兵。你可以利用你自己的兵进行扩张（鼠标左键选中想操作的格子，WASD控制方向，双击左键代表分出该格子中的一半兵进行操作）。

#### 每 25 turn，你的领土上所有格子都会增加 1 个兵。所以在前期应该快速扩张领土。

#### 游戏内有两种特殊格子：山地和古城。山地即上图浅灰色有折线的格子，这种格子不能破坏，也不能经过。古城即上图深灰色标有数字的格子，古城上的数字代表城内守卫的兵力。你可以花费 古城守卫兵力+1 数量的士兵占领古城，占领后古城将变为你的城池。你的城池与你的王城一样，每 1 turn 会为你生产 1 个兵，所以拥有自己的城池至关重要。

#### 你可以进攻敌对势力。如果你占领了某个其他势力的王城，那么这个势力就会被消灭，他的王城将会变为你的一座城池，他的领土将会全部变为你的领土。此外，他的领土上的所有兵力将会减半（向上取整），并成为你的兵力。所以，攻打敌人是致富的主要途径。
### 控制：鼠标选择 wasd左右上下移动。
## 贡献与反馈
欢迎对项目进行贡献或者提供反馈。如果你有任何建议或发现了 bug，请提交 Issue 或 Pull Request。

## 计划与未来
未来的计划包括但不限于：

GUI 版本的开发和发布。
实现多人联网游戏模式。
提升游戏性和用户体验。
