#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vocabullary{ //struct for the words of the vocabullery
    char *hellenicWord; //the greek word
    char *barbaricWord; //the english word
    struct vocabullary *next; //pointer to the next word
};
struct vocabullary *head = NULL; //first word
struct vocabullary *currentNode = NULL; //last word

struct vocabullary *find(char key[17], struct vocabullary **previous){ //it finds if there is the key in the vocab
    struct vocabullary *wordToFind=head; //wordToFind tike the adress of the first word in vocab
    struct vocabullary *temporary=NULL; //its the first word so there is no previous word (temporary get the adress of the prev struct)
    int checker0,checker1,checker2; //its easier for me to dont use strcmp inside of if
    checker0=0; //if it will get the value 1 then there is the key in the vocab
    while (wordToFind!=NULL){ //until wordToFind to check every words in the vocab
        checker1=strcmp(wordToFind->hellenicWord,key); //checking if the key is the greek word
        checker2=strcmp(wordToFind->barbaricWord,key); // -||-
        if((checker1*checker2)==0){ //if a checker is 0 it means that we found the key of the vocab
            checker0 = 1; //it gets value 1 as the key has been found
            break; //sorry for break
        }else{
            temporary = wordToFind; //keeping in temp the current address of wordToFind (so it is the previous adress now)
            wordToFind = wordToFind->next; //wordToFind get next adress
        }
    }
    if(checker0==1){ //if checker==1 the key is in the struct
        if(previous){ //if it is null it is the first word or you are not doing delete
            *previous = temporary; //the pointer take the value of the previous word (it needs if you want to delete a word to make the previous pointer see the next adress)
        }
        return wordToFind; //.
    }else{
        return NULL; //NULL if not found
    }
}

struct vocabullary *insertFirstWorld(char newHellenicWord[17], char newBarbaricWord[17]){ //creating the List
    struct vocabullary *newWord; //the first new word
    newWord=(struct vocabullary *)malloc(sizeof(struct vocabullary)); //give the word space (memory)
    if(newWord == NULL){ //no memory given
        printf("Something whent wrong\n");
        printf("Exiting program\n");
        exit(0);
    }
    newWord->hellenicWord = strdup(newHellenicWord); //put the values in the struct
    newWord->barbaricWord = strdup(newBarbaricWord); //with strcpy it was a bloody mess
    newWord->next = NULL; //no next word so it is NULL
    head = currentNode = newWord; //it is first and last word so both current and head have sanme adress
    return newWord;
}
struct vocabullary *insertWorld(char newHellenicWord[17], char newBarbaricWord[17]){
    if(head==NULL){ //if there is no first word go ton insertFirstWor(l)d and create the list
        return(insertFirstWorld(newHellenicWord,newBarbaricWord));
    }
    struct vocabullary *newWord; //the new word
    newWord = (struct vocabullary *) malloc (sizeof(struct vocabullary)); //give it space
    if(newWord==NULL){ //no space given
        printf("Something whent wrong\n");
        printf("Exiting program\n");
        exit(0);
    }
    newWord->hellenicWord = strdup(newHellenicWord); //Putin values
    newWord->barbaricWord = strdup(newBarbaricWord);
    newWord->next = NULL; //its the last word so next get NULL
    currentNode->next = newWord; //current get the address of newWord +current->next get null as there is no next in the end
    currentNode = newWord;
    return newWord;
}
void fooForInsert(){ //asking what values to insert in the list and checking if there are already in
    struct vocabullary *checker0; //it gets NULL if there is no word like the given one in the vocab
    char checker1[17],checker2[17]; //gets the word from the keyboard
    printf("Please give the Hellenic word: ");
    scanf("%s",checker1);
    checker0=find(checker1,NULL); //before calling insert it calls find to check if there is already in list
    if(checker0!=NULL){ //check0 is not NULL so it find found the word in the list
        printf("This word is already registered.\n");
    }else{ //check is NULL so find didnt found anything
        printf("Please give the English word: ");
        scanf("%s",checker2);
        checker0=find(checker2,NULL);
        if(checker0!=NULL){ //same (maybe this is no need because 2 greek words maybe have same translation
            printf("This word is already registered.\n");
        }else{
            insertWorld(checker1,checker2); //inserting the word
            printf("The new word has been registered\n");
        }
    }
    printf("Press enter to return to main menu.\n");
    getchar();getchar(); //let the user check the results and then press enter to go to menu agien
    return;
}

