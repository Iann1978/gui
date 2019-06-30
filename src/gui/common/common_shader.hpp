#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path, const char * geometry_file_path=nullptr);
GLuint LoadShaderFromSourceCode(const char *vertexShaderCode, const char *fragmentShaderCode, const char *geometryShaderCode = nullptr);

#endif
