#include <random>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Monster.h"

Player::Player() :Object(Object::Type::player, 0, 1, 0)
{

}

void Player::levelUp()
{
	level++;
	std::normal_distribution<double> randomHealth(20.0 + level * 5, 5.0);
	health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + level, 1.0);
	strength += std::max(1, (int)randomStrength(engine));
	SP += std::max(1, (int)randomStrength(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)level, (double)level / 2);
	std::unique_ptr<Item> found{ std::make_unique<Item>((Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine))) };

	std::cout << "You found a " << *found << "!!!!" << std::endl;
	if (
		auto haveOne{ inventory.find(found->getClassification()) };
		haveOne == inventory.end()
		|| inventory[found->getClassification()] < found
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		inventory[found->getClassification()] = std::move(found);
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

int Player::getLevel() const
{
	return level;
}

int Player::getSP() const
{
	return SP;
}

const std::map<Item::Type, std::unique_ptr<Item>> Player::getInventory() const
{
	return inventory;
}

void Player::heal()
{
	if (SP >= 2)
	{
		std::normal_distribution<double> randomHeal(strength, 3.0);
		int  amountHealed{ std::max(1, (int)randomHeal(engine)) };

		SP -= 2;
		std::cout << *this << " is healed by " << amountHealed << "hp!" << std::endl;
		health += amountHealed;
	}
	else
	{
		std::cout << "Not enough SP!!!" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& o, const Player& src)
{
	const Object& objSrc{ src };
	o << objSrc << ", SP:" << src.getSP();
	return o;
}

std::ostream& operator<<(std::ostream& o, const std::map<Item::Type, std::unique_ptr<Item>>& src)
{
	for(const auto & item: src)
		{
			o << "  " << *item.second << std::endl;
		};
	return o;
}

int Player::attack() const 
{
	int modifier{ 0 };
	if (auto sword{ inventory.find(Item::Type::sword) }; sword != inventory.end())
	{
		modifier += sword->second->getBonusValue();
	}

	return damageDone(modifier);
}

void Player::defend(int damage)
{
	int AC{ 0 };
	if (auto armor{ inventory.find(Item::Type::armor) }; armor != inventory.end())
	{
		AC += *armor->second;
	}
	if (auto shield{ inventory.find(Item::Type::shield) }; shield != inventory.end())
	{
		AC += *shield->second;
	}

	damageTaken(damage, AC);
}

void Player::update(Player* player, std::vector<std::unique_ptr<Monster>>& monsters) 
{
	std::cout << "What do you do? (a)ttack (h)eal ";
	char command{ 'x' };
	std::cin >> command;
	switch (command)
	{
	case 'a':
	{
		std::cout << "Which Monster: ";
		int monsterNum{ 0 };
		std::cin >> monsterNum;

		if (monsterNum > 0 && monsterNum <= monsters.size())
		{
			monsters[monsterNum - 1]->defend(player->attack());
		}
		break;
	}
	case 'h':
		player->heal();
		break;
	default:
		std::cout << "please enter a or h" << std::endl;
		break;
	}
}

