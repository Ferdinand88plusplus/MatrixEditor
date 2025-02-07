#include <vector>
#include <string>

enum MessageType{
    MT_Error,
    MT_Info,
};

struct EditorLogMsg{

    std::string text;
    MessageType type;

    // when the lifetime == 0 the messages is deleted
    unsigned char lifetime = 255;
};

namespace EditorLogstack {
    extern std::vector<EditorLogMsg> stack;

    void pushMessage(const std::string& text, MessageType type);

    inline void pushError(const std::string& message) { pushMessage(message, MT_Error); };
    inline void pushInfo(const std::string& message) { pushMessage(message, MT_Info); };
};