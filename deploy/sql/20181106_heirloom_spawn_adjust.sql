#emerald jungle
#fix spawnpoint that was under the bridge, can spawn key holding gorilla by 12% chance
UPDATE spawn2 SET z="-95" WHERE id=13552; -- whovian (7-Nov-18  1:52:00)
#boost spawn chance of key holding gorilla for one of the spawn points from 20% to 60%
UPDATE spawnentry SET chance=60 WHERE spawngroupID=9281 AND npcID=94123; -- whovian (7-Nov-18  1:55:25)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=9281 AND npcID=94054; -- whovian (7-Nov-18  1:55:39)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=9281 AND npcID=94063; -- whovian (7-Nov-18  1:55:44)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=9281 AND npcID=94074; -- whovian (7-Nov-18  1:55:51)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=9281 AND npcID=94124; -- whovian (7-Nov-18  1:55:57)

#great divide
#reduce respawn timer of shardwurm broodmother by 90% - from 6 hours to 36 minutes
UPDATE spawn2 SET respawntime="2160" WHERE id=22824; -- whovian (7-Nov-18  1:58:11)

#wakening land
#boost Grand_Vizier_Poolakacha`tei spawn chance from 25% to 64%
UPDATE spawnentry SET chance=64 WHERE spawngroupID=16143 AND npcID=119162; -- whovian (7-Nov-18  2:01:56)
UPDATE spawnentry SET chance=12 WHERE spawngroupID=16143 AND npcID=119047; -- whovian (7-Nov-18  2:02:02)
UPDATE spawnentry SET chance=12 WHERE spawngroupID=16143 AND npcID=119113; -- whovian (7-Nov-18  2:02:06)
UPDATE spawnentry SET chance=12 WHERE spawngroupID=16143 AND npcID=119147; -- whovian (7-Nov-18  2:02:10)

#cobalt scar
#boost spawn chance of bulthar herdleader from 25% to 60%
UPDATE spawnentry SET chance=60 WHERE spawngroupID=13632 AND npcID=117015; -- whovian (7-Nov-18  2:04:02)
UPDATE spawnentry SET chance=40 WHERE spawngroupID=13632 AND npcID=117009; -- whovian (7-Nov-18  2:04:08)

#burning woods
#boost gorgul spawn rate from 20% to 60%
UPDATE spawnentry SET chance=10 WHERE spawngroupID=7864 AND npcID=87005; -- whovian (7-Nov-18  2:05:21)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=7864 AND npcID=87006; -- whovian (7-Nov-18  2:05:26)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=7864 AND npcID=87103; -- whovian (7-Nov-18  2:05:31)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=7864 AND npcID=87105; -- whovian (7-Nov-18  2:05:36)
UPDATE spawnentry SET chance=60 WHERE spawngroupID=7864 AND npcID=87113; -- whovian (7-Nov-18  2:05:45)

#skyfire
#boost black scar spawn rate from 11% to 20%, reduce respawn timer from 10.7min to 1.5min
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91005; -- whovian (7-Nov-18  2:13:10)
UPDATE spawnentry SET chance=20 WHERE spawngroupID=11800 AND npcID=91088; -- whovian (7-Nov-18  2:13:15)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91012; -- whovian (7-Nov-18  2:13:20)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91031; -- whovian (7-Nov-18  2:13:25)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91063; -- whovian (7-Nov-18  2:13:30)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91081; -- whovian (7-Nov-18  2:13:35)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91094; -- whovian (7-Nov-18  2:13:40)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91100; -- whovian (7-Nov-18  2:13:45)
UPDATE spawnentry SET chance=10 WHERE spawngroupID=11800 AND npcID=91101; -- whovian (7-Nov-18  2:13:50)
UPDATE spawn2 SET respawntime="90" WHERE id=18547; -- whovian (7-Nov-18  2:14:39)
