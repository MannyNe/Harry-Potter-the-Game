#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(string filename) {

	m_fileName = filename;
}

Game::~Game() {

	// DELETE THE OBJECTS WITHIN BOTH VECTOR ARRAYS THAT
	// HAVE BEEN ALLOCATED DYNAMICALLY SO THAT MEMLEAKS
	// WON'T OCCUR.
	
	for (unsigned int i = 0; i < m_heroes.size(); i++) {

		delete m_heroes[i];
	}

	for (unsigned int i = 0; i < m_villains.size(); i++) {

		delete m_villains[i];
	}

	m_fileName = "";
}

void Game::LoadFile() {

	ifstream file; // VARIABLE NEEDED TO READ FROM FILE
	Hero* heroN = nullptr; // VARIABLE NEEDED TO CREATE NEW HERO OBJECTS
	Villain* villianN = nullptr; // VARIABLE NEEDED TO CREATE NEW VILLIAN OBJECTS
	string type = "", name = "", desc = "", hp = "", combat = "", rarity = ""; // STRINGS TO HOLD THE DATA PASSED FROM THE FILE
	int hpI = 0, combatI = 0, rarityI = 0, heroesC = 0, villiansC = 0; // INTEGER VALUES NEEDED TO STORE THE VALUES AS INTEGERS FROM FILES.

	file.open(m_fileName);

	if (file.fail()) {
		cout << "The file name \"" + m_fileName + "\" not found!" << endl;
	}
	else
	{
		while (!file.eof()) {

			getline(file, type, '|');
			getline(file, name, '|');
			getline(file, desc, '|');
			getline(file, hp, '|');
			getline(file, combat, '|');
			getline(file, rarity, '\n');

			// CHANGE THE ACQUIRED VARIABLES TO INT FROM STRING
			hpI = stoi(hp);
			combatI = stoi(combat);
			rarityI = RARITY[stoi(rarity)];

			if (type == "HERO") {

				heroN = new Hero(name, desc, hpI, combatI, rarityI);
				m_heroes.push_back(heroN);
				heroesC++;
			}
			else if(type == "VILLAIN") {

				villianN = new Villain(name, desc, hpI, combatI, rarityI);
				m_villains.push_back(villianN);
				villiansC++;
			}
		}
	}

	cout << "Heroes Loaded: " << heroesC;
	cout << " Villians Loaded: " << villiansC;
	cout << " Total Loaded: " << heroesC + villiansC << endl;
}

// PRINT THE HEROES USING THE OVERLOADED << OPERATOR FROM THE HERO CLASS
void Game::PrintHeroes() {

	for (unsigned int i = 0; i < m_heroes.size(); i++) {

		cout << endl << i + 1 << ". " << *m_heroes[i];
	}
}

// PRINT THE HEROES USING THE OVERLOADED << OPERATOR FROM THE VILLAIN CLASS
void Game::PrintVillains() {

	for (unsigned int i = 0; i < m_villains.size(); i++) {

		cout << endl << i + 1 << ". " << *m_villains[i];
	}
}

// PRINT THE HEROES THAT YOU OWN USING THE DISPLAY METHOD FROM THE LQUEUE CLASS
void Game::PrintMyHeroes() {

	cout << endl;
	m_myHeroes.Display();
}

// THE ACQUIRE HERO METHOD
void Game::AcquireHero() {

	int choice = 0, rarityL = 0; // VARIABLES USED FOR ACCEPTING CHOICE AND FOR STORING THE RARITY OF THE WIZARD RESPECTIVLEY

	// AS LONG AS THE INPUT IS GREATER THAN 5 AND LESS THAN 0, RUN THE
	// QUERY REPEATEDLY.
	
	do {

		cout << "\nHow rare of a wizard would you like to recruit?:\n"
			<< "1. Very Common(Very High Probability)\n"
			<< "2. Common(High Probability)\n"
			<< "3. Uncommon(Normal Probability)\n"
			<< "4. Rare(Low Probability)\n"
			<< "5. Ultra Rare(Extremely Low Probability)\n"
			<< "\nChoice: ";

		cin >> choice;

	} while (choice > 5 || choice < 0);

	// AFTER THE CHOICE, GET THE RARITY FROM THE CONSTANT ARRAY, THEN CALL THE
	// FOUND HERO METHOD TO ADD A HERO TO YOUR ROSTER.

	switch (choice)
	{
	case 1:
		rarityL = RARITY[4];
		FoundHero(rarityL);
		break;
	
	case 2:
		rarityL = RARITY[3];
		FoundHero(rarityL);
		break;

	case 3:
		rarityL = RARITY[2];
		FoundHero(rarityL);
		break;

	case 4:
		rarityL = RARITY[1];
		FoundHero(rarityL);
		break;

	case 5:
		rarityL = RARITY[0];
		FoundHero(rarityL);
		break;

	default:
		break;
	}
}

