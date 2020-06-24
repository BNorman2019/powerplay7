#ifndef PLAYER_H
#define PLAYER_H


#include "Object.h"
#include "Item.h"

class Monster;
class Player :
	public Object
{
public:
	Player();

	void levelUp();

	int getLevel() const;
	int getSP() const;
	const std::map<Item::Type, std::unique_ptr<Item>> getInventory() const;
	void heal();

	int attack() const override;
	void defend(int damage) override;
	void update(Player* player, std::vector<std::unique_ptr<Monster>>& monsters) override;


private:
	std::map<Item::Type, std::unique_ptr<Item>> inventory;
	int SP{ 0 };
};
std::ostream& operator<< (std::ostream& o, const Player& src);
std::ostream& operator<< (std::ostream& o, const std::map<Item::Type, std::unique_ptr<Item>>& src);
#endif // !PLAYER_H