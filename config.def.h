/* See LICENSE file for copyright and license details. */

/* appearance */
static const char dmenufont[]       = "monospace:size=7:weight=bold";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbgcolor[]      = "#de9700";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int snap      = 32;       /* monitor edge snap distance */

/* number of tags, must be less than 32 */
static const int tags = 9;

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;   /* number of clients in master area */
static const int resizehints = 1;   /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "termite", NULL };
static const char *lockcmd[]  = { "slock", NULL };
static const char *dvorcmd[]  = { "setxkbmap", "dvorak", NULL };
static const char *qwercmd[]  = { "setxkbmap", "us", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = dvorcmd } },     /* Set X keyboard layout to Dvorak*/
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = qwercmd } },     /* Set X keyboard layout to US */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },    /* Run dmenucmd[] */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },     /* Run termcmd[] */
	{ MODKEY,                       XK_o,      spawn,          {.v = lockcmd } },     /* Run lockcmd[] */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },          /* Bring focused window up in the floating stack */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },          /* Push focused window down in the floating stack */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },          /* Increment the number of windows in the master column(left column) */
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },          /* Decrement the number of windows in the master column */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05 } },       /* Decrease the spatial dominance of the master column */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05 } },       /* Increase the spatial dominance of the master column */
	{ MODKEY,                       XK_z,      zoom,           {0} },                 /* Put the focused window into the master column */
	{ MODKEY,                       XK_Tab,    view,           {0} },                 /* Switch between the currently and previously-visible tag */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },                 /* Close the focused window */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },  /* Use layout 0 (Tile), layouts[]  */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },  /* Use layout 1 (Floating), layouts[]  */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },  /* Use layout 2 (Monocle), layouts[]  */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                 /* Toggle floating on current window */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },         /* Prefix for switching viewed tags */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },         /* Prefix for tagging a window */
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },          /* Shift the view to the right */
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },          /* Shift the view to the left */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },          /* Focus the previous monitor */
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },          /* Focus the next monitor */
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },          /* Tag the focused window to the previous monitor */
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },          /* Tag the focused window to the next monitor */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)                     /* Tagging keys */
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },                 /* Quit */
};

/* button definitions */
static Button buttons[] = {
	/* event mask      button          function        argument */
	{  MODKEY,         Button1,        movemouse,      {0} },
	{  MODKEY,         Button2,        togglefloating, {0} },
	{  MODKEY,         Button3,        resizemouse,    {0} },
};
