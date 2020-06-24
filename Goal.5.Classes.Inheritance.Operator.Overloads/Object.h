#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <random>
#include <memory>

class Player;
class Monster;
class Object
{
public:
	static std::random_device seed;
	static std::default_random_engine engine;
	enum class Type { player, slime, orc, sprite, dragon, numTypes };

	Object() {}
	Object(Type name, int strength, int health, int level);


	bool isDead();
	Type getName() const;
	int getLevel() const;
	int getHealth() const;
	int getStrength() const;
	virtual int attack() const = 0;
	virtual void defend(int damage) = 0;
	virtual void update(Player* player, std::vector<std::unique_ptr<Monster>>& monsters) = 0;

protected:
	Type name{ Type::numTypes };
	int strength{ 0 };
	int health{ 0 };
	int level{ 0 };
	int damageDone(int modification) const;
	int damageTaken(int damageDone, int AC);

};

std::ostream& operator<< (std::ostream& o, const Object& src);
#endif // !OBJECT_H

