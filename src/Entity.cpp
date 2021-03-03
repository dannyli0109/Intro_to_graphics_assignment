#include "Entity.h"
#include "ShaderProgram.h"

Entity::Entity(std::string name, const std::vector<Component*>& components, const std::vector<Entity*>& children)
{
	this->name = name;
	this->components = components;
	this->children = children;

	for (Entity* child : children)
	{
		child->parent = this;
	}

	for (Component* component : components)
	{
		component->entity = this;
	}
}

Entity::~Entity()
{
	for (Component* component : components)
	{
		delete component;
	}

	for (Entity* child : children)
	{
		delete child;
	}
}

void Entity::Update(float deltaTime)
{
	for (Component* component : components)
	{
		component->Update(deltaTime);
	}

	for (Entity* child : children)
	{
		child->Update(deltaTime);
	}
}

void Entity::OnDraw()
{
	for (Component* component : components)
	{
		component->OnDraw();
	}
}

void Entity::Draw()
{
	for (Component* component : components)
	{
		component->OnDraw();
	}
	for (Component* component : components)
	{
		component->Draw();
	}

	for (Entity* child : children)
	{
		child->Draw();
	}
}


void Entity::AddChild(Entity* child)
{
	child->parent = this;
	children.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	auto position = std::find(children.begin(), children.end(), child);
	if (position != children.end())
	{
		children.erase(position);
		child->parent = nullptr;
	}
}

void Entity::AddComponent(Component* component)
{
	components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
	auto position = std::find(components.begin(), components.end(), component);
	if (position != components.end())
	{
		delete (*position);
		components.erase(position);
	}
}

Entity* Entity::GetParent()
{
	return parent;
}

std::string Entity::GetName()
{
	return name;
}

void Entity::DrawGui()
{

	for (Component* component : components)
	{
		component->DrawGui();
		ImGui::Separator();
	}
}
