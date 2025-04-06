// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Anomaly/Enum/HSAnomalyEnum.h"
#include "HSReportListBaseButton.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSReportListBaseButton : public UButton
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void SetSelectedValueText();

protected:
	class UHSReportBaseWidget* ReportBaseWidget;
};