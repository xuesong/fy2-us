#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "三清宫正殿");
	set("long", @LONG
正面是三清的金身塑像。塑像前的神桌上摆着各式水果
和一座小铜炉，铜炉里插着三支点着了的香。左右面墙上都
没有任何东西，却是刷得很白。大殿的正中是一座炼丹炉，
一位貌似仙人的道士正在炼丹。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  		"south" : "/u/taoguan/da_yuan",
		"northwest" : __DIR__"stoneroad",
]));
        set("valid_startroom", 1);
	set("objects", ([
                "/u/taoguan/npc/up_taoist" : 2,
                "/u/taoguan/npc/taolord2" : 1,

 ]) );
	setup();
}

