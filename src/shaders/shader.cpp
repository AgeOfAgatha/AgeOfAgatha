#ifndef SHADER
#define SHADER

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "shader.h"

/*--------------------------------------------//
Shader Class
//--------------------------------------------*/
    /*--------------------------------------------//
    utility function 
    prints the compile errors
    //--------------------------------------------*/
        void Shader::printShaderInfoLog(GLint shader){
            int infoLogLen = 0;
            int charsWritten = 0;
            GLchar *infoLog;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

            if (infoLogLen > 0)
            {
                infoLog = new GLchar[infoLogLen];
                // error check for fail to allocate memory omitted
                glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
                printf("InfoLog : \n%s\n", infoLog);
                delete [] infoLog;
            }
        }

    /*--------------------------------------------//
    utility function 
    for checking shader compilation/linking errors.
    //--------------------------------------------*/
        void Shader::checkCompileErrors(GLuint shader, char* type){
            GLint success;
            if(strcmp(type, "Program") != 0){
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if(!success){
                    printf("%s Shader not compiled\n", type);
                    printf("OpenGL error: %d\n", glGetError());
                    printShaderInfoLog(shader);
                    glDeleteShader(shader);
                    exit(1);
                }
            }else{
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if(!success){
                    printf("Program not linked\n");
                    printf("OpenGL error: %d\n", glGetError());
                    printShaderInfoLog(shader);
                    glDeleteShader(shader);
                    exit(1);
                }
            }
        }

    /*--------------------------------------------//
    utility function 
    Loads a file and reads it to a string
    //--------------------------------------------*/
        std::string Shader::loadFile(const char *fname){
            std::ifstream file(fname);
            if(!file.is_open()){
                printf("Unable to open file %s\n", fname);
                exit(1);
            }

            std::stringstream fileData;
            fileData << file.rdbuf();
            file.close();

            return fileData.str();
        }

    /*--------------------------------------------//
    utility function 
    Loads shader bins format
    //--------------------------------------------*/
        GLenum Shader::getFormat(const char* name){
            const char *fname = (std::string(name) + std::string(".format")).c_str();
            std::ifstream file(fname);
            if(!file.is_open()){
                return (GLenum)(36385);
            }

            std::stringstream fileData;
            fileData << file.rdbuf();
            file.close();

            return (GLenum)(atoi(fileData.str().data()));
        }

    /*--------------------------------------------//
    constructor 
    generates the shader on the fly
    //--------------------------------------------*/
        Shader::Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath){
            ID = glCreateProgram();

            // Load binary from file
            std::ifstream inputStream(std::string(name) + std::string(".bin"), std::ios::binary);
            std::istreambuf_iterator<char> startIt(inputStream), endIt;
            std::vector<char> buffer(startIt, endIt);  // Load file
            inputStream.close();

            // Install shader binary
            glProgramBinary(ID, getFormat(name), buffer.data(), buffer.size() );

            // Check for success/failure
            GLint status;
            glGetProgramiv(ID, GL_LINK_STATUS, &status);
            if( GL_FALSE == status ) {
                // retrieve the vertex/fragment source code from filePath
                std::string vertexCode;
                std::string fragmentCode;
                std::string geometryCode;

                if(vertexPath != NULL){
                    vertexCode = loadFile(vertexPath);
                }
                if(fragmentPath != NULL){
                    fragmentCode = loadFile(fragmentPath);
                }
                if(geometryPath != NULL){
                    geometryCode = loadFile(geometryPath);
                }
                // compile shaders
                // vertex shader
                unsigned int vertex;
                if(vertexPath != NULL){
                    const char* vShaderCode = vertexCode.c_str();
                    vertex = glCreateShader(GL_VERTEX_SHADER);
                    glShaderSource(vertex, 1, &vShaderCode, NULL);
                    glCompileShader(vertex);
                    checkCompileErrors(vertex, "Vertex");
                }
                // fragment Shader
                unsigned int fragment;
                if(fragmentPath != NULL){
                    const char * fShaderCode = fragmentCode.c_str();
                    fragment = glCreateShader(GL_FRAGMENT_SHADER);
                    glShaderSource(fragment, 1, &fShaderCode, NULL);
                    glCompileShader(fragment);
                    checkCompileErrors(fragment, "Fragment");
                }
                // geometry shader
                unsigned int geometry;
                if(geometryPath != NULL){
                    const char * gShaderCode = geometryCode.c_str();
                    geometry = glCreateShader(GL_GEOMETRY_SHADER);
                    glShaderSource(geometry, 1, &gShaderCode, NULL);
                    glCompileShader(geometry);
                    checkCompileErrors(geometry, "Geometry");
                }
                // shader Program
                ID = glCreateProgram();
                if(vertexPath != NULL)
                    glAttachShader(ID, vertex);
                if(fragmentPath != NULL)
                    glAttachShader(ID, fragment);
                if(geometryPath != NULL)
                    glAttachShader(ID, geometry);

                glLinkProgram(ID);
                checkCompileErrors(ID, "Program");


                //Check compatibility
                GLint formats = 0;
                glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
                if( formats < 1 ) {
                    std::cerr << "Driver does not support any binary formats." << std::endl;
                    exit(EXIT_FAILURE);
                }

                //Get the binary length
                GLint length = 0;
                glGetProgramiv(ID, GL_PROGRAM_BINARY_LENGTH, &length);

                //Retrieve the binary code
                std::vector<GLubyte> buffer(length);
                GLenum format = 0;
                glGetProgramBinary(ID, length, NULL, &format, buffer.data());

                //Write the binary to a file.
                std::string fName(std::string(name) + std::string(".bin"));
                std::cout << "Writing to " << fName << ", binary format = " <<format << std::endl;
                std::ofstream out(fName.c_str(), std::ios::binary);
                out.write( reinterpret_cast<char *>(buffer.data()), length );
                out.close();
                //Write the format to a file
                std::ofstream formatfile;
                formatfile.open (std::string(name) + std::string(".format"));
                formatfile << format;
                formatfile.close();

                // delete the shaders as they're linked into our program now and no longer necessery
                if(vertexPath != NULL)
                    glDeleteShader(vertex);
                if(fragmentPath != NULL)
                    glDeleteShader(fragment);
                if(geometryPath != NULL)
                    glDeleteShader(geometry);
            }
        }
    
    /*--------------------------------------------//
    Use
    Applies the shader program
    //--------------------------------------------*/
        void Shader::use(){ 
            glUseProgram(ID); 
        }

    /*--------------------------------------------//
    Utility setter/getter functions
    //--------------------------------------------*/
        int Shader::getAttribLoc(const std::string &name) const{
            return glGetAttribLocation(ID, name.c_str());
        }
        int Shader::getUniformLoc(const std::string &name) const{
            return glGetUniformLocation(ID, name.c_str());
        }
        // ------------------------------------------------------------------------
        void Shader::setBool(const std::string &name, bool value) const{         
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setInt(const std::string &name, int value) const{ 
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setFloat(const std::string &name, float value) const{ 
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setVec2(const std::string &name, const vec2 &value) const{ 
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, (float *)&value); 
        }
        void Shader::setVec2(const std::string &name, float x, float y) const{ 
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
        }
        void Shader::setVec2(const std::string &name, const glm::vec2 &value) const{
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
        // ------------------------------------------------------------------------
        void Shader::setVec3(const std::string &name, const vec3 &value) const{ 
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, (float *)&value); 
        }
        void Shader::setVec3(const std::string &name, float x, float y, float z) const{ 
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
        }
        void Shader::setVec3(const std::string &name, const glm::vec3 &value) const{
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
        // ------------------------------------------------------------------------
        void Shader::setVec4(const std::string &name, const vec4 &value) const{ 
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, (float *)&value); 
        }
        void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const{ 
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
        }
        void Shader::setVec4(const std::string &name, const glm::vec4 &value) const{
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
        // ------------------------------------------------------------------------
        void Shader::setMat4(const std::string &name, float* value) const{ 
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, (float *)value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const{
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const{
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const{
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

#endif