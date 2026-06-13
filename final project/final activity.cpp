#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct player{
    string name;
    int hp = 100;
    int maxHp = 100;
    int baseAttack = 20;
    int attack = 20;
    int level = 1;
    int gold = 0;
    int potion = 0;
    int exp = 0;
    int expNeeded = 100;
    string item = "None";
    bool hasSword = false;
    int totalCorrect = 0;
    int totalWrong = 0; 
};

struct enemy{
    string enemyName;
    int hp ;
    int attack;
    int level;
    int goldReward;
    int expReward;
};

string playerName();
void startUpMenu();
bool generateQuestions(int level);
bool askMathQuestions(int level, player &hero);
char getOperators(int level);
void displayMenu();
void firstEnemy();
void secondEnemy();
void finalBoss();
void heal(player &hero);
void swordMenu(player &hero);
void viewStats(player &hero);
void displayBasicStats(player &hero);
void displayMathStats(player &hero);
void battleEnemy(player &hero, enemy* currentEnemy);
void equipSword(player &hero);
void unequipSword(player &hero);
void shop(player &hero);
void updateExpNeeded(player &hero);
void levelUp(player &hero);
void displayEndingStats(player &hero);
void endingMenu(player &hero);
void playAgain();
void gameOver(player &hero, enemy *currentEnemy);

int main(){
    srand(time(0));
    startUpMenu();

    player hero;
        displayMenu();
        cout << endl;

        // create hero
        hero.name = playerName();

        cout << "Welcome, " << hero.name << "!\n\n"; 

        enemy enemies[] = {
            {"Goblin", 30, 10, 1, 50, 100},
            {"Skeleton", 75, 15, 2, 75, 150},
            {"Dragon", 150, 20, 3, 150, 250}
        };

        int totalEnemies = 3;

        for(int i = 0; i < totalEnemies; i++){
            if(i == 0){
                firstEnemy();
            }
            else if(i == 1){
                secondEnemy();
            }
            else if(i == 2){
                finalBoss();
            }
            battleEnemy(hero, &enemies[i]);

            if (hero.hp <= 0){
               gameOver(hero, &enemies[i]);
               return 0;
            }
            if(i < totalEnemies - 1){
                shop(hero);
            }
        }

        displayEndingStats(hero);
        playAgain();    

   return 0;
}

void startUpMenu(){
    int choice;
    bool validInput = false;

    while(!validInput){
        cout << "=============================" << endl;
        cout << "                             " << endl;
        cout << "    1. Start Game            " << endl;
        cout << "    2. How to play           " << endl;
        cout << "    3. Exit                  " << endl;
        cout << "                             " << endl;
        cout << "=============================" << endl;
        cout << "Choice: ";
        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid Input! Please enter 1, 2, or 3\n\n";
            continue;
        }

        switch(choice){
            case 1:
                cout << "\nStarting game.....\n" << endl;
                validInput = true;
                break;
            case 2:
                cout << "\n=== HOW TO PLAY ===" << endl;
                cout << "1. Answer math questions to attack enemies" << endl;
                cout << "2. Correct answer deal damage" << endl;
                cout << "3. Wrong answer make your attack miss" << endl;
                cout << "4. Buy Item/Potion at the shop after defeating a enemy" << endl;
                cout << "5. Use potions to heal (+30 HP)" << endl;
                cout << "6. Buy sword for +10 attack" << endl;
                cout << "7. Level up by gathering exp from defeating the enemies" << endl;
                cout << "8. Defeat all enemies to win" << endl;
                cout << "\nPress enter to continue.....";
                cin.ignore();
                cin.get();
                break;
            case 3:
                cout << "\nThanks for playing! Goodbye!!\n";
                exit(0);
                break;
            default:
                cout << "Invalid GNG";
                break;
        }
    }
}

void displayMenu(){
    cin.ignore();
    cout << "====================================" << endl;
    cout << "                                    " << endl;
    cout << "           WELCOME TO               " << endl;
    cout << "        MATH ADVENTURE RPG          " << endl;
    cout << "                                    " << endl;
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
    cout << "=========================\n\n";
    cout << "Your Journey Begins....." << endl;
    cout << "A Goblin Appears!\n";
    cout << "\n=========================\n";
}

