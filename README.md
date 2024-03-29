# ASCII-Sky-War

## 背景故事
Long long ago, an interplanetary war outbreaked, the evil invaders invaded all the planets for sufficient resources. During the period, many people died for the defense of their homeland. However, this massacre was far from over, and if no one could stand out to fight with the enemies, at last, maybe thousands of people would suffer the pain for a long time that anyone couldn’t imagine. In this emergency that allowed no time to delay, warriors appeared just like a beam of light in the dark, they piloted starships to fight with numerous evil starships bravely after a long time for training. In this game,  you can act as the brave man to experience the cruel war, piloting the starships to fight. 

## 项目简介
我的大一上学期C语言大作业

一个简易的飞机大战控制台小游戏, 附带排行榜前后端

前端使用Bootstrap+Ajax, 后端使用go语言开发

## 如何编译
### Windows
lib目录下附带32位版本的静态库, 如需64位库请自行编译

注: 用nmake编译PDCurses时需在Makefile.vc的开头加入变量PLATFORM = X86

**需要用Visual Studio 2022或以上版本构建项目**

### Linux
请自行下载/编译所需的库

```bash
在Ubuntu下可运行以下命令安装所需依赖库
sudo apt install libncurses5-dev
sudo apt install libcurl4-openssl-dev
```

本项目提供了一个简易的make脚本([Makefile](https://github.com/DawningW/ASCII-Sky-War/blob/main/Makefile))用于构建项目

在项目根目录下运行`make`会在build目录下生成名为skywar的可执行文件

运行`make clean`可清理*.o目标文件

## 第三方库
- incbin
- ncurses
- PDCurses-3.9
- miniaudio-0.10.42
- cJSON-1.7.15
- curl-7.73.0

## 排行榜服务器
详见项目中的server目录

在该目录下运行`go build`编译服务端

**config.toml**是服务端的配置文件

前端网页位于server/assets目录下

后端文档详见([API.md](https://github.com/DawningW/ASCII-Sky-War/blob/main/server/API.md))

感谢xaxys大佬编写的排行榜后端

## 许可
本项目代码以WTFPL协议开源, 但您不能未经修改直接编译整个项目再二次发布

另外不希望有同学直接clone项目后就作为C语言大作业交上去, 这对提升编程水平没有任何作用

如有发现这种行为, 我将随时可能删除此仓库

对该仓库许可协议的最终解释权归作者所有

引用的第三方库仍然遵守原协议

### 大连理工大学软件学院2016班作品
