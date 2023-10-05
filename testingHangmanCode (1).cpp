#include <iostream>
#include <cstdlib>//for rand()
#include<windows.h>//for beep
#include <map>
#include <cctype>//for tolower()
#include <algorithm>
#include<cmath>
#include<fstream>//for filing
#include<conio.h>//for getch()
#include<vector>
#include <ctime>

using namespace std;
class Game{
protected:
    string name;
    float score;
    int level;
    int mode;
public:
    Game(string n="", int s=0, int l=0, int m =0): name(n), score(s), level(l), mode(m){}
    void registration(){
    	cout<<"\t\t*************************************"<<endl;
cout<<"\t\t           Enter name: ";
cin>>name;
cout<<"\t\t*************************************"<<endl;
       
        cout<<"\n\t\t Hello "<<name<<", please "<<endl;
    }
    void set_level(){
        cout<<"\t\t-------------------------------------\n"<<endl;
        cout<<"\n\t\t Select Level: "<<endl;
        cout<<"\t\t 1-Easy "<<endl;
        cout<<"\t\t 2-Moderate "<<endl;
        cout<<"\t\t 3-Hard: "<<endl;
        cin>>level;
        cout<<"\t\t-------------------------------------"<<endl;
    }
    int get_level(){
        return level;
    }
    void set_mode(){
        cout<<"\n\n\t\t Select Mode "<<endl;
        cout<<"\t\t 1-Single "<<endl;
        cout<<"\t\t 2-Competition: "<<endl;
        cin>>mode;
        cout<<"\t\t-------------------------------------"<<endl;
        getch();
    }
    int get_mode(){
        return mode;
    }
    virtual void calculate_score()=0;
};


class Hangman: public Game{
protected:
    string secretWord;// the hidden word itself selected from a file at random
    char* characters;// to store and write down correct letters on blank
    char * guessedLetters;//holds both correct & incorrect letters guessed by the user either in upper case or lower.
    static int correctGuesses;//number of correct guesses
    int size;//secretword string size
    static int incorrectGuesses;//number of wrong guesses to calculate score.
    int alphabet_count;//counter variable only increments when new letter is guessed. used to add the new letter in next index
    static int toss;
    int *cross;//for knowing at which index the vowels exist in the word
    char guess;
    map<int,string, greater<int>>data;
    map<int,string>::iterator it;
    map<int,string, greater<int>>dataM;
    map<int,string>::iterator itM;
    map<int,string, greater<int>>dataH;
    map<int,string>::iterator itH;
public:
    Hangman(string n="", int s=0, int l=0, int m=0):Game(n,s,l,m){
        guessedLetters=new char[26];
    }

//void word_delete() {
//    string word;
//    vector<string> wordlist;
//    
//    ifstream ob("Word.txt");
//    if (ob.is_open()) {
//        while (!ob.eof()) {
//            ob >> word;
//            if (word != secretWord) {
//                wordlist.push_back(word);
//            }
//        }
//        ob.close();
//    } else {
//        cout << "Trouble opening file for reading." << endl;
//        exit(1);
//    }
//    
//    ofstream ob1("Word.txt");
//    if (ob1.is_open()) {
//        for (int i = 0; i < wordlist.size(); ++i) {
//            ob1 << wordlist[i] << endl;
//        }
//        ob1.close();
//    } else {
//        cout << "Trouble opening file for writing." << endl;
//        exit(1);
//    }
//}

    void initializing(){
        select_secretWord();
        size=secretWord.length();
        alphabet_count=-1;
        cross=new int[size];
        characters=new char[2*size];
        correctGuesses=0;
        incorrectGuesses=0;
        alphabet_count=-1;
    }

