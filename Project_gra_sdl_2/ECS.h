#pragma once
#include<iostream>
#include<vector>
#include <memory>
#include <algorithm>
#include<bitset>
#include<array>

class Component;
class Entity;
class Manager;

using component_ID = std::size_t;
using Group = std::size_t;

inline component_ID get_new_comp_type_ID()
{
	static component_ID last_ID = 0;
	return last_ID++;
}

template <typename T> inline component_ID get_comp_type_ID() noexcept
{
	static component_ID type_ID = get_new_comp_type_ID();
	return type_ID;
}

constexpr std::size_t max_comps = 32;
constexpr std::size_t max_groups = 32;

using Component_bitset = std::bitset<max_comps>;
using Group_bitset = std::bitset<max_groups>;

using Component_array = std::array<Component*, max_comps>;

class Component
{
private:

public:
	Entity* entity;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {};

};

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>>components;

	Component_array component_arrey;
	Component_bitset component_bitset;
	Component_bitset group_bitset;

public:
	Entity(Manager& m_manager): manager(m_manager){}

	void update()
	{
		for (auto& c : components) c->update();
		
	}
	void draw() 
	{ 
		for (auto& c : components) c->draw(); 
	}

	bool is_active(void) const { return active; }
	void destroy() { active = false; }

	bool has_group(Group m_group)
	{
		return group_bitset[m_group];
	}

	void add_group(Group m_group);
	void del_group(Group m_group)
	{
		group_bitset[m_group] = false;
	}

	template <typename T> bool has_component()const
	{
		return component_bitset[get_comp_type_ID<T>()];
	}

	template <typename T, typename... T_args> 
	T& add_component(T_args&&... m_args)
	{
		T* c(new T(std::forward<T_args>(m_args)...));
		c->entity = this;
		std::unique_ptr<Component> u_ptr{ c };
		components.emplace_back(std::move(u_ptr));

		component_arrey[get_comp_type_ID<T>()] = c;

		component_bitset[get_comp_type_ID<T>()] = true;

		c->init();

		return *c;
	}

	template <typename T> T& get_comp() const
	{
		auto ptr(component_arrey[get_comp_type_ID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, max_groups> grouped_entities;

public:
	void update()
	{
		for (auto& e : entities)e->update();
	}
	void draw()
	{
		for (auto& e : entities)e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < max_groups; i++)
		{
			auto& v(grouped_entities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* m_entity)
					{
						return !m_entity->is_active() || !m_entity->has_group(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& m_entity)
			{
				return !m_entity->is_active();
			}),
				std::end(entities));
	}

	void add_to_group(Entity* m_entity, Group m_group)
	{
		grouped_entities[m_group].emplace_back(m_entity);
	}

	std::vector<Entity*>& get_group(Group m_group)
	{
		return grouped_entities[m_group];
	}

	Entity& add_entity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> u_ptr{ e };
		entities.emplace_back(std::move(u_ptr));
		return *e;
	}
};
