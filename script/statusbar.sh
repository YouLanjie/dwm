#!/usr/bin/zsh

#================================================================
#   Copyright (C) 2023 YouLanjie
#
#   文件名称：statusbar.sh
#   创 建 者：youlanjie
#   创建日期：2023年04月08日
#   描    述：状态栏
#
#================================================================

while (( 1 )) {
	xsetroot -name "^c#4B005B^^b#7799AA0x99^ Vol:`pactl get-sink-volume @DEFAULT_SINK@ |awk '{print $5}'|sed -n "1p"` ^c#4B005B^^b#7E51680x99^`date '+%Y年%m月%d日 %a %H:%M:%S'` "
	sleep 0.1
}

