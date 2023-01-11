#include "ShaderGL.h"
#include "../Utils/Log.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <string>

ShaderGL &ShaderGL::use()
{
    glUseProgram(id);
    return *this;
}

void ShaderGL::compile(const GLchar *vertexSource, const GLchar *fragmentSource,
                       const GLchar *tessControlSource, const GLchar *tessEvalSource, const GLchar *geometrySource)
{
    compileVertexShader(vertexSource);
    bool tessExists = compileTessControlShader(tessControlSource);
    tessExists &= compileTessEvalShader(tessEvalSource);
    bool gsExists = compileGeometryShader(geometrySource);
    compileFragmentShader(fragmentSource);
    createShaderProgram(tessExists, gsExists);
    printAllParams(id);
}

void ShaderGL::compileVertexShader(const GLchar *vertex_source)
{
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_source, NULL);
    glCompileShader(vs);
    checkShaderErrors(vs, "vertex");
}

void ShaderGL::compileFragmentShader(const GLchar *fragment_source)
{
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_source, NULL);
    glCompileShader(fs);
    checkShaderErrors(fs, "fragment");
}

bool ShaderGL::compileTessControlShader(const GLchar *tessControlSource) {
    if(tessControlSource == nullptr) {
        return false;
    }

    tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tcs, 1, &tessControlSource, NULL);
    glCompileShader(tcs);
    checkShaderErrors(tcs, "tessellation control");
    return true;
}

bool ShaderGL::compileTessEvalShader(const GLchar *tessEvalSource) {
    if(tessEvalSource == nullptr) {
        return false;
    }

    tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tes, 1, &tessEvalSource, NULL);
    glCompileShader(tes);
    checkShaderErrors(tes, "tessellation evaluation");
    return true;
}

bool ShaderGL::compileGeometryShader(const GLchar *geometry_source)
{
    if (geometry_source == nullptr)
    {
        return false;
    }

    gs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs, 1, &geometry_source, NULL);
    glCompileShader(gs);
    checkShaderErrors(gs, "geometry");

    return true;
}

void ShaderGL::createShaderProgram(bool tessShadersExist, bool geometryShaderExists)
{
    // Create program
    id = glCreateProgram();
    glAttachShader(id, fs);
    if (tessShadersExist)
    {
        glAttachShader(id, tcs);
        glAttachShader(id, tes);
    }
    if (geometryShaderExists)
    {
        glAttachShader(id, gs);
    }
    glAttachShader(id, vs);
    glLinkProgram(id);

    // Check for linking error
    int params = -1;
    glGetProgramiv(id, GL_LINK_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "Could not link shader programme GL index " << id;
        printProgramInfoLog(id);
    }
    if (!isValid(id))
    {
        LOG(Error) << "Could not validate shader" << id;
    }

    // Delete shaders for they are no longer used
    glDeleteShader(vs);
    if (tessShadersExist)
    {
        glDeleteShader(tcs);
        glDeleteShader(tes);
    }
    if (geometryShaderExists)
    {
        glDeleteShader(gs);
    }
    glDeleteShader(fs);
}

void ShaderGL::setFloat(const GLchar *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(id, name), value);
}
void ShaderGL::setInteger(const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(id, name), value);
}
void ShaderGL::setVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(id, name), x, y);
}
void ShaderGL::setVector2f(const GLchar *name, const Vector2 &value)
{
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}
void ShaderGL::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}
void ShaderGL::setVector3f(const GLchar *name, const glm::vec3& value)
{
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}
void ShaderGL::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}
void ShaderGL::setVector4f(const GLchar *name, const Vector4 &value)
{
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}
void ShaderGL::setMatrix4(const GLchar *name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void ShaderGL::setMatrix4Row(const GLchar *name, const Matrix4Row &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, matrix.getAsFloatPtr());
}
void ShaderGL::printShaderInfoLog(GLuint shaderIndex)
{
    int maxLength = 2048;
    int actualLength = 0;
    char log[2048];
    glGetShaderInfoLog(shaderIndex, maxLength, &actualLength, log);
    LOG(Info) << "ShaderGL info log for GL index" << shaderIndex;
    LOG(Info) << log;
}