// THE FOUNDHERO METHOD
void Game::FoundHero(int rarity) {

	cout << "You ask around to see if anyone would be willing to join you." << endl;
	int randNum = 0 + rand() % 229; // TAKE A RANDOM NUMBER BETWEEN 0 AND 229

	// IF THE RANDOM HERO CHOSEN HAS A RARITY WHICH IS SIMILLAR TO THE PLAYERS CHOSEN
	// RARITY, THEN ADD THE HERO TO THE PLAYERS ROSTER.
	if (m_heroes[randNum]->GetRarity() == rarity) {

		// ADD THE HERO IN THE PLAYERS ROSTER ONLY IF HE DOESN'T EXIST IN
		// THE PLAYERS ROSTER
		if (m_myHeroes.Find(m_heroes[randNum]) == -1) {

			cout << "With some amount of effort, " << m_heroes[randNum]->GetName() << " has agreed to join you!" << endl;
			m_myHeroes.Push(m_heroes[randNum]);
		}
	}
	else {

		cout << "No one would join your cause." << endl;
	}
}

// THE MAINMENU METHOD: PROMPTS USER FOR AN INPUT
void Game::MainMenu() {

	int choice = 0;

	do {

		cout << "\nWhat would you like to do ? :\n"
			<< "1. See All Heroes\n"
			<< "2. See All Villains\n"
			<< "3. See Your Heroes\n"
			<< "4. Try to Acquire a New Hero\n"
			<< "5. Train a Hero\n"
			<< "6. Enter a Wizard Battle\n"
			<< "7. Exit\n"
			<< "\nChoice: ";

		cin >> choice;

	} while (choice > 7 || choice < 0);

	switch (choice)
	{
	case 1:
		PrintHeroes();
		MainMenu();
		break;

	case 2:
		PrintVillains();
		MainMenu();
		break;

	case 3:
		PrintMyHeroes();
		MainMenu();
		break;

	case 4:
		AcquireHero();
		MainMenu();
		break;

	case 5:
		TrainHero();
		MainMenu();
		break;

	case 6:
		Battle();
		MainMenu();
		break;

	case 7:
		break;

	default:
		break;
	}

}

// THE PREPAREVILLIAN METHOD
void Game::PrepareVillains() {

	int players = 0;

	// THE VILLANS MUST BE BETWEEN 0 AND THE ALLOWABLE NUMBER OF VILLIANS
	do{

		cout << "\nHow many villains would you like to battle?: ";
		cin >> players;

	} while (players < 0 || players == 0 || players > MAX_VILLAINS);

	while (players > 0)
	{
		//randomy select the villians and add it to the villain battle roster
		int randNum = 0 + rand() % 93;
		if (m_bVillains.Find(m_villains[randNum]) == -1) {

			m_bVillains.Push(m_villains[randNum]);
			players--;
		}
	}

	cout << SEP << endl;
	m_bVillains.Display(); // DISPLAY THE VILLIANS IN THE BATTLE ROSTER
	cout << SEP << endl;
}

// THE PREPAREHEROES METHOD
void Game::PrepareHeroes() {

	int choice = 0;
	int counter = 0;
	int heroesL = int(m_myHeroes.size());

	// AS LONG AS THE USER DOESNT INPUT -1 OR IF HIS CHOICE OF HEROES
	// DOESNT EXCEED THE ALLOWABLE AMOUNT OF HEROES, ADD HEROES TO THE
	// BATTLE ROSTER

	do {

		cout << "Add from 1 to 5 heroes to your battle roster\nEnter -1 when done" << endl;
		m_myHeroes.Display();
		cout << endl << "Choice: ";
		cin >> choice;

		if (heroesL >= choice && choice != -1 && counter < MAX_HEROES) {

			m_bHeroes.Push(m_myHeroes.operator[](choice - 1));
			counter++;
		}
		else if(heroesL < choice) {
			cout << "\nThe value you entered is greater than your heroes list, try again" << endl;
		}
		else if (counter >= MAX_HEROES) {
			cout << "\nMaximum amout of heroes reached" << endl;
			choice = -1;
		}

	} while (choice != -1);

	cout << SEP << endl;
	cout << "The hero wizards stand ready to battle" << endl;
	m_bHeroes.Display(); // THE BATTLE READY HEROES
	cout << SEP << endl;
}

