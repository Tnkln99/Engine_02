#include "Mesh.h"


Mesh::Mesh(char c){
    typeOfMesh = c;
    loadPreMade(c);
}

Mesh::~Mesh() {
    std::cout<<"Mesh "<< typeOfMesh <<" is deleting"<<std::endl;
}

unsigned int & Mesh::getId() {
    return id;
}

char Mesh::getTypeOfMesh() const {
    return typeOfMesh;
}

const std::vector<unsigned int> &Mesh::getIndices() {
    return indices;
}

const std::vector<Vertex> &Mesh::getVertices() {
    return vertices;
}

void Mesh::loadPreMade(char c) {
    if(c == 'c'){
        generateCube();
    }
    else if(c == 'i'){
        generateIcosahedron();
    }
    else{
        std::cout<<"error loading the mesh.. "<<std::endl;
        exit(1);
    }
}

void Mesh::generateCube() {
    std::vector<glm::vec3> positions;
    positions.push_back(glm::vec3 {-1, -1,  1});//0
    positions.push_back(glm::vec3 {1, -1,  1});//1
    positions.push_back(glm::vec3 {-1,  1,  1});//2
    positions.push_back(glm::vec3 {1,  1,  1});//3
    positions.push_back(glm::vec3 {-1, -1, -1});//4
    positions.push_back(glm::vec3 {1, -1, -1});//5
    positions.push_back(glm::vec3 {-1,  1, -1});//6
    positions.push_back(glm::vec3 {1,  1, -1});//7

    indices = {
            //Top
            2, 7, 6,
            2, 3, 7,

            //Bottom
            0, 4, 5,
            5, 1, 0,

            //Left
            0, 2, 6,
            6, 4, 0,

            //Right
            1, 7, 3,
            5, 7, 1,

            //Front
            0, 1, 3,
            0, 3, 2,

            //Back
            4, 6, 7,
            7, 5, 4
    };

    std::vector<glm::vec3> normals = computeVertexNormals(positions);

    fillVertices(positions, normals);
}

void Mesh::generateIcosahedron() {
    std::vector<glm::vec3> positions;
    positions = {
            glm::vec3(0.000f,  0.000f,  1.000f),
            glm::vec3(0.894f,  0.000f,  0.447f),
            glm::vec3(0.276f,  0.851f,  0.447f),
            glm::vec3(-0.724f,  0.526f,  0.447f),
            glm::vec3(-0.724f, -0.526f,  0.447f),
            glm::vec3(0.276f, -0.851f,  0.447f),
            glm::vec3(0.724f,  0.526f, -0.447f),
            glm::vec3(-0.276f,  0.851f, -0.447f),
            glm::vec3(-0.894f,  0.000f, -0.447f),
            glm::vec3(-0.276f, -0.851f, -0.447f),
            glm::vec3(0.724f, -0.526f, -0.447f),
            glm::vec3(0.000f,  0.000f, -1.000f) };

    indices = {
            2, 1, 0,
            3, 2, 0,
            4, 3, 0,
            5, 4, 0,
            1, 5, 0,
            11, 6, 7,
            11, 7, 8,
            11, 8, 9,
            11, 9, 10,
            11, 10,6,
            1, 2, 6,
            2, 3, 7,
            3, 4, 8,
            4, 5, 9,
            5, 1, 10,
            2,  7, 6,
            3,  8, 7,
            4,  9, 8,
            5, 10, 9,
            1, 6, 10 };

    std::vector<glm::vec3> normals = computeVertexNormals(positions);

    fillVertices(positions, normals);
}


void Mesh::connectDots(int a, int b, int c) {
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}



std::vector<glm::vec3> Mesh::computeVertexNormals(const std::vector<glm::vec3>& positions) {
    std::vector<glm::vec3> normals;

    for(int i = 0; i < positions.size(); i ++){
        normals.push_back(glm::vec3(0.0f));
    }

    for(int i = 0; i < indices.size() - 3; i+=3){
        unsigned int ia = indices[i];
        unsigned int ib = indices[i+1];
        unsigned int ic = indices[i+2];

        glm::vec3 aPos = positions[ia];

        glm::vec3 bPos = positions[ib];

        glm::vec3 cPos = positions[ic];

        glm::vec3 e1 = aPos - bPos;
        glm::vec3 e2 = cPos - bPos;
        glm::vec3 no = cross( e1, e2 );

        normals[ia] += no;

        normals[ib] += no;

        normals[ic] += no;
    }

    for(int i = 0; i < positions.size(); i++){
        normals[i] = glm::normalize(normals[i]);
    }

    return normals;
}

void Mesh::fillVertices(const std::vector<glm::vec3> &positions, const std::vector<glm::vec3> &normals) {
    for(int i = 0; i < positions.size(); i++){
        vertices.push_back( Vertex{positions[i],normals[i] } );
    }
}
