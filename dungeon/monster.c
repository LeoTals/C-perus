/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
/*typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};
*/

/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}

int checkplayer(Game *game, int x, int y){
	int p_x = game->position.x;
	int p_y = game->position.y;
	int match = 0;
	if(p_x == x){
		match++;
	}
	if(p_y == y){
		match++;
	}
	if (match == 2){return 1;}
	else{return 0;}
}
/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */
void moveTowards(Game *game, Creature *monst) {
	int has_moved = 0;
	int mon_x = monst->pos.x;
	int mon_y = monst->pos.y;
    int xdir = (mon_x == game->position.x)?0:(mon_x > game->position.x)?-1:1;
	int ydir = (mon_y == game->position.y)?0:(mon_y > game->position.y)?-1:1;
	if(xdir != 0){
		if((!isBlocked(game,mon_x+xdir,mon_y))&&(!!(checkplayer(game,mon_x+ydir,mon_y)))){
			monst->pos.x+=xdir;
			has_moved++;
		}
	}
	if((ydir != 0)&&(has_moved==0)){
		if((!isBlocked(game,mon_x,mon_y+ydir))&&(!(checkplayer(game,mon_x,mon_y+ydir)))){
			monst->pos.y+=ydir;
			has_moved++;
		}
	}
	int tries = 0;
	int dir = rand()%4;
	while ((has_moved==0)&&(tries<4)){
		switch(dir){
			case 0: //up
				if((!isBlocked(game,mon_x+1,mon_y))&&(!(checkplayer(game,mon_x+1,mon_y)))){
					monst->pos.x++;
					has_moved=1;
					break;
				}else{tries++;break;}
			case 1: //down
				if((!isBlocked(game,mon_x-1,mon_y))&&(!(checkplayer(game,mon_x-1,mon_y)))){
					monst->pos.x--;
					has_moved=1;
					break;
				}else{tries++;break;}
			case 2: //left
				if((!isBlocked(game,mon_x,mon_y-1))&&(!(checkplayer(game,mon_x,mon_y-1)))){
					monst->pos.y--;
					has_moved=1;
					break;
				}else{tries++;break;}
			case 3: //right
				if((!isBlocked(game,mon_x,mon_y+1))&&(!(checkplayer(game,mon_x,mon_y+1)))){
					monst->pos.y++;
					has_moved=1;
					break;
				}
				else{tries++;break;}
		}
		dir++;
		if(dir == 4){dir=0;}
	}
}	

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(Game *game, Creature *monst) {
	int xdir = 0;
	int ydir = 0;
	int monx = monst->pos.x;
	int mony = monst->pos.y;
	int gamex = game->position.x;
	int gamey = game->position.y;
	if(monx < gamex){xdir = -1;}
	else{xdir = 1;}
	if(monx < gamex){xdir = -1;}
	else{xdir = 1;}
	if(monx-gamex == 0&&!isBlocked(game,monx,mony+ydir)){
		monst->pos.y+=ydir;
		return;
	}
	if(mony-gamey == 0&&!isBlocked(game,monx+xdir,mony)){
		monst->pos.x+=xdir;
		return;

	int dir = rand()%2;
	if (dir == 0){
		if(!isBlocked(game,monx+dir,mony)){
			monst->pos.x+=xdir;
			return;
		}
		if(!isBlocked(game,monx,mony+ydir)){
			monst->pos.y+=ydir;
			return;
		}
	}else{
		if(!isBlocked(game,monx+dir,mony)){
			monst->pos.x+=xdir;
			return;
		}
		if(!isBlocked(game,monx,mony+ydir)){
			monst->pos.y+=ydir;
			return;
		}
		}
	}
	if(!isBlocked(game,monx+1,mony)){
		monst->pos.x++;
		return;
	}
	if(!isBlocked(game,monx-1,mony)){
		monst->pos.x--;
		return;
	}
	if(!isBlocked(game,monx,mony+1)){
		monst->pos.y++;
		return;
	}
	if(!isBlocked(game,monx,mony-1)){
		monst->pos.y--;
		return;
	}
	else{
		return;
	}
}	