void secondEnemy(){
    cout << "\n===========================" << endl;
    cout << "          LEVEL 2           " << endl;
    cout << "===========================" << endl;
    
    cout << "===============================\n";
    cout << "\nJust bones but they hit hard...\n\n";
    cout << "===============================" << endl;
}

void finalBoss(){
    cout << "\n===========================" << endl;
    cout << "          LEVEL 3           " << endl;
    cout << "===========================" << endl;

    cout << "===================================================\n";
    cout << "\nThe ground shakes as the dragon lands before you...\n\n";
    cout << "===================================================" << endl;
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
        cout << "Buy potion from the shop after defeating enemies\n";
        return;
    }

    hero.potion--;

    int healAmount = 30;
    hero.hp += healAmount;

    if(hero.hp > hero.maxHp) hero.hp = hero.maxHp;
    cout << "\n==============================" << endl;
    cout << "You used a potion! (" << hero.potion << " left)" << endl;
    cout << "You healed " << healAmount << " Current HP: " << hero.hp << endl;
    cout << "Current HP: " << hero.hp << endl;
    cout << "==============================" << endl;
}

void equipSword(player &hero){
    if(hero.hasSword){
        hero.item = "Sword (+10 ATK)";
        hero.attack = hero.baseAttack + 10;
        cout << "\nYou have equipped the sword! Attack increased to " << hero.attack << "!\n";
    } else{
        cout << "\nYou dont have a sword";
    }
}   

/* Create a way for the player(hero) to unequip Weapon(Sword) */
void unequipSword(player &hero){
    if(!hero.hasSword){
        cout << "\nYou don't own a sword\n";
        return;
    }

    if(hero.hasSword && hero.item == "Sword (+10 ATK)"){
        hero.attack = hero.baseAttack;
        hero.item = "None";

        cout << "\n=================" << endl;
        cout << "SWORD UNEQUIPPED!!" << endl;
        cout << "Attack decreased to " << hero.attack << endl;
        cout << "=================\n";
    }
    else{
        cout << "\nYour sword is already unequipped\n";
        cout << "Current attack: " << hero.attack << endl;
    }
}

void swordMenu(player &hero){
    int choice;
    if(hero.hasSword){
        cout << "\n===SWORD MENU===" << endl;
        cout << "1. Equip Sword" << endl;
        cout << "2. Unequip Sword" << endl;
        cout << "3. Back to battle";
        cout << "\n===SWORD MENU===" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                equipSword(hero);
                break;
            case 2:
                unequipSword(hero);
                break;
            case 3:
                cout << "\nReturning to battle...\n";
                break;
        }
    }
    else{
        cout << "\nPress enter to continue....";
        cin.ignore();
        cin.get();
    }
}

void updateExpNeeded(player &hero){
    if(hero.level == 1){
        hero.expNeeded = 100;
    }
    else if(hero.level == 2){
        hero.expNeeded = 150;
    }
    else{
        hero.expNeeded = 0;
    }
}

void levelUp(player &hero){
    if(hero.level >= 3){
        cout << "\nYou're already at MAX LVL!\n";
        return;
    }

    while(hero.exp >= hero.expNeeded && hero.level < 3){
        hero.exp -= hero.expNeeded;
        hero.level++;

        hero.maxHp += 20;
        hero.hp += 20;
        hero.baseAttack += 5;
        
        if(hero.hasSword && hero.item == "Sword (+10 ATK)"){
            hero.attack = hero.baseAttack + 10;
        }
        else{
            hero.attack = hero.baseAttack;
        }

        updateExpNeeded(hero);

        cout << "\n====================================";
        cout << "\n      LEVEL UP! Now Level " << hero.level << "! ";
        cout << "\n====================================" << endl;
        cout << "Max HP Increased to: " << hero.maxHp << endl;
        cout << "Current HP: " << hero.hp << "/" << hero.maxHp << endl;
        cout << "Attack Increased to: " << hero.attack; 
        cout << "\n====================================\n";
    }
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

    swordMenu(hero);
    
}