void readFromFile(){ //foo that opens the file to read
    char firstWorld[17],secondWord[17]; //words to insert in the list
    FILE *fileWithTheVocab; //file to open
    fileWithTheVocab = fopen("datFileIsProgramFile.txt","r"); //open to file
    if(!fileWithTheVocab){ //file is open?
        printf("There was a problem with opening the program file.\n");
        printf("Exiting Program");
        exit(0);
    }
    while(fgets(firstWorld,(sizeof(firstWorld)*2)+2,fileWithTheVocab)!=NULL){ //gets line from file
        strtok(firstWorld, "\n"); //when i was getting the second line it gave a \n to the first.. so i strtok it
        while(fgets(secondWord,(sizeof(secondWord)*2)+2,fileWithTheVocab)!=NULL){ //get second line (1st line is greek 2nd is english, 3nd greek 4th eng.....)
            strtok(secondWord, "\n"); //same as the other strtok
            fflush(stdin);
            insertWorld(firstWorld,secondWord); //insert the word in the list
            break; //sorry agien xP
        }
    }
    if(fclose(fileWithTheVocab)!=0){ //closing file
        printf("There was a problem with closing the program file.\n");
        printf("Exiting Program");
        exit(0); //if there is problem with closing file then the program will exit
    }
}
void writeToFile(){ //you can save your list in the .txt file with this method
    FILE *fileWithTheVocab;
    struct vocabullary *wordThatIsGettingSaved = head;
    fileWithTheVocab = fopen("datFileIsProgramFile.txt","w"); //open file to save
    if(!fileWithTheVocab){ //if not open then exit
        printf("There was a problem with opening the program file.\n");
        printf("Exiting Program");
        exit(0);
    }else{ //if open
        while(wordThatIsGettingSaved != NULL){ //until is NULL save the words in the txt
            fprintf(fileWithTheVocab,"%s\n",wordThatIsGettingSaved->hellenicWord); //save greek word
            fprintf(fileWithTheVocab,"%s\n",wordThatIsGettingSaved->barbaricWord); //save english word
            wordThatIsGettingSaved = wordThatIsGettingSaved->next; //next andress of the list
        }
        return;
    }
}

int update(char key[17], char newHellenicWord[17], char newBarbaricWord[17]){ //foo for updating word
    struct vocabullary *wordToUpdate;
    wordToUpdate = find(key,NULL); //it takes the andress of the word that find gives
    if (wordToUpdate==NULL){ //if NULL then there is no word in the list like the word key
        return 0;
    }
    strcpy(wordToUpdate->hellenicWord,newHellenicWord); //update the words of the struct
    strcpy(wordToUpdate->barbaricWord,newBarbaricWord);
    return 1;
}
void fooForEditWord(){ //foo for getting the words the user want to update
    char key[17],newHellenicWord[17],newBarbaricWord[17];
    int isEverythingOk;
    printf("Please give the word you wish to update: ");
    scanf("%s",key); //the word that the user want to update (can be both greek or english
    if(find(key,NULL)==NULL){ //if find return NULL then "no word == key" on list
        printf("There is no word \"%s\"\n",key);
        printf("Press enter to return to main menu.\n");
        getchar();getchar(); //let the user see the results and then go to main menu with enter
        return;
    }
    printf("Please give the new Hellenic word: ");
    scanf("%s",newHellenicWord); //taking the new updated word
    printf("Please give the new English word: ");
    scanf("%s",newBarbaricWord); // -||-
    isEverythingOk = update(key,newHellenicWord,newBarbaricWord); //sending them to the update foo to update the list
    if(isEverythingOk==1){ //if ==1 everything was ok
        printf("The word has been updated.\n");
        printf("Press enter to return to main menu.\n");
        getchar();getchar();
    }else{ //That does not need too much as the update check itself if everything was ok (so "isEverythingOk" and the next print are useless)
        printf("Useless print message (this condition is already been checked)");
    }
    return;
}

