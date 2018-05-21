sub EVENT_SAY { 

  if($text=~/Hail/i){
    quest::say("Greetings, $name. Are you a [ " . quest::saylink("true warrior") . " ]?");
    return;
  }

  if($text=~/true warrior/i){
    quest::say("Then you shall be tested as one.  Choose.  [ ". quest::saylink("runed wind amulet"). " ] [ " . quest::saylink("aerated pauldrons") . " ] [ " . quest::saylink("azure ruby ring") . " ] [ " . quest::saylink("belt of the four winds") . " ] [ " . quest::saylink("dagas") . " ] [ " . quest::saylink("fangol") . " ]");
    return;
  }

  if ($text=~/runed wind amulet/i) {
    quest::say("Remember, true strength lies not only in the body, but in the mind as well. Return to me a bronze disc, a small pick and a stone amulet. If you manage to do this my runed wind amulet will be yours.");
    return;
  }
  if ($text=~/aerated pauldrons/i) {
    quest::say("Foolishness or bravery, $name?  We shall see. Return to me a pearlescent globe, a silver mesh and a spiroc air totem  In return, you will receive both my deepest respect and the aerated pauldrons.");
    return;
  }
  if ($text=~/azure ruby ring/i) {
    quest::say("The test of skill it is. Go upward and retrieve these three items: an ivory tessera, a tiny ruby, and an azure ring. Return these to me and the azure ruby ring shall be yours.");
    return;  
  }

  if ($text=~/fangol/i) {
    quest::say("efreeti battle axe, honeyed nectar, bottled djinni, ethereal emerald. Bring me these items, and I'll give you a fangol.");
    return;
  }

  if ($text=~/dagas/i) {
    quest::say("djinni war blade, virulent poison, mottled spiroc feather. Bring me these items, and I'll give you a dagas.");
    return;
  }

  if ($text=~/belt of the four winds/i) {
    quest::say("efreeti belt, pegasus statuette, spiroc wind totem, wind tablet. Bring me these items, and I'll give you a belt of the four winds.");
    return;
  }

}



sub EVENT_ITEM {  
 
  if(plugin::check_handin(\%itemcount, 20935 => 1, 20972 => 1, 20973 => 1)) {
    #warrior test of strength using bronze disc, small pick, stone amulet
    quest::summonitem(14569); #runed wind amulet
    quest::ding(); 
    quest::exp(841790);
    quest::say("You have proven yourself worthy.");
    quest::depop();
  }

  if(plugin::check_handin(\%itemcount, 20942 => 1, 20974 => 1, 20975 => 1)) {
    #warrior test of force using pearlescent globe, silver mesh, spiroc air totem
    quest::summonitem(4321); #aerated pauldrons
    quest::ding(); 
    quest::exp(841790);
    return;
  }
      

  if(plugin::check_handin(\%itemcount, 20928 => 1, 20795 => 1, 20971 => 1)) {
    #warrior test of skill using ivory tessera, tiny ruby, azure ring
    quest::summonitem(14551); #azure ruby ring
    quest::ding(); 
    quest::exp(841790);
  }

  if(plugin::check_handin(\%itemcount, 20983 => 1, 20963 => 1, 20981 => 1, 20982 => 1)) { #warrior test of bash using efreeti battle axe, honeyed nectar, bottled djinni, ethereal emerald
    quest::summonitem(11675); #fangol
     quest::ding(); 
     quest::exp(841790);
    }
  
  if(plugin::check_handin(\%itemcount, 20980 => 1, 20979 => 1, 20956 => 1)) { #warrior test of smash using djinni war blade, virulent poison, mottled spiroc feather
    quest::summonitem(11674); #dagas 
     quest::ding(); 
     quest::exp(841790);
    }

  if(plugin::check_handin(\%itemcount, 20976 => 1, 20949 => 1, 20977 => 1, 20978 => 1)) { #warrior test of think using efreeti belt, pegasus statuette, spiroc wind totem, wind tablet
    quest::summonitem(11673); #belt of the four winds
     quest::ding(); 
     quest::exp(841790);
  }

  if (plugin::check_handin(\%itemcount, 2193 => 1)) {
    quest::say("This shows your discipline.");
    return;
  }

  if (plugin::check_handin(\%itemcount, 5523 => 1)) {
    quest::say("This shows your wit.");
    return;
  }

  if (plugin::check_handin(\%itemcount, 14551 => 1)) {
    quest::say("This shows your desire.");
    return;
  }

  if (plugin::check_handin(\%itemcount, 4504 => 1)) {
    quest::say("This shows your dedication.");
    return;
  }

  if (plugin::check_handin(\%itemcount, 2346 => 1)) {
    quest::say("This shows your faith.");
    return;
  }

  #Need to check if 1,2,3 or 4 stacks of experience bottles are turned in, otherwise player gets credit and items are returned.
  if(plugin::check_handin(\%itemcount, 100001 => 1)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }
    if(plugin::check_handin(\%itemcount, 100001 => 2)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }
    if(plugin::check_handin(\%itemcount, 100001 => 3)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }
    if(plugin::check_handin(\%itemcount, 100001 => 4)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }

  plugin::return_items(\%itemcount);
}
#END of FILE Zone:airplane  ID:5039 -- Torgon_Blademaster 