/*
Programmer: Chike Egwuatu
Class: Cpts 121, Spring 2018,
Programmer Assignment: Pa2
Date: January,27,2018
Description: Compile a Music Manager using Linked List and double stars. While also
Using structs.
*/
// Had Help with PA from Jovan private tutor

#include "Header.h"
int main(void)
{
	srand(time(NULL));
	Node *phead = NULL;
	int menu_option = 0, display_menu = 0;
	// while loop for the main menu
	while (menu_option != 11) // while loop that loops until exit has been executed
	{
		main_menu(); // call main menu
		printf("\nEnter An option: "); // enter which option
		scanf("%d", &menu_option); // scan the entered option
		if (menu_option == 1) // execute load records
		{
			load_records(&phead);
			system("cls");
			printf("Music files have been loaded\n\n");
			system("pause");
			system("cls");
		}
		else if (menu_option == 2) // execute store data
		{
			store_data(phead);
			system("cls");
			printf("Music files have been stored\n\n");
			system("pause");
			system("cls");
		}
		else if (menu_option == 3) // execute display artist or display specific artist
		{
			display_option();
			printf("\nEnter Option 1 or 2: "); 
			scanf("%d", &display_menu);
			if (display_menu == 1) // display all artist
			{
				system("pause");
				system("cls");
				display(phead);
				printf("\n");
				system("pause");
				system("cls");
			}
			else if (display_menu == 2) // display a specific artist
			{
				system("pause");
				system("cls");
				display_artist(phead); // display specific Artist
				printf("\n");
				system("pause");
				system("cls");
			}
		}
		else if (menu_option == 4) //insert a new song
		{
			system("pause");
			system("cls");
			insert_song(&phead);
			system("pause");
			system("cls");
		}
		else if (menu_option == 5) //delete a song
		{
			system("pause");
			system("cls");
			delete_song(&phead);
			system("pause");
			system("cls");
		}
		else if (menu_option == 6) // edit a certain record in the csv
		{
			system("pause");
			system("cls");
			edit_records(&phead); // function to edit records
			system("pause");
			system("cls");
		}
		else if (menu_option == 7) // sort the list by a certain condition
		{
			system("pause");
			system("cls");
			sort(&phead);
			system("pause");
			system("cls");
		}
		else if (menu_option == 8) // edit the rating of a certain record
		{
			system("pause");
			system("cls");
			edit_rating(&phead); // function to specificly edit rating
			system("pause");
			system("cls");
		}
		else if (menu_option == 9) // play the song for a certain amount of time
		{
			system("pause");
			system("cls");
			play_songs(phead); // function to play a song
			system("pause");
			system("cls");
		}
		else if (menu_option == 10) // shuffle function
		{
			system("pause");
			system("cls");
			shuffle(&phead);
			system("pause");
			system("cls");
		}
		else if (menu_option == 11) // exit and store the data
		{
			system("cls");
			store_data(phead); // function to store data
			printf("****Music Files have been saved****\n\n\n");
			system("pause");
			system("cls");

		}
	}
}