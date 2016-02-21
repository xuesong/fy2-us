
#include <weapon.h>

inherit FORK;

void create()
{
	set_name("钉钯", ({ "dingpa" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "一把九齿钉钯。\n");
		set("value", 2500);
		set("material", "steel");
		set("rigidity", 40);
		set("wield_msg", "$N从腰间拔出一把$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插在腰间。\n");
	}
	init_fork(60);
	setup();
}
