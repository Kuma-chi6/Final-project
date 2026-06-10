#include <iostream>
#include <random>
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;

// MATH ADVENTURE GAME

char getOperator(int level){
    char easy[] = {'+', '-'};
    char medium = 'x';
    char hard[] = {'x', '/', '-', '+'};

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

void easy(){
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;
    int level = 1;
    char op = getOperator(level);

    cout << num1 << " " << op << " " << num2 << endl;
}

void medium(){
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;
    int level = 2;
    char op = getOperator(level);

    cout << num1 << " " << op << " " << num2 << endl;
}

void hard(){
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;
    int num3 = rand() % 100 + 1;
    int level = 1;
    char op = getOperator(level);

    cout << "(" << num1  << " " << "*" << " " << num2 << ") " << op << " " << num3 << endl;
}


int main()
{
    srand(time(0));

    cout << "Easy Question: "; 
    easy();

    cout << "Medium Question: "; 
    medium();
    cout << "Hard Question: ";
    hard();

   return 0;
}