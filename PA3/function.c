#include "Header.h"

//function for the main menu
void main_menu(void)
{
	printf("*Digital Music Manager Menu*\n\n");
	printf("1. Load\n");
	printf("2. Store\n");
	printf("3. Display\n");
	printf("4. Insert\n");
	printf("5. Delete\n");
	printf("6. Edit\n");
	printf("7. Sort\n");
	printf("8. Rate\n");
	printf("9. Play\n");
	printf("10. Shuffle\n");
	printf("11. Exit\n");
}
// function to create Node block
Node* makeNode(Record NewData)
{
	Node *pMem = (Node*)malloc(sizeof(Node));
	if (pMem != NULL)
	{
		pMem->pNext = NULL; // points pmen to next
		pMem->pPrev = NULL; // points pmem to previus node
		pMem->data = NewData;
	}
	return pMem; // returns pMem
}

int insert_at_front(Node **pList, Record Newdata)
{
	Node *pMem = makeNode(Newdata);
	int success = 0;
	if (pMem != NULL) // if pMem is not empty, seperate data
	{
		success = 1; // set condition to 1
		if (*pList == NULL) // If *Plist is empty
		{
			*pList = pMem;
		}
		else
		{
			(*pList)->pPrev = pMem;
			pMem->pNext = *pList; // points pMem pNext to the pointer *plist
			*pList = pMem; //*plist address is now set to pMem
		}
	}
}

void load_records(Node **pList)
{
	FILE *infile = NULL; // initialize file
	char *token = NULL; // initialize token
	Record NewData; // initialize data
	char line[100] = "", copyLine[100] = "";
	char temp[100] = "";
	infile = fopen("music.csv", "r");
	//int i = 1;
	if (infile != NULL) // if file does have data
	{
		while (!feof(infile)) // read end of file
		{
			fgets(line, 100, infile);
			if (strcmp(line, temp) != 0)
			{
				strcpy(copyLine, line);
				strcpy(temp, line);
				if (copyLine[0] == '\"') // for the condition "last,name"
				{
					token = strtok(copyLine, " ");
					strcpy(NewData.Artist, token);
					token = strtok(NULL, ",");
					strcat(NewData.Artist, " ");
					strcat(NewData.Artist, token);
				}
				else // run if there is no "last,name"
				{
					token = strtok(copyLine, ",");
					strcpy(NewData.Artist, token);
				}
				token = strtok(NULL, ",");
				strcpy(NewData.Album_title, token); // record data into struct
				token = strtok(NULL, ",");
				strcpy(NewData.song, token);
				token = strtok(NULL, ",");
				strcpy(NewData.Genre, token);
				token = strtok(NULL, ":");
				NewData.Song_length.Minutes = atoi(token);
				token = strtok(NULL, ",");
				NewData.Song_length.Seconds = atoi(token);
				token = strtok(NULL, ",");
				NewData.Number_times_played = atoi(token);
				token = strtok(NULL, "\n");
				NewData.Rating = atoi(token);
				insert_at_front(pList, NewData); // insert new node into the new record data to the front of the list
			}
		}

	}
	fclose(infile); // close file
}

void store_data(Node *pList)
{
	FILE *infile = NULL;
	infile = fopen("music.csv", "w");
	while (pList != NULL)
	{
		if (pList->pNext != NULL) // if list that points to next is null then proceed to print file
		{
			fprintf(infile, "%s,", pList->data.Artist); // store the data into the file
			fprintf(infile, "%s,", pList->data.Album_title);
			fprintf(infile, "%s,", pList->data.song);
			fprintf(infile, "%s,", pList->data.Genre);
			fprintf(infile, "%d:", pList->data.Song_length.Minutes);
			fprintf(infile, "%d,", pList->data.Song_length.Seconds);
			fprintf(infile, "%d,", pList->data.Number_times_played);
			fprintf(infile, "%d\n", pList->data.Rating);
			pList = pList->pNext;
		}
		else
		{
			fprintf(infile, "%s,", pList->data.Artist);
			fprintf(infile, "%s,", pList->data.Album_title);
			fprintf(infile, "%s,", pList->data.song);
			fprintf(infile, "%s,", pList->data.Genre);
			fprintf(infile, "%d:", pList->data.Song_length.Minutes);
			fprintf(infile, "%d,", pList->data.Song_length.Seconds);
			fprintf(infile, "%d,", pList->data.Number_times_played);
			fprintf(infile, "%d", pList->data.Rating);
			pList = pList->pNext;
		}
	}
	fclose(infile);
}

