// npc: /d/city/npc/wei.c
// Jay 5/15/96

inherit NPC;

void create()
{
        set_name("Τ����", ({ "wei chunfang", "chunfang", "wei" }) );
        set("gender", "Ů��" );
	set("title", "����Ժ�ϰ���");
//	set("nickname", "¹����");
        set("age", 42);
        set("long", 
            "Τ�����ǵ���¹������컨���ܶ���ΤС�����������"
	    "����ϣ��������ȴ档\n");
        set("str", 25);
        set("per", 25);
        set("con", 25);
        set("int", 25);
        set("shen_type", 1);

        set_skill("unarmed", 20);
	set_skill("force", 20);
        set_skill("dodge", 35);

        set("combat_exp", 25000);

        set("max_kee", 300);
        set("max_gin", 100);
        set("force", 500);
        set("max_force", 500);

        set("attitude", "friendly");
        set("inquiry", ([
            "name" : "�����Ҿ���Τ������",
            "ΤС��" : "�����ҵĹԶ��ӣ����þ����㡣",
            "����Ժ" : "��������Ժ�������ݳ���ͷһ�ݵ�������ȥ����",
            "here" : "��������Ժ�������ݳ���ͷһ�ݵ�������ȥ����",
       ]) );

        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                "Τ���������˵�������������ұ��µúܣ�ÿ���кü������ˡ�\n",
                "Τ����ŭ������������裬Ҫ����ɲ������ë���ӵ�����Ժ���������ô�ɨ�����˳�ȥ���\n",
                "Τ��������˵������һ˫�۾���߯�����ģ������Ǹ����\n",
        }) );
//        carry_object(__DIR__"obj/flower_shoe")->wear();

//        carry_object("__DIR__obj/pink_cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
    command("look " + me->query("id"));

    if (me->query("gender")=="����") {
       command("say �㵱��������������������裬���������ɲػض��ӣ����ǲ��ź�̫�࣡");
       command("kick " + me->query("id"));
       message("vision", me->name() +"��Τ����һ���߳����⡣\n",
                environment(me), ({me}));
       me->move("/d/city/nandajie2");
       message("vision", me->name() +"���˴�����Ժ�����˳������Ե��ڵ��ϣ��ĵ�����������\n", 
                environment(me), ({me}));

    }
    else {
    if (me->query("class") =="bonze") {
       command("say �ϣ�" + RANK_D->query_respect(me) 
                +"Ҳ�������������Ժ����");
       command("say �뵱���ҽӹ�һ������������ϴ�ǰһ��Ҫ���һ����������Ӿ͹�����������ҡ�");
    }
    if (me->query("gender")=="Ů��") {
       command("say ��ѽ�������´����Ҳ��Ҥ�ӣ��ɺ���ͬ��");
       command("sigh");
       command("say ��ϧ�Ҷ��Ӳ��ڣ���Ȼ�����ź��㡣");
    }
    command("say ¥��¥�µĹ����ǣ��������ˣ�");
    }
    return ;
}
