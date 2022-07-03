#ifndef CONE_H
#define CONE_H
#include <cylinder.h>


std::vector<TVertex> getBottomCircleVertices(const float Radius, const float Height)
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle = 0.0f;

    // Ô²×¶
    glm::vec3 position;
    glm::vec3 normal;
    TVertex tVertex;
    std::vector<TVertex> BottomCircleVertices;
    for (int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        position.x = Radius * cos(sectorAngle);
        position.y = 0.0f;
        position.z = Radius * sin(sectorAngle);

        glm::vec3 OT(0.0f, Height, 0.0f);
        glm::vec3 BT = OT - position;
        normal = glm::normalize(glm::cross(glm::cross(OT, position), BT));

        tVertex.Position = position;
        tVertex.Normal = normal;

        BottomCircleVertices.push_back(tVertex);
    }

    return BottomCircleVertices;
}

void buildConeVertices(std::vector<TVertex>& vertices, const float Radius, const float Height)
{
    std::vector<TVertex> vctBot = getBottomCircleVertices(Radius, Height);
    TVertex Top;
    Top.Position = glm::vec3(0.0f, Height, 0.0f);
    Top.Normal = glm::vec3(0.0f, 0.0f, 0.0f);

    // ²àÃæ
    for (int i = 0; i < vctBot.size() - 1; ++i)
    {
        vertices.push_back(Top);
        vertices.push_back(vctBot[i]);
        vertices.push_back(vctBot[i + 1]);
    }

    // µ×²¿Ô²ÐÎ
    TVertex tVertex;
    for (int i = 0; i < vctBot.size() - 1; ++i)
    {
        tVertex.Position = glm::vec3(0.0f, 0.0f, 0.0f);
        tVertex.Normal = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices.push_back(tVertex);

        tVertex.Position = vctBot[i].Position;
        vertices.push_back(tVertex);

        tVertex.Position = vctBot[i + 1].Position;
        vertices.push_back(tVertex);
    }
}


#endif
