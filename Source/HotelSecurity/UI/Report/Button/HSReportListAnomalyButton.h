// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/Report/Button/HSReportListBaseButton.h"
#include "HSReportListAnomalyButton.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSReportListAnomalyButton : public UHSReportListBaseButton
{
	GENERATED_BODY()
	
public:
	FName GetAnomalyValue() { return AnomalyValue; }
	void SetAnomalyValue(FName SettingValue) { AnomalyValue = SettingValue; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AnomalyValue;

public:
	virtual void SetSelectedValueText() override;
};