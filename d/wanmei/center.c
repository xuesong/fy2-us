// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ROOM;
void create()
{
        set("short", "��÷��");
        set("long", @LONG
�˸����������ٶ����İ�÷ľ����ϸ�����ɡ���÷ľ����������ľ��
��ײ���Ӳ�����ʯ����ɢ����һ�ɵ��������㣬���겻˥�������ĵ�һ����
���÷ľ���졣����ΰ��������ţ�����ľ�Ƽ��Ե�׺�����һ��
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"yard",
  "east" : __DIR__"backyard",
]));
        set("objects", ([
		__DIR__"npc/master" :1,
                        ]) );

        setup();
        replace_program(ROOM);
}