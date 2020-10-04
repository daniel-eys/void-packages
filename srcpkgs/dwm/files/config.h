/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1;        /* border pixel of windows */
static const unsigned int gappx    = 0;        /* gap pixel between windows */
static const unsigned int snap     = 16;       /* snap pixel */
static const int showbar           = 1;        /* 0 means no bar */
static const int topbar            = 1;        /* 0 means bottom bar */
static const char    *fonts[]      = { "LiterationMono Nerd Font:pixelsize=13:antialias=true:autohint=false" };
static const char dmenufont[]      = "LiterationMono Nerd Font:pixelsize=13:antialias=true:autohint=false";
static const char col_dgray[]      = "#292929";
static const char  col_gray[]      = "#bbbbbb";
static const char col_bgray[]      = "#eeeeee";
static const char  col_cyan[]      = "#005577";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray,  col_dgray, col_dgray },
	[SchemeSel]  = { col_bgray, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = {
	"", /*  0 music */
	"", /*  1 web   */
	"", /*  2 mail  */
	"", /*  3 chat  */
	"", /*  4 misc  */
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance     title        tags mask     isfloating   monitor */
	{ "Firefox",     NULL,        NULL,        1 << 1,       0,           -1 },
	{ "Chromium",    NULL,        NULL,        1 << 1,       0,           -1 },
	{ "qutebrowser", NULL,        NULL,        1 << 1,       0,           -1 },
	{ "mpv",         NULL,        NULL,        1 << 1,       0,           -1 },
	{  NULL,         NULL,       "neomutt",    1 << 2,       0,           -1 },
	{  NULL,         NULL,       "bpytop",     1 << 0,       0,           -1 },
	{  NULL,         NULL,       "ncmpcpp",    1 << 0,       0,           -1 },
	{  NULL,         NULL,       "scratchpad",      0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile           },    /* first entry is default */
	{ "[F]",      NULL           },    /* no layout function means floating behavior */
	{ "[M]",      monocle        },
	{ "TTT",      bstack         },
	{ "===",      bstackhoriz    },
	{ "[@]",      spiral         },
	{ "[\\]",     dwindle        },
	{ "|M|",      centeredmaster },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char   *dmenucmd[] = { "dmenu_run", "-F", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dgray, "-nf", col_gray, "-sb", col_cyan, "-sf", col_bgray, NULL };
static const char *mpdmenucmd[] = { "mpdmenu", NULL };
static const char    *termcmd[] = { "st", NULL };
static const char    *browcmd[] = { "qutebrowser", NULL };
static const char    *mailcmd[] = { "st", "-t", "neomutt", "neomutt", NULL };
static const char  *rangercmd[] = { "st", "-t", "ranger", "ranger", NULL };
static const char      *lfcmd[] = { "st", "-t", "lf", "lf", NULL };
static const char  *bpytopcmd[] = { "st", "-t", "bpytop", "bpytop", NULL };
static const char *ncmpcppcmd[] = { "st", "-t", "ncmpcpp", "ncmpcpp", NULL };
static const char     *padcmd[] = { "st", "-t", "scratchpad", "-g", "80x24-50+40", NULL };
static const char  *editorcmd[] = { "st", "-t", "neovim", "nvim", NULL };
static const char    *lockcmd[] = { "i3lock", "-c", "000000", NULL };
static const char  *rebootcmd[] = { "doas", "/usr/bin/reboot", NULL };
static const char    *shutcmd[] = { "doas", "/usr/bin/shutdown", "-h", "now", NULL };
static const char    *suspcmd[] = { "doas", "/usr/bin/zzz", NULL };
static const char    *voldown[] = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char      *volup[] = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char    *volmute[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_semicolon,      spawn,          {.v = mpdmenucmd } },
	{ ControlMask|MODKEY,           XK_t,      spawn,          {.v = termcmd } },
	{ ControlMask|MODKEY,           XK_b,      spawn,          {.v = browcmd } },
	{ ControlMask|MODKEY,           XK_m,      spawn,          {.v = mailcmd } },
	{ ControlMask|MODKEY,           XK_j,      spawn,          {.v = rangercmd } },
	{ ControlMask|MODKEY,           XK_f,      spawn,          {.v = lfcmd } },
	{ ControlMask|MODKEY,           XK_g,      spawn,          {.v = bpytopcmd } },
	{ ControlMask|MODKEY,           XK_n,      spawn,          {.v = ncmpcppcmd } },
	{ ControlMask|MODKEY,           XK_p,      spawn,          {.v = padcmd } },
	{ ControlMask|MODKEY,           XK_e,      spawn,          {.v = editorcmd } },
	{ ControlMask|MODKEY,           XK_l,      spawn,          {.v = lockcmd } },
	{ ControlMask|MODKEY,           XK_r,      spawn,          {.v = rebootcmd } },
	{ ControlMask|MODKEY,           XK_q,      spawn,          {.v = shutcmd } },
	{ ControlMask|MODKEY,           XK_s,      spawn,          {.v = suspcmd } },
	{ ControlMask|MODKEY,           XK_i,      spawn,          SHCMD("$HOME/bin/set-screen") },
	{ ControlMask|MODKEY,           XK_w,      spawn,          SHCMD("$HOME/bin/set-wallpaper") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD("$HOME/bin/focus-browser") },
	{ 0,                      0x1008ff11,      spawn,          {.v = voldown } },
	{ 0,                      0x1008ff13,      spawn,          {.v = volup } },
	{ 0,                      0x1008ff12,      spawn,          {.v = volmute } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_c,      switchcol,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ ControlMask|MODKEY,           XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

