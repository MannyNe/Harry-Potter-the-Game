#include "Villain.h"
#include <iostream>

using namespace std;

Villain::Villain() {


}

Villain::Villain(string name, string desc, int hp, int combat, int rarity) {


}

int Villain::GetCombat() {


}

int Villain::GetHp() {

	
}

int Villain::GetRarity() {


}

string Villain::GetName() {


}

string Villain::GetDesc() {

	
}

void Villain::SetHp(int newHp) {


}

void Villain::SetCombat(int newCombat) {


}

void Villain::Attack() {


}

ostream& operator<<(ostream& output, Villain& myVillain) {
	output << "Change this " << myVillain.m_name << endl;
	return output;
}