#include "Mesh.h"

void Mesh::loadPreMade(char c) {
    if(c == 'c'){
        generateCube();
    }
    else if(c == 's'){
        generateSphere(20,20);
    }
    else if (c == 't'){
        generateTore(20,20);
    }
    else if(c == 'i'){
        generateIcosahedron();
    }
    else{
        std::cout<<"error loading the mesh.. "<<std::endl;
        exit(1);
    }

    GLuint VBO, EBO;
    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, positionDots.size() * sizeof(GLfloat), positionDots.data(), GL_STATIC_DRAW);

    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, connections.size() * sizeof(GLuint), connections.data(), GL_STATIC_DRAW);


    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    //std::cout<<"connections size: "<<connections.size()<<std::endl;
    //std::cout<<"potionDots size: "<<positionDots.size()<<std::endl;
}

void Mesh::draw() {
    glDrawElements(GL_TRIANGLES, connections.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::clean() {
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::generateSphere(int nX, int nY) {
    float deltaTeta = 2*M_PI / (float)nX;
    float deltaPhi = M_PI / (float)nY;

    for(int i=0; i < nX; i++){
        for(int j=0; j < nY; j++){
            float teta = deltaTeta * i;
            float phi = deltaPhi * j - M_PI/2;

            putDots(std::cos(teta)*std::cos(phi),std::sin(teta)*std::cos(phi),std::sin(phi));
        }
    }

    for(int i=0; i < nX ; i++){
        for(int j=0; j < nY-1; j++){
            if(i == nX -1){
                connectDots(i*nY+j, i*nY+j+1, j);
                connectDots(j+1, j, i*nY+j+1);
            }else{
                connectDots(i*nY+j, i*nY+j+1, (i+1)*nY+j);
                connectDots((i+1)*nY+j+1, (i+1)*nY+j, i*nY+j+1);
            }
        }
    }

}

void Mesh::generateCube() {
    positionDots =  {
            -1, -1,  1, //0
            1, -1,  1, //1
            -1,  1,  1, //2
            1,  1,  1, //3
            -1, -1, -1, //4
            1, -1, -1, //5
            -1,  1, -1, //6
            1,  1, -1  //7
    };

    connections = {
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
}

void Mesh::generateTore(int nX, int nY) {
    float R = 1.5;
    float r = 0.5;
    float angleChqEtp = 2*M_PI / (float)nX;
    //float deltaPhi = M_PI / (float)nY;

    for(int i=0; i < nX; i++){ //u
        for(int j=0; j < nY; j++){ // v
            float Q = angleChqEtp * i;
            float P = angleChqEtp * j;

            putDots((R + r*std::cos(Q))*std::cos(P), (R + r*std::cos(Q))*std::sin(P), r*std::sin(Q));
        }
    }

    for(int i = 0; i < nX; i++){
        for(int j = 0; j < nY; j++){
            if (j == nY-1 && i == nY-1){
                connectDots(i*nY+j, i*nY, j);
                connectDots(i*nY, j+1, i);

                //std::cout<<"if T1 C1 :"<< i*nY << "T1 C2: "<< 48 << "T1 C3: "<< i <<" i: "<<i<<" j: "<<j<<std::endl;
            }
            else if (j == nY-1){
                connectDots(i*nY+j, i*nY, (i+1)*nY+j);
                connectDots((i+1)*nY, (i+1)*nY+j, i*nY);

                //std::cout<<"else if1 T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+1 << "T1 C3: "<<(i+1)*nY+j<<" i: "<<i<<" j: "<<j<<std::endl;
            }
            else if(i == nY-1){
                connectDots(i*nY+j, i*nY+j+1, j);
                connectDots(j+1, j, i*nY+j+1);


                //std::cout<<"else if T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+j+1 << "T1 C3: "<< j<<" i: "<<i<<" j: "<<j<<std::endl;
                //std::cout<<"if T2 C1 :"<< j + 1<< "T2 C2: "<< j << "T2 C3: "<<i*nY+j+1<<"i: "<<i<<"j: "<<j<<std::endl;
            }else{
                connectDots(i*nY+j, i*nY+j+1, (i+1)*nY+j);
                connectDots((i+1)*nY+j+1, (i+1)*nY+j, i*nY+j+1);

                //std::cout<<"T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+j+1 << "T1 C3: "<<(i+1)*nY+j<<" i: "<<i<<" j: "<<j<<std::endl;
                //std::cout<<"T2 C1 :"<< (i+1)*nY+j+1 << "T2 C2: "<< (i+1)*nY+j << "T2 C3: "<<i*nY+j+1<<"i: "<<i<<"j: "<<j<<std::endl;
            }
        }
    }
}

void Mesh::generateIcosahedron() {
    connections = {
            2, 1, 0,
            3, 2, 0,
            4, 3, 0,
            5, 4, 0,
            1, 5, 0,
            11, 6,  7,
            11, 7,  8,
            11, 8,  9,
            11, 9,  10,
            11, 10, 6,
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

    positionDots = {
            0.000f,  0.000f,  1.000f,
            0.894f,  0.000f,  0.447f,
            0.276f,  0.851f,  0.447f,
            -0.724f,  0.526f,  0.447f,
            -0.724f, -0.526f,  0.447f,
            0.276f, -0.851f,  0.447f,
            0.724f,  0.526f, -0.447f,
            -0.276f,  0.851f, -0.447f,
            -0.894f,  0.000f, -0.447f,
            -0.276f, -0.851f, -0.447f,
            0.724f, -0.526f, -0.447f,
            0.000f,  0.000f, -1.000f };
}


void Mesh::connectDots(int a, int b, int c) {
    connections.push_back(a);
    connections.push_back(b);
    connections.push_back(c);
}
void Mesh::putDots(float a, float b, float c) {
    positionDots.push_back(a);
    positionDots.push_back(b);
    positionDots.push_back(c);
}