    void startGame(int gamemode=1) {
        int flag=1,count=1;
        bool gameover=false;
        int totalattempts=0,x=0,totalattempts1=0,totalattempts2=0,temp1=0,incorrectguesses1=0,incorrectguesses2=0,correctguesses1=0,correctguesses2=0,temp2=0; // while (flag != 0) {
        system("cls");
        cout<<endl;
        display_empty_blanks();
        int turn=toss;
        while (!gameover){
            cout << endl;
            if(mode==2) {
                if (turn % 2 != 0) {
                    cout << "\tPlayer 1 turn" << endl;
                    totalattempts1++;
                    temp1++;
                    entering_guessed_letter();
                    cout << endl;
                }
                if (turn % 2 == 0) {
                    cout << "\tPlayer 2 turn" << endl;
                    totalattempts2++;
                    temp2++;
                    entering_guessed_letter();
                    cout << endl;
                }
                if (turn % 2 != 0) {
                    cout << "\tTotal attempts: " << totalattempts1 << endl;
                    if (IsACorrectGuess(guess) == -1) {
                        Beep(1000,500);
                        incorrectguesses1++;
                    }
                    else{
                        correctguesses1++;
                    }
                    cout << "\tPlayer 1 Incorrect Guesses: " << incorrectguesses1 << endl;
                    cout << "\tPlayer 2 Incorrect Guesses: " << incorrectguesses2 << endl;
                }
                if (turn % 2 == 0) {
                    cout << "\tTotal attempts: " << totalattempts2 << endl;
                    if (IsACorrectGuess(guess) == -1) {
                        Beep(1000,500);
                        incorrectguesses2++;
                    }
                    else{
                        correctguesses1++;
                    }
                    cout << "\tPlayer 1 Incorrect Guesses: " << incorrectguesses1 << endl;
                    cout << "\tPlayer 2 Incorrect Guesses: " << incorrectguesses2 << endl;
                }
                turn++;

                display_hangman(incorrectguesses1+incorrectguesses2);
                getch();
                system("cls");
            }
            else{
                entering_guessed_letter();
                cout << endl;
                int temp;
                totalattempts++;
                if(temp<incorrectGuesses){
                    Beep(1000,500);
                }
                cout<<"\tTotal Attempts: "<<totalattempts<<endl;
                display_hangman(incorrectGuesses);
                temp=incorrectGuesses;
                getch();
                system("cls");
            }

            if(mode==1){
                if (correctGuesses == size) {
                    system("cls");
                    cout << "\n\t\tYou guessed the word correctly" << endl;
                    gameover = true;
                }

                if (incorrectGuesses == 7 ) {
                    system("cls");
                    cout << "\n\t\tYou lost" << endl;
                    gameover = true;

                }
            }
            if(mode==2){
                if(correctguesses1+correctguesses2==size){
                    system("cls");
                    cout<<"\t\tGAMEOVER!\n"<<endl;
                    gameover=true;
                }
                if(incorrectguesses1+incorrectguesses2==7){
                    system("cls");
                    cout<<"\t\tGAMEOVER!\n"<<endl;
                    gameover=true;
                    break;
                }
            }


        }
        if(mode==2){
            competitionwinner(incorrectguesses1,incorrectguesses2,totalattempts1,totalattempts2);
        }
        if(mode==1){
            cout << "\t\tCorrect words: " << correctGuesses<<"/"<<size<< endl;
            calculate_score();
            cout << "\t\tYour score is: " << score << endl;
            cout<<"Total Attempts: "<<totalattempts<<endl;
            write_score_in_files();
        }
    }

    void select_secretWord(){
        ifstream word("Word.txt");
        try{
            if(word.is_open()){
                if(level==1){
                	while(1){
                    word>>secretWord;
                     if(secretWord.length()==4){
                        	srand(time(0));
    						int num= rand()%5+1;
                        	for(int i=1;i<num;i++){
                        		word>>secretWord;
							}
                            break;
                        }
                    }
                    
                }
            
                else if(level==2){
                    while(1){
                        word>>secretWord;
                        if(secretWord.length()==6){
                        	srand(time(0));
    						int num= rand()%5+1;
                        	for(int i=1;i<num;i++){
                        		word>>secretWord;
							}
                            break;
                        }
                    }}
                else if(level==3){
                    while(1){
                        word>>secretWord;
                        if(secretWord.length()==8){
                        	srand(time(0));
    						int num= rand()%5+1;
                        	for(int i=1;i<num;i++){
                        		word>>secretWord;
							}
                            break;
                        }
                    }}
                else{
                    cout<<"Level not defined."<<endl;
                }
            }
            else{
                throw("Trouble Accessing word file.");
            }
        }
        catch(const char * msg){
            cout<<msg<<endl;
        }
    }

