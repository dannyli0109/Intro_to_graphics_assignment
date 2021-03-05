#include "Entity.h"
#include "ShaderProgram.h"

/**
 * Entity class, represents an object in the scene.
 */
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

/**
 * Entity will update it's component first, then update it's children.
 *
 * \param deltaTime
 */
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

void Entity::LateUpdate()
{
	components.erase(
		std::remove_if(
			components.begin(), 
			components.end(), 
			[](Component* component) { 
				if (component->ShouldDelete())
				{
					delete component;
					return true;
				}
				return false;
			}
		), components.end()
	);

	for (Entity* child : children)
	{
		child->LateUpdate();
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

	for (int i = 0; i < components.size(); i++)
	{
		Component* component = components[i];
		//std::string remove = "Remove###";
		//remove += i;
		//if (ImGui::Button(remove.c_str()))
		//{
		//	std::cout << "delete clicked" << std::endl;
		//	component->Delete();
		//}
		//ImGui::SameLine();
		bool tree = ImGui::TreeNodeEx(component->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen);
		if (tree)
		{
			component->DrawGui();
			ImGui::Separator();
			ImGui::TreePop();
		}
	}

	//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
	//if (ImGui::Button("Add Component", ImVec2(-1.0f, 0.0f))) {
	//	std::cout << "clicked" << std::endl;
	//}
	//ImGui::PopItemWidth();
}
