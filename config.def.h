/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
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
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
};

/* assorted layout options */
static const float mfact      = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */


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
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "termite", NULL };
static const char *lockcmd[]  = { "slock", NULL};
static const char *dvorcmd[]  = { "setxkbmap", "dvorak", NULL};
static const char *qwercmd[]  = { "setxkbmap", "us", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = dvorcmd } },         /* Set x keyboard layout to dvorak */
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = qwercmd } },         /* Set X keyboard layout to us */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },        /* Start dmenu_run in the way defined in dmenucmd[] */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },         /* Start your terminal as defined in termcmd[] */
	{ MODKEY,                       XK_o,      spawn,          {.v = lockcmd } },         /* Start your lock command, as defined in lockcmd[] */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },              /* Bring focused window up in the floating stack */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },              /* Push focused window down in the floating stack */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },              /* Increment the number of windows in the master column(left column) */
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },              /* Decrement the number of windows in the master column */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },            /* Decrease the spatial dominance of the master column */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },            /* Increase the spatial dominance of the master column */
	{ MODKEY,                       XK_z,      zoom,           {0} },                     /* zoom */
	{ MODKEY,                       XK_Tab,    view,           {0} },                     /* Switch between the currently and previously-visible tag */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },                     /* Close a window */
	{ MODKEY,                       XK_t,      setlayout,      {.lt = tile} },            /* Use Tile layout */
	{ MODKEY,                       XK_f,      setlayout,      {.lt = NULL} },            /* Use Floating layout */
	{ MODKEY,                       XK_m,      setlayout,      {.lt = monocle} },         /* Use Monocle layout */
	{ MODKEY,                       XK_space,  setlayout,      {0} },                     /* Switch to tiling layout */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                     /* Toggle floating on current window */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },             /* Prefix for switching viewed tags */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },             /* Prefix for tagging a window */
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1}   },             /* Shift the view to the right */
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1}   },             /* Shift the view to the left */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },              /* Switch monitor focus backward(usually to the left) */
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },              /* Switch monitor focus forward(usually to the right) */
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },              /* Tag focused window backward in the monitor stack */
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },              /* Tag focused window forward in the monitor stack */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)                         /* Tagging keys, all number keys by default. Go ahead and add more tags, or remove them if you'd like. */
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },                    /* Quit */
};

/* button definitions */
static Button buttons[] = {
	/* event mask      button          function        argument */
	{  MODKEY,         Button1,        movemouse,      {0} },
	{  MODKEY,         Button2,        togglefloating, {0} },
	{  MODKEY,         Button3,        resizemouse,    {0} },
};
