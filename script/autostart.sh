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
	sleep 0.5
}&

if [[ $wallpaper_path == "" ]] export wallpaper_path="$HOME/Pictures/Wallpaper"

nohup zsh -c "
while (( 1 )) {
	if [[ -f $wallpaper_path/wallpaper_set.jpg || -f $wallpaper_path/wallpaper_set.png ]] {
		feh --bg-fill $wallpaper_path/wallpaper_set.jpg
		feh --bg-fill $wallpaper_path/wallpaper_set.png
	} else {
		feh --randomize --bg-fill $wallpaper_path/*
		sleep 2m
	}
	sleep 1m
}
" 2>&1 >/dev/null

xsetroot -cursor_name left_ptr
setxkbmap -option 'caps:ctrl_modifier'

#########
#  app  #
#########

# conky
#conky -c ~/.config/conky/conky_leon
# picom窗口特效合成器（主要是窗口透明）
picom -b &
# 启动playerctld（多媒体控制服务）
playerctld daemon &
# utools
pgrep -u "$USER" -x utools > /dev/null || nohup utools >/dev/null &
# 剪切板管理器
copyq --start-server &
# 通知
nohup dunst >> /dev/null &
# 启动kdeconnect服务
nohup kdeconnectd 2>&1 >/dev/null &
# kdeconnect监视
nohup kdeconnect-indicator 2>&1 >/dev/null &
# kde身份认证
nohup /usr/lib/polkit-kde-authentication-agent-1 2>&1 >/dev/null &
# 输入法
fcitx5 &
# 更新kde的应用程序打开方式
while (( 1 )) { XDG_MENU_PREFIX=plasma- kbuildsycoca6 ;sleep 2 }&

