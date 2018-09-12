#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define sleep(x) Sleep(1000 * x) // credit to stack overflow

typedef struct Duration
{
	int Minutes;
	int Seconds;
}duration;

typedef struct Record
{
	char Artist[40];
	char Album_title[100];
	char song[100];
	char Genre[20];
	duration Song_length;
	int Number_times_played;
	int Rating;

}Record;

typedef struct Node
{
	Record data;
	struct Node *pNext, *pPrev;

}Node;

void main_menu(void); // main menu
Node* makeNode(Record Data); // make node function
int insert_at_front(Node **pList, Record Newdata); //insert new data to top of list
void load_records(Node **pList); // load records from csv
void store_data(Node *pList); // store data from csv
void display(Node *pList); // display the contents of the csv
void display_artist(Node *plist); // display a specific artist
void display_option(void); // option for user to display all artist or one artist
void edit_records(Node **pList); // edit a record's contents
Node* findNode(Node *pList, char* name);
void edit_rating(Node **pList); // edit the rating specifically
void play_songs(Node *pList); // display the song on the terminal for a certain amount of time then go to another record
void insert_song(Node **pList); // insert record
void delete_song(Node **pList); // delete song
int size_ofList(Node *pLists); // determine size of the list
void sort(Node **pList); // sort the list depending on condition
void shuffle(Node **pList); // shuffle the playlist