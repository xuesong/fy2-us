// yang.c 杨老板 

inherit NPC;
inherit F_VENDOR;
// inherit F_DEALER;

void create()
{
	set_name("杨永福", ({ "Yang yongfu", "yang" }));
	set("title", "杂货铺老板");
	set("shen_type", 1);

	set("gender", "男性");
	set("age", 45);
	set("long",
		"杨老板是土生土长的扬州人，做了几十年的小买卖。\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 40000);
	set("attitude", "friendly");
	set("vendor_goods", ([
		    __DIR__"obj/mabudai" : 9,
			__DIR__"obj/beixin":9,
			__DIR__"obj/toukui":9,
			__DIR__"obj/cycle":9,
			__DIR__"obj/surcoat":9,
			__DIR__"obj/shield":9,
			__DIR__"obj/huwan":9,
			__DIR__"obj/zhitao":9,
			__DIR__"obj/huyao":9,
			__DIR__"obj/caoxie":9,
			__DIR__"obj/pixue":9,
			__DIR__"obj/shoutao":9,
			__DIR__"obj/tieshou":9,
	]));
	
	setup();
	carry_object("/obj/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
