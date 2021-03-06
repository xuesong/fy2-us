// taolord.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name( "丁白云" , ({ "master ding", "master", "ding" }) );
        set("nickname",HIB "晴空白云" NOR);
        set("gender", "女性");
        set("age", 46);
        set("long",
                
"丁白云是丁乘风的师妹，也是丁乘风的亲妹妹。丁白云年轻时遭白天羽抛弃，\n"
"伤心欲绝，于是设计杀了白天羽后到此出家。\n");

        set("combat_exp", 10000000);
        set("score", 200000);

        set("class", "taoist");

        set("str", 20);
        set("int", 30);
        set("cor", 20);
        set("cps", 30);
        set("spi", 30);

        set("force", 2000);
        set("max_force", 1000);
        set("force_factor", 30);

        set("atman", 1400);
        set("max_atman", 1400);

        set("mana", 4000);
        set("max_mana", 2000);
        set("mana_factor", 5);

        set("inquiry", ([
                "谷衣心法": 
"谷衣心法是我茅山派为对抗邪魔外道所创的内功心法。\n",
                "三清宫": 
"我茅山派自张天师开山立派至今，世世代代皆以降妖伏魔为己任。\n"
        ]) );

        set("apprentice_available", 3);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: cast_spell, "drainerbolt" :),
                (: cast_spell, "netherbolt" :),
                (: cast_spell, "feeblebolt" :),
                (: cast_spell, "invocation" :),
        }) );

        create_family("三清宫", 6, "女主持");

        set_skill("literate", 70);
        set_skill("magic", 40);
        set_skill("force", 30);
        set_skill("spells", 200);
	set_skill("scratching",50);
	set_skill("move", 40);
        set_skill("unarmed", 30);
        set_skill("sword", 100);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set_skill("gouyee", 100);
        set_skill("notracesnow", 100);
        set_skill("snowshade-sword", 80);

        set_skill("taoism", 100);
        set_skill("necromancy", 100);
	set_skill("scratmancy",50);

        map_skill("spells", "necromancy");
        map_skill("parry", "snowshade-sword");
        map_skill("sword", "snowshade-sword");
        map_skill("move", "notracesnow");
        map_skill("dodge", "notracesnow");


        set_temp("apply/dodge", 20);
        set_temp("apply/armor", 20);

        setup();

        carry_object(__DIR__"obj/sword2")->wield();
        carry_object(__DIR__"obj/robe2")->wear();
        carry_object(__DIR__"obj/hat2")->wear();
        carry_object(__DIR__"obj/shoe2")->wear();
}

void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 贫道今天已经收了三个弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if( (string)ob->query("gender") != "女性" )
                command("say 贫道是出家人，不便收男徒，得罪了。");
        else {
                command("say 嗯... 想入我三清宫？也好....");
                command("recruit " + ob->query("id") );
        }
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
        add("apprentice_availavble", -1);
}

void init()
{
        add_action("give_quest", "quest");
}
 
void re_rank(object student)
{
        int exp;
        exp = (int) student->query("combat_exp");
        if( exp <= 32000 ) {
                student->set("title","三清宫尼姑");
                return ;
        } else if ( exp <= 128000 ) {
                student->set("title","三清宫小师太");
                return ;
        } else if ( exp <= 512000 ) {
                student->set("title","三清宫师太");
                return ;
        } else if ( exp <= 1536000 ) {
                student->set("title","三清宫圣尼");
                return ;
        } else if ( exp <= 3456000 ) {
                student->set("title","三清宫神尼");
                return ;
        } else if ( exp <= 5187000 ) {
                student->set("title","三清宫菩萨");
                return ;
        } else if ( exp <= 26244000 ) {
                student->set("title","三清宫副主持");
                return ;
        } else
                student->set("title","三清宫主持");
                return ;

}
