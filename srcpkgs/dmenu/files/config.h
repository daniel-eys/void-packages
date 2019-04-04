/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar             = 1;        /* 0 means always bottom bar     */
static int fuzzy              = 0;        /* 1 means always fuzzy matching */
static const char   *prompt   = NULL;     /* input field prompt            */
static const char    *fonts[] = { "monospace:size=10" };
static const char col_dgray[] = "#292929";
static const char  col_gray[] = "#bbbbbb";
static const char col_bgray[] = "#eeeeee";
static const char  col_cyan[] = "#005577";
static const char col_bcyan[] = "#3377aa";

static const char *colors[SchemeLast][2] = {
	/*               fg         bg       */
	[SchemeNorm] = { col_gray,  col_dgray },
	[SchemeSel]  = { col_bgray, col_cyan  },
	[SchemeOut]  = { col_bgray, col_bcyan },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
