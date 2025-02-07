#include "ConfigParser.h"

#include "fFile.h"
#include "../ErrorDispatcher.h"
#include "../EditorLogstack.h"

#define FORMATRIX_X()for(int x = 0 ; x < result.matrixWidth; x++)
#define FORMATRIX_Y()for(int y = 0 ; y < result.matrixHeight; y++)


#define WRITEMATRIX(value) \
for(int y = 0; y < globconst::matrixHeight; y++){   \
    for(int x = 0; x < globconst::matrixWidth; x++){    \
        insertStr = std::to_string(mechos.matrix.cells[y][x].value);    \
        if(x != globconst::matrixWidth-1){  \
            insertStr += ' ';   \
        }   \
        write(insertStr); \
    }   \
    write("\r\n");  \
}

IO::MechosCfgParseInfo* IO::MechosConfigParser::parse(const std::string &cfgname)
{
    recognizeCfgType(cfgname);

    if(cfgType == CT_Unsupported){
        EditorLogstack::pushError("Unsupported file format!");
        return 0;
    }

    open(cfgname);
    
    // if cant open file or its just empty 
    if(fileData.empty()){
        return 0;
    }

    switch(cfgType){
    default:
        return 0;
    case CT_AciScb:
        return parseScb();
    case CT_AciScr:
        return parseScr();
    }
}

void IO::MechosConfigParser::inject(MechosCfgInjectInfo &info)
{
    std::string insertStr;
    for(int i = 0; i < info.mechosesCount; i++){
        MechosInfo& mechos = info.mechosesArray[i];

        size_t endOfMatrixes = 0;
        size_t begOfMatrixes = 0;
        
        // first matrix block
        forcedFind("matrix");
        begOfMatrixes = readOff;

        // name (param after matrxies)
        forcedFind("name");
        endOfMatrixes = readOff - 4; //! 4 - length of "name" string
        
        readOff = begOfMatrixes;
        // erase matrixes (and keep 'matrix' word)
        fileData.erase(begOfMatrixes, endOfMatrixes - begOfMatrixes);

        WRITEMATRIX(active);
        write("slot_types\r\n");
        WRITEMATRIX(slotType);
        write("slot_nums\r\n");
        WRITEMATRIX(slotNum);
    }
}

void IO::MechosConfigParser::open(const std::string &cfgname)
{
    fFile inputFile(fFile::AS_INPUT);

    fresult openResult = inputFile.Open(cfgname);
    if(openResult != fFile::CODE_SUCCESS){
        //ErrorDispatcher::Throw("IO::MechosConfigParser", "Failed to open "+cfgname+" - " + fFile::strCode(openResult));
        EditorLogstack::pushError("Failed to open "+cfgname+" - " + fFile::strCode(openResult));
        fileData.clear();
        return;
    }

    fileData = inputFile.fileData;
}

void IO::MechosConfigParser::forcedFind(const std::string &str)
{
    size_t searchPos = fileData.find(str, readOff);
    if(searchPos == std::string::npos){
        ErrorDispatcher::Throw("IO::MechosConfigParser", "Failed to find "+ str + " in config");
    }

    readOff = searchPos + str.size();

    // string is must be splitted by spaces
    if(skipChars.find(fileData[searchPos-1]) == std::string::npos){
        forcedFind(str);
    }
    if(skipChars.find(fileData[readOff]) == std::string::npos){
        forcedFind(str);
    }
}

int IO::MechosConfigParser::readInt()
{

    skip();
    size_t begin = readOff;
    rskip();

    std::string strnum = fileData.substr(begin, readOff - begin);

    return atoi(strnum.c_str());
}

std::string IO::MechosConfigParser::readStr()
{
    
    skip();
    size_t begin = readOff;
    rskip();

    std::string string = fileData.substr(begin, readOff - begin);

    string.erase(0, 1); // erase '"' at the begin

    return string;
}

void IO::MechosConfigParser::skip()
{
    for(readOff; readOff < fileData.size(); readOff++){
        if(skipChars.find(fileData[readOff]) == std::string::npos){
            return;
        }
    }

    ErrorDispatcher::Throw("IO::MechosConfigParser", "Reached the end of file after attempt to GET more data");
}

void IO::MechosConfigParser::rskip()
{
    if(fileData[readOff] == '"'){
        for(readOff++; readOff < fileData.size(); readOff++){
            if(fileData[readOff] == '"'){
                return;
            }
        }
    }
    else{
        for(readOff; readOff < fileData.size(); readOff++){
            if(skipChars.find(fileData[readOff]) != std::string::npos){
                return;
            }
        }
    }

    ErrorDispatcher::Throw("IO::MechosConfigParser", "Reached the end of file after attempt to READ more data");
}

void IO::MechosConfigParser::write(const std::string &str)
{
    fileData.insert(readOff, str);
    readOff += str.size();
}

void IO::MechosConfigParser::recognizeCfgType(const std::string& filename)
{
    // get extension of file
    size_t dotPosition = filename.rfind('.');
    if(dotPosition == std::string::npos){
        cfgType = CT_Unsupported;
        return;
    }
    dotPosition++;
    std::string extension = filename.substr(dotPosition, filename.size()-dotPosition);

    if(extension == "scr"){
        cfgType = CT_AciScr;
        return;
    }
    if(extension == "scb"){
        cfgType = CT_AciScb;
        return;
    }

    cfgType = CT_Unsupported;
}

MechosCfgParseInfo *IO::MechosConfigParser::parseScr()
{
    return nullptr;
}

MechosCfgParseInfo *IO::MechosConfigParser::parseScb()
{
    return nullptr;
}
