# git笔记

## 初步

### Git 是什么？

#### 直接记录快照，而非差异比较

Git把数据看作是对小型文件系统的一系列快照。在Git中，每当提交更新或保存项目状态时，它基本上会对当时的全部文件创建一个快照并保存这个快照的索引。为了效率，如果文件没有修改，Git不再重新存储该文件，而是只保留一个链接指向之前存储的文件。Git对待数据更像是一个快照流(stream of snapshots)。

#### 近乎所有操作都是本地执行

在Git中的绝大多数操作都只需要访问本地文件和资源，一般不需要来自网络上其它计算机的信息。

#### Git保证完整性

Git中所有的数据在存储前都计算校验和，然后以校验和来引用。这意味着不可能在Git不知情时更改任何文件内容或目录内容。

#### Git一般只添加数据

你执行的Git操作，几乎只往Git数据库中添加数据。 你很难使用Git从数据库中删除数据，也就是说Git几乎会执行任何可能导致文件不可恢复的操作。

#### 三种状态

Git 有三种状态，文件可能处于其中之一：**已提交**（committed）、**已修改**（modified）和**已暂存**（staged）。
+ 已修改表示修改了文件，但还没保存到数据库中。
+ 已暂存表示对一个已修改文件的当前版本做了标记，使之包含在下次提交的快照中。
+ 已提交表示数据已经安全地保存在本地数据库中。

这会让我们的Git项目拥有三个阶段：工作区、暂存区以及Git目录。

工作区是对项目的某个版本独立提取出来的内容。 这些从Git仓库的压缩数据库中提取出来的文件，放在磁盘上供你使用或修改。

暂存区是一个文件，保存了下次将要提交的文件列表信息，一般在Git仓库目录中。 按照Git的术语叫做“索引”，不过一般说法还是叫“暂存区”。

Git仓库目录是Git用来保存项目的元数据和对象数据库的地方。 这是Git中最重要的部分，从其它计算机克隆仓库时，复制的就是这里的数据。

基本的Git工作流程如下：
1. 在工作区中修改文件。
2. 将你想要下次提交的更改选择性地暂存，这样只会将更改的部分添加到暂存区。
3. 提交更新，找到暂存区的文件，将快照永久性存储到Git目录。

如果 Git 目录中保存着特定版本的文件，就属于**已提交**状态。 如果文件已修改并放入暂存区，就属于**已暂存**状态。  如果自上次检出后，作了修改但还没有放到暂存区域，就是**已修改**状态。

### 安装

#### Linux

https://git-scm.com/download/linux

 #### MacOS

https://git-scm.com/download/mac

#### Windows

https://git-scm.com/download/win

### 初次运行Git前的配置

Git 自带一个git config的工具来帮助设置控制Git外观和行为的配置变量。 这些变量存储在三个不同的位置：

1. /etc/gitconfig 文件: 包含系统上每一个用户及他们仓库的通用配置。如果在执行git config时带上--system 选项，那么它就会读写该文件中的配置变量。（由于它是系统配置文件，因此你需要管理员或超级用户权限来修改它。）
2. ~/.gitconfig 或 ~/.config/git/config 文件：只针对当前用户。 你可以传递--global选项让 Git读写此文件，这会对你系统上所有的仓库生效。
3. 当前使用仓库的Git目录中的config文件（即.git/config）：针对该仓库。你可以传递--local选项让 Git 强制读写此文件，虽然默认情况下用的就是它。（当然，你需要进入某个Git仓库中才能让该选项生效。）

在Windows系统中，Git会查找$HOME目录下（一般情况下是 C:\Users\$USER ）的.gitconfig文件。Git 同样也会寻找/etc/gitconfig文件，但只限于 MSys 的根目录下，即安装Git时所选的目标位置。

可以通过以下命令查看所有的配置以及它们所在的文件：

```shell
git config --list --show-origin
```

#### 用户信息

安装完Git之后，要做的第一件事就是设置你的用户名和邮件地址。这一点很重要，因为每一个Git提交都会使用这些信息，它们会写入到你的每一次提交中，不可更改：

```shell
git config --global user.name "liuweijun999"
git config --global user.email liuweijun999@qq.com
```
#### 文本编辑器

配置默认文本编辑器，当Git需要你输入信息时会调用它。如果未配置，Git会使用操作系统默认的文本编辑器。

| 编辑器 | 设置命令 |
| -- | -- |
| Atom | `git config --global core.editor "atom --wait"`|

| BBEdit (Mac, with command line tools) | `git config --global core.editor "bbedit -w"` |

| Emacs | `git config --global core.editor emacs` |

| Gedit (Linux) | `git config --global core.editor "gedit --wait --new -window" `|

| Gvim (Windows 64-bit) | `git config --global core.editor "'C:/Program Files/Vim/vim72/gvim.exe' --nofork '%*'" (Also see note below)`|

| Kate (Linux) | `git config --global core.editor "kate"` |

| nano | `git config --global core.editor "nano -w"` |

|Notepad (Windows 64-bit) | `git config core.editor notepad` |

|Notepad++ (Windows 64-bit) | `git config --global core.editor "'C:/Program Files/Notepad++/notepad++.exe' -multiInst -notabbar -nosession -noPlugin" (Also see note below)` |

|Scratch (Linux) | `git config --global core.editor "scratch-text-editor"` |

