#ifndef SHADER_H
#define SHADER_H

class Shader;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../globals.h"
    #include "../../deps/glm/glm.hpp"
    #include "../../deps/glm/gtc/matrix_transform.hpp"
    #include "../../deps/glm/gtc/type_ptr.hpp"
    #include "../common/vector.h"

    #include <stdlib.h>
    #include <iostream>
    #include <vector>
    #include <cstdio>

/*--------------------------------------------//
Shader Class
//--------------------------------------------*/
    class Shader{
        private:
            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
                GLenum getFormat(const char* name);
                void printShaderInfoLog(GLint shader);
                void checkCompileErrors(GLuint shader, const char* type);
                char* loadFile(const char *fname);

        public:
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                unsigned int ID;

            /*--------------------------------------------//
            constructor
            //--------------------------------------------*/
                Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath);

            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
                void use();
                int getAttribLoc(const char* &name) const;
                int getUniformLoc(const char* &name) const;
                void setBool(const char* &name, bool value) const;
                void setInt(const char* &name, int value) const;
                void setFloat(const char* &name, float value) const;
                void setVec2(const char* &name, const vec2 &value) const;
                void setVec2(const char* &name, float x, float y) const;
                void setVec2(const char* &name, const glm::vec2 &value) const;
                void setVec3(const char* &name, const vec3 &value) const;
                void setVec3(const char* &name, float x, float y, float z) const;
                void setVec3(const char* &name, const glm::vec3 &value) const;
                void setVec4(const char* &name, const vec4 &value) const;
                void setVec4(const char* &name, float x, float y, float z, float w) const;
                void setVec4(const char* &name, const glm::vec4 &value) const;
                void setMat4(const char* &name, float* value) const;
                void setMat2(const char* &name, const glm::mat2 &mat) const;
                void setMat3(const char* &name, const glm::mat3 &mat) const;
                void setMat4(const char* &name, const glm::mat4 &mat) const;
    };
#endif
