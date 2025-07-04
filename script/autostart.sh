#!/usr/bin/bash

#================================================================
#   Copyright (C) 2023 YouLanjie
#
#   文件名称：autostart.sh
#   创 建 者：youlanjie
#   创建日期：2023年02月11日
#   描    述：no things
#
#================================================================

hostname=$(cat /etc/hostname)
while [[ $(ps "$$" >/dev/null && echo $?) == 0 ]] ; do
	# 设置标题
	# "前景色: ^c#FFFFFF^"
	# "背景色: ^b#000000^"
	xsetroot -name "^c#000000^^b#F61717^ $(whoami)@$hostname ^b#1bf617^ `pactl get-sink-volume @DEFAULT_SINK@ |awk '{print $5}'|sed -n "1p"` ^b#1D8CEC^ `date '+%Y/%m/%d %a %H:%M:%S'` "
	sleep 0.3
done &

if [[ $wallpaper_path == "" ]]; then
	export wallpaper_path="$HOME/Pictures/Wallpaper"
fi

while [[ $(ps "$$" >/dev/null && echo $?) == 0 ]]; do
	if [[ -f $wallpaper_path/wallpaper_set.jpg || -f $wallpaper_path/wallpaper_set.png ]]; then
		feh --bg-fill $wallpaper_path/wallpaper_set.jpg
		feh --bg-fill $wallpaper_path/wallpaper_set.png
	else
		feh --randomize --bg-fill $wallpaper_path/*
		sleep 2m
	fi
	sleep 1m
done &

xsetroot -cursor_name left_ptr
setxkbmap -option 'caps:ctrl_modifier'

#########
#  app  #
#########

# picom窗口特效合成器（主要是窗口透明）
# 只考虑在非虚拟机环境下运行
if [[ $(systemd-detect-virt) == "none" ]]; then
	picom -b &
fi
# 启动playerctld（多媒体控制服务）
playerctld daemon &
# utools
pgrep -u "$USER" -x utools > /dev/null || utools &
# 剪切板管理器
copyq --start-server &
# 通知
dunst >> /dev/null &
# 启动kdeconnect服务
# kdeconnectd 2>&1 >/dev/null &
# kdeconnect监视
# kdeconnect-indicator 2>&1 >/dev/null &
# kde身份认证
/usr/lib/polkit-kde-authentication-agent-1 &
# 输入法
fcitx5 &
# 更新kde的应用程序打开方式
while [[ $(ps "$$" >/dev/null && echo $?) == 0 ]]; do
	XDG_MENU_PREFIX=plasma- kbuildsycoca6
	sleep 2
done

