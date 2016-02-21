// servant.c

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("���Ŵ�ѩ", ({ "master ximen", "ximen", "master" }) );
        set("title", "��÷ׯ��");
        set("gender", "����");
        set("age", 34);
        set("long",
"���Ŵ�ѩ���ǵ�����������֮һ�������Ѿ������ˣ��޽����ľ��磮��\n"
               ); 

        set("attitude", "peaceful");
        set("combat_exp", 10000000);
        set("score", 200000);
        set("agi",25);
        set("int",30);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hunranyijian" :),
                (: perform_action, "dodge.feitiantui" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
		"���Ŵ�ѩ��Ц������˷������ɱ�ң�\n"
        }) );
        set("chat_chance", 1);
        set("chat_msg", ({
                "���Ŵ�ѩŭ�����½С�������ӵ�����ɽׯ����ҲҪɱ���㣡��\n",
        }) );
        set("str", 30);
        set("int", 30);
        set("cor", 300);
        set("cps", 30);
        set("con", 30);

        set("force", 4000);
        set("max_force", 2200);
        set("force_factor", 30);

        set("inquiry", ([
                "��ʦ": 
"�������и���أ����������Ϊʦ�ģ��ý������в�������������(accept 
test)��\n",
		"apprentice" :
"�������и���أ����������Ϊʦ�ģ��ý������в�������������(accept
test)��\n"

        ]) );

        create_family("��÷ɽׯ", 1, "ׯ��");

        set_skill("force", 100);
        set_skill("unarmed", 100);
        set_skill("sword", 150);
        set_skill("parry", 100);
        set_skill("dodge", 80);
        set_skill("throwing", 50);
	set_skill("move", 150);

        set_skill("doomforce", 100);
        set_skill("doomstrike", 100);
        set_skill("doomsteps", 90);
	set_skill("doomsword",120);

        map_skill("force", "doomforce");
        map_skill("unarmed", "doomstrike");
        map_skill("sword", "doomsword");
        map_skill("dodge", "doomsteps");


        setup();

        carry_object(__DIR__"obj/xuejian")->wield();
	carry_object(__DIR__"obj/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_accept", "accept");
        add_action("give_quest", "quest");

}
int do_accept(string arg)
{
        mapping guild;

        if( arg== "test" ) {
                say("\n���Ŵ�ѩ���˵�ͷ��˵�����ܺã����ǵ�һ��....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(), 
query_temp("weapon"));
                if( (int)this_player()->query("kee") < 0 
                || !present(this_player(), environment())) {
                        
say("���Ŵ�ѩ̾�˿�����˵��������һ�ж��Ų����������Բ�����....\n");
                        return 1;
		}
                say("\n���Ŵ�ѩ˵�������ǵڶ���....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(), 
query_temp("weapon"));
                if( (int)this_player()->query("kee") < 0 
                || !present(this_player(), environment())) {
                        
say("���Ŵ�ѩ���ߡ���һ����˵���������������಻�����ļһ�....\n");
                        return 1;
                }
                say("\n���Ŵ�ѩ˵��������������....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(), 
query_temp("weapon"));
                if( (int)this_player()->query("kee") < 0 
                || !present(this_player(), environment())) {
                        
say("���Ŵ�ѩ̾������ϧ���ѵ���һ���书���޴���....\n");
                        return 1;
                }
                
say("\n���Ŵ�ѩ������Ц��˵������������ٵ�һ������֮�ţ�\n\n");
                command("recruit " + this_player()->query("id") );
                return 1;
        }
        return 0;
}

void re_rank(object student)
{
        int exp;
        exp = (int) student->query("combat_exp");
        if( exp <= 32000 ) {
                student->set("title","��÷ɽׯ����");
                return ;
        } else if ( exp <= 128000 ) {
                student->set("title","��÷ɽׯ���");
                return ;
        } else if ( exp <= 512000 ) {
                student->set("title","��÷ɽׯС�ܼ�");
                return ;
        } else if ( exp <= 1536000 ) {
                student->set("title","��÷ɽׯ�ܼ�");
                return ;
        } else if ( exp <= 3456000 ) {
                student->set("title","��÷ɽׯ��ܼ�");
                return ;
        } else if ( exp <= 5187000 ) {
                student->set("title","��÷ɽׯ�ܹ�");
                return ;
        } else if ( exp <= 26244000 ) {
                student->set("title","��÷ɽׯ���ܹ�");
                return ;
        } else
                student->set("title","��÷ɽׯ��ׯ��");
                return ;

}

void killed_enemy(object who)
{
        command("say ����֮ͽ��������ϧ��\n");
}
