#pragma once

#include "Selectable.generated.h"

UINTERFACE(MinimalAPI)
class USelectable : public UInterface
{
    GENERATED_BODY()
};

class ISelectable
{
    GENERATED_BODY()

public:
    virtual void Select();

    virtual void Deselect();
};