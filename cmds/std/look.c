// look.c

#include <room.h>
#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string getper(object me, object obj);
string tough_level(int power);
string gettof(object me, object obj);
string getdam(object me, object obj);
string *tough_level_desc = ({
        BLU "不堪一击" NOR,
        BLU "毫不足虑" NOR,
        BLU "不足挂齿" NOR,
        BLU "初学乍练" NOR,
        HIB "初窥门径" NOR,
        HIB "略知一二" NOR,
	HIB "普普通通" NOR,
	HIB "平平淡淡" NOR,
        HIB "平淡无奇" NOR,
        HIB "粗通皮毛" NOR,
        HIB "半生不熟" NOR,
        HIB "马马虎虎" NOR,
	HIB "略有小成" NOR,
        HIB "已有小成" NOR,
        HIB "驾轻就熟" NOR,
        CYN "心领神会" NOR,
        CYN "了然於胸" NOR,
	CYN "略有大成" NOR,
	CYN "已有大成" NOR,
        CYN "豁然贯通" NOR,
        CYN "出类拔萃" NOR,
	CYN "无可匹敌" NOR,
	CYN "技冠群雄" NOR,
        CYN "神乎其技" NOR,
        CYN "出神入化" NOR,
	CYN "傲视群雄" NOR,
        HIC "登峰造极" NOR,
	HIC "所向披靡" NOR,
        HIC "一代宗师" NOR,
	HIC "神功盖世" NOR,
        HIC "举世无双" NOR,
        HIC "惊世骇俗" NOR,
        HIC "震古铄今" NOR,
	HIC "深藏不露" NOR,
        HIR "深不可测" NOR
});
string *heavy_level_desc= ({
	"极轻",
	"很轻",
	"不重",
	"不轻",
	"很重",
	"极重"	
});
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	int result;

	if( !arg ) result = look_room(me, environment(me));
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = look_living(me, obj);
		else result = look_item(me, obj);
	} else result = look_room_item(me, arg);

	return result;
}

int look_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string str, *dirs;

	if( !env ) {
		write("你的四周灰蒙蒙地一片，什麽也没有。\n");
		return 1;
	}
	str = sprintf( "%s - %s\n    %s%s",
		env->query("short"),
		wizardp(me)? file_name(env): "",
		env->query("long"),
		env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = env->query("exits")) ) {
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
				dirs[i] = 0;
		dirs -= ({ 0 });
		if( sizeof(dirs)==0 )
			str += "    这里没有任何明显的出路。\n";
		else if( sizeof(dirs)==1 )
			str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
		else
			str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
				implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
	}
//	str += env->door_description();

	inv = all_inventory(env);
	for(i=0; i<sizeof(inv); i++) {
		if( inv[i]==me ) continue;
		if( inv[i]->query("no_shown")) continue;
		if( !me->visible(inv[i]) ) continue;
		str += "  " + inv[i]->short() + "\n";
	}

	write(str);
	return 1;
}

int look_item(object me, object obj)
{
	mixed *inv;
	string prep;

	write(obj->long());
	inv = all_inventory(obj);
	if( !obj->is_closed() && sizeof(inv)) {
		switch( (string)obj->query("prep") ) {
			case "on":
				prep = "上";
				break;
			case "under":
				prep = "下";
				break;
			case "behind":
				prep = "后";
				break;
			case "inside":
				prep = "里";
				break;
			default:
				prep = "里";
				break;
                        }
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("%s面有：\n  %s\n", prep,
			implode(inv, "\n  ") ), me);
	}
	return 1;
}

