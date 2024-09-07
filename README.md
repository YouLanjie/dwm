# DWM YES

> 注意：这是一个基于[yaocccc/dwm](https://github.com/yaocccc/dwm/的)fork仓库，存放我自己再配置的dwm，对其中的历史记录进行了rebase压缩。

## 功能

- 支持布局 tile(磁块)、magicgrid(进阶的网格布局)
- 键盘移动/调整窗口大小 且移动/调整时有窗口间吸附效果
- 窗口隐藏
- 窗口可自定义是否全局(在所有tag内展示)
- 更好的浮动窗口支持
- 优化后的status2d 状态栏，可用鼠标点击操作
- 系统托盘支持
- overview
- mod + tab, 在窗口间切换 有浮动窗口时仅在浮动窗口切换
- mod + [tag], 切换tag到指定目录时 可指定一个cmd，若目标tag无窗口 则执行该tag


## 状态栏

请将每一个块置为下列样式, 可参考使用本仓库statusbar相关脚本

```plaintext
  ^sdate^^c#2D1B46^^b#335566^  11/04 00:42 ^d^

  ^s?????^ => 点击时的信号值
  ^c?????^ => 前景色
  ^b?????^ => 背景色
  ^d^      => 重置颜色

  也可以直接从^c ^b 定义前景色 后景色透明度
  ^c#??????0xff^ => 0xff 前景色透明度
  ^b#??????0x11^ => 0x11 后景色透明度

  请在dwm启动时 调用 $DWM/statusbar/statusbar.sh cron

  注意 ~/.profile中需要有 该环境变量为强依赖关系
  export DWM=~/workspace/dwm

  点击事件发生时 会调用 $DWM/statusbar/statusbar.sh 并传入信号值 请自行处理
  例如 $DWM/statusbar/statusbar.sh date L  # 其中date为信号值 L为按键 (L左键 M中键 R右键)
```

## 随DWM启动的自启动命令

dwm启动时会去调用 $DWM/autostart.sh 脚本

可参考 [autostart脚本](https://github.com/yaocccc/dwm/blob/master/DEF/autostart.sh)

