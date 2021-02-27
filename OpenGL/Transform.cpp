#include "Transform.h"
#include "GameObject.h"
#include "ShaderProgram.h"

/**
 * Transform component, defines position, rotation and scale for the object.
 * 
 * \param position
 * \param rotation
 * \param scale
 */
Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    localTransform = glm::mat4(1.0f);
	globalTransform = glm::mat4(1.0f);

    SetPosition(position);
}


void Transform::SetPosition(const glm::vec3& position)
{
    localTransform[3][0] = position.x;
    localTransform[3][1] = position.y;
    localTransform[3][2] = position.z;
}

void Transform::Translate(const glm::vec3& direction)
{
    localTransform = glm::translate(localTransform, direction);
}

void Transform::RotateX(float deg)
{
    glm::rotate(localTransform, glm::radians(deg), glm::vec3(1.0f, 0, 0));
}

void Transform::RotateY(float deg)
{
    glm::rotate(localTransform, glm::radians(deg), glm::vec3(0, 1.0f, 0));
}

void Transform::RotateZ(float deg)
{
    glm::rotate(localTransform, glm::radians(deg), glm::vec3(0, 0, 1.0f));
}

void Transform::Update(float deltaTime, ShaderProgram& shader)
{
    assert(gameObject != nullptr);
    GameObject* parent = gameObject->GetParent();
    if (parent)
    {
        Transform* parentTransform = parent->GetComponent<Transform>();
        if (parentTransform)
        {
            globalTransform = parentTransform->globalTransform * localTransform;
        }
    }
    else 
    {
        globalTransform = localTransform;
    }

    shader.SetUniform("modelMatrix", localTransform);
}
