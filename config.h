/* See LICENSE file for copyright and license details. */

#define EXIT_AND_RESTART 5

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

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
    /* class            instance    title       tags mask       isfloating   monitor */
    { "Gimp",           NULL,       NULL,       1 << 2,         True,        -1 },
    { "URxvt",          "work",     NULL,       1 << 1,         False,       -1 },
    { "Firefox",        NULL,       NULL,       1 << 0,         False,       -1 },
    { "VirtualBox",     NULL,       NULL,       1 << 3,         True,        -1 },
    { "Thunderbird",    NULL,       NULL,       1 << 3,         False,       -1 },
    { "Skype",          NULL,       NULL,       1 << 4,         True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol       arrange function */
    { "[M]",        monocle },  /* full screen */
    { "[T]",        tile },     /* tiling */
    { "[F]",        NULL },     /* floating */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define CMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static const char *term_cmd[]  = { "urxvtc", "-e", "zsh", "-c", "tmux", NULL };
static const char *print_screen_cmd[] = { "scrot", "%Y-%m-%d-%H%M%S_$wx$h.png", "-e", "mv $f /home/gedi/images/screenshots", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    // command shortcuts
    { MODKEY,                       XK_r,       spawn,          CMD("/home/gedi/scripts/path_dmenu") },
    { MODKEY,                       XK_t,       spawn,          {.v = term_cmd } },
    { MODKEY,                       XK_s,       spawn,          CMD("sudo /usr/sbin/pm-suspend") },
    { MODKEY,                       XK_e,       spawn,          CMD("/home/gedi/scripts/email/check_mailbox.sh /home/gedi/accounts.dat") },
    { MODKEY,                       XK_a,       spawn,          CMD("urxvtc -e amixer") },
    { MODKEY,                       XK_w,       spawn,          CMD("urxvtc -e wicd-curses") },
    { 0,                            XK_F12,     spawn,          CMD("mpc next") },
    { 0,                            XK_F11,     spawn,          CMD("mpc toggle") },
    { 0,                            XK_F10,     spawn,          CMD("mpc prev") },
    { 0,                            XK_F9,      spawn,          CMD("/home/gedi/scripts/touchpad_toggle") },
    { MODKEY,                       XK_b,       togglebar,      {0} },
    // print screen
    { 0,                            XK_Print,   spawn,          {.v = print_screen_cmd } },
    { ControlMask,                  XK_Print,   spawn,          CMD("/home/gedi/scripts/area_screenshot") },
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