    void display_empty_blanks(){
        cout<<"\t\t";
//formating + searching where the vowels are in the word
        for(int i=0;i<size;i++){
            if(secretWord[i]=='A'||secretWord[i]=='a'||secretWord[i]=='I'||secretWord[i]=='i'||secretWord[i]=='E'||secretWord[i]=='e'||secretWord[i]=='O'||secretWord[i]=='o'||secretWord[i]=='U'||secretWord[i]=='u'){
                cout<<"- ";
                cross[i]=1;
            }
            else{
                cout<<"- ";
                cross[i]=0;
            }
        }
        character_fill();
        cout<<endl;
//for adding the crosses underneath the places the word has a vowel
        cout<<"\t\t";
        for(int i=0;i<size;i++){
            if(cross[i]==1){
                cout<<"x ";
            }
            else{
                cout<<"  ";
            }
        }
        cout<<"\n";
    }

    void display_used_Alphabets(){
        cout<<"\n\n\tUsed Alphabets: ";
        for(int i=0;i<=alphabet_count;i++){
            cout<<guessedLetters[i]<<" ";
        }
        cout<<endl;
    }

    void display_blanks(){
//to display blanks on correct or incorrect guess
        cout<<"\n\t\t";
        for(int i=0;i<2*size;i++){
            cout<<characters[i];
        }
        cout<<endl;
        cout<<"\t\t";
        for(int i=0;i<size;i++){
            if(cross[i]==1){
                cout<<"x ";
            }
            else{
                cout<<"  ";
            }
        }
        cout<<endl;
    }
    bool isAlreadyGuessed(char guess){
        for(int i=0;i<=alphabet_count;i++){
            if(guess==guessedLetters[i]){//a==a
                return true;
            }

            else if(guess==guessedLetters[i]-32){//A==a
                return true;
            }
            else if(guess==guessedLetters[i]+32){//a==A
                return true;
            }
        }
        alphabet_count++;
        guessedLetters[alphabet_count] = guess;
        return false;
    }

    int IsACorrectGuess(char guess,int gamemode=0,int count=0){
//if correct letter is guessed, fills it in blanks.
        int j=0;
        for(int i=0;i<size;i++){
            if(guess==secretWord[i]){
                correctGuesses++;
                write_letter_on_blank(guess,i);
                j++;}
            else if(guess==secretWord[i]-32){
                correctGuesses++;
                write_letter_on_blank(secretWord[i],i);
                j++;}
        }
        if(j==0){
            incorrectGuesses++;
            return -1;}
        else{
            return 0;
        }
    }

    void character_fill(){
        int len=size*2;
//for spaces
        for(int i=1;i<len;i=i+2){
            characters[i]= ' ';
        }
//for blanks
        for(int i=0;i<len;i=i+2){
            characters[i]= '-';
        }
    }

    void write_letter_on_blank(char guess, int n){
        characters[2*n]=guess;
    }


