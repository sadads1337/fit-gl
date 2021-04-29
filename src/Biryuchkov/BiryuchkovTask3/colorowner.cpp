#include "colorowner.h"



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
void ColorOwner::setActive(const int ac)
{
    active = ac;
}
void ColorOwner::setSources(const std::vector<SourceLight*> &srcs)
{
    vect = srcs;
}
