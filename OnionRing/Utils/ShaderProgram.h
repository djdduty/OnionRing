#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <vector>
#include <map>
#include <System/OS/PlatformIncludes.h>
#include <Utils/BcString.h>


namespace BearClaw {

class ShaderProgram
{
public:
	
	enum AttribType {
		VERTEX_COORD_ATTRIB,
		NORMAL_ATTRIB,
		TEXTURE_COORD_ATTRIB,
		TANGENT_ATTRIB,
		BITANGENT_ATTRIB,
		VERTEX_ATTRIB1,
		VERTEX_ATTRIB2,
		VERTEX_ATTRIB3,
		VERTEX_ATTRIB4,
        COUNT_ATTRIB_TYPE
	};

	enum ShaderType {
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVAL_SHADER,
		FRAGMENT_SHADER,
		COUNT_SHADER_TYPE
	};

	static const int MAX_TEXTURES = 8;

    ShaderProgram();
	~ShaderProgram();
	void init();
	void loadShader(ShaderProgram::ShaderType st, std::string fileName);
	void setProgramOutput(int index, std::string name);
	GLint getProgramOutput(std::string name);
	void setVertexAttribName(ShaderProgram::AttribType at, std::string name);
	void prepareProgram();
	void setUniform(std::string name, void *value);
	void setUniform(std::string name, int value);
	void setUniform(std::string name, float value);
	static void setBlock(std::string name, void *value);
	static void setBlockUniform(std::string blockName, std::string uniformName, void *value);
	static void setBlockUniformArrayElement(std::string blockName, std::string uniformName, int arrayIndex, void * value);
	GLuint getProgramIndex();
	GLuint getShaderIndex(ShaderProgram::ShaderType);
	std::string getShaderInfoLog(ShaderProgram::ShaderType);
	std::string getProgramInfoLog();
	std::string getAllInfoLogs();
	bool isProgramValid();
	bool isShaderCompiled(ShaderProgram::ShaderType);
	bool isProgramLinked();


protected:
	typedef struct uniforms {
		GLenum type;
		GLuint location;
		GLuint size;
		GLuint stride;
	}myUniforms;

	typedef struct blockUniforms {
		GLenum type;
		GLuint offset;
		GLuint size;
		GLuint arrayStride;
	} myBlockUniform;

	class UniformBlock {

		public:
			int size;
			GLuint buffer;
			GLuint bindingIndex;
			std::map<std::string, myBlockUniform > uniformOffsets;
	};
	bool pInited;

	static int spBlockCount;

	static std::map<std::string, UniformBlock> spBlocks;

	static GLenum spGLShaderTypes[ShaderProgram::COUNT_SHADER_TYPE];
	
	static std::string spStringShaderTypes[ShaderProgram::COUNT_SHADER_TYPE];

	std::string pResult;

	GLuint pShader[ShaderProgram::COUNT_SHADER_TYPE], pProgram;

	std::map<std::string, myUniforms> pUniforms;

	void addUniforms();
	
	void addUniform(std::string name, GLenum type, unsigned int size);

	void addBlocks();

	int typeSize(int type);

	char *textFileRead(std::string fileName);
};
}

#endif
