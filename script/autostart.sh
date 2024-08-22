#!/usr/bin/zsh

#================================================================
#   Copyright (C) 2023 YouLanjie
#
#   文件名称：autostart.sh
#   创 建 者：youlanjie
#   创建日期：2023年02月11日
#   描    述：no things
#
#================================================================

while (( 1 )) {
	# 设置标题
	xsetroot -name "^c#4B005B^^b#7799AA0x99^ Vol:`pactl get-sink-volume @DEFAULT_SINK@ |awk '{print $5}'|sed -n "1p"` ^c#4B005B^^b#7E51680x99^ `date '+%Y年%m月%d日 %a %H:%M:%S'` "
	# 更新kde的应用程序打开方式
	XDG_MENU_PREFIX=plasma- kbuildsycoca6
	sleep 0.1
}&

fork "zsh -c \"while (( 1 )) { feh --randomize --bg-fill ~/图片/Wallpaper/* ;sleep 3m }\""&

feh --randomize --bg-fill ~/图片/Wallpaper/*
xsetroot -cursor_name left_ptr

# conky -c ~/.config/conky/conky_leon

# 启动picom
pgrep -x picom > /dev/null || picom -b

# 启动playerctld
playerctld daemon

# 启动utools
pgrep -x utools > /dev/null || nohup utools >/dev/null &

# klipper
# pgrep -x klipper > /dev/null || nohup klipper 2>&1 >/dev/null &

# 通知
nohup dunst >> /dev/null &

# 启动kdeconnect服务
pgrep -x kdeconnectd > /dev/null || nohup kdeconnectd 2>&1 >/dev/null &
# 启动kdeconnect启动器
pgrep -x kdeconnect-indicator > /dev/null || nohup kdeconnect-indicator 2>&1 >/dev/null &

# 启动polkit-kde-authentication-agent
nohup /usr/lib/polkit-kde-authentication-agent-1 2>&1 >/dev/null &

setxkbmap -option 'caps:ctrl_modifier'
fcitx5
