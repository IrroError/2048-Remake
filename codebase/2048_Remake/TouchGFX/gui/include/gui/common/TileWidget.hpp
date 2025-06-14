#ifndef TILEWIDGET_HPP
#define TILEWIDGET_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/Unicode.hpp>

using namespace touchgfx;

class TileWidget : public Container
{
public:
    TileWidget();
    virtual ~TileWidget() {}

    // Set the tile value (0 for empty, 2, 4, 8, 16, etc.)
    void setValue(uint16_t value);
    
    // Get current value
    uint16_t getValue() const;
    
    // Animation methods
    void animateSpawn();
    void animateMerge();
    
    // Setup the tile appearance
    void setupTile(int16_t x, int16_t y, int16_t width, int16_t height);

protected:
    static const int16_t TILE_SIZE = 60;
    static const int16_t TILE_MARGIN = 8;
      Box tileBackground;
    TextArea tileText;
    Unicode::UnicodeChar tileTextBuffer[5]; // For numbers up to 9999
    
    uint16_t currentValue;
    
    // Helper methods
    colortype getTileColor(uint16_t value) const;
    colortype getTextColor(uint16_t value) const;
    void updateAppearance();
};

#endif // TILEWIDGET_HPP