//print All artist records
void display(Node *pList)
{
	printf("Album,Album Title,Song,Genre,Song-Length,Numberoftimesplayed,Rating\n\n");
	while (pList != NULL)
	{
		printf("%s,", pList->data.Artist);
		printf("%s,", pList->data.Album_title);
		printf("%s,", pList->data.song);
		printf("%s,", pList->data.Genre);
		printf("%d:", pList->data.Song_length.Minutes);
		printf("%d,", pList->data.Song_length.Seconds);
		printf("%d,", pList->data.Number_times_played);
		printf("%d\n", pList->data.Rating);
		pList = pList->pNext;
	}
}

//print certain record of artist
void display_artist(Node *pList)
{
	char artist[100], artist_name[100];
	int success = 0;
	printf("If the Artist has two names,\nPlease enter it as \"Last Name, First Name\" And If they only have one name Enter their name:"); // Tell user instructions
	scanf("%s", &artist_name); // scan the given name
	if (artist_name[0] == '\"') // a condition for names with " " in them and also a comma
	{
		scanf("%s", &artist); // scan the additional name
		strcat(artist_name, " "); // combine the names
		strcat(artist_name, artist);
	}
	printf("\n");
	while (pList != NULL)
	{
		if (strcmp(pList->data.Artist, artist_name) == 0) // If the name matches the dta then print the Artist Record
		{
			printf("%s,", pList->data.Artist); // Print Artist 
			printf("%s,", pList->data.Album_title); // print Album Title
			printf("%s,", pList->data.song);
			printf("%s,", pList->data.Genre);
			printf("%d:", pList->data.Song_length.Minutes);
			printf("%d,", pList->data.Song_length.Seconds);
			printf("%d,", pList->data.Number_times_played);
			printf("%d\n", pList->data.Rating);
			success = 1;
		}
		pList = pList->pNext; // point to the next
	}
	if (success != 1) // if they could not find Artist print to user artist wasnt found
	{
		printf("\n\nArtist Was not Found");
	}
}

//function to display options for printing records
void display_option(void)
{
	printf("\n**Display Options**\n\n");
	printf("1.Print All Records\n");
	printf("2.Print a record to a specific Artist\n");
}

//function to find node 
Node* findNode(Node *pList, char* name)
{
	Node *pTemp = pList;
	if (pTemp != NULL)
	{
		while (pTemp != NULL && strcmp(pTemp->data.Artist, name) != 0)
		{
			pTemp = pTemp->pNext;
		}
	}
	return pTemp;
}


