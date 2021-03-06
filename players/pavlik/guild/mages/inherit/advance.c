#include "/players/pavlik/guild/mages/defs.h"

/*
 *
 * This file contains code for guild advancement and costs
 * including guild ranks and stats/attribs/etc
 *
 */


/*
 * Guild Exp required for each guild rank
 */

rank_costs(rank)
{
  int xp;

  if(rank == 1) xp = 500;
  if(rank == 2) xp = 1225;
  if(rank == 3) xp = 1900;
  if(rank == 4) xp = 2650;
  if(rank == 5) xp = 3650;
  if(rank == 6) xp = 6300;
  if(rank == 7) xp = 9257;
  if(rank == 8) xp = 12214;
  if(rank == 9) xp = 15171;
  if(rank == 10) xp = 18128;
  if(rank == 11) xp = 21085;
  if(rank == 12) xp = 24042;
  if(rank == 13) xp = 26999;
  if(rank == 14) xp = 29956;
  if(rank == 15) xp = 34741;
  if(rank == 16) xp = 39526;
  if(rank == 17) xp = 44311;
  if(rank == 18) xp = 49096;
  if(rank == 19) xp = 53881;
  if(rank == 20) xp = 58666;
  if(rank == 21) xp = 63541;
  if(rank == 22) xp = 68236;
  if(rank == 23) xp = 78236;
  if(rank == 24) xp = 88236;
  if(rank == 25) xp = 98236;
  if(rank == 26) xp = 108236;
  if(rank == 27) xp = 118236;
  if(rank == 28) xp = 128236;
  if(rank == 29) xp = 138236;
  if(rank == 30) xp = 148236;
  if(rank == 31) xp = 165791;
  if(rank == 32) xp = 183346;
  if(rank == 33) xp = 200901;
  if(rank == 34) xp = 218456;
  if(rank == 35) xp = 236011;
  if(rank == 36) xp = 253566;
  if(rank == 37) xp = 271121;
  if(rank == 38) xp = 288676;
  if(rank == 39) xp = 323533;
  if(rank == 40) xp = 358390;
  if(rank == 41) xp = 393247;
  if(rank == 42) xp = 428104;
  if(rank == 43) xp = 462961;
  if(rank == 44) xp = 497818;
  if(rank == 45) xp = 532405;
  if(rank == 46) xp = 567262;
  if(rank == 47) xp = 619625;
  if(rank == 48) xp = 671988;
  if(rank == 49) xp = 724351;
  if(rank == 50) xp = 776714;
  if(rank == 51) xp = 829077;
  if(rank == 52) xp = 881440;
  if(rank == 53) xp = 933803;
  if(rank == 54) xp = 986166;
  if(rank == 55) xp = 1089309;
  if(rank == 56) xp = 1192452;
  if(rank == 57) xp = 1295595;
  if(rank == 58) xp = 1398738;
  if(rank == 59) xp = 1501881;
  if(rank == 60) xp = 1605024;
  if(rank == 61) xp = 1708167;
  if(rank == 62) xp = 1811310;
  if(rank == 63) xp = 1979778;
  if(rank == 64) xp = 2148246;
  if(rank == 65) xp = 2316714;
  if(rank == 66) xp = 2485182;
  if(rank == 67) xp = 2653650;
  if(rank == 68) xp = 2822118;
  if(rank == 69) xp = 2990586;
  if(rank == 70) xp = 3159054;
  if(rank >= 71) xp = 3327522;

  return xp * 5;
}


/*
 *
 */
school_costs(pts)
{
  int x, max_pts;

  if(tp->query_guild_rank() > 60) max_pts = 100;
  else if(tp->query_guild_rank() > 50) max_pts = 83;
  else if(tp->query_guild_rank() > 40) max_pts = 65;
  else if(tp->query_guild_rank() > 30) max_pts = 48;
  else if(tp->query_guild_rank() > 20) max_pts = 33;
  else if(tp->query_guild_rank() > 10) max_pts = 20;
  else max_pts = 10;
  if(x > max_pts + 2)
  return 69;

  if(pts > 72) x = 8225;
  else if(pts > 63) x = 4950;
  else if(pts > 54) x = 3100;
  else if(pts > 45) x = 1760;
  else if(pts > 36) x = 925;
  else if(pts > 27) x = 470;
  else if(pts > 18) x = 300;
  else if(pts > 9) x = 160;
  else x = 90;
  x = x + (pts * 2);

  return x;
}


