#ifndef H_CMD
#define H_CMD
#include"cmd_parser.h"

struct cmd_item CmditemsList[] =
{
	{'-','h',0,NULL,"Cause to print help text"},
	{'-','T',0,"4","Set width of a tab #cols columns"},
	{'-','t',0,NULL,"Auto save on exit, don't prompt"},
        {'-','b',0,NULL,"Use bold font"},
        {'-','M',0,"1,1","Start at line LINE, column COLUMN"},
	{0,0,0,NULL,NULL}
};
#endif
