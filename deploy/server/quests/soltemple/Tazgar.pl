sub EVENT_ITEM {
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