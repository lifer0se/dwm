/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx        = 3;        /* border pixel of windows */
static const unsigned int snap            = 2;        /* snap pixel */
static const unsigned int gappih          = 30;       /* horiz inner gap between windows */
static const unsigned int gappiv          = 30;       /* vert inner gap between windows */
static const unsigned int gappoh          = 75;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov          = 75;       /* vert outer gap between windows and screen edge */
static       int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar                  = 1;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
static const int startontag               = 1;        /* 0 means no tag active on start */
static const int leftpad                  = 11;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int rightpad                 = 2;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int user_bh                  = 35;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int swallowfloating          = 1;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning  = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 2;   /* systray spacing */
static const unsigned int systrayrightpad = 15;   /* systray spacing */
static const int systrayiconsize          = 28;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int systraypinningfailfirst  = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;        /* 0 means no systray */
static const char *fonts[]                = { "Roboto:style=Bold:size=13" };

static const char col_gray1[] = "#2B2E37";
static const char col_gray2[] = "#555E70";
static const char col_gray3[] = "#747880";
static const char col_gray4[] = "#929AAD";
static const char col_cyan1[] = "#8BABF0";
static const char col_cyan2[]  = "#5294E2";

static const char col1[]	  = "#AAC0F0";
static const char col2[]	  = "#C1B54E";
static const char col3[]	  = "#C1514E";
static const char col4[]	  = "#4EC150";
static const char col5[]      = "#ffffff";
static const char col6[]      = "#ffffff";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
SchemeCol5, SchemeCol6, SchemeSel, SchemeTag, SchemeTitle }; /* color schemes */

 static const char *colors[][3]      = {
 	/*               fg         bg         border   */
    [SchemeNorm]  = { col_gray4, col_gray1, col_gray2 },
    [SchemeCol1]  = { col1,      col_gray1, col_gray2 },
    [SchemeCol2]  = { col2,      col_gray1, col_gray2 },
    [SchemeCol3]  = { col3,      col_gray1, col_gray2 },
    [SchemeCol4]  = { col4,      col_gray1, col_gray2 },
    [SchemeCol5]  = { col5,      col_gray1, col_gray2 },
    [SchemeCol6]  = { col6,      col_gray1, col_gray2 },
    [SchemeSel]   = { col_cyan1, col_gray1,  col_cyan2  },
	[SchemeTag] = { col_gray2, col_gray1, col_gray2 },
	[SchemeTitle] = { col_gray3, col_gray1, col_gray2 },
};


