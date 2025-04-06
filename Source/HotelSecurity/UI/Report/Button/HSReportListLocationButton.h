// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/Report/Button/HSReportListBaseButton.h"
#include "HSReportListLocationButton.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSReportListLocationButton : public UHSReportListBaseButton
{
	GENERATED_BODY()
	
public:
	FName GetLocationValue() { return LocationValue; }
	void SetLocationValue(FName SettingValue) { LocationValue = SettingValue; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LocationValue;

public:
	virtual void SetSelectedValueText() override;
};