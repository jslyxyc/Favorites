解决方法：将用户名添加到vboxsf组中

输入命令：

`sudo vi /etc/group`

在vboxsf组后添加你的用户名：

`vboxsf:x:998:myname`

group文件包含了unix组的名称和每个组中的成员列表，每一行代表一个组，包含四个字段：

组名：加密的口令：GID号：成员列表，成员列表…，各个成员列表用逗号隔开

或者直接使用如下命令，将当前有效用户追加到vboxsf的成员列表中：

`sudo usermod -aG vboxsf $(whoami)`

最后重启虚拟机即可
