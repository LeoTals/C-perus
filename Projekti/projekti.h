#ifndef FIGHTERBOIS
#define FIGHTERBOIS

typedef struct character{
	char *name;
	int hp;
	int xp;
	char *weapon;
	int maxdmg;
	int tohit;
	int ac;
} Character;

int add_char(Character *characters, char *input);
int attack(Character *characters,char *input);
int printc(Character *characters);
int save(Character *characters, char *input);
int load(Character *characters, char *input);
int ac_hit(Character *characters, char *input);
void explaindamage();
void freeall(Character *characters);

#endif