/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "InconsolataSansMono:size=11";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* class            instance    title       tags mask     isfloating   monitor */
    { "Gimp",           NULL,       NULL,       1 << 7,       True,        -1 },
    { "Firefox",        NULL,       NULL,       1 << 0,       False,       -1 },
    { "Thunderbird",    NULL,       NULL,       1 << 8,       False,       -1 },
    { "Skype",          NULL,       NULL,       1 << 4,       True,        -1 },
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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static const char *dmenu_cmd[] = { "/bin/zsh", "-c", "/home/gedi/scripts/path_dmenu", NULL };
static const char *term_cmd[]  = { "urxvtc", "-e", "zsh", "-c", "tmux", NULL };
static const char *sleep_cmd[]  = { "/bin/zsh", "-c", "'sudo /usr/sbin/pm-suspend'", NULL };
static const char *email_cmd[]  = { "/bin/zsh", "-c", "'/home/gedi/scripts/email/check_mailbox.sh /home/gedi/accounts.dat'", NULL };
static const char *alsa_cmd[]  = { "urxvtc", "-e", "amixer", NULL };
static const char *ranger_cmd[]  = { "urxvtc", "-e", "ranger", NULL };
static const char *touchpad_toggle_cmd[] = { "/bin/zsh", "-c", "/home/gedi/scripts/touchpad_toggle", NULL };
static const char *print_screen_cmd[] = { "scrot", "'%Y-%m-%d-%H%M%S_$wx$h.png'", "-e", "'mv $f /home/gedi/images/screenshots'", NULL };
static const char *print_screen_area_cmd[] = { "sleep 0.2;", "scrot", "'%Y-%m-%d-%H%M%S_$wx$h.png'", "-e", "'mv $f /home/gedi/images/screenshots'", "-s", NULL };

static const char *quit_cmd[]  = { "/bin/zsh", "-c", "killall", "startdwm", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    // command shortcuts
    { MODKEY,                       XK_r,       spawn,          {.v = dmenu_cmd } },
    { MODKEY,                       XK_t,       spawn,          {.v = term_cmd } },
    { MODKEY,                       XK_s,       spawn,          {.v = sleep_cmd } },
    { MODKEY,                       XK_e,       spawn,          {.v = email_cmd } },
    { MODKEY,                       XK_a,       spawn,          {.v = alsa_cmd } },
    { MODKEY,                       XK_w,       spawn,          {.v = ranger_cmd } },
    { 0,                            XK_F12,     spawn,          {.v = touchpad_toggle_cmd } },
    { MODKEY,                       XK_b,       togglebar,      {0} },
    // print screen
    { 0,                            XK_Print,   spawn,          {.v = print_screen_cmd } },
    { ControlMask,                  XK_Print,   spawn,          {.v = print_screen_area_cmd } },
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
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    // quit X
    { MODKEY|ShiftMask,             XK_q,       spawn,          {.v = quit_cmd} },
    // reload X
    { MODKEY|ShiftMask,             XK_r,       quit,           {0} },
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

