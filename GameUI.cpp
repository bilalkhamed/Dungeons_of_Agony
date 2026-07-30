#include "GameUI.h"

void GameUI::clearScreen() const{
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For mac (Bilal)
    #endif
}

char GameUI::getCleanInput() const {
    char inp = cin.get();
    if (inp != '\n'){
        cin.ignore(10000, '\n');
    }
    return inp;
}

int GameUI::showMainMenu() const{
    clearScreen();
    cout << "=====================================================" << endl;
    cout << "============" << "DUNGEONS OF AGONY" << "============" << endl;
    cout << "=====================================================" << endl << endl;
    cout << "   [1] Start Game" << endl;
    cout << "   [2] Exit" << endl << endl;
    cout << "=====================================================" << endl;
    cout << "Enter choice (1-2) and press ENTER: ";

    char inp = getCleanInput();
    if (inp == '1'){
        return 1;
    }
    else if (inp == '2'){
        return 2;
    }
    else{
        return 0;
    }
}

char GameUI::showDifficultyMenu(int choice) const {
    clearScreen();
    cout << "=====================================================" << endl;
    cout << "============" << "SELECT DIFFICULTY" << "============" << endl;
    cout << "=====================================================" << endl << endl;
    cout << "   OPTIONS:                   DIFFICULTY DETAILS:" << endl;
    cout << "-------------------       ----------------------" << endl;
    
    if (choice == 1){ cout << "  > [*] 1. Easy    <              - Dungeons to Clear : 3" << endl;}
    else{             cout << "    [ ] 1. Easy                   - Dungeons to Clear : 3" << endl;}

    if (choice == 2){ cout << "  > [*] 2. Medium  <              - Dungeons to Clear : 6" << endl;}
    else{             cout << "    [ ] 2. Medium                 - Dungeons to Clear : 6" << endl;}

    if (choice == 3){ cout << "  > [*] 3. Hard    <              - Dungeons to Clear : 10" << endl;}
    else{             cout << "    [ ] 3. Hard                   - Dungeons to Clear : 10" << endl;}

    cout << "                                  ----------------------" << endl << endl;

    cout << "=====================================================" << endl;
    cout << "CONTROLS: [W/S] MOVE SELECTION | [E] TO CONFIRM CHOICE" << endl;
    cout << "=====================================================" << endl;
    cout << " Action > ";

    return getCleanInput();
}

char GameUI::showClassMenu(int choice) const {
    clearScreen();

    // Needs a default constructor for each class
    Warrior tempWarrior;
    Mage tempMage;
    Assassin tempAssassin;

    cout << "=====================================================" << endl;
    cout << "==============" << "SELECT CLASS" << "===============" << endl;
    cout << "=====================================================" << endl << endl;
    cout << "   CLASSES:                   CLASS STATS:" << endl;
    cout << "-------------------       ----------------------" << endl;

    if (choice == 1){ cout << "  > [*] 1. Warrior <              - Base HP          : " << tempWarrior.getHp() << endl; }
    else{             cout << "    [ ] 1. Warrior                - Base HP          : " << tempWarrior.getHp() << endl; }

    if (choice == 2){ cout << "  > [*] 2. Mage    <              - Base HP          : " << tempMage.getHp() << endl; }
    else{             cout << "    [ ] 2. Mage                   - Base HP          : " << tempMage.getHp() << endl; }

    if (choice == 3){ cout << "  > [*] 3. Assassin<              - Base HP          : " << tempAssassin.getHp() << endl; }
    else{             cout << "    [ ] 3. Assassin               - Base HP          : " << tempAssassin.getHp() << endl; }

    if (choice == 1) {
        cout << "                                  - Base Damage      : " << tempWarrior.getDamage() << endl;
        cout << "                                  -Attack Speed     : " << tempWarrior.getAttackSpeed() << endl;
        cout << "                                  - Armor            : " << tempWarrior.getArmor() << endl;
        cout << "                                  - Gold Ratio       : " << tempWarrior.getGoldRatio() << "x" << endl;
    } 
    else if (choice == 2) {
        cout << "                                  - Base Damage      : " << tempMage.getDamage() << endl;
        cout << "                                  - Attack Speed     : " << tempMage.getAttackSpeed() << endl;
        cout << "                                  - Armor            : " << tempMage.getArmor() << endl;
        cout << "                                  - Gold Ratio       : " << tempMage.getGoldRatio() << "x" << endl;
    } 
    else if (choice == 3) {
        cout << "                                  - Base Damage      : " << tempAssassin.getDamage() << endl;
        cout << "                                  - Attack Speed     : " << tempAssassin.getAttackSpeed() << endl;
        cout << "                                  - Armor            : " << tempAssassin.getArmor() << endl;
        cout << "                                  - Gold Ratio       : " << tempAssassin.getGoldRatio() << "x" << endl;
    }

    cout << "                                  ----------------------" << endl << endl;

    cout << "=====================================================" << endl;
    cout << "CONTROLS: [W/S] MOVE SELECTION | [E] TO CONFIRM CHOICE" << endl;
    cout << "=====================================================" << endl;
    cout << " Action > ";

    return getCleanInput();
}

char GameUI::drawGrid(const Player& p, int totalDungeons, int x, int y, const bool doorsCleared[], int totalDoors, string& logMsg) const {
    clearScreen();

    cout << "=====================================================" << endl;
    cout << "Player: " << p.getClassName()
    << " | HP: " << p.getHp() << "/" << p.getMaxHp()
    << " | Gold: " << p.getGold()
    << " | Cleared: " << p.getDungeonsCleared() << "/" << totalDungeons << endl;
    cout << "=====================================================" << endl << endl;

    // Draw the grid
}

