inherit ROOM;
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.

void create()
{
        set("short", "ç��֮��");
        set("long", @LONG
���ܹ������죬�����ܲ���Ũ�ܿ������Ҷ�ڱ��������ǳ���ʹ�˷ֲ���
��ҹ����������һ��ļž���ֻ�з紵�����ҵ�ɳɳ֮����ż��һ������Х��
�������ȷ�Ʈ�����ʡ�
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"groupe2",
  "west" : __DIR__"groupw2",
  "north" : __DIR__"groupn2",
  "south" : __DIR__"groups2",

]));
        setup();
}
void init()
{
        add_action("climbing", "climb");
}

int climbing(string arg)
{
        object obj;
        object me;
        if(!arg || arg=="")
        {
                return 0;
        }
        if( arg == "tree" || arg == "����" || arg == "��")
        {
        me = this_player();
        message_vision("$Nץ��ͻ������֦��������˳������������ȥ��\n", me);
        me->start_busy(3);
        call_out("fliping",3,me);
        me->stop_busy();
        return 1;
        }
        else
        {
                write("�㲻������"+arg+"\n");
                return 1;
        }
}
int fliping(object me)
{
	if(!me->is_ghost()){
        me->move(__DIR__"top2");
        message_vision("$N˳����������������\n", me);
	}
        return 1;
}