//function to edit certain record
void edit_records(Node **pList)
{
	char artist[100], artist_name[100], new_name[100], new_nameplus[100], new_albumtitle[100], new_album_title_plus[100], new_song[100], new_songplus[100];
	char new_genre[100], new_genreplus[100];
	char new_songlength_minutes[100], new_songlength_minutes_plus[100], new_song_length_seconds[100], new_song_lenth_secondsplus[100];
	char new_timesplayed[100], new_timesplayedplus[100], new_rating[100], new_rating_plus[100];
	int success = 0, i = 0, record_number = 0, edit_record = 0;
	Node *pTemp = NULL;
	Node *MatchingNodes[50] = { NULL };
	printf("If the Artist has two names,\nPlease enter it as \"Last Name, First Name\" And If they only have one name Enter their name:");
	scanf("%s", &artist_name); // scan name
	gets(artist); // get the second part of the name
	strcat(artist_name, artist); // attach second part of name to the first part of the name
	MatchingNodes[i] = findNode(*pList, &artist_name);
	printf("\n");
	while (MatchingNodes[i] != NULL)
	{
		//pTemp = findNode(*pList, &artist);
		//MatchingNodes[i] = pTemp;
		//i++;
		printf("%d. ", i + 1);
		printf("%s,", MatchingNodes[i]->data.Artist);
		printf("%s,", MatchingNodes[i]->data.Album_title);
		printf("%s,", MatchingNodes[i]->data.song);
		printf("%s,", MatchingNodes[i]->data.Genre);
		printf("%d:", MatchingNodes[i]->data.Song_length.Minutes);
		printf("%d,", MatchingNodes[i]->data.Song_length.Seconds);
		printf("%d,", MatchingNodes[i]->data.Number_times_played);
		printf("%d\n", MatchingNodes[i]->data.Rating);
		i++;
		MatchingNodes[i] = findNode(MatchingNodes[i - 1]->pNext, &artist_name);
	}
	if (MatchingNodes[0] == NULL)
	{
		printf("Record Was not Found\n\n");
	}
	else
	{
		printf("\nWhich Record Would you like to edit: ");
		scanf("%d", &record_number); // scan the certain record
		printf("\nEdit:\n1.Artist\n2.Album Title\n3.Song\n4.Genre\n5.Song_length\n6.Numberoftimesplayed\n7.Rating\n");
		printf("\nChoose what you would like to edit: "); // choose what you would like to edit
		scanf("%d", &edit_record);
		switch (edit_record) // create a switch statement for the case.....
		{
		case 1: // change artist name
			printf("Enter the New name of the Arist: ");
			scanf("%s", &new_name);
			gets(new_nameplus);
			strcat(new_name, new_nameplus);
			strcpy(MatchingNodes[record_number - 1]->data.Artist, new_name);
			store_data(*pList);
			printf("The Artist Name has been Changed!\n");
			break;
		case 2:
			printf("Enter the new Album Title: ");
			scanf("%s", &new_albumtitle);
			gets(new_album_title_plus);
			strcat(new_albumtitle, new_album_title_plus);
			strcpy(MatchingNodes[record_number - 1]->data.Album_title, new_albumtitle);
			store_data(*pList);
			printf("The Album Title has been changed and stored\n");
			break;
		case 3:
			printf("Enter the new song name: ");
			scanf("%s", &new_song);
			gets(new_songplus);
			strcat(new_song, new_songplus);
			strcpy(MatchingNodes[record_number - 1]->data.song, new_song);
			store_data(*pList);
			printf("The new Song has been changed and stored\n");
			break;
		case 4:
			printf("Enter the new Genre: ");
			scanf("%s", &new_genre);
			gets(new_genreplus);
			strcat(new_genre, new_genreplus);
			strcpy(MatchingNodes[record_number - 1]->data.Genre, new_genre);
			store_data(*pList);
			printf("The new Genre has been changed and stored\n");
			break;
		case 5: // Fix Seconds
			printf("Enter the new song length, FIRST enter the minutes (X): ");
			scanf("%s:", &new_songlength_minutes/*,&new_song_length_seconds*/);
			printf("Now enter the Seconds (XX): "); // ask user to input seconds now
			scanf("%s", &new_song_length_seconds); // enter seconds.
												   //gets(new_songlength_minutes_plus);
												   //strcat(new_songlength_minutes, new_songlength_minutes_plus);
												   //gets(new_song_lenth_secondsplus);
												   //strcat(new_song_length_seconds, new_song_lenth_secondsplus);
			MatchingNodes[record_number - 1]->data.Song_length.Minutes = atoi(new_songlength_minutes); // Store Minutes
			MatchingNodes[record_number - 1]->data.Song_length.Seconds = atoi(new_song_length_seconds); // Store Seconds
			store_data(*pList); // New Data is Stored
			printf("The New song length has been Stored\n\n");
			break;
		case 6:
			printf("Enter the new amount of number of times played: ");
			scanf("%s", &new_timesplayed);
			gets(new_timesplayedplus);
			strcat(new_timesplayed, new_timesplayedplus);
			MatchingNodes[record_number - 1]->data.Number_times_played = atoi(new_timesplayed);
			store_data(*pList);
			printf("The New number of times has been recorded\n\n");
			break;
		case 7:
			printf("Enter A new Rating: ");
			scanf("%s", &new_rating);
			gets(new_rating_plus);
			strcat(new_rating, new_rating_plus);
			MatchingNodes[record_number - 1]->data.Rating = atoi(new_rating);
			store_data(*pList);
			printf("The New Rating Has Been Implemented\n\n");
			break;
		}
	}


}

