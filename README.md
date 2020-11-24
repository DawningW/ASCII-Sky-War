# ASCII-Sky-War

## 背景故事
long long ago, an interplanetary war outbreaked, the evil invaders invaded all the planets for sufficient resources. During the period, many people died for the defense of their homeland. However, this massacre was far from over, and if no one could stand out to fight with the enemies, at last, maybe thousands of people would suffer the pain for a long time that anyone couldn’t imagine. In this emergency that allowed no time to delay, warriors appeared just like a beam of light in the dark, they piloted starships to fight with numerous evil starships bravely after a long time for training. In this game,  you can act as the brave man to experience the cruel war, piloting the starships to fight. 

## 项目简介
我的大一上学期C语言大作业

## 如何编译
### Windows
lib目录下附带32位版本的静态库, 如需64位库请自行编译

注: 用nmake编译PDCurses时需在Makefile.vc的开头加入变量PLATFORM = X86

需要用Visual Studio 2019或以上版本构建项目

### Linux
请自行下载/编译所需的库

本项目提供了一个简易的make脚本(Makefile)用于构建项目

在项目根目录下运行make会生成名为build的可执行文件

运行make clean可清理*.o目标文件

## 第三方库
- PDCurses-3.9
- cJSON-1.7.14
- curl-7.73.0

## 许可
本项目代码以WTFPL协议开源, 但您不能未经修改直接编译整个项目再二次发布

另外不希望有同学直接clone项目后就作为C语言大作业交上去, 这对提升编程水平没有任何作用

如有发现这种行为, 我将随时可能删除此仓库

对该仓库许可协议的最终解释权归作者所有

引用的第三方库仍然遵守原开源协议

### 大连理工大学软件学院2016班612寝室作品
