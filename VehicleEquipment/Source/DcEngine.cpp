#include "DcEngine.hpp"

void DcEngine::setValues(const std::vector<uint8_t>&& valueList)
{
    //TODO if!=3 to throw ze sraka
    out1 = *valueList.begin();
    out2 = *(valueList.begin() + 1);
    pwm = *(valueList.begin() + 2);
}
