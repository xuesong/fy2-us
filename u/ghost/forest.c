
inherit ROOM;

void create()
{
	set("short", "ԭʼ����");
	set("long", @LONG
������һƬ�ڰ����ڰ��г����˸�ʽ������Σ�գ�ÿһ�ֶ�����
�����������ڴ�������ʧ�˷��򣬼��ʾ�����������
LONG
	);
	set("exits", ([
		"north" : __DIR__"forest7",
		"south" : __DIR__"forest1",
		"east" : __DIR__"forest5",
		"west" : __DIR__"forest6",
	]));
	set("outdoors", "ghost");
        set("NONPC",1);
	setup();
        replace_program(ROOM);
}