void deleteAword(){ //foo for deleting a word
    char key[17];
    printf("Please give the word you wish to delete: ");
    scanf("%s",key); //the keyword you want to delete from the list
    struct vocabullary *previousWorld = NULL; //the previous word from the word you want to delete
    struct vocabullary *worldForDelete = NULL; //word you want to delete
    worldForDelete = find(key,&previousWorld);
    if(worldForDelete == NULL){ //if NULL then there is no word like the key
        printf("There is no \"%s\" word in the vocabullary\n",key);
        printf("Press enter to return to main menu.\n");
        getchar();getchar(); //let the user see that he put wrong key and then go to main menu
        return;
    }else{
        if(previousWorld != NULL) //if there is previous (not the first word of the list) then
            previousWorld->next = worldForDelete->next; //put previous to so the next
        if(worldForDelete == currentNode){ //if word to telete is the last then
            currentNode = previousWorld; //the last word take the address of the previous word as the previous is the new last
        }else if(worldForDelete == head){ //if the wordForDdelete is the first word on the list then
            head = worldForDelete->next; //head take the adress of the 2nd word as 2nd will become the 1st
        }
    }
    free(worldForDelete); //freeing memory of the deleted word
    worldForDelete = NULL; //Nulling the word
    printf("The word \"%s\" is deleted from the the vocabullary\n",key);
    printf("Press enter to return to main menu.\n");
    getchar();getchar(); //the user sees the results and then press enter to go main manu
    return;
}

void printAllWorlds(){ //printing alll the words of the list
    struct vocabullary *wordForPrint = head; //get adress of the first word pf the list
    printf("\n -------Printing list Start-------");
    while(wordForPrint != NULL){ //while until it gets to NULL (last word)
        printf("\n \"%s\" : \"%s\" \n",wordForPrint->hellenicWord,wordForPrint->barbaricWord);
        wordForPrint = wordForPrint->next;
    }
    printf(" --------Printing list End-------- \n");
    printf("Press enter to return to main menu.\n");
    getchar();getchar(); //let the user see the results
    return;
}
void printAword(){ //foo for geting the word the user wants to translate
    char key[17];
    printf("Please give the word you wish to translate: ");
    scanf("%s",key);
    struct vocabullary *wordForPrint = head; //get adreess of the first word of the list so as it gets the next and next until it finds the key
    wordForPrint=find(key,NULL); //gets NULL if no key on list
    printf("\n -------Translator Start-------");
    if(wordForPrint==NULL){ //==NULL then no key on list
        printf("\nThere is no such a word (%s) in the vocabullary.\n",key);
    }else{ // !=NULL so it prints the 2 words
        printf("\n \"%s\" : \"%s\" \n",wordForPrint->hellenicWord,wordForPrint->barbaricWord);
    }
    printf(" --------Translator End-------- \n");
    printf("Press enter to return to main menu.\n");
    getchar();getchar(); //let the user see the results
    return;
}
void printAsetance(){ //foo for geting a setance hat the user wants to translate (it leaves the words that are not in the list untranslated)
    struct vocabullary *wordOfSentence=NULL;
    int helper;
    char wholeSentance[201]; //the setance can have 201 chars only
    printf("\nPlease give the sentence you want to translate: ");
    do{
        fgets(wholeSentance, sizeof wholeSentance, stdin);
    }while(wholeSentance[0]=='\n'); //this do_while is in need as fgets is getting whatever it want and the fflush is not doing anything
    strtok(wholeSentance, "\n"); //agien put the \n out of the setance
    char * eachWord; //each word of wholeSentance
    eachWord = strtok (wholeSentance," ,.-"); //gets the first word of wholeSentance
    printf("\n -------Translator Start-------\n");
    while (eachWord != NULL){ //until it is null (the end of the sentance) do
        wordOfSentence=find(eachWord,NULL); //see if it is in the list
        if(wordOfSentence!=NULL){ //if it is on the struct then
            helper = strcmp(eachWord,wordOfSentence->barbaricWord); //see if it is the english word
            if(helper == 0){ //if it is the english word then
                printf ("%s ",wordOfSentence->hellenicWord); //print the hellenic
            }else{ //it is the english
                printf ("%s ",wordOfSentence->barbaricWord);
            }
        }else{ //that word of the setance is not in the struct
            printf("%s ",eachWord); //print that word
        }
        eachWord = strtok (NULL, " ,.-"); //strtok it agien to get the next word of the setance
    }
    printf("\n --------Translator End-------- \n");
    printf("Press enter to return to main menu.\n");
    getchar();getchar(); //user see the result and then he presses enter to continue
}

