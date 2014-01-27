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
    { "3:fox",      &layouts[L_TILE],       -1,     -1 },
    { "4:med",      &layouts[L_FLOAT],      -1,     -1 },
    { "5:chat",     &layouts[L_FLOAT],      -1,     -1 },
};

static const Rule rules[] = {
    /* class                        instance    title       tags mask   isfloating  iscentered  monitor */
    { "feh",                        NULL,       NULL,       0,          True,       True,       -1 },
    { "Firefox",                    NULL,       NULL,       1 << 2,     False,      False,      -1 },
    { "Chromium",                   NULL,       NULL,       1 << 0,     False,      False,      -1 },
    { "libreoffice-calc",           NULL,       NULL,       1 << 3,     False,      False,      -1 },
    { "libreoffice-impress",        NULL,       NULL,       1 << 3,     False,      False,      -1 },
    { "libreoffice-startcenter",    NULL,       NULL,       1 << 3,     False,      False,      -1 },
    { "libreoffice-writer",         NULL,       NULL,       1 << 3,     False,      False,      -1 },
    { "Gimp",                       NULL,       NULL,       1 << 4,     True,       False,      -1 },
    { "VirtualBox",                 NULL,       NULL,       1 << 4,     True,       False,      -1 },
    { "Thunderbird",                NULL,       NULL,       1 << 2,     False,      False,      -1 },
    { "Skype",                      NULL,       NULL,       1 << 4,     True,       True,       -1 },
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

#define CMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static const char *term_cmd[]  = { "st", "-e", "tmux", NULL };
static const char *print_screen_cmd[] = { "scrot", "%Y-%m-%d-%H%M%S_$wx$h.png", "-e", "mv $f /home/gedi/images/screenshots", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    // command shortcuts
    { MODKEY,                       XK_r,       spawn,          CMD("/home/gedi/scripts/path_dmenu") },
    { MODKEY,                       XK_n,       spawn,          CMD("/home/gedi/scripts/notes_dmenu") },
    { MODKEY,                       XK_t,       spawn,          {.v = term_cmd } },
    { MODKEY,                       XK_s,       spawn,          CMD("systemctl suspend") },
    { MODKEY,                       XK_e,       spawn,          CMD("/home/gedi/scripts/email/check_mailbox.sh /home/gedi/accounts.dat") },
    { MODKEY,                       XK_q,       spawn,          CMD("st -e ncmpc") },
    { MODKEY,                       XK_a,       spawn,          CMD("st -e alsamixer") },
    { MODKEY,                       XK_f,       spawn,          CMD("st -e ranger") },
    { MODKEY,                       XK_w,       spawn,          CMD("st -e wicd-curses") },
    // mpd music playback hotkeys
    { MODKEY,                       XK_F12,     spawn,          CMD("mpc next") },
    { MODKEY,                       XK_F11,     spawn,          CMD("mpc toggle") },
    { MODKEY,                       XK_F10,     spawn,          CMD("mpc prev") },
    // toggle touchpad
    { MODKEY,                       XK_F9,      spawn,          CMD("/home/gedi/scripts/touchpad_toggle") },
    // toggle VGA1 screen
    { 0,                            XK_F7,      spawn,          CMD("/home/gedi/scripts/vga_on") },
    // toggle status bar visibility
    { MODKEY,                       XK_b,       togglebar,      {0} },
    // print screen
    { 0,                            XK_Print,   spawn,          {.v = print_screen_cmd } },
    { ControlMask,                  XK_Print,   spawn,          CMD("/home/gedi/scripts/area_screenshot") },
    // keyboard layouts
    { MODKEY|ShiftMask,             XK_F1,      spawn,          CMD("setxkbmap -layout us") },
    { MODKEY|ShiftMask,             XK_F2,      spawn,          CMD("setxkbmap -layout lt") },
    { MODKEY|ShiftMask,             XK_F3,      spawn,          CMD("setxkbmap -layout fr") },
    // lock screen
    { MODKEY,                       XK_F5,      spawn,          CMD("slimlock") },
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
    { MODKEY|ShiftMask,             XK_f,       setlayout,      {.v = &layouts[2]} },
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

