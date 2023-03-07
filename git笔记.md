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

```shell
git status 
```

On branch main

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

```shell
git add file
```
`git add` 多功能命令：可以用它开始跟踪新文件，或者把已跟踪的文件放到暂存区，还能用于合并时把有冲突的文件标记为已解决状态等。

#### 状态简览

使用`git status -s`命令或`git status --short`命令，将得到一种格式更为紧凑的状态输出。

```shell
git status -s
```

```shell
git sttus --short
```

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

```shell
git diff --staged
```

注意，`git diff`本身只显示尚未暂存的改动，而不是自上次提交以来所做的所有改动。所以有时候你一下子暂存了所有更新过的文件，运行`git diff`后却什么也没有。

`git diff --cached`查看已经暂存起来的变化（`--staged` 和`--cached`是同义词）。

```shell
git diff --cached
```

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

Git提供了一个跳过使用暂存区域的方式，只要在提交的时候，给`git commit`加上`-a`选项，Git就会自动把所有已经跟踪过的文件暂存起来一并提交，从而跳过 git add 步骤。

```shell
git commit -a -m "commit message"
```

`-a`选项使本次提交包含了所有修改过的文件。 这很方便，但是要小心，有时这个选项会将不需要的文件添加到提交中。

#### 移除文件

要从 Git中移除某个文件，就必须要从暂存区域移除。然后提交。可以用`git rm`命令完成此项工作，并连带从工作目录中删除指定的文件，这样以后就不会出现在未跟踪文件清单中了。

如果只是简单地从工作目录中手工删除文件，运行`git status`时就会在"Changes not staged for commit"部分（也就是未暂存清单）。

要删除之前修改过或已经放到暂存区的文件，则必须使用强制删除选项`-f`，这是一种安全特性，用于防止误删尚未添加到快照的数据，这样的数据不能被Git恢复。
```shell
git rm -f file
```

使用`--cached`选项可以把文件从Git仓库中删除（亦即从暂存区域移除），但仍然希望保留在当前工作目录中。换句话说，你想让文件保留在磁盘，但是并不想让Git继续跟踪。 当忘记添加.gitignore文件时，把一些不需要文件添加到暂存区时，这一做法尤其有用。

```shell
git rm --cached file
```

`git rm`命令后面可以列出文件或者目录的名字，也可以使用 glob 模式。例如：

```shell
 git rm log/\*.log
```

注意到星号*之前的反斜杠\， 因为Git有它自己的文件模式扩展匹配方式，所以我们不用shell来帮忙展开。此命令删除log/目录下扩展名为.log 的所有文件.

#### 移动文件

要在Git中对文件改名，可以这么做：

```shell
git mv file_from file_to
```
 
运行`git mv`就相当于运行了下面三条命令:

```shell
mv file_from file_to
git rm file_from
git add file_to
```

如此分开操作，Git也会意识到这是一次重命名。`git mv`是一条命令而非三条命令，直接使用`git mv`方便得多。不过在使用其他工具重命名文件时，记得在提交前`git rm`删除旧文件名，再`git add`添加新文件名。

### 查看提交历史

`git log`命令可以想回顾下提交历史。

```shell
git log
```

