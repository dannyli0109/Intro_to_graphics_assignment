#include "Transform.h"
#include "Entity.h"
#include "ShaderProgram.h"

/**
 * Transform component, defines position, rotation and scale for the object.
 *
 * \param position
 * \param rotation
 * \param scale
 */
Transform::Transform(const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& rotation = glm::vec3(0, 0, 0), const glm::vec3& scale = glm::vec3(1, 1, 1))
{
    this->name = "Transform";

    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    
    globalTransform = glm::mat4(1.0f);
}


void Transform::Set(ShaderProgram* shader)
{
    shader->SetUniform("modelMatrix", globalTransform);
}

void Transform::SetPosition(const glm::vec3& position)
{
    this->position = position;
}

glm::vec3 Transform::GetPosition()
{
    return position;
}

void Transform::Translate(const glm::vec3& direction)
{
    //localTransform = glm::translate(localTransform, direction);
    //position = glm::translate()
    position += direction;
}

void Transform::RotateX(float deg)
{
    //glm::rotate(localTransform, glm::radians(deg), glm::vec3(1.0f, 0, 0));
    rotation.x += deg;
}

void Transform::RotateY(float deg)
{
    /*glm::rotate(localTransform, glm::radians(deg), glm::vec3(0, 1.0f, 0));*/
    rotation.y += deg;
}

void Transform::RotateZ(float deg)
{
    //glm::rotate(localTransform, glm::radians(deg), glm::vec3(0, 0, 1.0f));
    rotation.z += deg;
}

glm::mat4& Transform::GetTransformMatrix()
{
    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    transform = glm::scale(transform, scale);

    transform[3].x = position.x;
    transform[3].y = position.y;
    transform[3].z = position.z;

    return transform;
}

Transform* Transform::Create(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    return new Transform(
        position, rotation, scale 
    );
}


void Transform::Update(float deltaTime)
{
    assert(entity != nullptr);
    Entity* parent = entity->GetParent();
    glm::mat4 localTransform = GetTransformMatrix();
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

}

void Transform::DrawGui()
{
    ImGui::DragFloat3("Position", &position.x, 0.1f);
    ImGui::DragFloat3("Rotation", &rotation.x);
    ImGui::DragFloat3("Scale", &scale.x, 0.01);
}

void Transform::OnDraw()
{
    Material* material = entity->GetComponent<Material>();
    if (material)
    {
        Set(material->GetShader());
    }
}
