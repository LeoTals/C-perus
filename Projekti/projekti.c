#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projekti.h"

Character *add_char(Character *characters, char *input)
{
	//input mallia name hp weapon maxdmg
	char *token = strtok(input+2," ");
	if(!token){
		printf("Error, no input was found.\n");
		return 0;
		}
	char *name = calloc(strlen(token)+1,sizeof(char));
	if(!name){
		free(name);
		printf("Error while reserving memory for character name.\n");
		return 0;
	}
	strcpy(name,token);
	token = strtok(NULL," ");
	if(!token){
		printf("Error, input is incomplete.\n");
		free(name);
		return 0;
		}
	char *stop = token+strlen(token)+1;
	long int hp = strtol(token,&stop,10);
	token = strtok(NULL," ");
	if(!token){
		printf("Error, input is incomplete.\n");
		free(name);
		return 0;
		}
	char *weapon = calloc(strlen(token)+1,sizeof(char));
	if (!weapon){
		printf("Error while reserving memory for weapon name.\n");
		free(name);
		free(weapon);
		return 0;
	}
	strcpy(weapon,token);
	token = strtok(NULL," ");
	if(!token){
		printf("Error, input is incomplete.\n");
		free(name);
		free(weapon);
		return 0;
		}
	stop = token+strlen(token)+1;
	long int maxdmg = strtol(token,&stop,10);
	if(!(maxdmg>0)){
		printf("Error, a weapon must do more than 0 points of damage.\n");
		free(name);
		free(weapon);
		return 0;
	}
	long int xp = 0;
	if((token = strtok(NULL," "))){
		stop = token + strlen(token) + 1;
		xp = strtol(token,&stop,10);
	}
	int nmb = characters[0].NoC;
	Character *n = realloc(characters,(nmb+1)*sizeof(Character));
	n[nmb].name = name;
	n[nmb].hp = hp;
	n[nmb].xp = 0;
	n[nmb].weapon = weapon;
	n[nmb].maxdmg = maxdmg;
	n[nmb].tohit = 0;
	n[nmb].ac = 10;
	n[nmb].xp = xp;
	n[0].NoC++;
	printf("%s has been successfully created!\n",n[nmb].name);
	return n;
	
}
int attack(Character *characters, char *input)
{
	char *token = strtok(input+2," ");
	if(!token){return 0;}
	char *attacker = calloc(strlen(token)+1,sizeof(char));
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
	while(i < characters[0].NoC){
		int testattack = (strcmp(attacker, characters[i].name) ==0);
		int testdefence =(strcmp(defender, characters[i].name) ==0);
		
		if(!a&&testattack){
			a = characters + i;
		}
		if(!d&&testdefence){
			d = characters + i;
		}
		//debug function
		//printf("Checked %s   attacker - %d defender - %d\n",characters[i].name,testattack,testdefence);
		i++;
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
		return 0;
	}
	if(a->hp == 0){
		printf("Dead characters cannot attack.\n");
		free(attacker);
		free(defender);
		return 0;
	}
	int hitroll = 20-(rand()%20); //calculating hit
	int critical = 0;
	if(hitroll == 20){critical = 1;}
	int hit = hitroll + a->tohit;
	int hitsuccess = 0;
	if(hit>=d->ac){hitsuccess = 1;}
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
		if(a->name == d->name){
			xpgain = 0;
		}
		a->xp += xpgain;
		if (a->name == d->name){
			printf("%s attacks... Himself??\n",a->name);
		}
		else{
			printf("%s attacks %s with %s!\n",a->name,d->name,a->weapon);
		}
		printf("%s rolled a %d! That hits %s!\n",a->name,hitroll,d->name);
		if(critical){
			printf("Critical hit!\n");
		}
		printf("%s takes %d damage.",d->name,damagedone);
		if(overkill){
			printf(" Overkill!!\n");
		}
		else{
			printf("\n");
		}
		if(d->hp == 0){
			printf("%s dies, ",d->name);
		}
		printf("%s gains %d experience points.\n",a->name,xpgain);
		if (a->name == d->name){
			printf("What were you thinking, %s????\n",a->name);
		}
		free(attacker);
		free(defender);
		return 1;
	}
	else{ 							//print output on a failed attack.
		if(a->name == d->name){
			printf("%s missed... himself? What? How? Why?\n",a->name);
		}
		else{
			printf("%s rolled a %d! That is not enough to hit %s!\n",a->name,hit,d->name);
		}
		free(attacker);
		free(defender);
		return 1;
	}
		
}