void ShaderGL::printProgramInfoLog(GLuint programId)
{
    int maxLength = 2048;
    int actualLength = 0;
    char log[2048];
    glGetProgramInfoLog(programId, maxLength, &actualLength, log);
    LOG(Info) << "program info log for GL index" << programId;
    LOG(Info) << log;
}

void ShaderGL::checkShaderErrors(GLuint shader, std::string shaderType)
{
    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "GL " << shaderType << " shader index " << shader << " did not compile.";
        printShaderInfoLog(shader);
    }
}

const char *ShaderGL::GLTypeToString(GLenum type)
{
    switch (type)
    {
    case GL_BOOL:
        return "bool";
    case GL_INT:
        return "int";
    case GL_FLOAT:
        return "float";
    case GL_FLOAT_VEC2:
        return "vec2";
    case GL_FLOAT_VEC3:
        return "vec3";
    case GL_FLOAT_VEC4:
        return "vec4";
    case GL_FLOAT_MAT2:
        return "mat2";
    case GL_FLOAT_MAT3:
        return "mat3";
    case GL_FLOAT_MAT4:
        return "mat4";
    case GL_SAMPLER_2D:
        return "sampler2D";
    case GL_SAMPLER_3D:
        return "sampler3D";
    case GL_SAMPLER_CUBE:
        return "samplerCube";
    case GL_SAMPLER_2D_SHADOW:
        return "sampler2DShadow";
    default:
        return "other";
    }
}

void ShaderGL::printAllParams(GLuint programId)
{
    LOG(Info) << "-----------------------------";
    LOG(Info) << "ShaderGL programme " << programId << " info:";
    int params = -1;
    glGetProgramiv(programId, GL_LINK_STATUS, &params);
    LOG(Info) << "GL_LINK_STATUS = " << params;

    glGetProgramiv(programId, GL_ATTACHED_SHADERS, &params);
    LOG(Info) << "GL_ATTACHED_SHADERS = " << params;

    glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &params);
    LOG(Info) << "GL_ACTIVE_ATTRIBUTES = " << params;
    for (GLuint i = 0; i < (GLuint)params; i++)
    {
        char name[64];
        int maxLength = 64;
        int actualLength = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(programId, i, maxLength, &actualLength, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char longName[77];
#if __linux__
                sprintf(longName, "%s[%i]", name, j);
#else
                sprintf_s(longName, "%s[%i]", name, j);
#endif
                int location = glGetAttribLocation(programId, longName);
                LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << longName << " location:" << location;
            }
        }
        else
        {
            int location = glGetAttribLocation(programId, name);
            LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << name << " location:" << location;
        }
    }

    glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &params);
    LOG(Info) << "GL_ACTIVE_UNIFORMS = " << params;
    for (GLuint i = 0; i < (GLuint)params; i++)
    {
        char name[64];
        int maxLength = 64;
        int actualLength = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(programId, i, maxLength, &actualLength, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char longName[77];
                sprintf(longName, "%s[%i]", name, j);
                int location = glGetUniformLocation(programId, longName);
                LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << longName << " location:" << location;
            }
        }
        else
        {
            int location = glGetUniformLocation(programId, name);
            LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << name << " location:" << location;
        }
    }
    printProgramInfoLog(programId);
}

bool ShaderGL::isValid(GLuint programId)
{
    glValidateProgram(programId);
    int params = -1;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &params);
    LOG(Info) << "program " << programId << " GL_VALIDATE_STATUS = " << params;
    if (params != GL_TRUE)
    {
        printProgramInfoLog(programId);
        return false;
    }
    return true;
}