void edit_rating(Node **pList)
{
	char artist[100], artist_name[100], new_rating[100], new_rating_plus[100];
	int success = 0, i = 0, record_number = 0, edit_record = 0;
	Node *pTemp = NULL;
	Node *MatchingNodes[50] = { NULL };
	printf("If the Artist has two names,\nPlease enter it as \"Last Name, First Name\" And If they only have one name Enter their name:");
	scanf("%s", &artist_name); // scan name
	gets(artist); // get the second part of the name
	strcat(artist_name, artist); // attach second part of name to the first part of the name
	MatchingNodes[i] = findNode(*pList, &artist_name);
	printf("\n");
	while (MatchingNodes[i] != NULL)
	{
		//pTemp = findNode(*pList, &artist);
		//MatchingNodes[i] = pTemp;
		//i++;
		printf("%d. ", i + 1);
		printf("%s,", MatchingNodes[i]->data.Artist);
		printf("%s,", MatchingNodes[i]->data.Album_title);
		printf("%s,", MatchingNodes[i]->data.song);
		printf("%s,", MatchingNodes[i]->data.Genre);
		printf("%d:", MatchingNodes[i]->data.Song_length.Minutes);
		printf("%d,", MatchingNodes[i]->data.Song_length.Seconds);
		printf("%d,", MatchingNodes[i]->data.Number_times_played);
		printf("%d\n", MatchingNodes[i]->data.Rating);
		i++;
		MatchingNodes[i] = findNode(MatchingNodes[i - 1]->pNext, &artist_name);
	}
	if (MatchingNodes[0] == NULL)
	{
		printf("Record Was not Found\n\n");
	}
	else
	{
		printf("\nWhich Record Would you like to edit: ");
		scanf("%d", &record_number);
		printf("\nEnter A new Rating 1-5 ||| 1 Being the Lowest and 5 Being the Highest: ");
		scanf("%s", &new_rating);
		gets(new_rating_plus);
		strcat(new_rating, new_rating_plus);
		MatchingNodes[record_number - 1]->data.Rating = atoi(new_rating);
		store_data(*pList);
		printf("The New Rating Has Been Implemented\n\n");
	}

}

//function to play selected song
void play_songs(Node *pList)
{
	Node *temp = pList; // create a temporary list to print all records
	int i = 1, record_number = 0, success = 0;
	while (temp != NULL)
	{
		printf("%d. ", i);
		printf("%s,", temp->data.Artist);
		printf("%s,", temp->data.Album_title);
		printf("%s,", temp->data.song);
		printf("%s,", temp->data.Genre);
		printf("%d:", temp->data.Song_length.Minutes);
		printf("%d,", temp->data.Song_length.Seconds);
		printf("%d,", temp->data.Number_times_played);
		printf("%d\n", temp->data.Rating);
		temp = temp->pNext;
		i++;
	}

	//sleep(1);
	//printf("The Record You selected will now play\n");
	while (success == 0)
	{
		printf("\nWhich Record Would you like to start playing: ");
		scanf("%d", &record_number);
		for (i = 0; i < record_number - 1; i++)
		{
			if (pList->pNext != NULL)
			{
				pList = pList->pNext;
			}
			else
			{
				printf("Number entry is wrong, make sure the entry is corresponds to the song.");
				success = 0;
				break;
			}

		}
		if (i == record_number - 1)
		{
			success = 1;
		}

	}
	while (pList != NULL) // go down the selected list and play the song
	{
		system("cls");
		printf("Playing Selected Song\n");
		printf("%s,", pList->data.Artist);
		printf("%s,", pList->data.Album_title);
		printf("%s,", pList->data.song);
		printf("%s,", pList->data.Genre);
		printf("%d:", pList->data.Song_length.Minutes);
		printf("%d,", pList->data.Song_length.Seconds);
		printf("%d,", pList->data.Number_times_played);
		printf("%d\n", pList->data.Rating);
		sleep(2); // sleep for 2 seconds
				  //sleep((pList->data.Song_length.Minutes * 60) + pList->data.Song_length.Seconds);
		pList = pList->pNext;
		system("cls");
	}
	printf("All the songs have been played\n");

}

