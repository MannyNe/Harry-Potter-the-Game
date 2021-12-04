#include "Villain.h"
#include <iostream>

using namespace std;

/*	
* ALMOST ALL METHODS HERE ARE GETTERS AND SETTERS, SO I JUST THOUGHT
* IT WOULD BE UNNECESSARY TO COMMENT THEM, THEY'RE JUST STRAIGHTFORWARD
*/

Villain::Villain() {

	m_name = "";
	m_desc = "";
	m_combat = 0;
	m_hp = 0;
	m_rarity = 0;
}

Villain::Villain(string name, string desc, int hp, int combat, int rarity) {

	m_name = name;
	m_desc = desc;
	m_combat = combat;
	m_hp = hp;
	m_rarity = rarity;
}

int Villain::GetCombat() {

	return m_combat;
}

int Villain::GetHp() {

	return m_hp;
}

int Villain::GetRarity() {

	return m_rarity;
}

string Villain::GetName() {

	return m_name;
}

string Villain::GetDesc() {

	return m_desc;
}

void Villain::SetHp(int newHp) {

	m_hp = newHp;
}

void Villain::SetCombat(int newCombat) {

	m_combat = newCombat;
}

void Villain::Attack() {

	cout << m_name << " waves their wand and screams \"Avada Kedavra\"! " << endl;
}

ostream& operator<<(ostream& output, Villain& myVillain) {
	output << myVillain.GetName() << " (hp: " << myVillain.GetHp() << " combat: " << myVillain.GetCombat() << ")" << endl;
	return output;
}