|Sublime Text (macOS) | `git config --global core.editor "/Applications/Sublime\ Text.app/Contents/SharedSupport/bin/subl --new-window --wait"` |

|Sublime Text (Windows 64-bit) | `git config --global core.editor "'C:/Program Files/Sublime Text 3/sublime_text.exe' -w" (Also see note below)` |

|TextEdit (macOS) | `git config --global --add core.editor "open -W -n"` |

|Textmate | `git config --global core.editor "mate -w"` |

|Textpad (Windows 64-bit) | `git config --global core.editor "'C:/Program Files/TextPad 5/TextPad.exe' -m (Also see note below)` |

|Vim | `git config --global core.editor "vim"` |

|VS Code | `git config --global core.editor "code --wait"` |

|WordPad | `git config --global core.editor '"C:\Program Files\Windows NT\Accessories\wordpad.exe"'"` |

|Xi | `git config --global core.editor "xi --wait"` |

#### 检查配置信息

想要检查你的配置，可以使用`git config --list`命令来列出所有Git当时能找到的配置。

可能会看到重复的变量名，因为 Git 会从不同的文件中读取同一个配置（例如：/etc/gitconfig 与~/.gitconfig）。 这种情况下，Git会使用它找到的每一个变量的最后一个配置。

你可以通过输入 `git config <key>`： 来检查 Git 的某一项配置。

例如：

```shell
git config user.name
```

由于Git会从多个文件中读取同一配置变量的不同值，因此你可能会在其中看到意料之外的值而不知道为什么。此时，你可以查询Git中该变量的原始值，它会告诉你哪一个配置文件最后设置了该值：

```shell
 git config --show-origin <key>
```

例如：

```shell
git config --show-origin user.name
```

### 获取帮助

若使用Git时需要获取帮助，有三种等价的方法可以找到Git命令的综合手册。

```shell
git help <verb>
```

```shell
git <verb> --help
```

```shell
man git-<verb>
```

例如，要想获得`git config`命令的手册，执行：

```shell
git help config
```

这些命令很棒，因为你随时随地可以使用而无需联网。 如果你觉得手册或者本书的内容还不够用，你可以尝试在Freenode IRC服务器 https://freenode.net上的#git或#github 频道寻求帮助。

此外，如果你不需要全面的手册，只需要可用选项的快速参考，那么可以用`-h`选项获得更简明的 “help” 输出
例如：
```shell
git add -h
```

## git基础

### 获取Git仓库

通常有两种获取Git项目仓库的方式：

1. 将尚未进行版本控制的本地目录转换为Git仓库；
2. 从其它服务器 克隆 一个已存在的Git仓库。

#### 在已存在目录中初始化仓库

想要用Git来控制它，那么首先需要进入该项目目录中。

**Linux**
```shell
cd /home/user/my_project
```

**Linux**
```shell
cd /home/user/my_project
```

**Linux**
```shell
cd /home/user/my_project
```

然后，执行：

```shell
git init
```

该命令将创建一个名为.git 的子目录，这个子目录含有你初始化的Git仓库中所有的必须文件。 但是，在这个时候，我们仅仅是做了一个初始化的操作，你的项目里的文件还没有被跟踪。

如果在一个已存在文件的文件夹（而非空文件夹）中进行版本控制，你应该开始追踪这些文件并进行初始提交。可以通过`git add`命令来指定所需的文件来进行追踪，然后执行`git commit`：

```shell
git add file
```

```shell
git commit -m "commit message"
```

#### 克隆现有的仓库

想获得一份已经存在了的Git仓库的拷贝,这时就要用到`git clone`命令。Git 克隆的是该Git仓库服务器上的几乎所有数据，而不是仅仅复制完成你的工作所需要文件。 当你执行`git clone`命令的时候，默认配置下远程Git仓库中的每一个文件的每一个版本都将被拉取下来。

克隆仓库的命令是`git clone <url>`。 比如，要克隆 Git 的链接库libgit2，可以用下面的命令：

```shell
git clone https://github.com/libgit2/libgit2
```

这会在当前目录下创建一个名为 “libgit2” 的目录，并在这个目录下初始化一个.git文件夹， 从远程仓库拉取下所有数据放入.git文件夹，然后从中读取最新版本的文件的拷贝。

可以通过额外的参数指定新的目录名：

```shell
git clone https://github.com/libgit2/libgit2 mylibgit
```
这会执行与上一条命令相同的操作，但目标目录名变为了mylibgit。

### 记录每次更新到仓库

工作目录下的每一个文件都不外乎这两种状态：**已跟踪**或**未跟踪**。已跟踪的文件是指那些被纳入了版本控制的文件，在上一次快照中有它们的记录，在工作一段时间后，它们的状态可能是**未修改**，**已修改**或**已放入暂存区**。

工作目录中除已跟踪文件外的其它所有文件都属于未跟踪文件，它们既不存在于上次快照的记录中，也没有被放入暂存区。初次克隆某个仓库的时候，工作目录中的所有文件都属于已跟踪文件，并处于未修改状态，因为Git刚刚检出了它们，而尚未编辑过它们。

编辑过某些文件之后，由于自上次提交后对它们做了修改，Git将它们标记为已修改文件。 在工作时，可以选择性地将这些修改过的文件放入暂存区，然后提交所有已暂存的修改，如此反复。

#### 检查当前文件状态

可以用`git status`命令查看哪些文件处于什么状态。



