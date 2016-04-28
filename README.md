**Nuz Engine 主神游戏引擎**

--------------


御宅十字

----------


**一、概述**

--------

Nuz Engine，主神引擎是一个用于制作2D和3D游戏的游戏引擎，整个引擎划分为以下模块：
(斜体的为最小NUZ必须内容)

 - *场景管理器*
 - *虚拟文件系统*
 - *物理文件系统*
 - *声音管理器*
 - *输入设备管理器*
 - 实用工具集
 - 调试工具集


----------


**二、场景管理器**

-----------

场景管理器管理了一个场景，场景下可挂载其它的场景，并且还可以挂载物件和组件，物件可挂载组件和其他物件。
2D渲染中可以没有摄像机，也可以有摄像机，3D渲染必须有一个摄像机。
无论2D还是3D都只能各有一个摄像机。


----------


**三、虚拟文件系统**

------------

虚拟文件系统只用于存放只读的游戏资源，提供一个数据源接口，重写后可以挂载到虚拟文件系统的根目录和一级目录。需要获取数据时，虚拟文件系统返回一个已经全部加载完毕的缓冲区句柄，在此读取数据。


----------


**四、物理文件系统**

------------

它是一个虚拟文件系统数据源，同时提供了可以写出文件的接口，如果你想加载本地文件，你需要手动将它安装到数据虚拟文件系统里。


----------


**五、声音管理器**

-----------

声音管理器分为BGM播放器和SE播放器，以及自动SE播放器。
BGM播放器可以播放一个两段的循环音乐，如果你指定了头段，那么会播放一次头段然后不断播放循环段，如果你没有指定头段，则只循环播放尾段。
SE播放器可以简单的加载和播放一段音效。
如果仅仅想引起一个新的音效而不需要手动管理的话，使用自动SE播放器，只播放一次SE并且在SE播放完成后回收资源。


----------


**六、输入设备管理器**

-------------

输入设备管理器包含：
(斜体的为最小NUZ引擎必须内容)

 - *键盘管理器*
 - 鼠标管理器
 - 手柄管理器
 - VR设备管理器
 - AR设备管理器
 - 触摸管理器
 - 重力加速度计管理器
 - 陀螺仪管理器
 - 遥杆管理器
 - 震动设备管理器

对于手柄管理器，它只能接受手柄按钮管理，你可以从手柄管理器创建摇杆管理器等可以在手柄上嵌入的其他设备的管理器。


----------


**七、实用工具集**

-----------

它们都在单独的静态库里，可以酌情选用。

 - 常用着色器
 - CSV阅读器
 - Snow RV阅读器
 - Nuz RT阅读器
 - LuaCAPI封装类
 - TCP支持
 - UDP支持
 - 序列化数据包
 - 2D粒子系统物件组
 - 3D粒子系统物件组
 - 2D物理引擎
 - 3D物理引擎
 - 虚拟设备映射器


----------


**八、调试工具集**

-----------

 - 日志记录工具


----------


**九、编码风格**

----------

 - 类名：

一切类名每个单词首字母大写，如果该类为接口，则前缀大写I。
如IAssetLoader，IEngine。

 - 类的成员变量：

前缀m_，后跟单词，第一个单词全部小写，后跟单词均首字母大写，其余为小写。
如m_objList。

 - 类的私有成员函数：

第一个单词的首字母小写，其余均为首字母大写，其余字母小写。如useMatrix()

类的公有成员函数以及保护成员函数：
每单词首字母大写，如SetPosition()。

 - 参数列表和局部变量：

第一个单词首字母小写，其余单词首字母大写，如timeLimited。

大括号的开始与结束以及表达式写法：
大括号在结构开始处开始，在单独的行结束，后续结构则在上个大括号结束的同行结束，表达式则在每个运算符和数字间空格，但是自增自减运算符和括号没有空格，如：

    int main(){
        int i = 5;
        if(i == 5){
            i++;
            i--;
        }else if(i == 6){
            for(;;){
                i--;
            }
        }
    }

 - 每个cpp文件和.h文件：

文件应该注明该文件的修改日志，以及修改者是谁。
对于.h文件还应该注明每个类的作用和它的公有成员函数的作用。

