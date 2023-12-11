/* See LICENSE file for copyright and license details. */

#define EXIT_AND_RESTART 5

#define L_MONOCLE 0
#define L_TILE    1
#define L_BSTACK  2
#define L_FLOAT   3

/* appearance */
static const char font[]            = "InconsolataSansMono:size=11";

static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#073642";
static const char normfgcolor[]     = "#839496";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";

static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */

static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */

/* layouts */
static const Layout layouts[] = {
    /* symbol       arrange function */
    { "[M]",        monocle },  /* full screen */
    { "[T]",        tile },     /* tiling */
    { "[B]",        bstack},    /* bottom stack tiling */
    { "[F]",        NULL },     /* floating */
};

/* tagging */
static const Tag tags[] = {
    /* name         layout                  mfact   nmaster */
    { "1:web",      &layouts[L_MONOCLE],    -1,     -1 },
    { "2:ter",      &layouts[L_BSTACK],     -1,     -1 },
    { "3:idea",     &layouts[L_MONOCLE],    -1,     -1 },
    { "4:chat",     &layouts[L_MONOCLE],    -1,     -1 },
    { "5:ex1",      &layouts[L_FLOAT],      -1,     -1 },
    { "6:ex2",      &layouts[L_MONOCLE],    -1,     -1 },
    { "7:ex3",      &layouts[L_MONOCLE],    -1,     -1 },
    { "8:ex4",      &layouts[L_MONOCLE],    -1,     -1 },
    { "9:ex5",      &layouts[L_MONOCLE],    -1,     -1 },
};

static const Rule rules[] = {
    /* class                        instance    title       tags mask   isfloating  iscentered  monitor */
    { "feh",                        NULL,       NULL,       0,          True,       True,       -1 },
    { "Gimp",                       NULL,       NULL,       0,          True,       False,      -1 },
    { "VirtualBox",                 NULL,       NULL,       0,          True,       False,      -1 },
    { "Skype",                      NULL,       NULL,       0,          True,       True,       -1 },
};

static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *term_cmd[]  = { "alacritty", "-e", "tmux", NULL };
static const char *print_screen_cmd[] = { "scrot", "%Y-%m-%d-%H%M%S.png", "-e", "mv $f ~/images/screenshots", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    // command shortcuts
    { MODKEY,                       XK_r,       spawn,          CMD("dmenu_run") },
    { MODKEY,                       XK_z,       spawn,          CMD("dmenu_surf") },
    { MODKEY,                       XK_t,       spawn,          {.v = term_cmd } },
    { MODKEY,                       XK_s,       spawn,          CMD("systemctl suspend") },
    { MODKEY,                       XK_a,       spawn,          CMD("pavucontrol") }, // launch pulseaudio control
    { MODKEY,                       XK_f,       spawn,          CMD("alacritty -e ranger") }, // file manager
    // toggle touchpad
    { MODKEY,                       XK_F9,      spawn,          CMD("touchpad_toggle") }, // exec custom sh script
    // toggle status bar visibility
    { MODKEY,                       XK_b,       togglebar,      {0} },
    // print screen
    { 0,                            XK_Print,   spawn,          {.v = print_screen_cmd } },
    { ControlMask,                  XK_Print,   spawn,          CMD("area_screenshot") }, // exec custom sh script, uses scrot
    // keyboard layouts
    { MODKEY|ShiftMask,             XK_F1,      spawn,          CMD("setxkbmap -layout us") },
    { MODKEY|ShiftMask,             XK_F2,      spawn,          CMD("setxkbmap -layout lt") },
    { MODKEY|ShiftMask,             XK_F3,      spawn,          CMD("setxkbmap -layout fr") },
    { MODKEY|ShiftMask,             XK_F4,      spawn,          CMD("setxkbmap -layout ru") },
    // lock screen
    { MODKEY,                       XK_F5,      spawn,          CMD("setxkbmap -layout us;lxdm -c USER_SWITCH") }, // screen lock
    // window navigation
    { MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
    { MODKEY,                       XK_Tab,     focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
    // tiling
    { MODKEY,                       XK_i,       incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,       incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
    // layout actions
    { MODKEY,                       XK_Return,  zoom,           {0} },
    { MODKEY,                       XK_v,       view,           {0} },
    { MODKEY,                       XK_c,       killclient,     {0} },
    { MODKEY|ShiftMask,             XK_m,       setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,       setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,             XK_b,       setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_f,       setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_space,   setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
    { MODKEY,                       XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
    // desktop navigation
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    { MODKEY|ShiftMask,             XK_q,       quit,           {0} }, /* exit with success */
    { MODKEY|ShiftMask,             XK_r,       quit,           {.i = EXIT_AND_RESTART } }, /* restart dwm */
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = term_cmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

