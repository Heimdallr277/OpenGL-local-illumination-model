#ifndef CYLINDER_H
#define CYLINDER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const int sectorCount = 64;
//const float Radius = 2.0f;
//const float Height = 5.0f;


struct TVertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
};

std::vector<TVertex> getCircleVertices(const float Radius)
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle = 0.0f;

    // 圆柱
    glm::vec3 position;
    glm::vec3 normal;
    TVertex tVertex;
    std::vector<TVertex> CircleVertices;
    for (int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        position.x = Radius * cos(sectorAngle);
        position.y = 0.0f;
        position.z = Radius * sin(sectorAngle);

        normal.x = cos(sectorAngle);
        normal.y = 0.0f;
        normal.z = sin(sectorAngle);

        tVertex.Position = position;
        tVertex.Normal = normal;

        CircleVertices.push_back(tVertex);
    }

    return CircleVertices;
}

void buildCylinderVertices(std::vector<TVertex>& vertices, const float Radius, const float Height)
{
    std::vector<TVertex> unitVertices = getCircleVertices(Radius);

    // 获取上、下圆周点数组
    std::vector<TVertex> vctTop;
    std::vector<TVertex> vctBot;

    TVertex tVertex;
    for (int i = 0; i < unitVertices.size(); ++i)
    {
        tVertex.Position = unitVertices[i].Position;
        tVertex.Position.y = Height;
        tVertex.Normal = unitVertices[i].Normal;
        vctTop.push_back(tVertex);

        tVertex.Position.y = 0.0f;
        vctBot.push_back(tVertex);
    }

    assert(vctTop.size() >= 2);
    assert(vctBot.size() >= 2);

    // 圆柱侧面
    for (int i = 0; i < vctTop.size() - 1; ++i)
    {
        // 左三角形
        vertices.push_back(vctTop[i]);
        vertices.push_back(vctBot[i]);
        vertices.push_back(vctBot[i + 1]);

        // 右三角形
        vertices.push_back(vctTop[i]);
        vertices.push_back(vctTop[i + 1]);
        vertices.push_back(vctBot[i + 1]);
    }

    // 顶部圆形
    for (int i = 0; i < vctTop.size() - 1; ++i)
    {
        glm::vec3 position(0.0f, Height, 0.0f);
        glm::vec3 normal(0.0f, 1.0f, 0.0f);
        tVertex.Position = position;
        tVertex.Normal = normal;
        vertices.push_back(tVertex);

        tVertex.Position = vctTop[i].Position;
        vertices.push_back(tVertex);

        tVertex.Position = vctTop[i + 1].Position;
        vertices.push_back(tVertex);
    }

    // 底部圆形
    for (int i = 0; i < vctBot.size() - 1; ++i)
    {
        glm::vec3 position(0.0f, 0.0f, 0.0f);
        glm::vec3 normal(0.0f, -1.0f, 0.0f);
        tVertex.Position = position;
        tVertex.Normal = normal;
        vertices.push_back(tVertex);

        tVertex.Position = vctBot[i].Position;
        vertices.push_back(tVertex);

        tVertex.Position = vctBot[i + 1].Position;
        vertices.push_back(tVertex);
    }
}


#endif