/* tagging */
static const char *tags[] = {  "⭘", "⭘", "⭘", "⭘", "⭘", "⭘", "⭘" };
static const char *alttags[] = { "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title           tags mask  isfloating  isterminal  noswallow  monitor  donotcenter   x,y,w,h         borderpx*/
	{ "Termite",    NULL,     NULL,           0,         0,          1,           0,        -1,                0,  50,50,500,500,  borderpx },
	{ "Gcolor2",    NULL,     NULL,           0,         1,          0,           0,        -1,                0,  50,50,500,500,  borderpx },
	{ "Galculator", NULL,     NULL,           0,         1,          0,           0,        -1,                0,  50,50,500,700,  borderpx },
	{ "Gsimplecal", NULL,     NULL,           0,         1,          0,           0,        -1,                1,  817,50,50,50,   0 },
	{ "Godot",      NULL,     NULL,           1 << 5,    0,          0,           0,         0,                0,  50,50,500,500,  borderpx },
	{ "Termite",    NULL,     "GODOT",        1 << 4,    0,          0,           0,         0,                0,  50,50,500,500,  borderpx },
	{ NULL,         NULL,     "Event Tester", 0,         0,          0,           1,        -1,                0,  50,50,500,500,  borderpx } /* xev */
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 0  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "=[]",      tile },    /* first entry is default */
 	{ "[m]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

/* spotify control commands */
static const char *spotifycmd_previous[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Previous", NULL };
static const char *spotifycmd_play[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.PlayPause", NULL };
static const char *spotifycmd_next[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Next", NULL };

/* volume control commands */
static const char *mutecmd[] = { "amixer", "-q", "-D", "pulse", "sset", "Master", "toggle", NULL };
static const char *volumedowncmd[] = { "amixer", "-q", "-D", "pulse", "sset", "Master", "5%-", NULL };
static const char *volumeupcmd[] = { "amixer", "-q", "-D", "pulse", "sset", "Master", "5%+", NULL };

/* application launch commands */
static const char *termcmd[]  = { "termite", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-p", "run:", NULL };
static const char *bravecmd[] = { "brave", NULL };
static const char *braveinccmd[] = { "brave", "--incognito", NULL };
static const char *pcmanfmcmd[] = { "pcmanfm", NULL };
static const char *rangercmd[] = { "termite", "-e", "ranger", NULL };
static const char *vimcmd[] = { "termite", "-e", "nvim", NULL };
static const char *spotifycmd[] = { "spotify", NULL };
static const char *galculatorcmd[] = { "galculator", NULL };
static const char *godotcmd[] = { "/home/amnesia/.scripts/godot_launcher.sh", NULL };
static const char *langtogglecmd[] = { "/home/amnesia/.scripts/keyboard_layout_toggle.sh", "us", "gr", NULL };

/* other commands */
static const char *killxinitcmd[] = { "killall", "xinit", NULL };
static const char *killdwmcmd[] = { "killall", "dwm", NULL };


#include "movestack.c"
#include "shiftview.c"
static Key keys[] = {

	/* apps */
	{ MODKEY,				/*d*/ 40,		spawn,	    	{.v = dmenucmd } },
	{ MODKEY,				/*Return*/ 36,	spawn,	    	{.v = termcmd } },
	{ MODKEY,				/*w*/ 25,		spawn,	    	{.v = bravecmd } },
	{ MODKEY|ShiftMask,		/*w*/ 25,		spawn,	    	{.v = braveinccmd } },
	{ MODKEY,				/*f*/ 41,		spawn,	    	{.v = rangercmd } },
	{ MODKEY|ShiftMask,		/*f*/ 41,		spawn,	    	{.v = pcmanfmcmd } },
	{ MODKEY,				/*v*/ 55,		spawn,	    	{.v = vimcmd } },
	{ MODKEY,				/*s*/ 39,		spawn,	    	{.v = spotifycmd } },
	{ MODKEY|ShiftMask,		/*g*/ 42,		spawn,	    	{.v = godotcmd } },
	{ MODKEY,				/*z*/ 52,		spawn,	    	{.v = langtogglecmd } },
	{ MODKEY,				/*c*/ 54,		spawn,	    	{.v = galculatorcmd } },

	/* spotify*/
	{ MODKEY,				/*F9*/ 95,		spawn,	    	{.v = spotifycmd_previous } },
	{ MODKEY,				/*F11*/ 75,		spawn,	    	{.v = spotifycmd_play } },
	{ MODKEY,				/*F12*/ 96,		spawn,	    	{.v = spotifycmd_next } },

	/* volume*/
	{ MODKEY,				/*F13*/ 107,	spawn,	    	{.v = mutecmd } },
	{ MODKEY,				/*F14*/ 78,		spawn,	    	{.v = volumedowncmd } },
	{ MODKEY,				/*F15*/ 127,	spawn,	    	{.v = volumeupcmd } },

	/* dwm  control */
	{ MODKEY,				/*q*/ 24,		killclient,	   	{0} },
	{ MODKEY|ShiftMask,		/*q*/ 24,		spawn,		   	{.v = killxinitcmd } },
	{ MODKEY|ShiftMask,		/*r*/ 27,		spawn,		   	{.v = killdwmcmd } },
	{ MODKEY,				/*space*/ 65,	togglefloating,	{0} },
	{ MODKEY,               /*b*/ 56,      	togglebar,     	{0} },
	{ MODKEY,				/*g*/ 42,		togglegaps,   	{0} },
    { MODKEY,               /*u*/ 30,       incnmaster,     {.i = +1 } },
	{ MODKEY,               /*i*/ 31,       incnmaster,     {.i = -1 } },

	/* navigation*/
	{ MODKEY,               /*j*/ 44,      	focusstack,     {.i = +1 } },
	{ MODKEY,               /*k*/ 45,      	focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,		/*j*/ 44,		movestack,  	{.i = +1 } },
	{ MODKEY|ShiftMask,		/*k*/ 45,		movestack,  	{.i = -1 } },
	{ MODKEY|ControlMask,	/*j*/ 44,		setcfact,   	{.f = +0.25} },
	{ MODKEY|ControlMask,	/*k*/ 45,		setcfact,   	{.f = -0.25} },
	{ MODKEY|Mod1Mask,		/*j*/ 44,		shiftview,  	{.i = -1 } },
	{ MODKEY|Mod1Mask,		/*k*/ 45,		shiftview,  	{.i = +1 } },
	{ MODKEY,				/*h*/ 43,		switchcol,  	{0} },
	{ MODKEY,				/*l*/ 46,		switchcol,  	{.i = +1}  },
	{ MODKEY|ShiftMask,		/*h*/ 43,		zoom,	    	{0} },
	{ MODKEY|ShiftMask,		/*l*/ 46,		zoom,	    	{0} },
	{ MODKEY|ControlMask,	/*h*/ 43,		setmfact,   	{.f = -0.05} },
	{ MODKEY|ControlMask,	/*l*/ 46,		setmfact,   	{.f = +0.05} },
	{ MODKEY,				/*o*/ 32,		focusmon,   	{.i = +1 } },
	{ MODKEY|ShiftMask,		/*o*/ 32,		tagmon,	    	{.i = +1 } },

	{ MODKEY,           /*Down*/ 116,       moveresizeedge, {.v = "b"} },
	{ MODKEY,             /*Up*/ 111,       moveresizeedge, {.v = "t"} },
	{ MODKEY,          /*Right*/ 114,       moveresizeedge, {.v = "r"} },
	{ MODKEY,           /*Left*/ 113,       moveresizeedge, {.v = "l"} },
	{ MODKEY|ShiftMask, /*Down*/ 116,       moveresizeedge, {.v = "B"} },
	{ MODKEY|ShiftMask,   /*Up*/ 111,       moveresizeedge, {.v = "T"} },
	{ MODKEY|ShiftMask,/*Right*/ 114,       moveresizeedge, {.v = "R"} },
	{ MODKEY|ShiftMask, /*Left*/ 113,       moveresizeedge, {.v = "L"} },

    /*regular*/
	TAGKEYS(                /*1*/ 10,       0)
	TAGKEYS(                /*2*/ 11,       1)
	TAGKEYS(                /*3*/ 12,       2)
	TAGKEYS(                /*4*/ 13,       3)
	TAGKEYS(                /*5*/ 14,       4)
	TAGKEYS(                /*6*/ 15,       5)
	TAGKEYS(                /*7*/ 16,       6)
	TAGKEYS(                /*8*/ 17,       7)
	TAGKEYS(                /*9*/ 18,       8)

    /*numpad*/
	TAGKEYS(                /*1*/ 87,       0)
	TAGKEYS(                /*2*/ 88,       1)
	TAGKEYS(                /*3*/ 89,       2)
	TAGKEYS(                /*4*/ 83,       3)
	TAGKEYS(                /*5*/ 84,       4)
	TAGKEYS(                /*6*/ 85,       5)
	TAGKEYS(                /*7*/ 79,       6)
	TAGKEYS(                /*8*/ 80,       7)
	TAGKEYS(                /*9*/ 81,       8)
};

/* button definitions */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,   { .i = +1 } },
	//{ ClkLtSymbol,          0,              Button2,        killclient,           {0} },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,   { .i = -1 } },
    { ClkLtSymbol,          0,              Button4,        cyclelayout,   { .i = +1 } },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,   { .i = -1 } },

	{ ClkWinTitle,          0,              Button2,        killclient,           {0} },
	{ ClkWinTitle,          0,              Button4,        shiftview,	    {.i = -1 } },
	{ ClkWinTitle,          0,              Button5,        shiftview,	    {.i = +1 } },

	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        shiftview,	    {.i = -1 } },
	{ ClkStatusText,        0,              Button5,        shiftview,	    {.i = +1 } },

    { ClkEmptyBar,          0,              Button2,        killclient,           {0} },
	{ ClkEmptyBar,          0,              Button4,        shiftview,	    {.i = -1 } },
	{ ClkEmptyBar,          0,              Button5,        shiftview,	    {.i = +1 } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button2,        spawn,          {.v = dmenucmd } },
    { ClkTagBar,            0,              Button4,        shiftview,     { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,     { .i = +1 } },
};
