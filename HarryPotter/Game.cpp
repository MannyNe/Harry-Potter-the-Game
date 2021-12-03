#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(string filename) {

	m_fileName = filename;
}

Game::~Game() {

	for (unsigned int i = 0; i < m_heroes.size(); i++) {

		delete m_heroes[i];
	}

	for (unsigned int i = 0; i < m_villains.size(); i++) {

		delete m_villains[i];
	}

	m_fileName = "";
}

void Game::LoadFile() {

	//1 is type
	//2 is name
	//3 is desc
	//4 is hp
	//5 is combat
	//6 is rarity

	ifstream file; // VARIABLE NEEDED TO READ FROM FILE
	Hero* heroN = nullptr;
	Villain* villianN = nullptr;
	string type = "", name = "", desc = "", hp = "", combat = "", rarity = ""; // STRINGS TO HOLD THE DATA PASSED FROM THE FILE
	int hpI = 0, combatI = 0, rarityI = 0, heroesC = 0, villiansC = 0;

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

void Game::PrintHeroes() {

	for (unsigned int i = 0; i < m_heroes.size(); i++) {

		cout << endl << i + 1 << ". " << *m_heroes[i];
	}
}

void Game::PrintVillains() {

	for (unsigned int i = 0; i < m_villains.size(); i++) {

		cout << endl << i + 1 << ". " << *m_villains[i];
	}
}

void Game::PrintMyHeroes() {

	m_myHeroes.Display();
}

void Game::AcquireHero() {

	int choice = 0, rarityL = 0;

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

void Game::FoundHero(int rarity) {

	cout << "You ask around to see if anyone would be willing to join you." << endl;
	int randNum = 0 + rand() % 229;

	if (m_heroes[randNum]->GetRarity() == rarity) {

		// MAYBE ADD THE LIST OF COMMON ... THEN ITERARTE FROM THAT
		cout << "With some amount of effort, " << m_heroes[randNum]->GetName() << " has agreed to join you!" << endl;
		// use Lqueue.Find to check if the object exists in lqueue
		if (m_myHeroes.Find(m_heroes[randNum]) == -1) {

			m_myHeroes.Push(m_heroes[randNum]);
		}
	}
	else {

		cout << "No one would join your cause." << endl;
	}
}

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

void Game::PrepareVillains() {

	int players = 0;

	do{

		cout << "How many villains would you like to battle?: ";
		cin >> players;

	} while (players < 0 || players > MAX_VILLAINS); // WILL CHECK THIS OUT LATER. MUST FOCUS ON THE WHILE LOOP.

	while (players > 0)
	{
		//randomy select the villians and add it to the arry or lqueue?
		int randNum = 0 + rand() % 93;
		if (m_bVillains.Find(m_villains[randNum]) == -1) {

			m_bVillains.Push(m_villains[randNum]);
			players--;
		}
	}

	cout << SEP << endl;
	m_bVillains.Display();
	cout << SEP << endl;
}

void Game::PrepareHeroes() {

	int choice = 0;
	int size = m_myHeroes.size();

	if (size == 0) {

		cout << "There are no heroes to battle!" << endl;
	}
	else {

		do 
		{

			cout << "Add from 1 to 5 heroes to your battle roster\nEnter -1 when done" << endl;
			m_myHeroes.Display();
			cout << endl << "Choice: ";
			cin >> choice;

			if (choice < 0 || choice > int(m_heroes.size())) {

				cout << "Error: More than " << MAX_HEROES << " heroes aren't allowed." << endl;
			}
			else {

				m_bHeroes.Push(m_heroes[choice]);
			}

		} while (choice != -1 || size < MAX_HEROES); // WILL CHECK THIS OUT LATER. MUST FOCUS ON THE WHILE LOOP.

		cout << SEP << endl;
		cout << "The hero wizards stand ready to battle" << endl;
		m_bHeroes.Display();
		cout << SEP << endl;
	}
}

void Game::Battle() {

	cout << "UNDER DEV" << endl;
	PrepareVillains();
	PrepareHeroes();

	cout << "Done Preparing." << endl;

	do {



	} while ();


}

void Game::ResolveBattle() {

	//check the size for both LQueues, if one is greater than the other, the greater always wins
	cout << SEP << endl;
	if (m_bHeroes.size() > 0 && m_bVillains.size() == 0) {

		cout << "The hero wizards win the battle!" << endl;
	}
	else if (m_bHeroes.size() == 0 && m_bVillains.size() > 0) {

		cout << "The villain wizards win the battle!" << endl;
	}
	else {

		cout << "There are no winners, one in a million. This even isn't supposed to happen." << endl;
	}
	cout << SEP << endl;
}

void Game::TrainHero() {

	int choice = 0;
	int checker = int(m_myHeroes.size());

	do
	{
		if (m_myHeroes.IsEmpty()) {

			cout << endl;
			m_myHeroes.Display();
		}
		else {

			cout << "Which of your wizards would you like to train?:" << endl;
			m_myHeroes.Display();
			cout << endl;
			cout << "Choice: ";
			cin >> choice;

			if (choice < checker) {

				m_myHeroes.operator[](choice)->Train();

				cout << "\nYour " << m_myHeroes.operator[](choice)->GetName() << "has been trained." << endl;
				cout << "Your combat is now " << m_myHeroes.operator[](choice)->GetCombat() << endl;
			}
		}

	} while (choice > checker);
}