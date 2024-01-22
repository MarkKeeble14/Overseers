#pragma once

#include "UtilizesInput.generated.h"

UINTERFACE(MinimalAPI)
class UUtilizesInput : public UInterface
{
    GENERATED_BODY()
};

class IUtilizesInput
{
    GENERATED_BODY()

public:
    virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent);
};