void insert_song(Node **pList) //insert a new song
{
	char artist[100], artist_name[100], albumtitle[100], albumtitleplus[100], timesplayed[100];
	char song[100], songplus[100], genre[100], genreplus[100], minutes[100], seconds[100], rating[100];
	Record NewRecord; // create a new node to insert a record
	printf("You Will now create your own Record\n\n"); // prompt user to crete their own record
	printf("You Must First Enter the Artist Name: "); // directions for the user
	scanf("%s", &artist); // gather the name
	gets(artist_name); // and also gather the other name
	strcat(artist, artist_name); // combine the names
	strcpy(NewRecord.Artist, artist); // copy the name into the node
	system("cls");
	//store_data(*pList);
	printf("Now Enter the Album Title: ");
	scanf("%s", &albumtitle);
	gets(albumtitleplus);
	strcat(albumtitle, albumtitleplus);
	strcpy(NewRecord.Album_title, albumtitle);
	system("cls");
	printf("Now Enter the song name: ");
	scanf("%s", &song);
	gets(songplus);
	strcat(song, songplus);
	strcpy(NewRecord.song, song);
	system("cls");
	printf("Now Enter the Genre: ");
	scanf("%s", &genre);
	gets(genreplus);
	strcat(genre, genreplus);
	strcpy(NewRecord.Genre, genre);
	system("cls");
	printf("Now we will enter the Minutes and seconds, First the Minues: ");
	scanf("%s:", &minutes);
	NewRecord.Song_length.Minutes = atoi(minutes);
	system("cls");
	printf("Now Enter the Seconds: ");
	scanf("%s", &seconds);
	NewRecord.Song_length.Seconds = atoi(seconds);
	system("cls");
	printf("Now enter the new amount of times played: ");
	scanf("%s", &timesplayed);
	NewRecord.Number_times_played = atoi(timesplayed);
	system("cls");
	printf("Now Enter the Rating: ");
	scanf("%s", &rating);
	NewRecord.Rating = atoi(rating);
	system("cls");
	printf("\nThe new record has been stored");
	insert_at_front(pList, NewRecord); // insert at the front of the linked list
	store_data(*pList); // store the data
}

void delete_song(Node **pList)
{
	Node* pCur = *pList; // set p current to the list
	Node* pPrev = NULL; // set previous to null
	Node* pTemp = NULL; // set p temporary to null
	char song[100];
	char songplus[100];
	printf("Enter the Song that represents the record you want to delete: "); // prompt the user to enter a new song name
	scanf("%s", &song);
	gets(songplus);
	strcat(song, songplus);

	while (pCur != NULL && strcmp(pCur->data.song, song) != 0)
	{
		pPrev = pCur;
		pCur = pCur->pNext;
	}
	if (pPrev == NULL) // front of the list
	{
		pTemp = pCur;
		pCur = pCur->pNext; // set pCur to Pnext
		pCur->pPrev = NULL; // Set pcur pPrev to NULL cause theres nothing before
		*pList = pCur; // set the current list to Pcur so that it points to the new beggining of the list
		free(pTemp);
		store_data(*pList);
		printf("Changes Have been made to the list\n");
	}
	else if (pCur != NULL && pCur->pNext == NULL) // deleting at the last
	{
		pTemp = pCur;
		pPrev->pNext = NULL; // set pPrev to NULL end of the data
		pCur = NULL; // pCur equals null because theres nothing
		free(pTemp);
		store_data(*pList);
		printf("Changes Have been made to the List\n");
	}
	else if (pCur != NULL)
	{
		pTemp = pCur; // set pTemp to Pcur
		pCur = pCur->pNext; //point pCur to Pnext which is ptemp pCur
		pCur->pPrev = pPrev;// set pCur pPrev to pTemp pPrev
		pPrev->pNext = pCur;// pprev pNext now points to pcur
		free(pTemp);
		store_data(*pList);
		printf("Changes Have been made to the List\n");
	}
	else if (pCur == NULL) // display if the new song is not found
	{
		printf("\nSong was not found");
	}
}

