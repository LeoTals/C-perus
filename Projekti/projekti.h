#ifndef FIGHTERBOIS
#define FIGHTERBOIS

typedef struct character{
	char *name;
	long int hp;
	long int xp;
	char *weapon;
	long int maxdmg;
	long int tohit;
	long int ac;
	unsigned int NoC; //number of characters, stored in the first character
} Character;

Character *add_char(Character *characters, char *input);
int attack(Character *characters,char *input);
int printc(Character *characters);
int save(Character *characters, char *input);
Character *load(Character *characters, char *input);
int ac_hit(Character *characters, char *input);
void explaindamage();
void freeall(Character *characters);

#endif