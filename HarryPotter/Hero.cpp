#include "Hero.h"
#include <iostream>

using namespace std;

Hero::Hero() {

	m_name = "";
	m_desc = "";
	m_combat = 0;
	m_hp = 0;
	m_rarity = 0;
}

Hero::Hero(string name, string desc, int hp, int combat, int rarity) {

	m_name = name;
	m_desc = desc;
	m_combat = combat;
	m_hp = hp;
	m_rarity = rarity;
}

int Hero::GetCombat() {

	return m_combat;
}

int Hero::GetHp() {

	return m_hp;
}

int Hero::GetRarity() {

	return m_rarity;
}

string Hero::GetName() {

	return m_name;
}

string Hero::GetDesc() {

	return m_desc;
}

void Hero::SetHp(int newHp) {

	m_hp = newHp;
}

void Hero::SetCombat(int newCombat) {

	m_combat = newCombat;
}

void Hero::Train() {

	m_combat += 10;
}

void Hero::Attack() {

	cout << m_name << " waves their wand and screams \"Sectumsempra\"! " << endl;
}

ostream& operator<<(ostream& output, Hero& myHero) {
	output << myHero.GetName() << " (hp: " << myHero.GetHp() << " combat: " << myHero.GetCombat() << ")" << endl;
	return output;
}