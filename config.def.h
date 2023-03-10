/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char dmenufont[]       = "monospace:size=10";
static const char *fonts[]          = { "JetBrainsMono:style=medium:size=11", "monospace:size=11" };
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#bbbbbb", "#333333", "#444444" },
	[SchemeSel]  = { "#ffffff", "#37474f", "#42A5F5"  },
};

/* tagging */
static const int tagmax = 16;
static const char *tags[] = { "edge", "2", "3", "4", "5", "6", "7", "8", "9", "系统监视器", "11", "Bilibili", "网易云音乐", "Steam", "HMCL", "Minecraft", "QQ" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "uTools",   NULL,       NULL,       0,            1,           -1 },
	{ "Fsearch",  NULL,       NULL,       0,            1,           -1 },
	// { "Wine",     NULL,       NULL,       1 << 16,      1,           -1 },
	{ "QQ",       NULL,       NULL,       1 << 16,      1,           -1 },
	{ "bilibili", NULL,       NULL,       1 << 11,      1,           -1 },
	{ "Steam",    NULL,       NULL,       1 << 13,      1,           -1 },
	{ "center-termux", NULL,  NULL,       0,            1,           -1 },
	{ "Microsoft-edge", NULL, NULL,       1 << 0,       0,           -1 },
	{ "Minecraft* 1.18.2", NULL, NULL,    1 << 15,      0,           -1 },
	{ "netease-cloud-music", NULL, NULL,  1 << 12,      0,           -1 },
	{ "plasma-systemmonitor", NULL, NULL, 1 << 9,       0,           -1 },
	{ "org.jackhuang.hmcl.Launcher", NULL, NULL, 1<<14, 0,           -1 },
	// { "Gimp",     NULL,       NULL,       0,            0,           -1 },
	// { "Firefox",  NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tile",      tile },    /* first entry is default */
	{ "float",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
// #define MODKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "konsole", NULL };

static const char *local_restart_picom[]  = { "killall", "picom", "&&", "sleep", "1", "&&", "picom", "-b", NULL };
static const char *local_screensnap[]  = { "spectacle", NULL };
static const char *local_volume_up[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *local_volume_down[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *local_wallpaper[]   = { "feh", "--randomize", "--bg-fill", "~/图片/yuindex_bg/*", NULL };
static const char *local_file[]    = { "dolphin", NULL };
static const char *local_termcmd[] = { "alacritty", "--class", "center-termux", NULL };
static const char *local_editor[]  = { "emacs", "/home/Chglish/.emacs.d/org-files/GTD.org", NULL };
static const char *local_editor2[] = { "alacritty", "--class", "editor-nvim", "-e", "nvim", "/tmp/tmpfile.txt", NULL };
static const char *local_editor3[] = { "emacs", "/tmp/tmpfile.org", NULL };
static const char *local_transset_1[] = { "transset-df", "0.9999999", NULL };
static const char *local_transset_0[] = { "transset-df", "1", NULL };

static const Key keys[] = {
	{ MODKEY,                       XK_p,      spawn,          {.v = local_screensnap } },
	{ Mod1Mask,                     XK_F7,     spawn,          {.v = local_volume_down } },
	{ Mod1Mask,                     XK_F8,     spawn,          {.v = local_volume_up } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_b,      spawn,          {.v = local_wallpaper } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_1,      spawn,          {.v = local_restart_picom } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = local_file } },
	{ MODKEY,                       XK_x,      spawn,          {.v = local_editor } },
	{ MODKEY,                       XK_z,      spawn,          {.v = local_editor3 } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = local_editor2 } },
	{ MODKEY|Mod1Mask,              XK_Return, spawn,          {.v = local_termcmd } },
	{ Mod1Mask,                     XK_F11,    spawn,          {.v = local_transset_0 } },
	{ Mod1Mask,                     XK_F12,    spawn,          {.v = local_transset_1 } },
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_s,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_comma,  review,         {.i = 0 } },
	{ MODKEY,                       XK_period, review,         {.i = 1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_F1,                     9)
	TAGKEYS(                        XK_F2,                    10)
	TAGKEYS(                        XK_F3,                    11)
	TAGKEYS(                        XK_F4,                    12)
	TAGKEYS(                        XK_F5,                    13)
	TAGKEYS(                        XK_F6,                    14)
	TAGKEYS(                        XK_F7,                    15)
	TAGKEYS(                        XK_F8,                    16)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