int cmpxp(const void *a1,const void *b1)
{
	/* 
	 1. Kuollut hahmo lopussa
	 2. sort by xp
	*/
	int ret = 0;
	const Character *a = a1;
	const Character *b = b1;
	if (a->hp == 0 && b->hp != 0){
		ret = 1;
	}
	else if(b->hp == 0 && a->hp != 0){
		ret = -1;
	}
	else if(a->xp > b->xp){
		ret = -1;
	}
	else if(b->xp > a->xp){
		ret = 1;
	}
	else{
		ret = 0;
	}
	//test function
	//printf("Compared %s and %s, returned %d\n",a->name,b->name,ret);
	return ret;
}

int printc(Character *characters)
{
	int nmb = characters[0].NoC;
	//Count the number of characters
	qsort(characters,nmb,sizeof(Character),cmpxp);
	printf("%20s |  hp | %20s | dmg | hit |  AC | XP\n","Character name","Weapon");
	for(int i = 0;i<nmb;i++){
		Character c = characters[i];
		printf("%20s | %3ld | %20s | %3ld | %3ld | %3ld | %ld\n",c.name,c.hp,c.weapon,c.maxdmg,c.tohit,c.ac,c.xp);
	}
	return 1;
}
int save(Character *c, char *input)
{
	//mallia name hp weapon maxdmg
	FILE *f = fopen(input+2,"w");
	if(!f){
		printf("Error, failed to open file.\n");
		return 0;
	}
	for(int i = 0; i<c[0].NoC ; i++){
		fprintf(f,"%s %ld %s %ld %ld\n",c[i].name,c[i].hp,c[i].weapon,c[i].maxdmg,c[i].xp);
	}
	fclose(f);
	return 1;
}
Character *load(Character *characters,char *input)
{
	FILE *f = fopen(input+2,"r");
	if(!f){
		printf("Could not find/open file named \"%s\".\n",input+2);
		return NULL;
	}
	else{
		Character *newarray = calloc(1,sizeof(Character));
		newarray[0].NoC = 0;
		char *ptr = fgets(input+2,78,f);
		while(ptr){
			Character *success = add_char(newarray,input);
			if(!success){
				printf("Error, file contains invalid data.\n");
				fclose(f);
				return newarray;
			}
			else{
				newarray = success;
			}
			ptr = fgets(input+2,78,f);
		}
		if(newarray[0].NoC>0){
			printf("Game successfully loaded.\n");
			fclose(f);
			freeall(characters);
			free(characters);
			return newarray;
		}
		else{
			printf("Error, no characters in file.\n");
			fclose(f);
			return NULL;
		}
	}	
}
int ac_hit(Character *characters, char *input)
{
	char *token = strtok(input+2," ");
	if(!token){
		printf("Error, no input was found.\n");
		return 0;
		}
	char *name = calloc(strlen(token)+1,sizeof(char));
	if(!name){
		free(name);
		printf("Error while reserving memory for character name.\n");
		return 0;
	}
	strcpy(name,token);
	token = strtok(NULL," ");
	if(!token){
		printf("Error, input is incomplete.\n");
		free(name);
		return 0;
		}
	char *stop = token+strlen(token)+1;
	long int tohit = strtol(token,&stop,10);
	if(tohit == 0){
		if (strcmp(token,"0") != 0){
			printf("Error, invalid hit bonus.\n");
			free(name);
			return 0;
		}
	}
	token = strtok(NULL," ");
	if(!token){
		printf("Error, input is incomplete.\n");
		free(name);
		return 0;
		}
		stop = token+(strlen(token)+1);
	long int ac = strtol(token,&stop,10);
	if(ac == 0){
		if (strcmp(token,"0") != 0){
			printf("Error, invalid AC.\n");
			free(name);
			return 0;
		}
	}
	int found_it = 0;
	for(int i = 0; characters[i].name;i++){
		if (strcmp(name,characters[i].name) == 0){
			characters[i].tohit = tohit;
			characters[i].ac = ac;
			found_it = 1;
			break;
		}
	}
	if(!found_it){
		printf("Error, couldn't find character. Check spelling.\n");
		free(name);
		return 0;
	}
	else{
		printf("To hit and AC successfully set.\n");
		free(name);
		return 1;
	}
	
}
void explaindamage()
{
	printf("This game uses a 20 sided die, also known as a d20 for determining whether an attack hits.\n");
	printf("By default all characters have a 50%% chance of avoiding a hit.\n");
	printf("A character with an \"to hit\" bonus of more than 0 has a higher chance of hitting.\n");
	printf("A character with an armor class (ac) above 10 has a higher chance of avoiding damage.\n");
	printf("Use the \'P\' (for pro-mode) command to assign ac and to hit to a character.\n");
	printf("-----------------------------------------------------------------------------------\n");
	printf("Damage is determined by dividing the max damage by 6, and rolling that many six-sided-die or d6\n");
	printf("The leftover is added as a flat bonus to a damage roll, for example:\n");
	printf("If max damage is 13, that's 2 times 6 + 1, so the character will deal 2d6+1 damage.\n");
}
void freeall(Character *characters)
{
	int i = 0;
	int noc = characters[0].NoC;
	while(i<noc){
		free(characters[i].name);
		free(characters[i].weapon);
		i++;
	}
}