    void display_hangman(int incorrectGuesses){
        if (incorrectGuesses <= 7) {
            switch (incorrectGuesses) {
                case 0: {
                    cout << "                                                     +---------+ " << endl;
                    cout << "                                                     {        || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              ||" << endl;
                    cout << "                                                    ============  " << endl;

                    break;
                }
                case 1: {
                    cout << "                                                     +---------+ " << endl;
                    cout << "                                                     {        || " << endl;
                    cout << "                                                     O        || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              ||" << endl;
                    cout << "                                                    ============  " << endl;

                    break;
                }
                case 2: {
                    cout << "                                                     +---------+ " << endl;
                    cout << "                                                     {        || " << endl;
                    cout << "                                                     O        || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              ||" << endl;
                    cout << "                                                    ============  " << endl;

                    break;
                }
                case 3: {
                    cout << "                                                    +---------+ " << endl;
                    cout << "                                                    {        || " << endl;
                    cout << "                                                    O        || " << endl;
                    cout << "                                                   /|        || " << endl;
                    cout << "                                                    |        || " << endl;
                    cout << "                                                    |        || " << endl;
                    cout << "                                                             || " << endl;
                    cout << "                                                             || " << endl;
                    cout << "                                                             ||" << endl;
                    cout << "                                                   ============  " << endl;

                    break;
                }
                case 4: {
                    cout << "                                                     +---------+ " << endl;
                    cout << "                                                     {        || " << endl;
                    cout << "                                                     O        || " << endl;
                    cout << "                                                    /|\\       || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                              ||  " << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                              ||" << endl;
                    cout << "                                                    ============  " << endl;

                    break;
                }
                case 5: {
                    cout << "                                                    +---------+ " << endl;
                    cout << "                                                    {        || " << endl;
                    cout << "                                                    O        || " << endl;
                    cout << "                                                   /|\\       || " << endl;
                    cout << "                                                    |        || " << endl;
                    cout << "                                                    |        || " << endl;
                    cout << "                                                   /         || " << endl;
                    cout << "                                                  /          || " << endl;
                    cout << "                                                             ||" << endl;
                    cout << "                                                   ============  " << endl;

                    break;
                }
                case 6: {
                    cout << "                                                    +---------+ " << endl;
                    cout << "                                                    {        || " << endl;
                    cout << "                                                    O        || " << endl;
                    cout << "                                                   /|\\       || " << endl;
                    cout << "                                                    |        || " << endl;
                    cout << "                                                    |        || " << endl;
                    cout << "                                                   / \\       || " << endl;
                    cout << "                                                  /   \\      || " << endl;
                    cout << "                                                             ||" << endl;
                    cout << "                                                   ============  " << endl;

                    break;
                }
                case 7: {
                    cout << "You lost:" << endl;
                    cout << "                                                     +---------+ " << endl;
                    cout << "                                                     {        || " << endl;
                    cout << "                                                   o          || " << endl;
                    cout << "                                                    \\         ||  " << endl;
                    cout << "                                                    /|\\       || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                     |        || " << endl;
                    cout << "                                                    / \\       || " << endl;
                    cout << "                                                   /   \\      || " << endl;
                    cout << "                                                              ||" << endl;
                    cout << "                                                              || " << endl;
                    cout << "                                                     ============  " << endl;

                    break;
                }
            }
        }
    }
    void hint_detector(){
        if(size==4){
            cout<<"\tHINT: Fruit & Vegetable"<<endl;
        }
        else if(size==6){
            cout<<"\tHINT: Animal"<<endl;
        }
        else if(size==8){
            cout<<"\n\tHINT: Country"<<endl;
        }
    }

    void entering_guessed_letter(){
//guessed letter is entered, if correct,is written at that specific position based on the result IsACorrectGuess() gives.
        hint_detector();
        cout<<"\n\tEnter letter: ";
        int value;
        cin>>guess;

        try{
            if(!((guess>=97 && guess<=122) || (guess>=65 && guess<=90) )){
                throw "\tEnter alphabets only!";
            }
            if(isAlreadyGuessed(guess)){
                cout<<"\tYou have already guessed "<<endl;
            }
            else{

                IsACorrectGuess(guess);
                display_blanks();
                display_used_Alphabets();

            }}
        catch (const char* msg){
            cout<<msg<<endl;
            display_blanks();
            display_used_Alphabets();

        }
    }

    void Easysort_scores(){
        fstream file;
        file.open("Easy.txt",ios::in);
        if(file.is_open()){
            string value,line;
            int number;
            while(!file.eof()){
                getline(file, line);
                if((line[0]>=65 && line[0]<=90) || (line[0]>=97 && line[0]<=122)){
                    value = " ";
                    value = line;
                }
                else{
                    if(!line.empty()){
                        number = stoi(line);
                    }
                }
                data[number] = value;
            }
        }
        file.close();
        remove("Easy.txt");
        file.open("Easy.txt", ios::app);
        if(file.is_open()){
            it = data.begin();
            while(it!=data.end()){
                file<<it->second<<endl;
                file<<it->first<<endl;
                it++;
            }
        }
        file.close();
    }

