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

On branch main

Your branch is up to date with 'origin/main'.


nothing to commit, working tree clean
这说明你现在的工作目录相当干净。换句话说，所有已跟踪文件在上次提交后都未被更改过。

Changes to be committed:
已暂存状态。

Changes not staged for commit:
已跟踪文件的内容发生了变化，但还没有放到暂存区。

Untracked files:
未跟踪的文件，意味着Git在之前的快照（提交）中没有这些文件。

#### 跟踪新文件

使用命令`git add`开始跟踪一个文件。 所以，要跟踪README文件，运行：

```shell
git add README
```

#### 暂存已修改的文件

已跟踪文件的内容发生了变化，但还没有放到暂存区。要暂存这次更新，需要运行`git add`命令。

`git add` 多功能命令：可以用它开始跟踪新文件，或者把已跟踪的文件放到暂存区，还能用于合并时把有冲突的文件标记为已解决状态等。

#### 状态简览

使用`git status -s`命令或`git status --short`命令，将得到一种格式更为紧凑的状态输出。

新添加的未跟踪文件前面有 ?? 标记，新添加到暂存区中的文件前面有A标记，修改过的文件前面有M标记；左栏指明了暂存区的状态，右栏指明了工作区的状态。

#### 忽略文件
总会有些文件无需纳入Git的管理，也不希望它们总出现在未跟踪文件列表。可以创建一个名为 .gitignore的文件，列出要忽略的文件的模式。

文件.gitignore 的格式规范如下：
+ 所有空行或者以#开头的行都会被Git忽略，即注释。
+ 可以使用标准的glob模式匹配，它会递归地应用在整个工作区中。
+ 匹配模式可以以（/）开头防止递归。
+ 匹配模式可以以（/）结尾指定目录。
+ 要忽略指定模式以外的文件或目录，可以在模式前加上叹号（!）取反。

glob模式是指shell所使用的简化了的正则表达式。星号（`*`）匹配零个或多个任意字符；`[abc] `匹配任何一个列在方括号中的字符（这个例子要么匹配一个a，要么匹配一个 b,要么匹配一个c）； 问号（`?`）只匹配一个任意字符；如果在方括号中使用短划线分隔两个字符，表示所有在这两个字符范围内的都可以匹配（比如`[0-9]`表示匹配所有 0 到 9 的数字）。使用两个星号（`**`）表示匹配任意中间目录，比如`a/**/z`可以匹配a/z、a/b/z或a/b/c/z等。

例如：

```gitignore
# 忽略所有的 .a 文件
*.a

# 但跟踪所有的 lib.a，即便你在前面忽略了 .a 文件
!lib.a

# 只忽略当前目录下的 TODO 文件，而不忽略 subdir/TODO
/TODO

# 忽略任何目录下名为 build 的文件夹
build/

# 忽略 doc/notes.txt，但不忽略 doc/server/arch.txt
doc/*.txt

# 忽略 doc/ 目录及其所有子目录下的 .pdf 文件
doc/**/*.pdf
```

GitHub有一个十分详细的针对数十种项目及语言的[.gitignore 文件列表](https://github.com/github/gitignore)。

一个仓库可能只根目录下有一个.gitignore文件，它递归地应用到整个仓库中。然而，子目录下也可以有额外的.gitignore文件。子目录中的.gitignore文件中的规则只作用于它所在的目录中。

#### 查看已暂存和未暂存的修改

想知道具体修改了什么地方，可以用`git diff`命令。

要查看尚未暂存的文件更新了哪些部分，不加参数直接输入`git diff`；此命令比较的是工作目录中当前文件和暂存区域快照之间的差异。也就是修改之后还没有暂存起来的变化内容。

查看已暂存的将要添加到下次提交里的内容，可以用`git diff --staged`命令。 这条命令将比对已暂存文件与最后一次提交的文件差异。

注意，`git diff`本身只显示尚未暂存的改动，而不是自上次提交以来所做的所有改动。所以有时候你一下子暂存了所有更新过的文件，运行`git diff`后却什么也没有。

`git diff --cached`查看已经暂存起来的变化（`--staged` 和`--cached`是同义词）。

可以使用`git difftool`命令来调用emerge或vimdiff等软件（包括商业软件）输出diff的分析结果。使用`git difftool --tool-help`命令来看你的系统支持哪些Git Diff插件。

#### 提交更新

暂存区已经准备就绪，就可以提交了。在此之前，请务必确认还有什么已修改或新建的文件还没有`git add`过，否则提交的时候不会记录这些尚未暂存的变化。这些已修改但未暂存的文件只会保留在本地磁盘。每次准备提交前，先用`git status`看下，你所需要的文件是不是都已暂存起来。然后再运行提交命令`git commit`：

```shell
git commit
```

这样会启动你选择的文本编辑器来输入提交说明。

编辑器会显示类似下面的文本信息：默认的提交消息包含最后一次运行`git status`的输出，放在注释行里，另外开头还有一个空行，供你输入提交说明。

更详细的内容修改提示可以用`-v`选项查看，这会将你所作的更改的 diff 输出呈现在编辑器
中，以便让你知道本次提交具体作出哪些修改。

退出编辑器时，Git会丢弃注释行，用你输入的提交说明生成一次提交。

也可以在`commit`命令后添加`-m`选项，将提交信息与命令放在同一行.

```shell
git commit -m "commit message"
```

提交后它会告诉你，当前是在哪个分支（master）提交的，本次提交的完整 SHA-1 校验和是什么（463dc4f），以及在本次提交中，有多少文件修订过，多少行添加和删改过。

注意：提交时记录的是放在暂存区域的快照。 任何还未暂存文件的仍然保持已修改状态，可以在下次提交时纳入版本管理。 每一次运行提交操作，都是对你项目作一次快照，以后可以回到这个状态，或者进行比较。

#### 跳过使用暂存区域

Git提供了一个跳过使用暂存区域的方式，只要在提交的时候，给`git commit`加上`-a`选项，Git就会自动把所有已经跟踪过的文件暂存起来一并提交，从而跳过 git add 步骤：