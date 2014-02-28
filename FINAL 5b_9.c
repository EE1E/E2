#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* a function that takes in a pointer to structure variable and de-allocates memory for the matrix*/
void free_matrix(char **strmat)
{
	int i;
	for (i = 0; i < 1000; i++)
	{
		free(strmat[i]);
	}
	free(strmat);
}

/*removes all of punctuation letters and removes capital letters*/
void lowercase_remove_punct(char *original_string, char *processed_string)
{
	int i1, i2;
	char c;
	for (i1 = 0, i2 = 0; i1 < strlen(original_string); i1++)
	{
		c = original_string[i1];
		if ((c >= 'A') && (c <= 'Z'))
			processed_string[i2++] = original_string[i1] - 'A' + 'a';
		if (((c >= 'a') && (c <= 'z')) || (c == '\''))
			processed_string[i2++] = original_string[i1];
	}
	processed_string[i2] = '\0';
}

/*checks for a difference of one letter*/
void one_let(char *temp, char **dictmat)
{

	int i = 0, j, correct = 0;

	printf("Similar: ");

	for (i = 0; i < 1000; i++)
	{
		/*the words are the same size*/
		if (strlen(temp) == strlen(dictmat[i]))
		{
			/*if the character in both words is the same, it increments the variable correct*/
			for (j = 0; j < strlen(temp); j++)
				if (temp[j] == dictmat[i][j])
					correct++;


			/*only differers by one letter*/
			if (correct == (strlen(temp) - 1))
				printf("%s ", dictmat[i]);

			/*reset the correct variable*/
			correct = 0;
		}
	}

}


void last_two(char  *temp, char **dictmat)
{
	int i;

	for (i = 0; i < 1000; i++)
	{
		/*the words are the same size*/
		if (strlen(temp) == strlen(dictmat[i]))
		{
			/*makes sure that the strings are the same before the last two letters, then checks if the last two letters are swapped and prints out the suggestion*/
			if (strncmp(temp, dictmat[i], strlen(dictmat[i]) - 2) == 0)
				if (temp[strlen(temp) - 1] == dictmat[i][strlen(temp) - 2])
					if (temp[strlen(temp) - 2] == dictmat[i][strlen(temp) - 1])
						printf("%s ", dictmat[i]);
		}
	}
}

void last_let(char *temp, char **dictmat)
{
	char word[100];
	int i;

	/*copies the temp variable into the word variable except for the last letter, then inserts a null character*/
	strncpy(word, temp, strlen(temp) - 1);
	word[strlen(temp) - 1] = '\0';

	/*checks if the word excluding the last letter is available in the dictionary*/
	for (i = 0; i < 1000; i++)
		if (strcmp(word, dictmat[i]) == 0)
			printf("%s ", dictmat[i]);



}

int main(void)
{
	char temp[100];
	char **strmat, temp_line[100];
	int string_size;
	int i = 0, comp, file, found = 0, j = 0, foundmiss = 0;

	FILE* input;
	FILE* dict;

	/*opens the dictionary file and stores it into "strmat" array of strings*/
	dict = fopen("y:\\dict.txt", "r");
	/*checks if we can open the file, otherwise output error message*/
	if (dict == NULL)
	{
		printf("Could not open dict.txt for reading \n");
	}
	else
	{
		/*allocates the memory location to the rows or the array of pointers to the columns*/
		strmat = (char **)malloc(sizeof(char*)* 1000);

		
		do
		{
			/*temp_line is now the contents of the line in the file*/
			file = fscanf(dict, "%s", temp_line);
			/*makes sure does not go to the end of file*/
			if (file != EOF)
			{
				/*set the string size to include the null terminator*/
				string_size = strlen(temp_line) + 1;
				/*allocates the array to the size of the string including the null terminator*/
				lowercase_remove_punct(temp_line, temp_line);
				strmat[i] = (char *)malloc(sizeof(char)*string_size);
				/*copies the string into the array*/
				strcpy(strmat[i], temp_line);
				i++;
			}


		} while (file != EOF);

		/*closes the file*/
		fclose(dict);

	}

	/*opens the text file*/
	input = fopen("y:\\textfile.txt", "r");

	/*checks if we can open the file, otherwise output error message*/
	if (input == NULL)
	{
		printf("Could not open textfile.txt for reading \n");
	}
	else
	{
		/*allocates the memory location to the rows using a for loop*/

		do
		{
			/*temp_line is now the contents of the line in the file*/
			file = fscanf(input, "%s", temp);
			if (file != EOF)
			{
				/*remove punctuation*/
				lowercase_remove_punct(temp, temp);
				for (i = 0; i < 1000; i++)
				{
					comp = strcmp(temp, strmat[i]);
					if (comp == 0)
					{
						/*it has found the word in the dictionary*/
						found = 1;

					}

				}

				/*it has not found a word in the dictionary, so the word must be misspelt*/
				if (found == 0 && (strcmp(temp, "") != 0))
				{

					/*temp is the variable that is misspelt*/
					printf("\nMisspelled: %s \n", temp);

					/*checks for a difference of one letter*/
					one_let(temp, strmat);
					/*checks if the last two letters have been swapped*/
					last_two(temp, strmat);
					/*checks if last letter is missing*/
					last_let(temp, strmat);
				}
				found = 0;
				foundmiss = 0;


			}

		} while (file != EOF);

		/*closes the file*/
		fclose(input);


	}
	/*frees the array*/
	free_matrix(strmat);

	return 0;
}
