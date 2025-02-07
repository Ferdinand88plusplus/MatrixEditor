#include "MouseContactable.h"
#include "ButtonBase.h"

#include "../ErrorDispatcher.h"

namespace UI{
    class ImgButton : public MouseContactable<RectCollider>, public ButtonBase
    {
    public:
        sf::Sprite spriteRender;

        ContactType update() override;

        void create(const sf::Vector2f& pos, const std::string& imgname);

    private:
        sf::Texture spriteTexture;
    };
};