不传入任何参数的默认情况下，·git log`会按时间先后顺序列出所有的提交，最近的更新排在最上面。这个命令会列出每个提交的SHA-1校验和、作者的名字和电子邮件地址、提交时间以及提交说明。

选项`-p`或`--patch`会显示每次提交所引入的差异（按 补丁 的格式输出）。你也可以限制显示的日志条目数量，例如使用`-2`选项来只显示最近的两次提交。该选项除了显示基本信息之外，还附带了每次提交的变化。

```shell
git log -p -2
```

```shell
git log -patch -2
```

`--stat`选项在每次提交的下面列出所有被修改过的文件、有多少文件被修改了以及被修改过的文件的哪些行被移除或是添加了。在每次提交的最后还有一个总结。

```shell
git log --stat
```

`--pretty`这个选项可以使用不同于默认格式的方式展示提交历史。这个选项有一些内建的子选项供你使用。 比如`oneline`会将每个提交放在一行显示；外还有`short`,`full`和`fuller`选项，它们展示信息的格式基本一致，但是详尽程度不一。

```shell
git log --pretty=online
```

```shell
git log --pretty=short
```

```shell
git log --pretty=full
```

```shell
git log --pretty=fuller
```

`format`，可以定制记录的显示格式，例如：

```shell
git log --pretty=format:"%h - %an, %ar : %s"
```

`git log --pretty=format`常用的选项：

| 选项 | 说明 |
| -- | -- | -- |
| %H | 提交的完整哈希值 |
| %h | 提交的简写哈希值 |
| %T | 树的完整哈希值 |
| %t | 树的简写哈希值 |
| %P | 父提交的完整哈希值 |
| %p | 父提交的简写哈希值 |
| %an | 作者名字 |
| %ae | 作者的电子邮件地址 |
| %ad | 作者修订日期（可以用 --date=选项 来定制格式） |
| %ar | 作者修订日期，按多久以前的方式显示 |
| %cn | 提交者的名字 |
| %ce | 提交者的电子邮件地址 |
| %cd | 提交日期 |
| %cr | 提交日期（距今多长时间） |
| %s | 提交说明 |

**作者**指的是实际作出修改的人，**提交者**指的是最后将此工作成果提交到仓库的人。

当`oneline`或`format`与另一个`log`选项`--graph`结合使用时尤其有用。这个选项添加了一些ASCII字符串来形象地展示你的分支、合并历史：

```shell
git log --pretty=format:"%h %s" --graph
```

`git log`的常用选项：

| 选项 | 说明 |
| -- | -- |
| `-p` | 按补丁格式显示每个提交引入的差异。 |
| `--stat` | 显示每次提交的文件修改统计信息。 |
| `--shortstat` | 只显示 --stat 中最后的行数修改添加移除统计。 |
| `--name-only` | 仅在提交信息后显示已修改的文件清单。 |
| `--name-status` | 显示新增、修改、删除的文件清单。 |
| `--abbrev-commit` | 仅显示 SHA-1 校验和所有 40 个字符中的前几个字符。 |
| `--relative-date` | 使用较短的相对时间而不是完整格式显示日期（比如“2 weeks ago”）。 |
| `--graph` | 在日志旁以 ASCII 图形显示分支与合并历史。 |
| `--pretty` | 使用其他格式显示历史提交信息。可用的选项包括`oneline`、`short`、`full`、`fuller`和`format`（用来定义自己的格式）。 |
| `--oneline` | `--pretty=oneline --abbrev-commit` 合用的简写。 |

#### 限制输出长度

使用类似`-n`的选项，其中的n可以是任何整数，表示仅显示最近的n条提交。这个选项不是很常用，因为Git默认会将所有的输出传送到分页程序中，所以你一次只会看到一页的内容。

`--since`和`--until`选项可以按照时间作限制， 例如，下面的命令会列出最近两周的所有提交：

```shell
git log --since=2.weeks
```

该命令可用的格式十分丰富——可以是类似"2008-01-15"的具体的某一天，也可以是类似"2 years 1 day 3 minutes ago"的相对日期。

`--author`选项显示指定作者的提交，用`--grep`选项搜索提交说明中的关键字。

可以指定多个`--author`和`--grep`搜索条件，这样会只输出匹配任意`--author`模式和任意`--grep`模式的提交。然而，如果你添加了`--all-match`选项，则只会输出匹配所有`--grep`模式的提交。

`-S` 接受一个字符串参数，并且只会显示那些添加或删除了该字符串的提交。假设你想找出添加或删除了对某一个特定函数的引用的提交，可以调用：

```shell
git log -S function_name
```

如果只关心某些文件或者目录的历史提交，可以在`git log`选项的最后指定它们的路径。因为是放在最后位置上的选项，所以用两个短划线（`--`）隔开之前的选项和后面限定的路径名。

限制`git log`输出的选项：

| 选项 | 说明 |
| -- | -- |
| `-n` | 仅显示最近的n条提交。 |
| `--since`, `--after` | 仅显示指定时间之后的提交。 |
| `--until`, `--before` | 仅显示指定时间之前的提交。 |
| `--author` | 仅显示作者匹配指定字符串的提交。 |
| `--committer` | 仅显示提交者匹配指定字符串的提交。 |
| `--grep` | 仅显示提交说明中包含指定字符串的提交。 |
| `-S` | 仅显示添加或删除内容匹配指定字符串的提交。 |

`log`加上`--no-merges`选项可以避免显示的合并提交弄乱历史记录。

### 撤消操作

们提交完了才发现漏掉了几个文件没有添加，或者提交信息写错了。此时，可以运行带有`--amend`选项的提交命令来重新提交：

```shell
git commit --amend
```

注意，在修补最后的提交时，与其说是修复旧提交，倒不如说是完全用一个**新的提交替换旧的提交**，从效果上来说，就像是旧有的提交从未存在过一样，它并不会出现在仓库的历史中。

#### 取消暂存的文件

可以使用`git reset HEAD <file>`来取消暂存。

```shell
git reset HEAD <file>
```

[重置揭密]()中描述`reset`的更多细节。

#### 撤消对文件的修改

`git checkout -- <file>`可以把文件还原成上次提交时的样子（或者刚克隆完的样子，或者刚把它放入工作目录时的样子）。

```shell
git checkout -- <file>
```

注意，`git checkout -- <file>`是一个危险的命令。那个文件在本地的任何修改都会消失——Git会用最近提交的版本覆盖掉它。除非确实清楚不想要对那个文件的本地修改了，否则请不要使用这个命令。

如果仍然想保留对那个文件做出的修改，但是现在仍然需要撤消，可以使用[Git分支]()保存进度。

在Git中任何已提交的东西几乎总是可以恢复的。甚至那些被删除的分支中的提交或使用`--amend`选项覆盖的提交也可以恢复（[数据恢复]()）。 然而，任何你未提交的东西丢失后很可能再也找不到了。

### 远程仓库的使用

#### 查看远程仓库

想查看已经配置的远程仓库服务器，可以运行`git remote`命令。 它会列出指定的每一个远程服务器的简写。 如果克隆了仓库，那么至少应该能看到origin——这是 Git 给你克隆的仓库服务器的默认名字。

```shell
git remote
```

指定选项`-v`，会显示需要读写远程仓库使用的Git保存的简写与其对应的URL。

```shell
git remote -v
```

#### 添加远程仓库

运行`git remote add <shortname> <url>`添加一个新的远程Git仓库，同时指定一个方便使用的简写：

```shell
git remote add <shortname> <url>
```

例如·：

```shell
git remote add pb https://github.com/paulboone/ticgit
```

现在可以在命令行中使用pb来代替整个url。 例如，如果你想拉取Paul的仓库中有但你没有的信息，可以运行：

```shell
git fetch pb
```

Paul的master分支可以在本地通过pb/master访问到——你可以将它合并到自己的某个分支中；或者如果你想要查看它的话，可以检出一个指向该点的本地分支。

#### 从远程仓库中抓取与拉取

从远程仓库中获得数据，可以执行：

```shell
git fetch <remote>
```

这个命令会访问远程仓库，从中拉取所有你还没有的数据。执行完成后，你将会拥有那个远程仓库中所有分支的引用，可以随时合并或查看。

使用clone命令克隆了一个仓库，命令会自动将其添加为远程仓库并默认以"origin"为简写。`git fetch origin`会抓取克隆（或上一次抓取）后新推送的所有工作。注意`git fetch`命令只会将数据下载到你的本地仓库——它并不会自动合并或修改你当前的工作。你必须手动将其合并入工作。

如果当前分支设置了跟踪远程分支，那么可以用`git pull`命令来自动抓取后合并该远程分支到当前分支。默认情况下，`git clone`命令会自动设置本地master分支跟踪克隆的远程仓库的 master分支（或其它名字的默认分支）。运行`git pull`通常会从最初克隆的服务器上抓取数据并自动尝试合并到当前所在的分支。


#### 推送到远程仓库

`git push <remote> <branch>`将master分支推送到origin服务器时（再次说明，克隆时通常会自动帮你设置好那两个名字）。

```shell
git push <remote> <branch>
```

只有当你有所克隆服务器的写入权限，并且之前没有人推送过时，这条命令才能生效。 当你和其他人在同一时间克隆，他们先推送到上游然后你再推送到上游，你的推送就会毫无疑问地被拒绝。 你必须先抓取他们的工作并将其合并进你的工作后才能推送。

#### 查看某个远程仓库

要查看某一个远程仓库的更多信息，可以使用`git remote show <remote>`命令。例如：

```shell
git remote show origin
```

会列出远程仓库的URL与跟踪分支的信息。

这个命令列出了当你在特定的分支上执行 git push 会自动地推送到哪一个远程分支。它也同地列出了哪些远程分支不在你的本地，哪些远程分支已经从服务器上移除了，还有当你执行`git pull `时哪些本地分支可以与它跟踪的远程分支自动合并。

#### 远程仓库的重命名与移除

你可以运行`git remote rename`来修改一个远程仓库的简写名。 例如，想要将pb重命名为paul，可以运行：

```shell
git remote rename pd paul
```

注意的是这同样也会修改你所有远程跟踪的分支名字。 那些过去引用pb/master的现在会引用
paul/master。

要移除一个远程仓库可以使用`git remote remove`或`git remote rm`,例如

```shell
git remote rm paul
```

```shell
git remote remove paul
```

注意，一旦使用这种方式删除了一个远程仓库，那么所有和这个远程仓库相关的远程跟踪分支以及配置信息也会一起被删除。

### 打标签

```shell
git tag
```

列出已有的标签。这个命令以字母顺序列出标签。可以按照特定的模式查找标签，如：

```shell
git tag -l "v1.8.5*"
```

按照通配符列出标签需要`-l`或`--list`选项。

#### 创建标签

Git支持两种标签：轻量标签（lightweight）与附注标签（annotated）。

轻量标签很像一个不会改变的分支，它只是某个特定提交的引用。

附注标签是存储在Git数据库中的一个完整对象，它们是可以被校验的，其中包含打标签者的名字、电子邮件地址、日期时间，此外还有一个标签信息，并且可以使用GNU Privacy Guard（GPG）签名并验证。 通常会建议创建附注标签，这样可以拥有以上所有信息。但是只是想用一个临时的标签，或者因为某些原因不想要保存这些信息，那么可以用轻量标签。

#### 附注标签

运行`tag`命令时指定`-a`选项中创建附注标签。如

```shell
git tag v1.4 -m "version 1.4"
```

`-m`选项指定一条将会存储在标签中的信息。没有为附注标签指定一条信息，Git会启动编辑器要求你输入信息。

使用`git show`命令可以看到标签信息和与之对应的提交信息：

```shell
git show v1.4
```

输出显示了打标签者的信息、打标签的日期时间、附注信息，然后显示具体的提交信息。

#### 轻量标签

轻量标签本质上是将提交校验和存储到一个文件中——没有保存任何其他信息。创建轻量标签，不需要使用`-a`、`-s`或`-m`选项，只需要提供标签名字：

```shell
git tag v1.4l
```

如果在标签上运行`git show`，你不会看到额外的标签信息。命令只会显示出提交信息。

#### 后期打标签

要为过去的提交打标签，需要在命令的末尾指定提交的校验和（或部分校验和），如：

```shell
git tag -a v0.1 -m "Init" 5f886f
```

#### 共享标签

默认情况下，`git push`并不会传送标签到远程服务器，在创建完标签后，你必须显示地推送标签到远程服务器。这个过程就像共享远程分支一样。

```shell
git push origin <tagname>
```

要一次性的推送很多标签，可以使用`--tags`选项的`git push`命令。这将把不在远程服务器上的标签全部传送到那里。

```shell
git push origin --tags
```

这样，其他人从远程仓库克隆或拉去，也可以得到那些标签。

`git push <remote> --tags`推送两种标签，不会区分轻量标签和附注标签。

#### 删除标签

删除本地仓库标签，可以使用：

```shell
git tag -d <tagname>
```

上述命令不会更新远程仓库，要更新远程仓库，必须使用：

```shell
git push <remote> :refs/tags/<tagname>
```

更直观的删除远程仓库标签的方法是：

```shell
git push origin --delete <tagname>
```

#### 检出标签

要查看某个版本的文件内容，可以使用：

```shell
git checkout <tagname>
```

注意，这会使仓库处于“分离头指针”的状态，此状态下，做了某些更改然后提交，标签不会发生变化，提交的内容不属于任何分支，能且仅能通过提交哈希才能访问。因此，需要修复旧版本时，通常需要创建一个新分支：

```shell
git checkout -b <branch_name> <tagname>
```

### git别名

可以使用`git config`来为每一个命令设置别名。例如：

```shell
git config --global alias.st status
```

这意味着，当要输入`git status`时可以用`git st`代替。

## git分支






