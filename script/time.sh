#!/usr/bin/zsh

#================================================================
#   Copyright (C) 2023 YouLanjie
#   
#   文件名称：time.sh
#   创 建 者：youlanjie
#   创建日期：2023年02月24日
#   描    述：
#
#================================================================

while (( 1 )) {
	xsetroot -name "Vol:`pactl get-sink-volume @DEFAULT_SINK@ |awk '{print $5}'|sed -n "1p"` `date '+%Y年%m月%d日 %a %H:%M:%S'`"
	sleep 0.1
}&
