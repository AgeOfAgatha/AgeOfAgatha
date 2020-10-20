#ifndef SHADER_H
#define SHADER_H

class Shader;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../globals.h"
    #include "../common/vector.h"
    #include "../common/matrix.h"

    #include <stdlib.h>
    #include <string.h>
    #include <fstream>
    #include <sstream>
    #include <iostream>
    #include <vector>

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
                std::string loadFile(const char *fname);

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
                int getAttribLoc(const std::string &name) const;
                int getUniformLoc(const std::string &name) const;
                void setBool(const std::string &name, bool value) const;
                void setInt(const std::string &name, int value) const;
                void setFloat(const std::string &name, float value) const;
                void setVec2(const std::string &name, float x, float y) const;
                void setVec2(const std::string &name, const Vec2 &value) const;
                void setVec3(const std::string &name, float x, float y, float z) const;
                void setVec3(const std::string &name, const Vec3 &value) const;
                void setVec4(const std::string &name, float x, float y, float z, float w) const;
                void setVec4(const std::string &name, const Vec4 &value) const;
                void setMat4(const std::string &name, float* value) const;
                void setMat2(const std::string &name, const Mat2 &mat) const;
                void setMat3(const std::string &name, const Mat3 &mat) const;
                void setMat4(const std::string &name, const Mat4 &mat) const;
    };
#endif