int menuDesplay(){ //the interface for the user
    int menuChoice;
    printf("~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~\n");
    printf("Please choose a choice from the following menu (type from 1-7)\n");
    printf("1: Register a new word\n");
    printf("2: Edit an existing word\n");
    printf("3: Delete a word\n");
    printf("4: Translate a word\n");
    printf("5: Translate a setance\n");
    printf("6: Print all the words\n");
    printf("7: Quit\n");
    printf("Your choice is: ");
    scanf("%d",&menuChoice);
    fflush(stdin);
    while((menuChoice!=1)&&(menuChoice!=2)&&(menuChoice!=3)&&(menuChoice!=4)&&(menuChoice!=5)&&(menuChoice!=6)&&(menuChoice!=7)){
        printf("Plz choose between 1-7\n");
        printf("Your choice is: ");
        scanf("%d",&menuChoice);
        fflush(stdin);
    }
    return menuChoice; //returns the choice of the user
}
int main(){
    int menuChoice, helper;
    printf("Hello guest! This is a vocabullary project.\n");
    readFromFile(); //reads the words from the file
    helper=1;
    while(helper==1){ //it never gets other value (the program exits with the exit(0); command
        menuChoice=menuDesplay(); //get the choice of the user
        switch(menuChoice){
            case 1: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                    printf("Your choice is to insert a new word.\n");
                    fooForInsert(); //inserts a new word or creat a new vocab if it was empty before
                    break;
            case 2: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                    printf("Your choice is to edit a word.\n");
                    fooForEditWord(); //edit an existing word
                    break;
            case 3: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                    printf("Your choice is to delete a word.\n");
                    deleteAword(); //delete an existing word
                    break;
            case 4: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                    printf("Your choice is to translate a word.\n");
                    printAword(); //print a given from user word
                    break;
            case 5: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                    printf("Your choice is to translate a whole sentence.\n");
                    printAsetance(); //print a given from user setance
                    break;
            case 6: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                    printf("Your choice is to print all the words.\n");
                    printAllWorlds(); //prints all the words of the vocabullary
                    break;
            default: printf("\n~~~~~~~~~~~~~~~~~~~\n");
                     printf("Do you want to save before exiting? (0=NO,1=YES): ");
                     scanf("%d",&helper);
                     if(helper==1){ //checks if user want to save
                        writeToFile(); //save to .txt file
                        printf("Saving completed successfully!\n");
                    }
                     printf("Exiting program");
                     printf("\n.\n.\n.\n");
                     exit(0); //exiting
        }
    }
    return 0;
}
