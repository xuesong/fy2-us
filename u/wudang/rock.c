
inherit ROOM;

void create()
{
	set("short", "解剑石");
	set("long", @LONG
小路左边是一个红柱黄顶的小亭子，可供游人休息。亭子前方一
块半人高的巨石，上刻“解剑石”三个大字。此字乃当今皇叔－於蓝
天武，用大力金刚指所写，以表示对武当的尊敬和仰慕。武林中人在
此要解下佩戴的兵刃，才可上山。
LONG
	);
	set("exits", ([
		"northdown" : __DIR__"road2",
		"southup" : __DIR__"road3",
	]));
	set("objects", ([
		__DIR__"npc/taoist1" : 1,
	]));
	set("outdoors", "wudang");
	setup();
}

int valid_leave(object me, string dir)
{
        object *inv, ob;
        int i;

        if( userp(me)) {
        	if( dir == "southup"  && ob=present("xu", this_object())) {
                	inv = all_inventory(me);
                	for(i=0; i<sizeof(inv); i++) {
                        	if((int)(inv[i]->query("weapon_prop")) && (int)(inv[i]->query("equipped")))
                        	return notify_fail(ob->name()+"向你说道：施主不可带兵刃上山！n");
             		}
        	}
        }

        return 1;
}
