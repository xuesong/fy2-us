
inherit ROOM;

void create()
{
        set("short", "������Դ");
        set("long", @LONG
΢����������ף����������㡣������ɽ��������ɫ���ˡ�
������Ǵ���ɽ����������ǡ�˲���ɽ��Ѱ��һ�����Ҳ��������
�������������������֮�У�ǡ�Ƶ��������˼䡣
LONG
        );
        set("exits", ([ 
  "west" : __DIR__"small_river",
  "east" : __DIR__"cave_tunnel",
]));
        set("outdoors", "resort");

        setup();
        replace_program(ROOM);
}
