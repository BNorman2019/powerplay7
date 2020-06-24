#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
std::vector<std::unique_ptr<Monster>> createMonsters(const Player* player);
void displayBattle(const Player* player, const std::vector<std::unique_ptr<Monster>>& monsters);
void bringOutYourDead(std::vector<std::unique_ptr<Monster>>& monsters);
int main()
{
	std::unique_ptr<Player> player{ std::make_unique<Player>() };
	std::vector<std::unique_ptr<Monster>> monsters;
	while (!player->isDead())
	{
		player->levelUp();
		monsters = createMonsters(player.get());
		std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");
		while (!player->isDead() && monsters.size() > 0)
		{
			displayBattle(player.get(), monsters);
			player->update(player.get(), monsters);
			bringOutYourDead(monsters);
			std::cout << std::endl;
			std::for_each(monsters.begin(), monsters.end(), [&](std::unique_ptr<Monster>& monster)
				{
					monster->update(player.get(), monsters);
				});
			system("PAUSE");
			system("CLS");
		}
	}
	if (player->isDead())
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player->isDead() && monsters.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");
}
void displayBattle(const Player* player, const std::vector<std::unique_ptr<Monster>>& monsters)
{
	std::cout << *player << std::endl;
	std::cout << player->getInventory();
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(monsters.begin(), monsters.end(), [&](const std::unique_ptr<Monster>& monster)
			{
				std::cout << "   " << i << ". " << *monster << std::endl;
				i++;
			});
	}
}
std::vector<std::unique_ptr<Monster>> createMonsters(const Player* player)
{
	std::normal_distribution<double> randomNumMonsters((double)player->getLevel(), player->getLevel() / 2.0);
	std::vector<std::unique_ptr<Monster>> monsters(std::max(1, (int)randomNumMonsters(Object::engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			return std::make_unique<Monster>(player);
		});
	return monsters;
}
void bringOutYourDead(std::vector<std::unique_ptr<Monster>>& monsters)
{
	monsters.erase(
		std::remove_if(monsters.begin(), monsters.end(),
			[](std::unique_ptr<Monster>& monster)
			{
				if (monster->isDead())
				{
					std::cout << *monster << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		monsters.end());
}