    void Mediumsort_scores(){
        fstream file;
        file.open("Medium.txt",ios::in);
        if(file.is_open()){
            string value,line;
            int number;
            while(!file.eof()){
                getline(file, line);
                if((line[0]>=65 && line[0]<=90) || (line[0]>=97 && line[0]<=122)){
                    value = " ";
                    value = line;
                }
                else{
                    if(!line.empty()){
                        number = stoi(line);
                    }
                }
                dataM[number] = value;
            }
        }
        file.close();
        remove("Medium.txt");
        file.open("Medium.txt", ios::app);
        if(file.is_open()){
            itM = dataM.begin();
            while(itM!=dataM.end()){
                file<<itM->second<<endl;
                file<<itM->first<<endl;
                itM++;
            }
        }
        file.close();
    }

    void Hardsort_scores(){
        fstream file;
        file.open("Hard.txt",ios::in);
        if(file.is_open()){
            string value,line;
            int number;
            while(!file.eof()){
                getline(file, line);
                if((line[0]>=65 && line[0]<=90) || (line[0]>=97 && line[0]<=122)){
                    value = " ";
                    value = line;
                }
                else{
                    if(!line.empty()){
                        number = stoi(line);
                    }
                }
                dataH[number] = value;
            }
        }
        file.close();
        remove("Hard.txt");
        file.open("Hard.txt", ios::app);
        if(file.is_open()){
            itH = dataH.begin();
            while(itH!=dataH.end()){
                file<<itH->second<<endl;
                file<<itH->first<<endl;
                itH++;
            }
        }
        file.close();
    }






    void write_score_in_files(){
        if(level==1){
            Easysort_scores();
        }
        else if(level==2){
            Mediumsort_scores();
        }
        else if(level==3){
            Hardsort_scores();
        }
    }

    void display_all_level_scores(){
        fstream file;
        file.open("Easy.txt",ios::in);
        if(file.is_open()){
            cout<<"------Easy------"<<endl;
            string line;
            while(getline(file,line)){
                cout<<line<<endl;
            }
            file.close();
        }
        file.open("Medium.txt",ios::in);
        if(file.is_open()){
            cout<<"------Medium------"<<endl;
            string line;
            while(getline(file,line)){
                cout<<line<<endl;
            }
            file.close();
        }
        file.open("Hard.txt",ios::in);
        if(file.is_open()){
            cout<<"------Hard------"<<endl;
            string line;
            while(getline(file,line)){
                cout<<line<<endl;
            }
            file.close();
        }
    }

    void High_score(){

        fstream file;
        file.open("Easy.txt",ios::in);
        if(file.is_open()){
            cout<<"------Easy------"<<endl;
            string line;
            for(int i=0;i<2;i++){
                getline(file,line);
                cout<<line<<endl;
            }
            file.close();
        }
        file.open("Medium.txt",ios::in);
        if(file.is_open()){
            cout<<"------Medium------"<<endl;
            string line;
            for(int i=0;i<2;i++){
                getline(file,line);
                cout<<line<<endl;
            }
            file.close();
        }
        file.open("Hard.txt",ios::in);
        if(file.is_open()){
            cout<<"------Hard------"<<endl;
            string line;
            for(int i=0;i<2;i++){
                getline(file,line);
                cout<<line<<endl;
            }
            file.close();
        }
    }



