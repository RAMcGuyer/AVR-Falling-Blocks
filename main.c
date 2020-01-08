/*
 * Partners: Ross McGuyer (rmcgu002@ucr.edu)
 *       
 * Lab Section: 023
 * Assignment: Final Project
 *  
 * I acknowledge all content contained herein, excluding template or example
 *   code, is my own work. 
 *
 * Base Nokia 5110 library provided by littleBuster (https://github.com/LittleBuster/avr-nokia5110),
 *    and used under GPL 3.0.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nokia5110/nokia5110.h"
#include "nokia5110/nokia5110.c"

#define spaceChar  0x20
#define blockChar  0x7F
#define heartChar  0x80
#define playerChar 0x81

char loc[14][7];
unsigned short score = 0;				
unsigned char playGame = 0;

unsigned char left;
unsigned char right;
unsigned char resetButton;

void init_grid(){
	for (unsigned char i = 0; i < 14; i++)
	{
		for(unsigned char j = 0; j < 7; j++){
				loc[i][j] = spaceChar;
		}
	}
}
//Reads the location array and writes the
void readGrid(){
	uint8_t x_cursor;
	uint8_t y_cursor;
	nokia_lcd_clear();
	for(unsigned char i = 0; i < 14; i++){
		for(unsigned j = 0; j < 7; j++){
			x_cursor = 6*i;
			y_cursor = 2 + j*6;
			
			nokia_lcd_set_cursor(x_cursor, y_cursor);
			nokia_lcd_write_char(loc[i][j], 1);
			
		}
	}
}



unsigned char index0 = 0, index1 = 0, index2 = 0, index3 = 0, index4 = 0, index5 = 0, index6 = 0, index7 = 0, index8 = 0,
index9 = 0, index10 = 0, index11 = 0, index12 = 0, index13 = 0;
char col0[] = {spaceChar, blockChar, spaceChar, blockChar, heartChar, spaceChar, spaceChar, blockChar, spaceChar, spaceChar, spaceChar}; // col 0, size 11
char col1[] = {spaceChar, spaceChar, spaceChar, spaceChar, heartChar, blockChar, spaceChar}; // col 1, size 7
char col2[] = {spaceChar, spaceChar, blockChar, spaceChar, spaceChar, spaceChar, spaceChar, blockChar, spaceChar}; // col 2, size 9
char col3[] = {spaceChar, spaceChar, spaceChar, blockChar, spaceChar, blockChar, blockChar, heartChar, spaceChar, spaceChar, blockChar, spaceChar, spaceChar}; // col 3, size 13
char col4[] = {blockChar, spaceChar, blockChar, spaceChar, spaceChar, spaceChar, heartChar, spaceChar, spaceChar, blockChar, spaceChar, spaceChar, blockChar, spaceChar, heartChar, blockChar}; // col 4, size 16
char col5[] = {spaceChar, spaceChar, spaceChar, spaceChar, blockChar, blockChar, spaceChar, blockChar, spaceChar, spaceChar, heartChar, blockChar}; // col 5, size 12
char col6[] = {spaceChar, spaceChar, blockChar, blockChar, spaceChar, spaceChar, blockChar, spaceChar, spaceChar, blockChar, spaceChar}; // col 6, size 11
char col7[] = {blockChar, blockChar, spaceChar, spaceChar, spaceChar, blockChar, spaceChar}; // col 7, size 7
char col8[] = {spaceChar, blockChar, spaceChar, spaceChar, spaceChar, spaceChar, spaceChar, spaceChar, spaceChar, heartChar, blockChar, blockChar, blockChar, spaceChar, spaceChar}; // col 8, size 15
char col9[] = {spaceChar, spaceChar, blockChar, spaceChar, spaceChar, blockChar, spaceChar, blockChar, blockChar, spaceChar, spaceChar, spaceChar, spaceChar, spaceChar}; // col 9, size 14
char col10[] = {blockChar, spaceChar, spaceChar, spaceChar, blockChar, spaceChar, blockChar, spaceChar, heartChar}; // col 10, size 9
char col11[] = {blockChar, spaceChar, spaceChar, blockChar, heartChar, blockChar, spaceChar, spaceChar, spaceChar, spaceChar, blockChar}; // col 11, size 11
char col12[] = {spaceChar, blockChar, spaceChar, spaceChar, spaceChar, blockChar, spaceChar, blockChar, spaceChar, heartChar, blockChar, spaceChar}; // col 12, size 12
char col13[] = {spaceChar, spaceChar, blockChar, spaceChar, blockChar, spaceChar, heartChar, spaceChar, spaceChar}; // col 13, size 9

char getColumnByIndex(unsigned char in){
	char code = 0x23; // # <--- Error symbol
		if(in == 0)
		{
			if(index0 > 10){index0 = 0;}
			code = col0[index0];
			index0++;
			}
		else if(in == 1){
			if(index1 > 6){index1 = 0;}
			code = col1[index1];
			index1++;
			}
		else if(in == 2){
			if(index2 > 8){index2 = 0;}
			code = col2[index2];
			index2++;
			}
		else if(in == 3){
			if(index3 > 12){index3 = 0;}
			code = col3[index3];
			index3++;
			}
		else if(in == 4){
			if(index4 > 15){index4 = 0;}
			code = col4[index4];
			index4++;
			}
		else if(in == 5){
			if(index5 > 11){index5 = 0;}
			code = col5[index5];
			index5++;
			}
		else if(in == 6){
			if(index6 > 10){index6 = 0;}
			code = col6[index6];
			index6++;
			}
		else if(in == 7){
			if(index7 > 6){index7 = 0;}
			code = col7[index7];
			index7++;
			}
		else if(in == 8){
			if(index8 > 14){index8 = 0;}
			code = col8[index8];
			index8++;
			}
		else if(in == 9){
			if(index9 > 13){index9 = 0;}
			code = col9[index9];
			index9++;
			}
		else if(in == 10){
			if(index10 > 8){index10 = 0;}
			code = col10[index10];
			index10++;
			}
		else if(in == 11){
			if(index11 > 10){index11 = 0;}
			code = col11[index11];
			index11++;
			}
		else if(in == 12){
			if(index12 > 11){index12 = 0;}
			code = col12[index12];
			index12++;
			}
		else if(in == 13){
			if(index13 > 8){index13 = 0;}
			code = col13[index13];
			index13++;
			}
		else{
			code = 0x023; // # <--- Error symbol
		}
	
	return code;
}

unsigned char collision = 0;
void shift(){
	for (unsigned char h = 14; h > 0; --h)
	{
		for(unsigned char k = 7; k > 0; --k)
		{
			if(loc[h-1][k-1] != playerChar)
			{
				if(k > 1)
				{
					loc[h-1][k-1] = loc[h-1][k-2];	
				}
				else if(k == 1)
				{
					loc[h-1][k-1] = getColumnByIndex(h-1);
				}
			}
			else if(loc[h-1][k-1] == playerChar){
				if(loc[h-1][k-2] == blockChar){
					collision = 1;
				}
				else if(loc[h-1][k-2] == heartChar){
					score++;
				}
			}
		}
	}
}

void displayScore(){
	nokia_lcd_clear();
	unsigned char ones = (score % 10);
	unsigned char tens = ((score % 100) / 10);
	unsigned char hundreds = ((score % 1000) / 100);
	unsigned char thousands = ((score % 10000) / 1000);
	
	nokia_lcd_set_cursor(5, 10);
	nokia_lcd_write_string("Score: ", 1);
	
	if(thousands > 0){
		nokia_lcd_set_cursor(45, 10);
		nokia_lcd_write_char(thousands+0x30, 1);	
	}
	if(hundreds > 0){
		nokia_lcd_set_cursor(51, 10);
		nokia_lcd_write_char(hundreds+0x30, 1);
	}
	if(tens > 0){
		nokia_lcd_set_cursor(57, 10);
		nokia_lcd_write_char(tens+0x30, 1);
	}	
	
	nokia_lcd_set_cursor(63, 10);
	nokia_lcd_write_char(ones+0x30, 1);
	nokia_lcd_render();
}

// ********************************************* //
// 		      END OF HELPER FUNCTIONS            //
// ********************************************* //

unsigned char gameCtr = 0;
unsigned char playerAt;
unsigned playerNext;
unsigned speedLevel;
enum Game_States {start, warmUp, play, stop, reset} game_state;
int gameTick(int game_state){
	
	//Transitions
	switch(game_state){
		case start :
			init_grid();
			playerAt = 7;
			playerNext = playerAt;
			game_state = warmUp;
			score = 0;
			speedLevel = 0;
			break;
		case warmUp :
			if(resetButton){game_state = reset;}
			else{
				game_state = (gameCtr < 60) ? warmUp : play;
			}
			break;	
		case play :
			if(resetButton){game_state = reset;}
			else{game_state = (collision == 0) ? play : stop;}
			break;
		case stop :
			if(resetButton){game_state = reset;}
			else{game_state = stop;}
			break;
		case reset :
			game_state = start;
			playGame = 0;
			collision = 0;
			gameCtr = 0;
			break;
	}
	
	//Actions
	switch(game_state){
		case start :
		break;
		case warmUp :
			gameCtr++;
		break;
		case play :
			playGame = 1;
		break;
		case stop :
			playGame = 0;
		break;
		case reset :
			playGame = 2;
		break;
	}
	
	return game_state;
}

enum Block_States {off, resting, fall} block_state;
unsigned char cnt = 0;
unsigned char speed = 10;
int blockTick(int block_state){
	
	//Transitions
	switch(block_state){
		case off :
			speed = 10;
			block_state = (playGame == 0) ? off : resting;
		break;
		case resting :
			if (cnt >= speed){
				block_state = (playGame == 1) ? fall : off;;
				cnt = 0;	
			}
			else
				block_state = resting;
			break;
		
	   case  fall :
			block_state = (playGame == 1) ? resting : off;
			if(speed < 30){
				speedLevel++;
			}
			if(speedLevel > 30){
				speed = 4;
			}
			else if(speedLevel > 15){
				speed = 7;
			}
			break;	
	}
	// Actions
	
	switch(block_state){
		case off :
			break;
		case resting :
			cnt++;
			break;
		
	 case fall :
		shift();
		break;
	}
	return block_state;
}


enum Player_States {noControl, wait, move, release} player_state;
int playerTick(int player_state){
		
		//Transitions
		switch(player_state){
			
			case noControl :
				player_state = (playGame  == 1) ? wait : noControl;
				break;
			case wait:
			if(playGame !=1){player_state = noControl;}
			else{
				if(left || right)
				{
					player_state = move;		
				}
				else{player_state = wait;}
				}
			break;
			case move :
			if(playGame !=1){player_state = noControl;}
			else{
				player_state = release;
			}
			break;
			case release :
			if(playGame !=1){player_state = noControl;}
			else{
				if(left || right){
					player_state = release;
				}
				else{
					player_state = wait;
				}
			}
			break;
		}
		//Actions
		
		switch(player_state){
			case noControl :
				break;
			case wait :
				break;
			case move :
				if((left && right) || (!left && !right)){
					playerNext = playerAt;
				}
				else if(left && !right){
					if(playerAt > 0){
						playerNext = playerAt -1;
					}
				}
				else if(!left && right){
					if(playerAt < 13){
						playerNext = playerAt +1;
					}
				}
				break;
			case release :
				break;
		}
		
		if(loc[playerNext][6] == blockChar){
			collision = 1;
		}
		else if(loc[playerNext][6] == heartChar){
			score++;
			loc[playerAt][6] = spaceChar;
			loc[playerNext][6] = playerChar;
		}
		else{
			loc[playerAt][6] = spaceChar;
			loc[playerNext][6] = playerChar;
		}
		
		playerAt = playerNext;
		return player_state;
	}


enum Display_States {pregame, game, gameover, postgame, resetScreen} display_state;
unsigned char dispCtr = 0;
int displayTick(int display_state){
	
	//Transitions
	switch(display_state){
		case pregame:
			if(playGame == 0){
				display_state = pregame;
			}
			else if(playGame == 1){
				display_state = game;
			}
			else if(playGame == 2){
				display_state = resetScreen;
			}
			break;
		case game :
			if(playGame == 0){
				display_state = gameover;
			}
			else if(playGame == 1){
				display_state = game;
			}
			else if(playGame == 2){
					display_state = resetScreen;
			}
			break;
		case gameover :
			if(playGame == 0 && dispCtr < 30){
				display_state = gameover;
			}
			else if(playGame == 1){
				display_state = game;
			}
			else if(playGame == 2){
				display_state = resetScreen;
			}
			else{
				display_state = postgame;
				dispCtr = 0;
			}
			break;
		case postgame :
			if(playGame == 2){
				display_state = resetScreen;
			}
			else{
				display_state = postgame;
			}
			break;
		case resetScreen :
			display_state = pregame;
			break;
	}
		
	//Actions
	switch(display_state){
		case pregame :
			nokia_lcd_clear();
			nokia_lcd_set_cursor(10, 7);
			nokia_lcd_write_string("Avoid the", 1);
			nokia_lcd_set_cursor(25, 14);
			nokia_lcd_write_string("blocks.", 1);
			nokia_lcd_set_cursor(10, 28);
			nokia_lcd_write_string("Catch the", 1);
			nokia_lcd_set_cursor(25, 35);
			nokia_lcd_write_string("hearts.", 1);
			nokia_lcd_render();
		break;
		case game :
			nokia_lcd_clear();
			readGrid();
			nokia_lcd_render();
		break;
		case gameover :
		nokia_lcd_clear();
		nokia_lcd_set_cursor(20, 7);
		nokia_lcd_write_string("GAME", 2);
		nokia_lcd_set_cursor(20, 28);
		nokia_lcd_write_string("OVER", 2);
		nokia_lcd_render();
		dispCtr++;
		break;
		case postgame :
			displayScore();
		break;
		case resetScreen :
			nokia_lcd_clear();
			break;
	}
	return display_state;
}

// End of tick Functions

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	
	nokia_lcd_init();
	nokia_lcd_clear();
	
	int playerTracker = noControl;
	int gameTracker = start;
	int testState = pregame;
	int fallingStateTest = off;
	while(1){
		
		resetButton = ~PINA & 0x01;
		right = ~PINA & 0x02;
		left = ~PINA & 0x04;
		gameTracker = gameTick(gameTracker);
		testState = displayTick(testState);
		playerTracker = playerTick(playerTracker);
		fallingStateTest = blockTick(fallingStateTest);
	_delay_ms(10);
		
	}
	
	return 0;
}