/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
	for (unsigned int i = 0; i < game->numMonsters; i++) {
		Creature *orc = &game->monsters[i];
		if(orc->hp != 0){
			int xorc = orc->pos.x;
			int yorc = orc->pos.y;
			int xp = game->position.x;
			int yp = game->position.y;
			int xdis = 0;
			int ydis = 0;
			if(xorc<=xp){ xdis = xp-xorc;}
			else{xdis = xorc - xp;}
			if(yorc<=xp){ ydis = yp-yorc;}
			else{ydis = yorc - yp;}
			if(((xdis==1)&&(ydis<=1))||((ydis==1)&&(xdis<=1))){
				orc->attack(game,orc);
			}
			else{
				orc->move(game,orc);
				}
		}
	}
}

/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The moster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) {
	char **orcnames = calloc(26,sizeof(char*));
	for(int a = 0;a<26;a++){
		orcnames[a] = calloc(10,sizeof(char));
	}
	strcpy(orcnames[0],"Arokh");
	strcpy(orcnames[1],"Bazulub");
	strcpy(orcnames[2],"Cruds");
	strcpy(orcnames[3],"Dubomboz");
	strcpy(orcnames[4],"Ekk");
	strcpy(orcnames[5],"Feng");
	strcpy(orcnames[6],"Gell");
	strcpy(orcnames[7],"Hagren");
	strcpy(orcnames[8],"Ilga");
	strcpy(orcnames[9],"Jarg");
	strcpy(orcnames[10],"Korag");
	strcpy(orcnames[11],"Lubash");
	strcpy(orcnames[12],"Mhurren");
	strcpy(orcnames[13],"Nil");
	strcpy(orcnames[14],"Ohr");
	strcpy(orcnames[15],"Puyet");
	strcpy(orcnames[16],"Quyen");
	strcpy(orcnames[17],"Ront");
	strcpy(orcnames[18],"Shump");
	strcpy(orcnames[19],"Tanglar");
	strcpy(orcnames[20],"Ugarth");
	strcpy(orcnames[21],"Varg");
	strcpy(orcnames[22],"Wola");
	strcpy(orcnames[23],"Xork");
	strcpy(orcnames[24],"Yurk");
	strcpy(orcnames[25],"Zagga");
	//int monsternumber = game->opts.numMonsters;
	Creature *orcs = calloc(game->opts.numMonsters,sizeof(Creature));
	game->monsters = orcs;
	for(unsigned int i = 0;i<game->opts.numMonsters;i++){
		Creature *orc = &game->monsters[i];
		if(i == 68){
			strcpy(orc->name,"Bob the Easter egg");
			orc->sign = 'b';
		}
		else{
		strcpy(orc->name,orcnames[i%25]);
		if(i/26+1 == 2){
			strcat(orc->name," 2nd");
		}
		if(i/26+1 == 3){
			strcat(orc->name," 3rd");
		}
		strcat(orc->name," the orc");
		orc->sign = orc->name[0];
		}
		orc->hp = 8 + (rand()%5);
		orc->maxhp = 12;
		int succ = 0;
		while (succ == 0){
			int x = rand()%game->opts.mapWidth;
			int y = rand()%game->opts.mapHeight;
			int blocked = isBlocked(game,x,y);
			if((blocked)||((game->position.x==x)&&(game->position.y==y))){
				succ = 0;
			}
			else{
				orc->pos.x = x;
				orc->pos.y = y;
				succ = 1;
				printf("Succesfully positioned %s, orc number %d at %d,%d with sign %c\n",orc->name,i,orc->pos.x,orc->pos.y,orc->sign); //test
			}
		}
		orc->move = moveTowards;
		orc->attack = attackPunch;
	}
	for(int i = 0;i<26;i++){
		free(orcnames[i]);
	}
	free(orcnames);
	printf("monstercount is now %d\n",game->opts.numMonsters);
}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
