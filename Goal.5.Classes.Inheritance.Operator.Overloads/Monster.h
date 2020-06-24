#ifndef MONSTER_H
#define MONSTER_H
#include "Object.h"

class Player;
class Monster :
	public Object
{
public:
	Monster() {};
	Monster(const Player* player);

	int attack() const override;
	void defend(int damage) override;
	void update(Player* player, std::vector<std::unique_ptr<Monster>>& monsters) override;
private:
	int AC{ 0 };

};

#endif // !MONSTER_H