#include <gui/common/TileWidget.hpp>
#include <touchgfx/Color.hpp>

TileWidget::TileWidget() : currentValue(0)
{
    setWidth(TILE_SIZE);
    setHeight(TILE_SIZE);
    
    // Setup background box
    tileBackground.setPosition(0, 0, TILE_SIZE, TILE_SIZE);
    tileBackground.setColor(Color::getColorFromRGB(205, 193, 180)); // Default empty tile color
    add(tileBackground);
    
    // Initialize the text buffer with empty text
    Unicode::snprintf(tileTextBuffer, 5, "");
    
    // Setup text area with default parameters
    tileText.setXY(0, 0);
    tileText.setWidth(TILE_SIZE);
    tileText.setHeight(TILE_SIZE);
    tileText.setTypedText(TypedText(T_TILENUMBER));
    tileText.setWildcard(tileTextBuffer);
    tileText.setColor(Color::getColorFromRGB(119, 110, 101)); // Dark text for light tiles
    tileText.setVisible(false); // Hide initially (empty tile)
    add(tileText);
    
    updateAppearance();
}

void TileWidget::setValue(uint16_t value)
{
    if (currentValue != value) {
        currentValue = value;
        updateAppearance();
    }
}

uint16_t TileWidget::getValue() const
{
    return currentValue;
}

void TileWidget::setupTile(int16_t x, int16_t y, int16_t width, int16_t height)
{
    setPosition(x, y, width, height);
    
    // Set up the tile background to fill the entire area
    tileBackground.setPosition(0, 0, width, height);
    
    // Set the text area to use the full tile size for alignment
    tileText.setPosition(0, 0, width, height);
    
    // Ensure the text has a valid type
    tileText.setTypedText(TypedText(T_TILENUMBER));
    
    // Set initial empty text
    Unicode::snprintf(tileTextBuffer, 5, "");
    tileText.setWildcard(tileTextBuffer);
}

void TileWidget::updateAppearance()
{
    if (currentValue == 0) {
        // Empty tile
        tileBackground.setColor(Color::getColorFromRGB(205, 193, 180));
        tileText.setVisible(false);
    } else {
        // Tile with value
        tileBackground.setColor(getTileColor(currentValue));
        tileText.setColor(getTextColor(currentValue));
        
        // Convert number to text
        Unicode::snprintf(tileTextBuffer, 5, "%d", currentValue);
        
        // Use a consistent font size with center alignment
        tileText.setTypedText(TypedText(T_TILENUMBER));
        tileText.setWildcard(tileTextBuffer);
        
        // Make sure the text is visible
        tileText.setVisible(true);
    }
    
    invalidate();
}

colortype TileWidget::getTileColor(uint16_t value) const
{
    switch (value) {
        case 2:    return Color::getColorFromRGB(238, 228, 218);
        case 4:    return Color::getColorFromRGB(237, 224, 200);
        case 8:    return Color::getColorFromRGB(242, 177, 121);
        case 16:   return Color::getColorFromRGB(245, 149, 99);
        case 32:   return Color::getColorFromRGB(246, 124, 95);
        case 64:   return Color::getColorFromRGB(246, 94, 59);
        case 128:  return Color::getColorFromRGB(237, 207, 114);
        case 256:  return Color::getColorFromRGB(237, 204, 97);
        case 512:  return Color::getColorFromRGB(237, 200, 80);
        case 1024: return Color::getColorFromRGB(237, 197, 63);
        case 2048: return Color::getColorFromRGB(237, 194, 46);
        default:   return Color::getColorFromRGB(60, 58, 50); // Super tiles (4096+)
    }
}

colortype TileWidget::getTextColor(uint16_t value) const
{
    if (value <= 4) {
        return Color::getColorFromRGB(119, 110, 101); // Dark text for light tiles
    } else {
        return Color::getColorFromRGB(249, 246, 242); // Light text for dark tiles
    }
}

void TileWidget::animateSpawn()
{
    // Simple scale animation for new tiles
    // This would require implementing custom animation in TouchGFX
    // For now, just update appearance
    updateAppearance();
}

void TileWidget::animateMerge()
{
    // Animation for tile merging
    // For now, just update appearance
    updateAppearance();
}
