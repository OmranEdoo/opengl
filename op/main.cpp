#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "layerraster.h"
#include "trajectory.h"

#include <cmath>



using namespace std;

int main()
{

    /////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


    /////////////////////////Ouverture de la fen�tre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //d�finition de la taille de la fen�tre
    //int width = 600;
    //int height = 600;

    //On r�cup�re les dimensions de l'�cran pour cr�er la fen�tre
    /*GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);*/

    //Enfin on cr�e la fen�tre
    int width;
    int height;

    //On rcupre les dimensions de l'cran pour crer la fentre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary, nullptr, nullptr, &width, &height);

    //Enfin on cre la fentre
    GLFWwindow* window = glfwCreateWindow(width, height, "MNT_DYNAMIQUE", NULL, NULL);

    glfwSwapInterval(1);
    //On v�rifie que l'initialisation a bien march�
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la cr�ation de la f�n�tre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on d�finit la fen�tre cr��e comme la fen�tre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



    /////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Initialisation de GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

    /////////////////////////On cr�e un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


    /////////////////////////On cr�e un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader("../shaders/SimpleVertexShader.vertexshader", "../shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

    /////////////////////////On cr�e un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;

    va.Bind();

    /////////////////////////On cr�e la camera et les contr�les/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

    /////////////////////////Cr�ation des formes � afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    vector<glm::vec3> g_vertex_buffer_data = {
        glm::vec3(-1.0f, -1.0f, -1.0f),  //0
        glm::vec3(-1.0f, -1.0f,  1.0f),  //1
        glm::vec3(-1.0f,  1.0f,  1.0f),  //2
        glm::vec3( 1.0f,  1.0f, -1.0f),  //3
        glm::vec3(-1.0f,  1.0f, -1.0f),  //4
        glm::vec3( 1.0f, -1.0f,  1.0f),  //5
        glm::vec3( 1.0f, -1.0f, -1.0f),  //6
        glm::vec3( 1.0f,  1.0f,  1.0f)   //7
    };

    vector<glm::vec3> colors = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    };

    vector<unsigned int> bufferIndexData = {
        2, 3, 4,
        2, 3, 7,
        7, 6, 3,
        7, 6, 5,
        5, 0, 6,
        5, 0, 1,
        1, 4, 0,
        1, 4, 2,
        2, 5, 7,
        2, 5, 1,
        4, 6, 3,
        4, 6, 0
    };

    
    vector<glm::vec2> g_uv_buffer_data = {
        glm::vec2(0.000059f, 1.0f - 0.000004f),
        glm::vec2(0.000103f, 1.0f - 0.336048f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(1.000023f, 1.0f - 0.000013f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.999958f, 1.0f - 0.336064f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(0.667969f, 1.0f - 0.671889f),
        glm::vec2(1.000023f, 1.0f - 0.000013f),
        glm::vec2(0.668104f, 1.0f - 0.000013f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.000059f, 1.0f - 0.000004f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.336098f, 1.0f - 0.000071f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(1.000004f, 1.0f - 0.671847f),
        glm::vec2(0.999958f, 1.0f - 0.336064f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.668104f, 1.0f - 0.000013f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.668104f, 1.0f - 0.000013f),
        glm::vec2(0.336098f, 1.0f - 0.000071f),
        glm::vec2(0.000103f, 1.0f - 0.336048f),
        glm::vec2(0.000004f, 1.0f - 0.671870f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(0.000103f, 1.0f - 0.336048f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.667969f, 1.0f - 0.671889f),
        glm::vec2(1.000004f, 1.0f - 0.671847f),
        glm::vec2(0.667979f, 1.0f - 0.335851f)
    };

    std::cout << "0" << std::endl;


    Object o(g_vertex_buffer_data, bufferIndexData, g_uv_buffer_data, colors, "D:/omran/School/Ing3/opengl/tp/op/op/textures/t0010_0.png");

    std::cout << "1" << std::endl;

    std::string mntFilePath = "C:/Users/omran/Downloads/SantaMonicaMountains.png";
    LayerRaster mntLayer(mntFilePath);


    Object mnt(mntLayer.getVerticesVector(), mntLayer.getIndexTable(), mntLayer.getUvVector(), mntLayer.getColors(), "D:/omran/School/Ing3/opengl/tp/op/op/textures/47056.jpg");

    std::cout << "3" << std::endl;
    /////////////////////////Cr�ation de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    o.setPosition({ mntLayer.getMaxX(), mntLayer.getMaxY(), mntLayer.getVerticesVector()[mntLayer.getMaxX() + mntLayer.getMaxY()*mntLayer.getWidthTIFF()][2] + 1 });

    cam.setPosition({ mntLayer.getMaxX(), mntLayer.getMaxY() - 70, mntLayer.getVerticesVector()[mntLayer.getMaxX() + mntLayer.getMaxY() * mntLayer.getWidthTIFF()][2] + 5 });

    cam.setVerticalAngle(1.5);

    cam.computeMatrices(width, height);
    glm::mat4 m = o.getModelMatrix();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();
    
    glm::mat4 mvp = p * v * m;

    shader.setUniformMat4f("MVP", mvp);
    

    /////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    float alpha = 0;

    Trajectory trajectory;


    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {

        ////////////////On commence par vider les buffers///////////////
        renderer.Clear();

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        alpha += 0.01;

        o.setPosition(trajectory.computePositions(40, alpha, mntLayer));

        controls.update(deltaTime, &shader);

        if (controls.getMode()) {
            cam.setPosition(trajectory.computePositions(40, alpha - 0.3, mntLayer));
            cam.setPositionObject(o.getPosition());
        }

        int camX = cam.getPosition()[0]; 
        int camY = cam.getPosition()[1];
        int camZ = cam.getPosition()[2];

        if (camZ <= mntLayer.getVerticesVector()[camX + camY * mntLayer.getWidthTIFF()][2])
            cam.setPosition({ camX, camY, mntLayer.getVerticesVector()[camX + camY * mntLayer.getWidthTIFF()][2]});

        cam.computeMatrices(width, height);
        m = mnt.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p * v * m;
        shader.setUniformMat4f("MVP", mvp);

        renderer.Draw(va, mnt, shader);

        mnt.Unbind();

        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p * v * m;
        shader.setUniformMat4f("MVP", mvp);

        renderer.Draw(va, o, shader);

        o.Unbind();       

        ////////////////Partie rafraichissement de l'image et des �v�nements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();


    return 0;
}
