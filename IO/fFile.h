#pragma once

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <fstream>
#include <locale>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

typedef unsigned char fresult;
typedef unsigned char ffilemode;
typedef unsigned char fencoding;
typedef unsigned char ffnametype;

// ferdinand's IO File manipulator. Reads/writes the entire file per "Open()"/"Close()".
// C++ version required: >= C++17 
class fFile
{
private:

	enum FILENAMETYPE {
		FNT_STRING,
		FNT_WSTRING,
	};

	ffnametype fNType = FNT_STRING;
	std::string fileName;
	std::wstring wfileName;

	std::ifstream* input = 0;
	std::ofstream* output = 0;

	fresult ReadFile();
	fresult OpenFile();
	fresult CloseFile();

	// [ENCODING] -> CP866
	fresult ConvertFileEncoding();
	void CnvUTF8();
	void CnvANSI();

	fresult OutConvFileEncoding();
	void OutCnvANSI();
	
public:

	enum RESULT_CODE {
		CODE_SUCCESS = 0,
		CODE_NO_SUCH_FILE_OR_DIR,
		CODE_BAD_INPUT_MODE,
		CODE_NO_OPENED_FILE,
		CODE_BAD_ENCODING,
		CODE_UNSUPPORTED_ENCODING,
	};

	enum INPUT_MODE {
		AS_NULL = 0,
		AS_INPUT,
		AS_OUTPUT,
	};

	enum ENCODING_TYPE {
		ENC_NULL = 0,
		ENC_CP866,
		ENC_UTF8,
		ENC_ANSI,
	};

	std::string fileData;
	ffilemode inputMode = AS_NULL;
	fencoding encoding = ENC_CP866;

	fresult Open(const std::string& fname);
	fresult Open(const std::wstring& fname);
	fresult Close();

	static std::string strCode(fresult code);
	static fencoding encStr(const std::string& str);
	
	fFile(const std::string& fname, ffilemode mode = AS_INPUT);
	fFile(ffilemode mode = AS_NULL);

	~fFile();
};

// fFile-based buffer that reads the entire file and then can move his reading/writing pos.
// [Write/Read]+b = [Write/Read] binary.
class fFileStream {
private:

	void WriteChar(char c);
public:

	fFile buffer;
	size_t pos = 0;

	fresult Open(const std::string& fname);
	fresult Close();

	template<typename T>
	T Readb() {
		T val;

		memcpy((void*)(&val), buffer.fileData.data() + pos, sizeof(T));
		pos += sizeof(T);

		return val;
	}

	// Fills the buffer with data in current position (i.e read(buf.data(), buf.size()))
	void Read(std::string& buf);
	// WARNING: destination buffer is must be pre-allocated 
	void Read(char* dest, size_t size);

	void Write(const std::string& buf);
	void Write(const char* src, size_t size);

	template<typename T>
	void Writeb(T val) {
		for (size_t i = 0; i < sizeof(T); i++) {
			WriteChar(
				(char)
				((char*)(&val))[i]
			);
		}
	}

	fFileStream(const std::string& fname, ffilemode mode = fFile::AS_INPUT);
	fFileStream(ffilemode mode = fFile::AS_NULL);

	~fFileStream();
};