void Game::Battle() {

	bool ended = false; // CHECKER TO TERMINATE THE GAME IF IT ENDED.
	bool heroTurn = true; // CHECKER TO DETERMINE IF IT'S THE HEROE'S TURN TO ATTACK.
	int newHitPoint = 0; // VARIABLE USED TO SET THE NEW HP AFTER AN ATTACK TO A WIZARD.

	// IF THE SIZE OF THE HEROES VECTOR IS ZERO, IT MEANS THAT
	// THE USER DIDNT ACQUIRE HEROES YET, SO IT WON'T FORWARD 
	// WITH THE BATTLE.
	if (m_heroes.size() == 0) {

		cout << "There are no hero wizards to battle the villain wizards!" << endl;
	}
	else {

		PrepareVillains();
		cout << endl;
		PrepareHeroes();

		cout << "Done Preparing." << endl;

		do {

			// IF ITS THE HEROES TURN, THE HERO WILL GET TO ATTACK THE VILLIAN FIRST, AND IF HE ISN'T
			// THE VILLIAN WILL CONTINUE TO ATTACK
			cout << m_bHeroes.Front()->GetName() << " VS " << m_bVillains.Front()->GetName() << endl;
			if (heroTurn) {

				m_bHeroes.Front()->Attack();
				newHitPoint = m_bVillains.Front()->GetHp() - m_bHeroes.Front()->GetCombat();

				if (newHitPoint > 0) {

					m_bVillains.Front()->SetHp(newHitPoint);
					heroTurn = false;
				}
				else {

					cout << m_bVillains.Pop()->GetName() << " is defeated!" << endl;
				}

				if (m_bVillains.size() == 0) {

					ResolveBattle();
					ended = true;
				}
			}
			else {

				m_bVillains.Front()->Attack();
				newHitPoint = m_bHeroes.Front()->GetHp() - m_bVillains.Front()->GetCombat();

				if (newHitPoint > 0) {

					m_bHeroes.Front()->SetHp(newHitPoint);
					heroTurn = true;
				}
				else {

					cout << m_bHeroes.Pop()->GetName() << " is defeated!" << endl;
				}

				if (m_bHeroes.size() == 0) {

					ResolveBattle();
					ended = true;
				}
			}


		} while (!ended);

	}

	// CLEAR THE MEMORY ALLOCATED FOR THE BATTLING WIZARDS
	// BECAUSE THE GAME HAS ENDED.
	m_bHeroes.~Lqueue();
	m_bVillains.~Lqueue();
}

void Game::ResolveBattle() {

	//check the size for both LQueues, if one is greater than the other, the greater always wins
	cout << SEP << endl;
	if (m_bHeroes.size() > 0 && m_bVillains.size() == 0) {

		cout << "The hero wizards win the battle!" << endl;
	}
	else {

		cout << "The villain wizards win the battle!" << endl;
	}
	cout << SEP << endl;
}

void Game::TrainHero() {

	// TRAIN A HERO IF THE USER SUBMITS THE CORRECT CHOICE, IF HE/SHE DOESN'T
	// REPROMPT THE USER AGAIN.
	int choice = 0;
	int checker = int(m_myHeroes.size());

	do
	{
		if (m_myHeroes.IsEmpty()) {

			cout << endl;
			m_myHeroes.Display();
		}
		else {

			cout << "\nWhich of your wizards would you like to train?:\n" << endl;
			m_myHeroes.Display();
			cout << endl;
			cout << "Choice: ";
			cin >> choice;

			if (choice <= checker) {

				m_myHeroes.operator[](choice - 1)->Train();

				cout << "\nYour " << m_myHeroes.operator[](choice - 1)->GetName() << " has been trained." << endl;
				cout << "Your combat is now " << m_myHeroes.operator[](choice - 1)->GetCombat() << endl;
			}
		}

	} while (choice > checker);
}