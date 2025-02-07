#include "EditorLogstack.h"

namespace EditorLogstack{
    std::vector<EditorLogMsg> stack;
};

void EditorLogstack::pushMessage(const std::string &text, MessageType type)
{
    EditorLogMsg& message = stack.emplace_back();
    message.text = text;
    message.type = type;
}