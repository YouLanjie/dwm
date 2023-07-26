#!/usr/bin/zsh

chars=$(zenity --title 中文输入 --text 中文输入 --width 500 --entry 2>/dev/null)
xdotool type --delay 150 "$chars"
