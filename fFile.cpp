#include "fFile.h"

// fFile field

fresult fFile::ReadFile()
{
	size_t fileSize = 0;

	input->seekg(0, std::ios::end);
	fileSize = input->tellg();
	input->seekg(0, std::ios::beg);
	fileData.resize(fileSize);
	input->read((char*)fileData.data(), fileSize);

	return ConvertFileEncoding();
}

fresult fFile::OpenFile()
{
	switch (inputMode) {
	default:
		return CODE_BAD_INPUT_MODE;
		break;
	case AS_INPUT:
		input = new std::ifstream;

		switch (fNType) {
		case FNT_STRING:
			input->open(fileName, std::ios::binary);
			break;
		case FNT_WSTRING:
			input->open(wfileName.data(), std::ios::binary);
			break;
		}

		if (!input->is_open()) {
			return CODE_NO_SUCH_FILE_OR_DIR;
		}
		break;
	case AS_OUTPUT:
		output = new std::ofstream;

		switch (fNType) {
		case FNT_STRING:
			output->open(fileName, std::ios::binary);
			break;
		case FNT_WSTRING:
			output->open(wfileName.data(), std::ios::binary);
			break;
		}

		if (!output->is_open()) {
			return CODE_NO_SUCH_FILE_OR_DIR;
		}
		break;
	}

	fresult result = CODE_SUCCESS;
	
	switch (inputMode) {
	case AS_INPUT:
		result = ReadFile();
		break;
	}

	return result;
}

fresult fFile::CloseFile()
{
	fileName.clear(); wfileName.clear();

	if (!(input || output)) {
		return CODE_NO_OPENED_FILE;
	}

	fresult result = OutConvFileEncoding();

	switch (inputMode) {
	case AS_OUTPUT:
		output->write(fileData.data(), fileData.size());
		output->close();
		delete output;
		break;
	case AS_INPUT:
		input->close();
		delete input;
		break;
	}

	input = 0;
	output = 0;

	fileData.clear();

	return result;
}

namespace to866 {

#define INVALIDUTF8_EXC "Invalid UTF-8"
#define UNSUPUTF8SEQ_EXC "Unsupported UTF-8 sequence"

	std::wstring utf8_to_wstring(const std::string& utf8) {
		std::wstring result;
		size_t i = 0;
		while (i < utf8.size()) {
			const unsigned char& byte = utf8[i];
			if (byte < 0x80) {
				// 1 byte
				result += byte;
				i++;
			}
			else if ((byte & 0xE0) == 0xC0) {
				// 2 bytes
				if (i + 1 >= utf8.size()) throw std::runtime_error(INVALIDUTF8_EXC);
				wchar_t wc = ((utf8[i] & 0x1F) << 6) | (utf8[i + 1] & 0x3F);
				result += wc;
				i += 2;
			}
			else if ((byte & 0xF0) == 0xE0) {
				// 3 bytes
				if (i + 2 >= utf8.size()) throw std::runtime_error(INVALIDUTF8_EXC);
				wchar_t wc = ((utf8[i] & 0x0F) << 12) | ((utf8[i + 1] & 0x3F) << 6) | (utf8[i + 2] & 0x3F);
				result += wc;
				i += 3;
			}
			else {
				throw std::runtime_error(UNSUPUTF8SEQ_EXC);
			}
		}
		return result;
	}

	std::string ansi(const std::string& str) {
		std::string out;

		for (const unsigned char& c : str) {
			if (c >= 192) { // russian 'À' in ansi
				if (c >= 240) { // russian 'ð' in ansi
					out += c - 16;
					continue;
				}
				out += c - 64;
				continue;
			}
			out += c;
		}

		return out;
	}

	std::string utf(const std::string& str) {
		std::string localStr;
		std::wstring wideStr;

		wideStr = utf8_to_wstring(str);

		for (const wchar_t& wc : wideStr) {
			if (wc >= 1040 && wc <= 1103) {
				switch (wc) {
				default:
					if (wc > L'\x43f') {
						localStr += wc - 864;
					}
					else {
						localStr += wc - 912;
					}
					break;
				case L'\x451':
					localStr += '¸';
					break;
				case L'\x401':
					localStr += '¨';
					break;
				}
				
			}
			else {
				localStr += wc;
			}
		}
		return localStr;
	}
}