void battleEnemy(player &hero, enemy* currentEnemy){
    while(hero.hp > 0 && currentEnemy->hp > 0){
    int choice;

        // Display Stats
        cout << "\n================" << endl;
        cout << "Hero HP: " << hero.hp << endl;
        cout << currentEnemy->enemyName << " HP: " << currentEnemy->hp << endl;
         cout << "================" << endl;

        // Menu
        cout << "\n1. Attack \n2. Heal \n3. View Stats \n4. Equip/Unequip Sword \n5. Run" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        switch(choice){
            case 1:
                if(askMathQuestions(hero.level, hero)){
                    hero.totalCorrect++;

                    int damage = hero.attack;
                    bool isCritical = (rand() % 100) < 20;
                    if(isCritical){
                        damage = hero.attack * 2;
                        cout << "\n=============" << endl;
                        cout << "CRITICAL HIT!!" << endl;
                        cout << "==============" << endl;
                    }

                    currentEnemy->hp -= damage;

                    cout << "\n============================" << endl;
                    cout << "Correct you dealt " << damage << " damage!\n";
                    cout << "============================" << endl;
                }
                else{
                    hero.totalWrong++;

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
                if(!hero.hasSword){
                    cout << "\nYou don't own a sword\n";
                    cout << "Press enter to continue....";
                    cin.ignore();
                    cin.get();
                    continue;
                }
                else{
                    int equipChoice;
                    cout << "\n1. Equip Sword \n2. Unequip Sword \nChoice: ";
                    cin >> equipChoice;

                    if(equipChoice == 1) equipSword(hero);
                    else if(equipChoice == 2) unequipSword(hero);
                    else cout << "\nInvalid Choice!\n";
                    continue;
                }
                break;
            case 5:
                cout << "\nYOU RAN AWAY COWARD!!!\n";
                return;
            default:
                cout << "\nInvalid Choice! Try Again.\n";
                continue;
        }

        if(currentEnemy->hp > 0 && hero.hp > 0){
            hero.hp -= currentEnemy->attack;
            cout << "\n==================" << endl;
            cout << currentEnemy->enemyName << " attacks!" << endl;
            cout << "You lost: " << currentEnemy->attack << " HP.\n";
            cout << "==================" << endl;
        }

        if(hero.hp <= 0){
            cout << "\nYou Died Gng! Game Over!\n";
        }
        else if(currentEnemy->hp <= 0){
            cout << "\n" << currentEnemy->enemyName << " Defeated!\n";

            hero.gold += currentEnemy->goldReward;
            hero.exp += currentEnemy->expReward;

            cout << "\n+ " << currentEnemy->goldReward << " Gold\n";
            cout << "+ " << currentEnemy->expReward << " Exp\n";
            levelUp(hero);
        }
    }
}

void shop(player &hero){
    int choice;

    while (true){
        cout << "\n=== SHOP ===" << endl;
        cout << "Gold: " << hero.gold << endl;
        cout << "Potions owned: " << hero.potion << endl;
        cout << "=== SHOP ===" << endl;
        cout << "1. Buy Potion (20 Gold)" << endl;
        cout << "2. Buy Sword (50 Gold) - +10 Atk" << endl;
        cout << "3. Leave Shop" << endl;
        cout << "Choice: ";

        cin >> choice;

        switch(choice){
            case 1:
                if(hero.gold >= 20){
                    hero.potion++;
                    hero.gold -= 20;
                    
                    cout << "\nBought a potion! Total: " << hero.potion << endl;
                    cout << "Gold left: " << hero.gold << endl;
                }
                else{
                    cout << "\nNot Enough Gold." << endl;
                }
                break;

            case 2:
                if(hero.gold >= 50 && !hero.hasSword){
                    hero.gold -= 50;
                    hero.hasSword = true;
                    cout << "\nYou bought a sword\n";
                    cout <<  "Gold left: " << hero.gold << endl;

                    char equipNow;
                    cout << "Equip now? (y) (n): ";
                    cin >> equipNow;

                    if(equipNow == 'y' || equipNow == 'Y'){
                        equipSword(hero);
                    }
                    else if(hero.hasSword){
                        cout << "\nYou already own a sword!\n";
                    }
                    else{
                        cout << "\nNot enough gold! need 50 gold.";
                    }
                }  
                break;

            case 3:
                cout << "\nLeaving Shop....\n";
                return;
            default:
                cout << "\nInvalid choice\n";
        }
    }
}

void gameOver(player &hero, enemy *currentEnemy){
    cout << "\n=====================================\n";
    cout << "\n             GAME OVER               \n";
    cout << "\n=====================================" << endl;
    cout << "GAME OVER! You were defeated by the " << currentEnemy->enemyName << "!" << endl;
    cout << "Final Level: " << hero.level << endl;
    cout << "Final Gold: " << hero.gold << endl;
    cout << "Correct Answers: " << hero.totalCorrect << endl;
    cout << "Wrong Answers: " << hero.totalWrong << endl;

    int restartChoice;
    cout << "\n1. Play Again";
    cout << "\n2. Exit";
    cout << "\nChoice: ";
    cin >> restartChoice;

    if(restartChoice == 1){
        cout << "\nRestarting game..." << endl;
        main();
        return;
    }
    else{
        cout << "\nThanks for playing!" << endl;
        return;
    }

}

void displayBasicStats(player &hero){
    cout << "\n=== STATS ===" << endl;
    cout << "Hero: " << hero.name << endl;
    cout << "HP: " << hero.hp << endl;
    cout << "Attack: " << hero.attack << endl;  
    cout << "Level: " << hero.level << endl;
    cout << "Gold: " << hero.gold << endl;
    cout << "Exp: " << hero.exp << endl;
    cout << "Potion: " << hero.potion << endl;
    cout << "Item: " << hero.item << endl; 
}

void displayMathStats(player &hero){
    cout << "\n=== MATH PERFORMANCE ===" << endl;
    cout << "Correct Answers: " << hero.totalCorrect << endl;
    cout << "Wrong Answers: " << hero.totalWrong << endl;

    int total = hero.totalCorrect + hero.totalWrong;
    if(total > 0){
        int accuracy = (hero.totalCorrect * 100) / total;
        cout << "Accuracy: " << accuracy << "% " << endl;
        
        if(accuracy == 100) cout << "\nMATH GRANDMASTER" << endl;
        else if(accuracy >= 90) cout << "MATH MASTER" << endl;
        else if(accuracy >= 80) cout << "Excellent" << endl;
        else if(accuracy >= 70) cout << "Good" << endl;
        else if(accuracy >= 60) cout << "Needs more practice" << endl;
        else cout << "FAILED GNG" << endl;
    }
}

void displayEndingStats(player &hero){
    cout << "\n===================";
    cout << "\n    FINAL STATS    ";
    cout << "\n===================";

    displayBasicStats(hero);
    displayMathStats(hero);

    cout << "\n=== FINAL RATING ===" << endl;
    int total = hero.totalCorrect + hero.totalWrong;
    if(total > 0){
        int accuracy = (hero.totalCorrect * 100) / total;
        if(hero.level >= 3 && accuracy >= 90){
            cout << "LEGENDARY HERO!!!!";
        }
        else if(hero.level >= 2 && accuracy >= 80){
            cout << "SKILLED ADVENTURER!!" << endl;
        }
        else{
            cout << "PROMISING ROOKIE" << endl;
        }
    }
}

void endingMenu(player &hero){
        cout << "\n=====================================";
        cout << "\n       CONGRATULATIONS YOU WIN!      ";
        cout << "\n=====================================" << endl;
        cout << "You defeated all the enemies and saved the campus!\n";
        cout << "Final Level: " << hero.level << endl;
        cout << "Final Gold: " << hero.gold << endl; 
        cout << "Hero Level: " << hero.level << endl;
}

void playAgain(){
    int choice;

    cout << "\n\n================================" << endl;
    cout << "          PLAY AGAIN?           " << endl; 
    cout << "================================" << endl;
    cout << "1. Play Again \n2. Exit \nChoice: ";
    cin >> choice;

    switch(choice){
        case 1:
            cout << "\nRestarting game....\n\n";
            main();
            return;
            break;
        case 2:
            cout << "\nThanks for playing! Goodbye!!";
            exit(0);
            break;
        case 3:
            cout << "\nInvalid choice retrying...\n";
            return;
            break;
    }
}


// add choice to buy sword and potion, use pointers to update enemy LATER

/* 1. shop - DONE
   2. sword - DONE
   3. potion - DONE
   4. level system - DONE
   5. equip and unequip(wala pa) sword - DONE
   6. stats viewing and updating - DONE
   7. display the total answers after defeating the dragon - DONE
   8. display the mistakes also - DONE
   9. total gold also - DONE
   10. fix the potion thingy - DONE 
   11. loop the game after finishing ask if want to play again and make retrun to startup - DONE
   12. Ask if want to try again after dying - DONE */
