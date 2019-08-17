#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projekti.h"

int add_char(Character *characters, char *input)
{
	
}
int attack(Character *characters, char *input)
{
	char *token = strtok(input," ");
	if(!token){return 0;}
	char *attacker = calloc(strlen(token+1),sizeof(char));
	strcpy(attacker,token);
	token = strtok(NULL," ");
	if(!token){
		free(attacker);
		return 0;
		}
	char *defender = calloc(strlen(token)+1,sizeof(char));
	strcpy(defender,token);
	int i = 0;
	Character *a = NULL;
	Character *d = NULL;
	while(characters->name){
		if(!a&&(strcmp(attacker,characters[i].name)==0)){
			a = characters + i;
		}
		if(!d&&(strcmp(defender,characters[i].name)==0)){
			d = characters + i;
		}
	}
	if(!a||!d){
		printf("Couldn't find characters. Check spelling.\n");
		free(attacker);
		free(defender);
		return 0;
	}
	if(d->hp == 0){
		printf("Target is already dead.\n");
		free(attacker);
		free(defender);
		return 1;
	}
	if(a->hp == 0){
		printf("Dead characters cannot attack.\n");
	
	int hitroll = 20-(rand()%20);
	int critical = 0;
	if(hitroll == 20){critical = 1;}
	int hit = hitroll + a->tohit;
	int hitsuccess = 0;
	if(hit>d->ac){hitsuccess = 1;}
	int dmgdice = a->maxdmg/6;
	int flatbonus = a->maxdmg%6;
	int damagedone = 0;
	
	if(hitsuccess){		//Calculate damage and print output for successfull attack.
		int dicedamage = 0;
		for(int roll = 0;roll<dmgdice;roll++){
			dicedamage += (6 - (rand()%6));
		}
		if(critical){dicedamage *= 2;}	//crits double rolled damage, but not the flat damage.
		damagedone += dicedamage;
		damagedone += flatbonus;
		int overkill = 0;
		if(damagedone > d->hp){ //overkill
			d->hp = 0;
			overkill = 1;
		}
		else{
			d->hp -= damagedone;
		}											//output print for successful hits
		int xpgain = 0;
		xpgain += damagedone;
		if(d->hp == 0){
			xpgain = xpgain * 3;
			xpgain = xpgain / 2;
		}
		a->xp += xpgain;
		printf("%s rolled a %d! That hits %s!\n");
		if(critical){
			printf("Critical hit!\n");
		}
		printf("%s takes %d damage.");
		if(overkill){
			printf(" Overkill!!\n");
		}
		else{
			printf("\n");
		}
		if(d->hp == 0){
			printf("%s dies, ",%d->name);
		}
		printf("%s gains %d experience points.\n",a->name,xpgain);
		free(attacker);
		free(defender);
		return 1;
	}
	else{ //print output on a failed attack.
		printf("%s rolled a %d! That is not enough to hit %s!\n",a->name,hit,d->name);
		free(attacker);
		free(defender);
		return 1;
	}
		
}
int printc(Character *characters)
{
	
}
int save(Character *characters)
{
	
}
int load(Character *characters,char *input)
{
	FILE *f = fopen(input+2,"r");
	if(!f){
		printf("Could not find/open file named \"%s\".\n",input+2);
		return 0;
	}
	else{
		int added = 0;
		freeall(characters);
		realloc(characters,sizeof(Character));
		characters[0].name = NULL;
		fgets(input+2,78,f);
		while((feof(f)==0)&&(ferror(f)==0)){
			int success = add_char(characters,input);
			if(!success){
				printf("Error, file contains invalid data.\n");
				return 0;
			}
			else{
				added++;
			}
			fgets(input+2,78,f);
		}
		if(added>0){
			printf("Game successfully loaded.\n");
			return 1;
		}
		else{
			printf("Error, no characters in file.\n");
			return 0;
		}
	fclose(f);
	}	
}
int ac_hit(Character *characters, char *input)
{
	
}
void explaindamage()
{
	printf("This game uses a 20 sided die, also known as a d20 for determining whether an attack hits.\n");
	printf("By default all characters have a 50\% chance of avoiding a hit.\n");
	printf("A character with an \"to hit\" bonus of more than 0 has a higher chance of hitting.\n");
	printf("A character with an armor class (ac) above 10 has a higher chance of avoiding damage.\n");
	printf("Use the \'P\' (for pro-mode) command to assign ac and to hit to a character.\n")
	printf("-----------------------------------------------------------------------------------\n");
	printf("Damage is determined by dividing the max damage by 6, and rolling that many six-sided-die or d6\n");
	printf("The leftover is added as a flat bonus to a damage roll, for example:\n");
	printf("If max damage is 13, that's 2 times 6 + 1, so the character will deal 2d6+1 damage.\n");
}
void freeall(Character *characters){
	int i = 0;
	while(characters[i].name){
		free(characters[i].name);
		free(characters[i].weapon);
	}
}

int main()
{
	srand(time(0)); //rng for attack and damage rolls
	int game = 0; //while loop variable
	printf("Welcome to Adventurers of Erypetra!\n");
	printf("Generating a new game.\n");
	Character *characters = calloc(1,sizeof(Character));
	char *bufferloc = calloc(81,sizeof(char));
	char *buffer = bufferloc;
	if(characters&&buffer){
		characters[0].name = NULL;
		printf("Successfully created a new game.\n");
		game = 1
	}
	else{
		free(characters);
		free(buffer);
		printf("Failed to create a game.\n");
		game = 0; 
	}
	
	printf("Please enter a command:\n");
	printf("type \"H\" to see full list of commands.\n");
	while(game){
		printf("\n>");
		int success = 0;
		getline(buffer,80);
		if(feof(stdin)){
			buffer[0] = 'Q';
		}
		switch(buffer[0]){
			case 'A': //create character
				success = add_char(characters);
				break;
			case 'H': //attack 
				success = attack(characters)
				break;
			case 'L': //list
				success = printc(characters);
				break;
			case 'W': //save
				success = save(characters);
				break;
			case 'O': //load
				success = load(characters);
				break;
			case 'Q': //quit
				printf("Thanks for playing!\n");
				freeall(characters);
				free(buffer);
				game = 0;
				break;
			case 'H': //help
				printf("A name HP weapon maxdamage - create character.\n");
				printf("H attacker target - make two characters battle.\n");
				printf("L - Print a list of characters.\n");
				printf("W filename - save to a file.\n");
				printf("O filename - load from a file.\n");
				printf("H - display these hints.\n");
				printf("P charactername tohit armorclass - set a hit chance and an armor class.\n");
				printf("D - see how damage and combat is calculated.\n");
				printf("Q - quit.\n");
				break;
			case 'P': //promode, ac and to hit
				success = ac_hit(characters);
				break;
			case 'D': //damage explanation
				explaindamage();
				break;
			default:
				printf("I am sorry, I cannot let you do that. (invalid input)\n");
				success = 1;
		}
		if(!success){
			printf("Action not successful.\n");
		}
		
	}
	free(characters);
	free(bufferloc);
	return 0;
}