#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Mesh::Mesh(const std::string & objFile, const std::string & materialDir) {
    load(objFile, materialDir);
}

Mesh::Mesh(const std::string & c){
    nameOfMesh = c;
    loadPreMade(c);
}

Mesh::~Mesh() = default;

unsigned int & Mesh::getId() {
    return id;
}

const std::string & Mesh::getNameOfMesh() const {
    return nameOfMesh;
}

const std::vector<unsigned int> &Mesh::getIndices() {
    return indices;
}

const std::vector<Vertex> &Mesh::getVertices() {
    return vertices;
}

void Mesh::loadPreMade(const std::string & c) {
    if(c == "Cube")
    {
        load("../assets/models/cube.obj", "../assets/models");
    }
    else if(c == "Monkey")
    {
        load("../assets/models/monkey.obj", "../assets/models");
    }
    else if (c == "Sphere"){
        load("../assets/models/sphere.obj", "../assets/models");
    }
    else if(c == "Glass"){
        load("../assets/models/glass.obj", "../assets/models");
    }
    else{
        std::cout<<"error loading the mesh.. "<<std::endl;
        exit(1);
    }
}

void Mesh::load(const std::string &objFile, const std::string &materialDir) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objFile.c_str(), materialDir.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];


                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                }

                // Optional: vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    for(int i = 0; i < shapes[0].mesh.indices.size();i ++){
        indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    for(int i = 0; i < attrib.vertices.size(); i+=3){
        float x = attrib.vertices[i];
        float y = attrib.vertices[i+1];
        float z = attrib.vertices[i+2];
        positions.push_back(glm::vec3(x,y,z));
    }

    normals = computeNormals(positions);

    /*for(int i = 0; i < attrib.vertices.size(); i+=3){
        float x = attrib.normals[i];
        float y = attrib.normals[i+1];
        float z = attrib.normals[i+2];
        normals.push_back(glm::vec3(x,y,z));
    }*/

    fillVertices(positions, normals);
}

std::vector<glm::vec3> Mesh::computeNormals(const std::vector<glm::vec3>& positions) {
    std::vector<glm::vec3> normals;
    std::vector<int> nbSeen;
    normals.resize(positions.size(),glm::vec3(0));
    nbSeen.resize(positions.size(), 0);

    for(int i = 0; i < indices.size() - 3; i+=3){
        unsigned int ia = indices[i];
        unsigned int ib = indices[i+1];
        unsigned int ic = indices[i+2];

        glm::vec3 aPos = positions[ia];

        glm::vec3 bPos = positions[ib];

        glm::vec3 cPos = positions[ic];

        glm::vec3 e1 = bPos - aPos;
        glm::vec3 e2 = cPos - aPos;
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