int main()
{
	srand(time(0)); //rng for attack and damage rolls
	int game = 0; //while loop variable
	printf("Welcome to Adventurers of Erypetra!\n");
	printf("Generating a new game.\n");
	size_t maxin = 80;
	Character *characters = calloc(1,sizeof(Character));
	char *bufferloc = calloc(maxin+1,sizeof(char));
	char *buffer = bufferloc;
	if(characters&&buffer){
		characters[0].NoC = 0;
		printf("Successfully created a new game.\n");
		game = 1;
	}
	else{
		free(characters);
		free(buffer);
		printf("Failed to create a game.\n");
		game = 0; 
	}
	
	printf("Please enter a command:\n");
	printf("type \"T\" to see full list of commands.\n");
	while(game){
		printf("\n>");
		int success = 0;
		fgets(buffer,maxin,stdin);
		if(feof(stdin)){
			buffer[0] = 'Q';
		}
		else{
			int li = 0;
			while(buffer[li]!='\0'){
				li++;
			}
			if(buffer[li-1]=='\n'){
				buffer[li-1] = '\0';
			}
		}
		Character *check;
		switch(buffer[0]){
			case 'A': //create character
				check = add_char(characters,buffer);
				if(!check){
					success = 0;
				}
				else{
					success = 1;
					characters = check;
				}
				break;
				
			case 'H': //attack 
				success = attack(characters,buffer);
				break;
				
			case 'L': //list
				success = printc(characters);
				break;
				
			case 'W': //save
				success = save(characters,buffer);
				break;
				
			case 'O': //load
				check = load(characters,buffer);
				if(!check){
					success = 0;
				}
				else{
					success = 1;
					characters = check;
				}
				break;
				
			case 'Q': //quit
				printf("Thanks for playing!\n");
				freeall(characters);
				game = 0;
				success = 1;
				break;
				
			case 'T': //tips
				printf("A name HP weapon maxdamage - create character.\n");
				printf("H attacker target - make two characters battle.\n");
				printf("L - Print a list of characters.\n");
				printf("W filename - save to a file.\n");
				printf("O filename - load from a file.\n");
				printf("T - display these tips.\n");
				printf("P charactername tohit armorclass - set a hit chance and an armor class.\n");
				printf("D - see how damage and combat is calculated.\n");
				printf("Q - quit.\n");
				success = 1;
				break;
				
			case 'P': //promode, ac and to hit
				success = ac_hit(characters,buffer);
				break;
				
			case 'D': //damage explanation
				explaindamage();
				success = 1;
				break;
				
			case 'F':
				printf("F o7\n");
				success = 1;
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