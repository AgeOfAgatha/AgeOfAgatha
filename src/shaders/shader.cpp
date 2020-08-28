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
        void Shader::checkCompileErrors(GLuint shader, const char* type){
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
        char* Shader::loadFile(const char *fname){
			FILE* fp;
			long size;
			char* buffer;

			fp = fopen(fname , "rb");
			if(!fp){
				printf("failed to open %s\n", fname);
			}else{
				fseek(fp , 0L , SEEK_END);
				size = ftell(fp);
				rewind(fp);

				//allocate memory for entire content
				buffer = (char*)malloc(sizeof(char)*(size+1));
				if(!buffer){
					printf("memory alloc failed %s\n", fname);
				}else{
					//copy the file into the buffer
					if(1 != fread(buffer, size, 1, fp)){
						printf("file read failed %s\n", fname);
					}
				}
				fclose(fp);
			}
			return buffer;
        }

    /*--------------------------------------------//
    utility function
    Loads shader bins format
    //--------------------------------------------*/
        GLenum Shader::getFormat(const char* name){
			FILE* fp;
			long size;
			char* buffer;
			char* fname;

			fname = (char*)malloc(sizeof(char)*(strlen(name)+strlen(".format")+1));
			strcpy(fname,name);
			strcat(fname,".format");

			fp = fopen(fname , "rb");
			if(!fp){
				printf("failed to open %s\n", fname);
				return (GLenum)(36385);
			}else{
				fseek(fp , 0L , SEEK_END);
				size = ftell(fp);
				rewind(fp);

				//allocate memory for entire content
				buffer = (char*)malloc(sizeof(char)*(size+1));
				if(!buffer){
					printf("memory alloc failed %s\n", fname);
				}else{
					//copy the file into the buffer
					if(1 != fread(buffer, size, 1, fp)){
						printf("file read failed %s\n", fname);
					}
				}
				fclose(fp);
			}
			return (GLenum)(atoi(buffer));
        }

    /*--------------------------------------------//
    constructor
    generates the shader on the fly
    //--------------------------------------------*/
        Shader::Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath){
            ID = glCreateProgram();
            GLint status = GL_FALSE;
			FILE* fp;
			char* fname = (char*)malloc(sizeof(char)*(strlen(name)+strlen(".bin")+1));
            strcpy(fname, name);
            strcat(fname, ".bin");

            //load binary from file
			fp = fopen(fname , "rb");
			if(fp){
				fseek(fp , 0L , SEEK_END);
				long size = ftell(fp);
				rewind(fp);

				//allocate memory for entire content
				char* buffer = (char*)malloc(sizeof(char)*(size+1));
				if(buffer){
					//copy the file into the buffer
					if(1 != fread(buffer, size, 1, fp)){
						//file read fails
					}else{
						//install shader binary
						glProgramBinary(ID, getFormat(name), buffer, size);
						//check for success/failure
						glGetProgramiv(ID, GL_LINK_STATUS, &status);
					}
				}
				fclose(fp);
				free(buffer);
			}
            
            if(GL_FALSE == status){
                //retrieve the vertex/fragment source code from filePath
                const char* vertexCode;
                const char* fragmentCode;
                const char* geometryCode;

                if(vertexPath != NULL){
                    vertexCode = loadFile(vertexPath);
                }
                if(fragmentPath != NULL){
                    fragmentCode = loadFile(fragmentPath);
                }
                if(geometryPath != NULL){
                    geometryCode = loadFile(geometryPath);
                }
                //compile shaders
                //vertex shader
                unsigned int vertex;
                if(vertexPath != NULL){
                    vertex = glCreateShader(GL_VERTEX_SHADER);
                    glShaderSource(vertex, 1, &vertexCode, NULL);
                    glCompileShader(vertex);
                    checkCompileErrors(vertex, vertexPath);
                }
                //fragment Shader
                unsigned int fragment;
                if(fragmentPath != NULL){
                    fragment = glCreateShader(GL_FRAGMENT_SHADER);
                    glShaderSource(fragment, 1, &fragmentCode, NULL);
                    glCompileShader(fragment);
                    checkCompileErrors(fragment, fragmentPath);
                }
                //geometry shader
                unsigned int geometry;
                if(geometryPath != NULL){
                    geometry = glCreateShader(GL_GEOMETRY_SHADER);
                    glShaderSource(geometry, 1, &geometryCode, NULL);
                    glCompileShader(geometry);
                    checkCompileErrors(geometry, geometryPath);
                }
                //shader Program
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
                if(formats > 0) {

	                //Get the binary length
        	        GLint length = 0;
                	glGetProgramiv(ID, GL_PROGRAM_BINARY_LENGTH, &length);

	                //Retrieve the binary code
        	        std::vector<GLubyte> buffer(length);
                	GLenum format = 0;
	                glGetProgramBinary(ID, length, NULL, &format, buffer.data());

	                //Write the binary to a file.
	                fp = fopen(fname, "w+b");
	                fwrite((void*)buffer.data(), sizeof(GLubyte), buffer.size(), fp);
	                fclose(fp);

	                //Write the format to a file
	                char* ffname = (char*)malloc(sizeof(char)*(strlen(name)+strlen(".format")+1));
	                strcpy(ffname, name);
	                strcat(ffname, ".format");
	                fp = fopen(ffname, "w+b");
	                int i = 1;
	                int j = format;
	                while(j >= 10){
	                	j /= 10;
	                	i++;
	                }
	                char* formatc = (char*)malloc(sizeof(char)*(i+1));
	                sprintf(formatc, "%d", format);
	                fputs(formatc, fp);
	                fclose(fp);
	                free(formatc);
				}

                // delete the shaders as they're linked into our program now and no longer necessery
                if(vertexPath != NULL)
                    glDeleteShader(vertex);
                if(fragmentPath != NULL)
                    glDeleteShader(fragment);
                if(geometryPath != NULL)
                    glDeleteShader(geometry);
            }
            free(fname);
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
        int Shader::getAttribLoc(const char* &name) const{
            return glGetAttribLocation(ID, name);
        }
        int Shader::getUniformLoc(const char* &name) const{
            return glGetUniformLocation(ID, name);
        }
        // ------------------------------------------------------------------------
        void Shader::setBool(const char* &name, bool value) const{         
            glUniform1i(glGetUniformLocation(ID, name), (int)value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setInt(const char* &name, int value) const{ 
            glUniform1i(glGetUniformLocation(ID, name), value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setFloat(const char* &name, float value) const{ 
            glUniform1f(glGetUniformLocation(ID, name), value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setVec2(const char* &name, const vec2 &value) const{ 
            glUniform2fv(glGetUniformLocation(ID, name), 1, (float *)&value); 
        }
        void Shader::setVec2(const char* &name, float x, float y) const{ 
            glUniform2f(glGetUniformLocation(ID, name), x, y); 
        }
        void Shader::setVec2(const char* &name, const glm::vec2 &value) const{
            glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]); 
        }
        // ------------------------------------------------------------------------
        void Shader::setVec3(const char* &name, const vec3 &value) const{ 
            glUniform3fv(glGetUniformLocation(ID, name), 1, (float *)&value); 
        }
        void Shader::setVec3(const char* &name, float x, float y, float z) const{ 
            glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
        }
        void Shader::setVec3(const char* &name, const glm::vec3 &value) const{
            glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]); 
        }
        // ------------------------------------------------------------------------
        void Shader::setVec4(const char* &name, const vec4 &value) const{ 
            glUniform4fv(glGetUniformLocation(ID, name), 1, (float *)&value); 
        }
        void Shader::setVec4(const char* &name, float x, float y, float z, float w) const{ 
            glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
        }
        void Shader::setVec4(const char* &name, const glm::vec4 &value) const{
            glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]); 
        }
        // ------------------------------------------------------------------------
        void Shader::setMat4(const char* &name, float* value) const{ 
            glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, (float *)value); 
        }
        // ------------------------------------------------------------------------
        void Shader::setMat2(const char* &name, const glm::mat2 &mat) const{
            glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void Shader::setMat3(const char* &name, const glm::mat3 &mat) const{
            glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void Shader::setMat4(const char* &name, const glm::mat4 &mat) const{
            glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
        }

#endif