    void calculate_score(){
        if(incorrectGuesses==7&& correctGuesses==0){
        	cout<<"\nThe word was: "<<secretWord<<endl;
            score= 0;
        }
        else if(incorrectGuesses==7&& correctGuesses>0){
        	cout<<"\n    The Word was: "<<secretWord<<endl;
            score= ((correctGuesses*100/size)-incorrectGuesses);
            if(level==1){
                data.clear();
                data[score]=name;
                win();
            }
            else if(level==2){
                dataM.clear();
                dataM[score]=name;
                win();
            }
            else if(level==3){
                dataH.clear();
                dataH[score]=name;
                win();
            }
        }
        else if (incorrectGuesses<7&& correctGuesses==size){
        	//word_delete();
            score= ((correctGuesses*100/size)-incorrectGuesses);
            if(level==1){
                data.clear();
                data[score]=name;
                win();
            }
            else if(level==2){
                dataM.clear();
                dataM[score]=name;
                win();
            }
            else if(level==3){
                dataH.clear();
                dataH[score]=name;
                win();
            }
        }
    }

    void win(){
        cout << "\n**YOU GUESSED THE WORD CORRECTLY!**" << endl;
        cout << "                                                    +---------+ " << endl;
        cout << "                                                    {        || " << endl;
        cout<<"                                                             ||"<<endl;
        cout << "                                                    O        || " << endl;
        cout << "                        thank god i am save!      \\/|\\/      || " << endl;
        cout << "                                                    |        || " << endl;
        cout << "                                                    |        || " << endl;
        cout << "                                                   / \\       || " << endl;
        cout << "                                                  /   \\      || " << endl;
        cout << "                                                   ============  " << endl;

    }


    int tossing(){
        toss=rand()%2+1;
        return toss;}

    int getcorrectguess(){
        return correctGuesses;
    }
    void competition(){
        int flag=tossing();
        system("cls");
        cout<<"\n\t\tEntering Player 1 and Player 2 in the battlefield\n"<<endl;
        cout<<"\t\tTossing starts now\n"<<endl;
        cout<<"\t\t-------------------------"<<endl;
        cout<<"\t\t|Toss is won by Player "<<flag<<"|"<<endl;
        cout<<"\t\t-------------------------"<<endl;
        cout<<"\n\t\tPlayer " <<flag<<" would guess the word first: ";
        cout<<"\n\t\tStart Guessing!!"<<endl;
        getch();
        system("cls");
        startGame(2);
    }
    void competitionwinner(int incorrectguesses1,int incorrectguesses2,int totalattempts1,int totalattempts2){
        if(incorrectguesses1<incorrectguesses2){
            cout<<"Player 1 is the winner!"<<endl;
        }
        else if(incorrectguesses1>incorrectguesses2){
            cout<<"Player 2 is the winner!"<<endl;
        }
        else if(incorrectguesses1==incorrectguesses2){
            if(totalattempts1<totalattempts2){
                cout<<"Player 1 is the winner!"<<endl;
            }
            if(totalattempts1>totalattempts2){
                cout<<"Player 2 is the winner!"<<endl;
            }
            if(totalattempts1==totalattempts2){
                cout<<"Its a Draw!"<<endl;
            }


        }


    }

};


int Hangman::toss=0;
int Hangman::correctGuesses=0;
int Hangman::incorrectGuesses=0;

