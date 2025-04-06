// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/Report/Button/HSReportListBaseButton.h"
#include "HSReportListObjectButton.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSReportListObjectButton : public UHSReportListBaseButton
{
	GENERATED_BODY()
	
public:
	FName GetObjectValue() { return ObjectValue; }
	void SetObjectValue(FName SettingValue) { ObjectValue = SettingValue; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ObjectValue;

public:
	virtual void SetSelectedValueText() override;
};