#include <fstream>

#include "../Matrix.h"

namespace IO{
    enum ConfigType{
        CT_Unsupported,

        CT_AciScr, // raw script
        CT_AciScb, // binary script
    };

    struct MechosInfo{
        std::string name;
        InfoMatrix matrix;
    };
    struct MechosCfgParseInfo{
        int matrixWidth, matrixHeight;

        int mechosesCount = 0;
        MechosInfo* mechosesArray = 0;
    };
    struct MechosCfgInjectInfo{
        int mechosesCount = 0;
        MechosInfo* mechosesArray = 0;
    };

    class MechosConfigParser{
    public:
        MechosCfgParseInfo* parse(const std::string& cfgname);
        void inject(MechosCfgInjectInfo& info);
    private:

        std::string skipChars = " \t\r\n";

        std::string fileData;

        size_t readOff = 0;

        ConfigType cfgType = CT_Unsupported;

        void open(const std::string& cfgname);

        void forcedFind(const std::string& str);

        int readInt();
        std::string readStr();

        void skip();
        void rskip();

        void write(const std::string& str);

        void recognizeCfgType(const std::string& filename);

        MechosCfgParseInfo* parseScr();
        MechosCfgParseInfo* parseScb();
        
    };
};