int main() {

    Hangman g("",10,10,10);

    system("cls");
    char choice;
    main:
    system("cls");
     cout<<"                 *************************************"<<endl;
    cout<<"                        WELCOME TO HANGMAN GAME! "<<endl;
    cout<<"                 *************************************"<<endl;
    cout<<"                 *************************************"<<endl;
    cout<<"                 > Press Y to proceed with the game "<<endl;
    cout<<"                 > Press I for instructions"<<endl;
    cout<<"                 > Press H to view the highest score "<<endl;
    cout<<"                 > Press L to view the leaderboard "<<endl;
    cout<<"                 > Press Q to quit the game "<<endl;
       cout<<"                 *************************************"<<endl;
    cin>>choice;
    choice=tolower(choice);
    try{
    	if(!(choice=='L'||choice=='l'||choice=='h'||choice=='H'||choice=='I'||choice=='i'||choice=='Y'||choice=='y'||choice=='Q'||choice=='q')){
    		throw "Choose from above options only!";
		}
	}
	catch(const char *msg){
		cout<<msg<<endl;
		getch();
		goto main;
		cout<<"Press any key to continue.";
	}

    switch(choice){
        case 'y':
            system("cls");
            int mode,flag2;
            g.registration();
            while(flag2!=0) {
                g.set_level();
                try {
                    if (!(g.get_level() == 1 || g.get_level() == 2 || g.get_level() == 3)) {
                        throw " Please choose from the above levels only.";
                    }
                    g.initializing();
                    g.set_mode();
                    mode = g.get_mode();

                    try {
                        if (!(mode == 1 || mode == 2)) {
                            throw " Please choose from available modes only.";
                        }
                        g.initializing();
                        if (mode == 2) {
                            g.competition();
                        } else {
                            g.startGame(1);
                        }
                    }
                    catch (const char *msg) {
                        cout << msg << endl;
                    }
                }
                catch (const char *msg) {
                    cout << msg << endl;
                }
                getch();
                system("cls");
                cout << "Would you like to play again? Press 1-yes 0-no: ";
                cin >> flag2;
                if(flag2==0){
                    goto main;
                }

            }
            break;
        case 'i':
            system("cls");
            cout<<"\t\t\t\t\tWELCOME TO THE HANGMAN!\n"<<endl;
            cout<<"1. Your Goal is to guess the hidden word by suggesting letters\n within a certain number of attempts."<<endl;

            cout<<"\n2.You can play Hangman in single mode or in competition mode with level of difficulty of your choice"<<endl;

            cout<<"\n3. The game will provide you with a blank space for each letter in the hidden word.\n Your task is to guess the word by suggesting letters one at a time."<<endl;

            cout<<"\n4. To make a guess, simply type a letter on your keyboard and press enter.\n Make sure to enter only a single letter from A to Z\n(both uppercase and lowercase letters are allowed)."<<endl;

            cout<<"\n5. If the letter you guessed is present in the hidden word, \nit will be revealed in the corresponding blank spaces. If the letter appears multiple times,\nall instances will be filled in."<<endl;

            cout<<"\n6. If the letter you guessed is not present in the hidden word,\n you will receive a message indicating that the letter is incorrect."<<endl;

            cout<<"\n7. Be careful! You only have a limited number of \nattempts to guess the word. The life of Hangman is in your hands ;)"<<endl;

            cout<<"\n8. The game will end under the following conditions:\n- You correctly guess the entire word and win the game.\n- Your incorrect guesses exceed seven."<<endl;

            cout<<"\n9.You will be alloted with score at the end of the game on basis \nof your performance during the game."<<endl;

            cout<<"\n10. Your score will be displayed on the leaderboard with other potential players"<<endl;

            cout<<"\n11. The highest scorer will be displayed in the highest score section"<<endl;

            cout<<"\n12. In competition mode you will have to fight your battle against another player.\nThe player with greater number of correct guesses will win this battle."<<endl;

            cout<<"\n13. After the game ends, you will have the option to play again,\nview the leaderboard or exit the game."<<endl;

            cout<<"\nThat's it! Unveil your vocabulary powers and Have fun playing Hangman and\n try to guess the word correctly within mininum attempts. Good luck!"<<endl;
            getch();
            goto main;
            break;
        case 'h':
            system("cls");
            g.High_score();
            getch();
            goto main;
            break;

        case 'l':
            system("cls");
            g.display_all_level_scores();
            getch();
            goto main;
            break;
        case 'q':
            char flag;
            cout<<"\n\tAre you sure you want to quit the game?(Press Y for yes and N for no)"<<endl;
            cin>>flag;
            flag=tolower(flag);
            if(flag=='y'){
                system("cls");


                cout << "                                                    O       " << endl;
                cout << "                                    BYE BYE!      \\/|\\/      " << endl;
                cout << "                                                    |         " << endl;
                cout << "                                                    |         " << endl;
                cout << "                                                   / \\        " << endl;
                cout << "                                                  /   \\       " << endl;

                exit(0);
            }
            else{
                goto main;
            }
    }
}