train_cost(pts)
{
  if(pts >= 43) return 8000;
  else if(pts >= 36) return 6500;
  else if(pts >= 29) return 4000;
  else if(pts >= 22) return 2500;
  else if(pts >= 15) return 1500;
  else if(pts >= 8) return 1000;
  else return 500;
}


/*
 * spell_learn_cost
 */
spell_learn_cost(spell_level)
{
  if(spell_level == 1) return 1;
  if(spell_level == 2) return 2;
  if(spell_level == 3) return 2;
  if(spell_level == 4) return 3;
  if(spell_level == 5) return 3;
  if(spell_level == 6) return 4;
  if(spell_level == 7) return 4;
}


/*
 * stat_increase_amount
 */
stat_increase_amount(string stat)
{
  int modifier;
  int amount;

  if(member_array(stat, SCHOOLS) != -1)
  {
	modifier = guild->query_guild_stat("will power");
  }
  else if(member_array(stat, STATS) != -1)
  {
	modifier = guild->query_guild_stat("wisdom");
  }

  /* newbie bonus */
  if(modifier < 24 && tp->query_guild_rank() <= 18)
	amount = 3 + random(2);

  amount +=  (modifier/24) + random(modifier/6);
  if(amount < 1) amount = 1;
  if(amount > 8) amount = 8;

  return amount;

}


/*
 * spell_chances
 */
spell_chances(ob)
{
  int rank;
  rank = ob->query_guild_rank();

  /* [5] spells in ranks 1-10 */
  if(rank == 1) return spell_learn_cost(1);
  if(rank == 2) return spell_learn_cost(1);
  if(rank == 4) return spell_learn_cost(1);
  if(rank == 6) return spell_learn_cost(1);
  if(rank == 9) return spell_learn_cost(1);

  /* [5] spells in ranks 11-20 */
  if(rank == 11) return spell_learn_cost(2);
  if(rank == 13) return spell_learn_cost(2);
  if(rank == 14) return spell_learn_cost(2);
  if(rank == 17) return spell_learn_cost(2);
  if(rank == 18) return spell_learn_cost(2);

  /* [4] spells in ranks 21-30 */
  if(rank == 22) return spell_learn_cost(3);
  if(rank == 24) return spell_learn_cost(3);
  if(rank == 26) return spell_learn_cost(3);
  if(rank == 29) return spell_learn_cost(3);

  /* [4] spells in ranks 31-40 */
  if(rank == 32) return spell_learn_cost(4);
  if(rank == 35) return spell_learn_cost(4);
  if(rank == 36) return spell_learn_cost(4);
  if(rank == 39) return spell_learn_cost(4);

  /* [3] spells in ranks 41-50 */
  if(rank == 41) return spell_learn_cost(5);
  if(rank == 44) return spell_learn_cost(5);
  if(rank == 49) return spell_learn_cost(5);

  /* [2] spells in ranks 51-60 */
  if(rank == 53) return spell_learn_cost(6);
  if(rank == 58) return spell_learn_cost(6);

  /* [2] spells in ranks 61-71 */
  if(rank == 62) return spell_learn_cost(7);
  if(rank == 66) return spell_learn_cost(7);

  return 0;
}


/*
 * number of training sessions gained upon advancement
 */

training_sessions(ob)
{
  int amount;

  amount = 1 + random(present("mageobj", ob)->query_guild_stat("intelligence") / 8);

  /* newbie bonuses */
  if(tp->query_guild_rank() == 1) amount += 5;
  if(tp->query_guild_rank() > 1 && tp->query_guild_rank() < 10) amount += 2;

  /* cap */
  if(amount > 8) amount = 8;

  return amount;
}

