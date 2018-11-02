#ID91092
sub EVENT_SAY {
  if($text=~/hail/i) {
    quest::say("What brings you here mortal? I am the new guardian of Veeshan's Peak and I will allow you to pass. Let me know when you are [ready].");
  }
  if($text=~/ready/i) {
    quest::say("Very well.");
	quest::movepc(108,1682,41,27.13);
  }
}