string getper(object me, object obj)
{
	int per;
	int spi;

	int weight;
	string str;

	per = obj->query_per();
	spi = me->query_spi();

// 灵性差的人看的不准
	if (spi>35) weight = 0;
	else weight = (int)(35 - spi)/4 ;


	if (random(10)>6) per = per - weight;
	else per = per + weight ;

	
	if ((string) obj->query("gender") == "男性") {
		if (per > 20) str = "他相貌出众,百里挑一。\n";
		if ((per >= 15) && (per <=30)) 
			str = "他英俊潇洒,貌似潘安。\n";
		if ((per >= 10) && (per < 25)) 
			str = "他五官端正。\n";
		if (per < 5) 
			str = "他相貌平平。\n";
	}
	else if  ((string) obj->query("gender") == "女性"){
		if (per > 25)
			str = "她美奂绝伦,堪称人间仙子！\n";
		if ((per >= 20) && (per <= 30)) 
			str = "她有沉鱼落雁之容,避月羞花之貌！\n";
		if ((per >= 15) && (per < 25)) 
			str = "她风情万种,楚楚动人！\n"; 
		if ((per >= 10) && (per < 20))
			str = "她相貌平平,还看得过去。\n";
		if (per < 5) 
			str = "她的相貌嘛...马马虎虎吧。\n";
	}
	if (!(string) obj->query("family")) 
	{
	if(str) str +="但看起来好象对你并不很友善。\n";
	else str = "但看起来好象对你并不很友善。\n";
	}
	if( !str) str="";
	return str;
}
string gettof(object me, object ob)
{
	object weapon;
	string skill_type,parry_type;
	int attack_points;
        if( objectp(weapon = ob->query_temp("weapon")) )
        {
                skill_type = weapon->query("skill_type");
                parry_type = "parry";
        }
        else
        {
                skill_type = "unarmed";
                parry_type = "unarmed";
        }

        attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	return  tough_level(attack_points);
}
int look_living(object me, object obj)
{
	string str, limb_status, pro;
	mixed *inv;
	mapping my_fam, fam;

	if( me!=obj )
		message("vision", me->name() + "正盯著你看，不知道打些什麽主意。\n", obj);

	str = obj->long();

	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

	if( (string)obj->query("race")=="人类"
	&&	intp(obj->query("age")) )
		str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10));
		str+=getper(me,obj);
		str +=sprintf("武功看起来好象");
		str+=gettof(me,obj);
		str += sprintf("，");
		str +=sprintf("出手似乎");
		str +=getdam(me,obj);
                str += sprintf("。\n");
	// If we both has family, check if we have any relations.
	if( obj!=me
	&&	mapp(fam = obj->query("family"))
	&&	mapp(my_fam = me->query("family")) 
	&&	fam["family_name"] == my_fam["family_name"] ) {
	
		if( fam["generation"]==my_fam["generation"] ) {
			if( (string)obj->query("gender") == "男性" )
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
			else
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
		} else if( fam["generation"] < my_fam["generation"] ) {
			if( my_fam["master_id"] == obj->query("id") )
				str += pro + "是你的师父。\n";
			else if( my_fam["generation"] - fam["generation"] > 1 )
				str += pro + "是你的同门长辈。\n";
			else if( fam["enter_time"] < my_fam["enter_time"] )
				str += pro + "是你的师伯。\n";
			else
				str += pro + "是你的师叔。\n";
		} else {
			if( fam["generation"] - my_fam["generation"] > 1 )
				str += pro + "是你的同门晚辈。\n";
			else if( fam["master_id"] == me->query("id") )
				str += pro + "是你的弟子。\n";
			else
				str += pro + "是你的师侄。\n";
		}
	}

	if( obj->query("max_kee") )
		str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";

	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
			str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s身上带著：\n%s\n",
				pro, implode(inv, "\n") );
	}

	message("vision", str, me);

	if( obj!=me 
	&&	living(obj)
	&&	random((int)obj->query("bellicosity")/10) > (int)me->query_per() ) {
		write( obj->name() + "突然转过头来瞪你一眼。\n");
		COMBAT_D->auto_fight(obj, me, "berserk");
	}

	return 1;
}

string inventory_look(object obj, int flag)
{
	string str;

	str = obj->short();
	if( obj->query("equipped") )
		str = HIC "  √" NOR + str;
	else if( !flag )
		str = "    " + str;
	else
		return 0;

	return str;
}

int look_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !objectp(env = environment(me)) )
		return notify_fail("这里只有灰蒙蒙地一片，什麽也没有。\n");

	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
		if( stringp(item[arg]) )
			write(item[arg]);
		else if( functionp(item[arg]) )
			write((string)(*item[arg])(me));
			
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
		if( objectp(env = find_object(exits[arg])) )
			look_room(me, env);
		else {
			call_other(exits[arg], "???");
			look_room(me, find_object(exits[arg]));
		}
		return 1;
	}
	return notify_fail("你要看什麽？\n");
}
string tough_level(int power)
{

	int lvl;
	int rawlvl;
	int grade = 1;
	if(power<0) power=0;
	rawlvl = (int) pow( (float) 1.0 * power, 0.3);
	lvl = to_int(rawlvl/grade);
                        if( lvl >= sizeof(tough_level_desc) )
                                lvl = sizeof(tough_level_desc)-1;
                        return tough_level_desc[((int)lvl)];
}
string getdam(object me, object obj)
{

	int level;
	level = obj->query_temp("apply/damage");
	level = level / 50;
                        if( level >= sizeof(heavy_level_desc) )
                                level = sizeof(heavy_level_desc)-1;
                        return heavy_level_desc[((int)level)];
}

int help (object me)
{
	write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
	return 1;
}
