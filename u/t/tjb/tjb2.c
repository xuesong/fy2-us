// servant.c

inherit NPC;
inherit F_MASTER;
inherit F_VENDOR;
inherit F_CLEAN_UP;

void create()
{
        set_name("大愚", ({ "master tjb", "tjb", "master" }) );
        set("title", "江湖隐士");
        set("nickname", "老六");
        set("gender", "男性");
        set("age", 24);
        set("long",
                
"大愚在这里是为了promote来这里想当巫师的玩家, 因为最近很忙只好做个NPC\n"
                
"来代替了，请见谅，我也希望成为您的朋友(list tjb1)\n想申请巫师用apply\n"
"询问请用ask master about all\n");
        set("attitude", "peaceful");
        set("combat_exp", 1000000);
        set("vendor_goods", ([
               "名片":  "/obj/example/tjbcard",
           ]) );  
        set("score", 200000);
        set("env/wimpy",70);
        set("env/ppp","tjb");
        set("str", 30);
        set("int", 30);
        set("cor", 30);
        set("cps", 30);
        set("con", 30);
        set("force", 4000);
        set("max_force", 2200);
        set("force_factor", 30);

        set("inquiry", ([
                "武学": "武学之道....嗯....只可意会，不可言喻。\n",
                "拜师": 
"哦....我向来有个规矩，凡是想拜我为师的，得接我一招不死，你想试试(accept 
test tjb1)？\n",
                "all" : "拜师, 武学, 申请？\n",
                "申请" : "现在只为player申请升为apprentice\n",
        ]) );

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        create_family("绝尘派", 2, "弟子");
        assign_apprentice("弟子", 0);

        set_skill("force", 150);
        set_skill("unarmed", 150);
        set_skill("sword", 180);
        set_skill("parry", 100);
        set_skill("dodge", 150);
        set_skill("throwing", 50);
        set_skill("literate",100);

        set_skill("demon-force", 150);
        set_skill("doomsword", 120);
        set_skill("fall-steps", 150);

        map_skill("force", "demon-force");
        map_skill("sword", "doomsword");
        map_skill("dodge", "fall-steps");

        setup();

        carry_object("/obj/cloth")->wear();
        carry_object("/d/wanmei/npc/obj/xuejian")->wield();
        add_money("gold",100);
}

void init()
{
   object ob;
        ::init();
        if ( interactive(ob = this_player()) && !is_fighting()) {
            remove_call_out("greeting");
            call_out("greeting",1,ob);
        };
        add_action("do_accept", "accept");
        add_action("do_vendor_list","list"); 
}


int do_accept(string arg)
{
        mapping guild;

        if( arg== "test" ) {
                say("\n老六点了点头，说道：很好，这是第一招....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(), 
query_temp("weapon"));
                if( (int)this_player()->query("kee") < 0 
                || !present(this_player(), environment())) {
                        
say("老六叹了口气，说道：连一招都撑不过，真是自不量力....\n");
                        return 1;
                }
say("\n老六哈哈大笑，说道：今日老六终於觅得一个可造之才！\n\n");
                command("recruit " + this_player()->query("id") );
                return 1;
        }
        return 0;
}

 
void attempt_apprentice(object me)
{
	say(RANK_D->query_respect(me) + "若真的有心，不妨让我看看你的所学\n");
	
	tell_object(me, "如果想拜师的话，就请接受测试（accept test）\n");
}	 

void greeting(object ob)
{
  if (!ob || environment(ob) != environment()) return;
    say("大愚说道: 这位"+RANK_D->query_respect(ob)
       +"欢迎到此行走江湖 \n");
}

