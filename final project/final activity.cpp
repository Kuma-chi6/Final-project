#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct player{
    string name;
    int hp = 100;
    int attack = 20;
    int level = 1;
    int gold = 0;
    int exp = 0;
    int potion = 0;
    string item = "None";
};

struct goblin{
    int hp = 30;
    int attack = 10;
    int level = 1;
};

string playerName();
bool generateQuestions(int level);
bool askMathQuestions(int level, player &hero);
char getOperators(int level);
void displayMenu();
void firstEnemy();
void heal(player &hero);
void viewStats(player &hero);
void battleGoblin(player &hero, goblin &enemy);

int main()
{
    srand(time(0));
    displayMenu();
    cout << endl;

    // create hero
    player hero;
    hero.name = playerName();

    cout << "Welcome, " << hero.name << "!\n\n"; 

    goblin enemy1;
    battleGoblin(hero, enemy1);


   return 0;
}

void displayMenu(){
    cout << "====================================" << endl;
    cout << "       MATH ADVENTURE RPG           " << endl;
    cout << "====================================" << endl; 
}

string playerName(){
    string heroName;
    while (true){

        cout << "Enter Hero Name: ";
        getline(cin, heroName);
        cout << endl;

        bool valid = true;
        for(size_t i = 0; i < heroName.length(); i++){
            if(!isalpha(heroName[i]) && !isspace(heroName[i])){
                valid = false;
                break;
            }
        }

        if(heroName.empty()){
            cout << "Name cannot be empty. Please enter a name." << endl;
        }
        else if(!valid){
            cout << "Name can only contain letters and spaces!" << endl;
        }
        else{
            bool newWord = true;
            for(size_t i = 0; i < heroName.length(); i++){
                if(isspace(heroName[i])){
                    newWord = true;
                }
                else if(newWord){
                    heroName[i] = toupper(heroName[i]);
                    newWord = false;
                }
                else{
                    heroName[i] = tolower(heroName[i]);
                }
            }
            return heroName;
        }
    }
}

void firstEnemy(){
    cout << "Your Journey Begins....." << endl;
    cout << "A Goblin Appears!\n";
}

char getOperator(int level){
    char easy[] = {'+', '-'};
    char medium = 'x';
    char hard[] = {'+', '-'};

    if(level == 1){
        return easy[rand() % 2];
    }
    else if(level == 2){
        return medium;
    }
    else{
        return hard[rand() % 4];
    }
}

bool askMathQuestions(int level, player &hero){
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;
    int num3;
    int answer;
    int correctAnswer;
    char op = getOperator(hero.level);
    char op2;

    switch(hero.level){
        case 1:
            op = getOperator(1);
            cout << "\nSolve to attack:\n";
            cout << num1 << " " << op << " " << num2 << " " << "= " << "?\n";
            cout << "\nAnswer: ";
            cin >> answer;
            
            if(op == '+') correctAnswer = num1 + num2;
            else correctAnswer = num1 - num2;

            return answer == correctAnswer;
        
        case 2:
            cout << "Solve to attack:\n";
            cout << num1 << " " << "*" << " " << num2 << " " << "= " << "?\n";
            cout << "\nAnswer: ";
            cin >> answer;
            
            correctAnswer = num1 * num2;
            return answer == correctAnswer;

        case 3:
            num3 = rand() % 100 + 1;
            op2 = (rand() % 2 == 0) ? '+' : '-';

            cout << "Solve to attack\n";
            cout << "(" << num1 << " " << "x " << num2 << ") " << op2 << " " << num3 << " " << "= ?\n";
            cout << "\nAnswer: ";
            cin >> answer;

            int product;
            product = num1 * num2;

            if(op2 == '+') correctAnswer = product + num3;
            else correctAnswer = product - num3;

            return answer == correctAnswer;
    }
    return false;
}

void heal(player &hero){
    if(hero.potion <= 0){
        cout << "\nNo more potion gng...\n";
        return;
    }

    hero.potion--;

    int healAmount = 30;
    hero.hp += healAmount;

    if(hero.hp > 100) hero.hp = 100;
    cout << "\n==============================" << endl;
    cout << "You healed " << healAmount << " Current HP: " << hero.hp << endl;
    cout << "==============================" << endl;
}

void viewStats(player &hero){
    cout << "\n=== STATS ===" << endl;
    cout << "Hero: " << hero.name << endl;
    cout << "HP: " << hero.hp << endl;
    cout << "Attack: " << hero.attack << endl;
    cout << "Level: " << hero.level << endl;
    cout << "Gold: " << hero.gold << endl;
    cout << "Exp: " << hero.exp << endl;
    cout << "Potion: " << hero.potion << endl;
    cout << "Item: " << hero.item << endl; 
    cout << "=== STATS ===" << endl;
}

void battleGoblin(player &hero, goblin &enemy){
    while(hero.hp > 0 && enemy.hp > 0){
        int choice;

        // Display Stats
        cout << "\n=============" << endl;
        cout << "Hero HP: " << hero.hp << endl;
        cout << "Goblin HP: " << enemy.hp << endl;
         cout << "=============" << endl;

        // Menu
        cout << "\n1. Attack \n2. Heal \n3. View Stats \n4. Run" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        switch(choice){
            case 1:
                if(askMathQuestions(hero.level, hero)){
                    enemy.hp -= hero.attack;
                    cout << "\n============================" << endl;
                    cout << "Correct you dealt " << hero.attack << " damage!\n";
                    cout << "============================" << endl;
                }
                else{
                    cout << "\n=================================" << endl;
                    cout << "Wrong answer! Your attack missed\n";
                    cout << "=================================\n" << endl;
                }
                break;
            case 2:
                heal(hero);
                break;
            case 3:
                viewStats(hero);
                continue;
                break;
            case 4:
                cout << "\nYOU RAN AWAY COWARD!!!\n";
                return;
            default:
                cout << "\nInvalid Choice! Try Again.\n";
                continue;
        }

        if(enemy.hp > 0 && hero.hp > 0){
            hero.hp -= enemy.attack;
            cout << "\n==================" << endl;
            cout << "Goblin attacks!" << endl;
            cout << "You lost: " << enemy.attack << " HP.\n";
            cout << "==================" << endl;
        }

        if(hero.hp <= 0){
            cout << "\nYou Died Gng! Game Over!\n";
        }
        else if(enemy.hp <= 0){
            cout << "\nGoblin Defeated!\n";

            hero.gold += 50;
            hero.exp += 100;

            cout << "\n+50 Gold" << endl;
            cout << "+100 XP" << endl;
            
            int buy;
            
            cout << "\nPotion cost a 20 gold. You have " << hero.gold << " gold.\n";
            cout << "Buy a potion? (1) (2): ";
            cin >> buy;

            if(buy == 1 && hero.gold >= 20){
                hero.potion++;
                hero.gold -= 20;

                cout << "\nBought a potion! Total potions: " << hero.potion << endl;
                cout << "Gold Left: " << hero.gold << endl;
            }
        }
    }
}

// add choice to buy sword and potion, use pointers to update enemy LATER