fresult fFile::ConvertFileEncoding()
{
	if (encoding == ENC_CP866) return CODE_SUCCESS; 

	switch (encoding) {
	default:
		return CODE_BAD_ENCODING;
	case ENC_UTF8:
		CnvUTF8();
		break;
	case ENC_ANSI:
		CnvANSI();
		break;
	}

	return CODE_SUCCESS;
}

void fFile::CnvUTF8()
{
	fileData = to866::utf(fileData);
}

void fFile::CnvANSI()
{
	fileData = to866::ansi(fileData);
}

namespace from866 {
	std::string ansi(const std::string& str) {
		std::string out;

		for (const unsigned char& c : str) {

			if (c >= 128 && c <= 175) { // russian 'À' && russian 'ï'
				out += c + 64;
				continue;
			}
			if (c >= 224 && c <= 239) { // russian 'ð' && russian 'ÿ'
				out += c + 16;
				continue;
			}
			out += c;
		}

		return out;
	}
}

fresult fFile::OutConvFileEncoding()
{
	if (encoding == ENC_CP866) return CODE_SUCCESS;

	switch (encoding) {
	default:
		return CODE_BAD_ENCODING;
	case ENC_UTF8:
		return CODE_UNSUPPORTED_ENCODING;
		break;
	case ENC_ANSI:
		OutCnvANSI();
		break;
	}

	return CODE_SUCCESS;
}

void fFile::OutCnvANSI()
{
	fileData = from866::ansi(fileData);
}

fresult fFile::Open(const std::string& fname)
{
	fNType = FNT_STRING;

	fileName = fname;

	return OpenFile();
}

fresult fFile::Open(const std::wstring& fname)
{
	fNType = FNT_WSTRING;

	wfileName = fname;

	return OpenFile();
}

fresult fFile::Close()
{
	return CloseFile();
}

std::string fFile::strCode(fresult code)
{
	switch (code) {
	default:
		return "ERR_UNKNOWN_CODE";
	case CODE_SUCCESS:
		return "Success";
	case CODE_BAD_INPUT_MODE:
		return "Bad input mode";
	case CODE_NO_OPENED_FILE:
		return "No opened file";
	case CODE_NO_SUCH_FILE_OR_DIR:
		return "No such file or directory";
	case CODE_BAD_ENCODING:
		return "Bad encoding";
	case CODE_UNSUPPORTED_ENCODING:
		return "Unsupported encoding";
	}
}

fencoding fFile::encStr(const std::string& str)
{

	std::string copy = str;

	for (int i = 0; i < copy.size(); i++) {
		char c = copy[i];
		copy[i] = std::tolower(c);
	}

	if (copy == "utf8" || copy == "utf-8") {
		return ENC_UTF8;
	}
	if (copy == "cp866" || copy == "cp-866") {
		return ENC_CP866;
	}

	return ENC_NULL;
}

fFile::fFile(const std::string& fname, ffilemode mode)
{
	inputMode = mode;
	Open(fname);
}

fFile::fFile(ffilemode mode)
{
	inputMode = mode;
}

fFile::~fFile()
{
	Close();
}

// fFileStream field

void fFileStream::WriteChar(char c)
{
	buffer.fileData.insert(buffer.fileData.begin() + pos, c);
	pos++;
}

fresult fFileStream::Open(const std::string& fname)
{
	pos = 0;

	return buffer.Open(fname);
}

fresult fFileStream::Close()
{
	pos = 0;

	return buffer.Close();
}

void fFileStream::Read(std::string& buf)
{
	memcpy((char*)(buf.data()), buffer.fileData.data() + pos, buf.size());
	pos += buf.size();
}

void fFileStream::Read(char* dest, size_t size)
{
	memcpy(dest, buffer.fileData.data() + pos, size);
	pos += size;
}

void fFileStream::Write(const std::string& buf)
{
	for (char c : buf) {
		WriteChar(c);
	}
}

void fFileStream::Write(const char* src, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		WriteChar(src[i]);
	}
}

fFileStream::fFileStream(const std::string& fname, ffilemode mode)
{
	buffer.inputMode = mode;
	buffer.Open(fname);
}

fFileStream::fFileStream(ffilemode mode)
{
	buffer.inputMode = mode;
}

fFileStream::~fFileStream()
{
	buffer.Close();
}