int size_ofList(Node *pList) // a function to determine the size of the list
{
	Node *pMem = pList; // set the pmem to the list
	int L = 0;
	while (pMem != NULL)
	{
		L++; // increment to keep track of the size
		pMem = pMem->pNext;
	}
	return L;
}
void sort(Node **pList) // sort the list by a certain condition
{
	Node *pCur = *pList, *pPrev = *pList;
	Record temp;
	char artist[100], artistplus[100]; //set artist name
	char album[100], albumplus[100]; // set the album title
	int rating = 0, ratingplus = 0; // set the rating and times played to an integer
	int timesplayed = 0, timesplayedplus = 0;
	char *token = NULL;
	int sort_records = 0, size = 0, length = 0, passes = 0;
	int s = 0, c = 0, I = 0, i = 0;
	printf("You will now Sort the Records.\n\n");
	printf("1.Sort Based on Artist\n2.Sort Based on Album Title\n3.Sort Based on Rating\n4.Sort Based on times Played\n");
	printf("\nEnter a number to decide how you would like to sort: ");
	scanf("%d", &sort_records);
	switch (sort_records)
	{
	case 1: // sort based on artist
		size = size_ofList(*pList); // set size to the size of the list
		for (passes = 0; passes < (size - 1); ++passes) // basic bubble sort
		{
			s = 0;
			pCur = *pList; // set p cur to the list
			pPrev = *pList; // set the pprev to the list
			for (I = 0; I < (size - 1 - passes); I++)
			{
				pPrev = pCur; // set pprev to the current
				pCur = pCur->pNext; // then set current to the next

				strcpy(artist, pPrev->data.Artist);  // copy artist to the the list
				strcpy(artistplus, pCur->data.Artist);
				if (artist[0] == '\"') // this is for certain artist like "Swift Taylor"
				{
					token = strtok(artist, ",");
					length = strlen(token);
					for (i = 0; i < (length); i++)
					{
						artist[i] = artist[i + 1];
					}
				}
				if (artistplus[0] == '\"') // comparing artist plus and determining its condion if it has ""
				{
					token = strtok(artist, ",");
					length = strlen(token);
					for (i = 0; i < (length); i++)
					{
						artistplus[i] = artistplus[i + 1];
					}
				}
				if (pPrev->pPrev == NULL && strcmp(artist, artistplus) > 0) // if the previous equals null and its at the beggining of the list
				{
					//s = 1;
					//temp = pCur->data;
					strcpy(temp.Artist, pCur->data.Artist); // set temp to pcur so the data is stored in the temp to hold the value
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					///
					//pCur->data = pPrev->data;
					strcpy(pCur->data.Artist, pPrev->data.Artist); // set pcur to pprev, this means the previous data is at the front
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					pCur->data.Song_length = pPrev->data.Song_length;
					////
					//pPrev->data = temp;
					strcpy(pPrev->data.Artist, temp.Artist); // now implemnt p prev to the data which was store in temporary
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;

				}
				else if (pCur->pNext != NULL && strcmp(artist, artistplus) > 0) // if it is at the end of the list
				{
					//s = 1;
					//temp = pCur->data;
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					/////
					//pPrev->data = temp;
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					pCur->data.Song_length = pPrev->data.Song_length;
					////
					//pPrev->data = temp;
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
				else if (pCur->pNext == NULL && strcmp(artist, artistplus) > 0)
				{
					//s = 1;
					//temp = pCur->data;
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					//
					//pPrev->data = temp;
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					temp.Song_length = pCur->data.Song_length;
					////
					//pPrev->data = temp;
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
			}
		}
		printf("The file has been sorted by Artist\n");
		break;

	case 2: // sort based on album title
		size = size_ofList(*pList);
		for (passes = 0; passes < (size - 1); ++passes)
		{
			s = 0;
			pCur = *pList; //
			pPrev = *pList; //
			for (I = 0; I < (size - 1 - passes); I++)
			{
				pPrev = pCur;
				pCur = pCur->pNext;
				strcpy(album, pPrev->data.Album_title);
				strcpy(albumplus, pCur->data.Album_title);
				if (pPrev->pPrev == NULL && strcmp(album, albumplus) > 0)
				{
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					//
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					pCur->data.Song_length = pPrev->data.Song_length;
					////
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
				else if (pCur->pNext != NULL && strcmp(album, albumplus) > 0)
				{
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					/////
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					pCur->data.Song_length = pPrev->data.Song_length;
					////
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
				else if (pCur->pNext == NULL && strcmp(album, albumplus) > 0)
				{
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					//
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					temp.Song_length = pCur->data.Song_length;
					////
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
			}
		}
		printf("the files have been sorted by album title\n");
		break;

	case 3: // sort based on rating
		size = size_ofList(*pList);
		for (passes = 0; passes < (size - 1); ++passes)
		{
			s = 0;
			pCur = *pList; //
			pPrev = *pList; //
			for (I = 0; I < (size - 1 - passes); I++)
			{
				pPrev = pCur;
				pCur = pCur->pNext;
				rating = pPrev->data.Rating;
				ratingplus = pCur->data.Rating;
				if (pPrev->pPrev == NULL && ratingplus < rating)
				{
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					//
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					pCur->data.Song_length = pPrev->data.Song_length;
					////
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
				else if (pCur->pNext != NULL && ratingplus < rating)
				{
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					/////
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					pCur->data.Song_length = pPrev->data.Song_length;
					////
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
				else if (pCur->pNext == NULL && ratingplus < rating)
				{
					strcpy(temp.Artist, pCur->data.Artist);
					strcpy(temp.Album_title, pCur->data.Album_title);
					strcpy(temp.Genre, pCur->data.Genre);
					temp.Number_times_played = pCur->data.Number_times_played;
					temp.Rating = pCur->data.Rating;
					strcpy(temp.song, pCur->data.song);
					temp.Song_length = pCur->data.Song_length;
					//
					strcpy(pCur->data.Artist, pPrev->data.Artist);
					strcpy(pCur->data.Album_title, pPrev->data.Album_title);
					strcpy(pCur->data.Genre, pPrev->data.Genre);
					pCur->data.Number_times_played = pPrev->data.Number_times_played;
					pCur->data.Rating = pPrev->data.Rating;
					strcpy(pCur->data.song, pPrev->data.song);
					temp.Song_length = pCur->data.Song_length;
					////
					strcpy(pPrev->data.Artist, temp.Artist);
					strcpy(pPrev->data.Album_title, temp.Album_title);
					strcpy(pPrev->data.Genre, temp.Genre);
					pPrev->data.Number_times_played = temp.Number_times_played;
					pPrev->data.Rating = temp.Rating;
					strcpy(pPrev->data.song, temp.song);
					pPrev->data.Song_length = temp.Song_length;
				}
			}
		}
		printf("the files have been sorted by rating\n");
		break;

		case 4: // sort based on number of times played
			size = size_ofList(*pList);
			for (passes = 0; passes < (size - 1); ++passes)
			{
				s = 0;
				pCur = *pList; //
				pPrev = *pList; //
				for (I = 0; I < (size - 1 - passes); I++)
				{
					pPrev = pCur;
					pCur = pCur->pNext;
					timesplayed = pPrev->data.Number_times_played;
					timesplayedplus = pCur->data.Number_times_played;
					if (pPrev->pPrev == NULL && timesplayedplus < timesplayed)
					{
						strcpy(temp.Artist, pCur->data.Artist);
						strcpy(temp.Album_title, pCur->data.Album_title);
						strcpy(temp.Genre, pCur->data.Genre);
						temp.Number_times_played = pCur->data.Number_times_played;
						temp.Rating = pCur->data.Rating;
						strcpy(temp.song, pCur->data.song);
						temp.Song_length = pCur->data.Song_length;
						//
						strcpy(pCur->data.Artist, pPrev->data.Artist);
						strcpy(pCur->data.Album_title, pPrev->data.Album_title);
						strcpy(pCur->data.Genre, pPrev->data.Genre);
						pCur->data.Number_times_played = pPrev->data.Number_times_played;
						pCur->data.Rating = pPrev->data.Rating;
						strcpy(pCur->data.song, pPrev->data.song);
						pCur->data.Song_length = pPrev->data.Song_length;
						////
						strcpy(pPrev->data.Artist, temp.Artist);
						strcpy(pPrev->data.Album_title, temp.Album_title);
						strcpy(pPrev->data.Genre, temp.Genre);
						pPrev->data.Number_times_played = temp.Number_times_played;
						pPrev->data.Rating = temp.Rating;
						strcpy(pPrev->data.song, temp.song);
						pPrev->data.Song_length = temp.Song_length;
					}
					else if (pCur->pNext != NULL && timesplayedplus < timesplayed)
					{
						strcpy(temp.Artist, pCur->data.Artist);
						strcpy(temp.Album_title, pCur->data.Album_title);
						strcpy(temp.Genre, pCur->data.Genre);
						temp.Number_times_played = pCur->data.Number_times_played;
						temp.Rating = pCur->data.Rating;
						strcpy(temp.song, pCur->data.song);
						temp.Song_length = pCur->data.Song_length;
						/////
						strcpy(pCur->data.Artist, pPrev->data.Artist);
						strcpy(pCur->data.Album_title, pPrev->data.Album_title);
						strcpy(pCur->data.Genre, pPrev->data.Genre);
						pCur->data.Number_times_played = pPrev->data.Number_times_played;
						pCur->data.Rating = pPrev->data.Rating;
						strcpy(pCur->data.song, pPrev->data.song);
						pCur->data.Song_length = pPrev->data.Song_length;
						////
						strcpy(pPrev->data.Artist, temp.Artist);
						strcpy(pPrev->data.Album_title, temp.Album_title);
						strcpy(pPrev->data.Genre, temp.Genre);
						pPrev->data.Number_times_played = temp.Number_times_played;
						pPrev->data.Rating = temp.Rating;
						strcpy(pPrev->data.song, temp.song);
						pPrev->data.Song_length = temp.Song_length;
					}
					else if (pCur->pNext == NULL && timesplayedplus < timesplayed)
					{
						strcpy(temp.Artist, pCur->data.Artist);
						strcpy(temp.Album_title, pCur->data.Album_title);
						strcpy(temp.Genre, pCur->data.Genre);
						temp.Number_times_played = pCur->data.Number_times_played;
						temp.Rating = pCur->data.Rating;
						strcpy(temp.song, pCur->data.song);
						temp.Song_length = pCur->data.Song_length;
						//
						strcpy(pCur->data.Artist, pPrev->data.Artist);
						strcpy(pCur->data.Album_title, pPrev->data.Album_title);
						strcpy(pCur->data.Genre, pPrev->data.Genre);
						pCur->data.Number_times_played = pPrev->data.Number_times_played;
						pCur->data.Rating = pPrev->data.Rating;
						strcpy(pCur->data.song, pPrev->data.song);
						temp.Song_length = pCur->data.Song_length;
						////
						strcpy(pPrev->data.Artist, temp.Artist);
						strcpy(pPrev->data.Album_title, temp.Album_title);
						strcpy(pPrev->data.Genre, temp.Genre);
						pPrev->data.Number_times_played = temp.Number_times_played;
						pPrev->data.Rating = temp.Rating;
						strcpy(pPrev->data.song, temp.song);
						pPrev->data.Song_length = temp.Song_length;
					}
				}
			}
			printf("the files have been sorted by times played\n");
			break;

		break;
	}
}

void shuffle(Node **pList) // shuffle the playlist
{
	int length = size_ofList(*pList);
	Node *temp = *pList; //set the temp to plist
	Node *shuff[1000] = {NULL}; // set the shuff to NULL
	int in1 = 0, in2 = 0;
	for (int i = 0; i < length; i++) // set shuff to the list
	{
		shuff[i] = temp;
		temp = temp->pNext;
	}
	for (int i = 0; i < length; i++) // this is the loop to randomly shuffle the list
	{
		in1 = rand() % length; // set in1 to randomly generate
		in2 = rand() % length; // set in1 to randomly generate
		temp = shuff[in1]; // set temp to shuff1
		shuff[in1] = shuff[in2];// put shuff2 into shuff 1
		shuff[in2] = temp; //then put shuff1 into temp
	}
	*pList = shuff[0]; // set plist to the shuffle playlist
	
	for (int j = 0; j < length; j++) // this is to now implement the shuffle into the lis
	{
		if (j > 0 && j < (length -1))//Middle // implement from the middle
		{
			temp = shuff[j];
			temp->pNext = shuff[j + 1];
			temp->pPrev = shuff[j - 1];
		}
		else if (j == length -1)//End // implement at the end
		{
			temp = shuff[j];
			temp->pNext = NULL;
			temp->pPrev = shuff[j - 1];
		}
		else //BEginnign // implement at the start
		{
			temp = shuff[j];
			temp->pNext = shuff[j + 1];
			temp->pPrev = NULL;
		}
	}
	printf("\n The Playlist has been shuffled!\n"); //tell the user
}
