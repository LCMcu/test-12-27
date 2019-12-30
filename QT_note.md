## 											QT

### 1、QProcess

QProcess是QT提供的与外部程序进行交互的一个类，主要使用到以下的函数：

```c++
start();     //启动一个进程
kill();         //关闭启动的外部进程
write();     //向外部进程写入数据
readAllStandardOutput();     //读取外部进程的标准输出
readAllStandardError();        //读取外部进程的错误信息
```

- 创建QProcess对象并连接信号与槽

```c++
cmd = new QProcess(this);
connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
```

- 启动外部程序并写入数据

```c++
cmd->start("bash");             //启动终端(Windows下改为cmd)
cmd->waitForStarted();        //等待启动完成
cmd->write("ls\n");               //向终端写入“ls”命令，注意尾部的“\n”不可省略
```



### 2、**QString**

- 1、构造函数](https://www.cnblogs.com/retry/p/9328731.html#构造函数)
- 2、判断是否为空字符串](https://www.cnblogs.com/retry/p/9328731.html#判断是否为空字符串)
- 3、字符串转换为数值](https://www.cnblogs.com/retry/p/9328731.html#字符串转换为数值)
- 4、数值转换为字符串并设为 QString 对象的值](https://www.cnblogs.com/retry/p/9328731.html#数值转换为字符串并设为-qstring-对象的值)
- 5、大小写转换](https://www.cnblogs.com/retry/p/9328731.html#大小写转换)
- 6、QString 对象的比较](https://www.cnblogs.com/retry/p/9328731.html#qstring-对象的比较)
- 7、字符串处理](https://www.cnblogs.com/retry/p/9328731.html#字符串处理)
- 7.1、追加](https://www.cblogs.com/retry/p/9328731.html#追加)
- 7.2、查找](https://www.cnblogs.com/retry/p/9328731.html#查找)
- 7.3、插入](https://www.cnblogs.com/retry/p/9328731.html#插入)
- 7.4、移除](https://www.cnblogs.com/retry/p/9328731.html#移除)
- 7.5、替换](https://www.cnblogs.com/retry/p/9328731.html#替换)
- 7.6、搜索替换](https://www.cnblogs.com/retry/p/9328731.html#搜索替换)
- 7.7、清空](https://www.cnblogs.com/retry/p/9328731.html#清空)
- 7.8、截断](https://www.cnblogs.com/retry/p/9328731.html#截断)
- 7.9、截断获取子字符串](https://www.cnblogs.com/retry/p/9328731.html#截断获取子字符串)
- 7.A、空白字符操作](https://www.cnblogs.com/retry/p/9328731.html#a空白字符操作)
- 7.B、索引](https://www.cnblogs.com/retry/p/9328731.html#b索引)
- 7.C、统计](https://www.cnblogs.com/retry/p/9328731.html#c统计)

```c
详见：https://www.cnblogs.com/retry/p/9328731.html
```



### 3、QByteArry

QT之QByteArry

​		Qt通过QByteArray为我们提供了一个字节数组容器。QByteArray既可以用来存储原始的字节，包括'\0'，也可以用来存储传统的8-bit 的以'\0'结尾的字符串。使用QByteArray比使用普通的const char* 更方便。并且，在底层，它可以确保其中存储的数据以'\0'结尾，并且通过隐式共享（写时拷贝）策略减少内存的使用和不必要的数据复制。

- QByteArry的初始化      	(https://www.cnblogs.com/retry/p/9328697.html#qbytearry的初始化)

  ```c++
  1、
  QByteArray ba;
  ba.resize(3);
  ba[0] = 0x30;
  ba[1] = 0x31;
  ba[2] = 0x32;
  2、
  QByteArray strInt("1234");
  ```

  

- QByteArry的访问              (https://www.cnblogs.com/retry/p/9328697.html#qbytearry的访问)

- QByteArry的字节大小       (https://www.cnblogs.com/retry/p/9328697.html#qbytearry的字节大小)

- QByteArry的相互转换       (https://www.cnblogs.com/retry/p/9328697.html#qbytearry的相互转换)

- QByteArry的接口函数       (https://www.cnblogs.com/retry/p/9328697.html#qbytearry的接口函数)



### 5、QString 与QByteArry相互转换

1. #### QString 转QByteArry

```c++
QString str("hello");  
QByteArray bytes = str.toUtf8();    // QString转QByteArray方法1 
 
QString str("hello");  
QByteArray bytes = str.toLatin1();  // QString转QByteArray方法2

```

####   2.QByteArry转QString

```c++
    QByteArray bytes("hello world");
    QString string = bytes;      // QByteArray转QString方法1
 
    QByteArray bytes("hello world");
    QString string;
    string.prepend(bytes);       // QByteArray转QString方法2
```



### 6、QStringList 

QStringList 类提供了一个字符串列表
从 QList 继承而来，它提供快速索引为基础的接入以及快速插入和清除
其成员函数用于操作这个字符串列表如 append() ，insert(), replace(), removeAll(), removeAt(), removeFirst(),         	      removeLast(), and removeOne() 等      	
	

- **增加字符串**
  可以通过 append() ，或使用 <<，如
  QStringList fonts;
  fonts << "Arial" << "Helvetica" << "Times" << "Courier";
  // fonts:[ "Arial" ,"Helvetica", "Times" , "Courier"]
- **合并字符串使用 join( )**
  QString str = fonts.join(",");
  // str == "Arial,Helvetica,Times,Courier"
- **拆分字符串**
  QString str = " Arial,Helvetica, ,Times,Courier ";
  QStringList list1 = str.split(",");
  // list1: [ " Arial ", " Helvetica ", ” “, " Times ", " Courier " ]
  QStringList list2 = str.split(",", QString::SkipEmptyParts);
  // list2: [ " Arial ", " Helvetica ", " Times ", " Courier " ]
  也就是说如果有 QString ：： SkipEmptyParts ，空项不会出现在结果。默认情况下，空项被保留
- **索引**
  IndexOf （）函数返回给定字符串的第一个出现的索引。
  而 lastIndexOf （）函数，返回字符串的最后一次出现的索引。
- **替换 replaceInStrings （）**
  QStringList files;
  files << "$QTDIR/src/moc/moc.y"
  << "$QTDIR/src/moc/moc.l"
  << "$QTDIR/include/qconfig.h";
  files.replaceInStrings("$QTDIR", "/usr/lib/qt");
  // files: [ "/usr/lib/qt/src/moc/moc.y", ...]
- **过滤 filter （）**
  可以让你提取一个新的列表只包含这些字符串包含一个特定的字符串（或匹配特定正则表达式）：
  QStringList list;
  list << "Bill Murray" << "John Doe" << "Bill Clinton";
  QStringList result;
  result = list.filter("Bill");
  // result: ["Bill Murray", "Bill Clinton"]

### 7、text Browser 类

```c++
ui->textBrowser->append(str);    //每调用1次换行显示
```

```c++
textBrowser->insertPlainText(str); //插入  依次往后显示
```

```c++
ui->textBrowser_Receive->moveCursor(QTextCursor::End);*//接收框始终定为在末尾一行
```

### 8、SerialPort 相关类

#### QSerialPort

#### QSerialPortInfo

### 9、QComboBox

QComboBox小部件是组合的按钮和弹出列表。[更多...](https://doc.qt.io/qt-5/qcombobox.html#details)

| 标头：   | #include <QComboBox>                                       |
| -------- | ---------------------------------------------------------- |
| qmake：  | QT + =小部件                                               |
| 继承：   | [QWidget](https://doc.qt.io/qt-5/qwidget.html)             |
| 继承者： | [QFontComboBox](https://doc.qt.io/qt-5/qfontcombobox.html) |



## **BootLoader**

CortexM3有3种启动方式 ：
BOOT1=1 BOOT0=1 ，中断向量表定位于SRAM区，即起始地址为0x2000000，同时复位后PC指针位于0x2000000处。 
BOOT1=x BOOT0=0，中断向量表定位于FLASH区，即起始地址为0x8000000，同时复位后PC指针位于0x8000000处。 
BOOT1=0 BOOT0=1 ，中断向量表定位于内置Bootloader区，此时可通过串口下载程序的二进制文件到flash区。

中断向量：中断的地址的变量；
中断向量表：中断类型号与相应中断源的[中断处理](https://www.baidu.com/s?wd=中断处理&tn=SE_PcZhidaonwhc_ngpagmjz&rsv_dl=gh_pc_zhidao)程序入口地址之间的连接表；
[中断服务程序](https://www.baidu.com/s?wd=中断服务程序&tn=SE_PcZhidaonwhc_ngpagmjz&rsv_dl=gh_pc_zhidao)：发生中断时所执行的中断代码。

### M3启动

​	Cortex-M3内核规定，起始地址必须存放堆顶指针，而第二个地址则必须存放复位中断入口向量地址，这样在Cortex-M3内核复位后，会自动从起始地址的下一个32位空间取出复位中断入口向量，跳转执行复位中断服务程序。对比ARM7/ARM9内核，Cortex-M3内核则是固定了中断向量表的位置而起始地址是可变化的。

### 堆栈

一个由c/C++编译的程序占用的内存分为以下几个部分 
1、栈区（stack）— 由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈。 
2、堆区（heap） — 一般由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收 。注意它与数据结构中的堆是两回事，分配方式倒是类似于链表，呵呵。 
3、全局区（静态区）（static）—，全局变量和静态变量的存储是放在一块的，初始化的全局变量和静态变量在一块区域， 未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。 - 程序结束后有系统释放 
4、文字常量区—常量字符串就是放在这里的。 程序结束后由系统释放 
5、程序代码区—存放函数体的二进制代码。



## **git**

git init  

git add  filename

git commit -m  "........" 

git  log     //查看提交记录

git status   // 查看暂存区 和工作区状态

git  checkout  --filename  //从暂存区或版本库恢复  撤销工作区的修改

git reset HEAD  filename     //把暂存区的修改撤销掉（unstage），重新放回工作区



## sqlite3

### C API

打开数据库：

```c
int sqlite3_open(const char *filename, sqlite3 **ppDb)
```

参数：filename: 数据库路径和及名称

​			ppDb: 回填的数据库句柄。

执行SQL 语句：

```c
int sqlite3_exec(sqlite3 *, const char *sql, int (*callback)(void *, int, char **, char **), 
                 void * , char **errmsg)
```

参数： db： 数据库

​			sql:  SQL语句

​			callback：回调函数 

​			void *   ：回调函数的第一个参数

​			errmsg  ：错误信息



```c
int sqlite_callback(void* para, int columnCount, char** columnValue, char** columnName);
```

参数：pvoid ：  由 sqlite3_exec() 的第四个参数传递而来 

​			columnCount:  表的列数

​			columnValue: 指向查询结果的指针数组, 可以由 sqlite3_column_text() 得到

​			columnName:  指向表头名的指针数组, 可以由 sqlite3_column_name() 得到

​			