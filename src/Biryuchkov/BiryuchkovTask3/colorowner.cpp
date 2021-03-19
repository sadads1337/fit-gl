#include "colorowner.h"

ColorOwner::ColorOwner()
{

}

void ColorOwner::setDialog(QColorDialog* dial)
{
    colorDialog = dial;
}
void ColorOwner::checkColor()
{
    if (colorDialog)
    {
        vect[active]->setColor(colorDialog->currentColor());
    }
}
void ColorOwner::setActive(int ac)
{
    active = ac;
}
void ColorOwner::setSources(std::vector<SourceLight*> srcs)
{
    vect = srcs;
}
