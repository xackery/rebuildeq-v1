sub EVENT_SAY {
  if($text=~/hail/i) {
    quest::say("You $name. We hear of you. We need help. You [ ". quest::saylink("help Crakneks"). " ] or you [ ".quest::saylink("help self") ." ]?");
  }
  if($text=~/help crakneks/i) {
    quest::say("Ha!! We hear of great adventurer. You?!! Me no think so. You prove self to Crakneks before you help us. Go to Innoth.. Innotu.. Innooth.. Arghh!! You go to outside Oggok. Find fat alligator bit Lork brother in two. Bring brother, Nork, body back. Then me know you strong.");
  }
  if($text=~/help self/i) {
    quest::say("You help self by get better with Rallos Zek. Find me missing chapters for [ ". quest::saylink("book"). " ], me help you.");
  }
  if ($text=~/uglan/i) {
   quest::say("Uglan brave warrior of Oggok. He now in Neriak. Work for dark elves. He NO LIKE dark elves!! He work because we make him. He spy for Crakneks.");
  }
  if ($text=~/book/i) {
    quest::say("Book lost all over. Doctrine, lost chapters, Rallos made many creatures you know? Each creature, different page.. Ogres first, Giants next. Orcs be third. 4th uhm.. I forget. Oh!! Goblins. Go find me chapters. You get Doctrine.");
  }
}

sub EVENT_ITEM {
  if(plugin::check_handin(\%itemcount, 100041 => 1, 100042 => 1, 100043 => 1, 100044 => 1)) {
    quest::say("Ay danks. Doctrine all yours.");    
    quest::exp(1000);
    quest::summonitem(100040);
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
  if(plugin::check_handin(\%itemcount, 100040 => 1)) {
    return;
  }


  if(plugin::check_handin(\%itemcount, 20523 => 1)) {
    quest::say("Ay danks. Take dis to Uglan.");
    quest::summonitem(16547);
  }
  elsif(plugin::check_handin(\%itemcount, 1717 => 1)) {
    quest::say("Arg! Dem damned Orcs and Dark Elves! To da hells with dem! I be wantin revenge! Bring me da hearts of da dark elf ammbassador's K'ryn who can be locat'd in da shamen tun'ls, and D'vinn who can be located in da crushbone with da orc emperor.");
  }
  elsif(plugin::check_handin(\%itemcount, 13227 => 1)) {
    quest::say("Ahahaha! Da basterds! Here be a reward for ye!");
    quest::summonitem(13355);
  }
  elsif(plugin::check_handin(\%itemcount, 13356 => 1)) {
    quest::say("Ahhh!! Boohoohoo. Nork!! That you arm. Me will take care of you now. Thank you for killing gator. You must be strong. Now you help Crakneks. We hear.. ohh, poor Nork, we hear trouble begins. Find ogre warrior [Uglan]. Give him this. It broken. He know where you from. Go. Nork.. Poor Nork.");
    quest::faction(57,10);
    quest::faction(46,10);
    quest::faction(128,-10);
    quest::summonitem(13357);
    quest::exp(50);
  }
  elsif(plugin::check_handin(\%itemcount, 18840 => 1)) {
    quest::say("What this!! So, dark elves think they can bash ogres. Replace with blue orcs. Dumb Zulort friend with dark elf ambassador in Oggok. We kill him. We kill Crushbone dark elf ambassador also. This slow down plan. We need a hero. Me guess you do. You go. Go bring Lork both Crushbone and Oggok dark elf hearts. Then you be hero.");
    quest::faction(57,10);
    quest::faction(46,10);
    quest::faction(128,-10);
    quest::exp(100);
    quest::summonitem(5030);
  }
  elsif(plugin::check_handin(\%itemcount, 13358 => 1, 13227 => 1)) {
    quest::say("That show dark elves who strongest. Me hope you kill many blue orcs. You Craknek Hero now. You take this. It mine. Hero reward. You great ogre now. Smash best.");
    quest::faction(57,10);
    quest::faction(46,10);
    quest::faction(128,-10);
    quest::exp(100);
    quest::ChooseRandom(13359,13355,2136,2130,2135,2132,2128);
  }
  #do all other handins first with plugin, then let it do disciplines
  plugin::try_tome_handins(\%itemcount, $class, 'Warrior');
  plugin::return_items(\%itemcount);
}
#END of FILE Zone:oggok  ID:49040 -- Lork