// qianchi.c

inherit ROOM;

void create()
{
	set("short", "ǧ�ߴ�");
	set("long", @LONG
ǰ����һб���촹ʯ�ݵ�ɽ�ף�����Ǻպ�������ǧ�ߴ���ǧ�ߴ���
��һ�����Ҽ����ѷ쿪����ɣ�б��Լ��ʮ�ȣ���Լ��ʮ�ף�����һ����
�䡣������Ǿ���ʮ�㣬���ǲ�Ҫð���ʵǵĺá�
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"westdown" : __DIR__"qingke",
		"southup" : __DIR__"baichi",
	]));

	set("objects", ([ 
		__DIR__"npc/youke" : 2,
	]));
 
	set("no_clean_up", 0);
	set("outdoors", "huashan" );

	setup();
}
 
int valid_leave(object me, string dir)
{
	if (dir == "southup"){
		me->add("gin", -30);
		me->add("kee", -30);
	}
	return 1;
}