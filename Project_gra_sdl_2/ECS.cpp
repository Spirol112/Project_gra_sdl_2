#include "ECS.h"

void Entity::add_group(Group m_group)
{
	group_bitset[m_group] = true;
	manager.add_to_group(this, m_group);
}
