#include "Hero.h"
#include <iostream>

using namespace std;

Hero::Hero() {


}

Hero::Hero(string name, string desc, int hp, int combat, int rarity) {


}

int Hero::GetCombat() {


}

int Hero::GetHp() {


}

int Hero::GetRarity() {


}

string Hero::GetName() {


}

string Hero::GetDesc() {


}

void Hero::SetHp(int newHp) {


}

void Hero::SetCombat(int newCombat) {


}

void Hero::Train() {


}

void Hero::Attack() {


}

ostream& operator<<(ostream& output, Hero& myHero) {
	output << "Change this " << myHero.m_name << endl;
	return output;
}