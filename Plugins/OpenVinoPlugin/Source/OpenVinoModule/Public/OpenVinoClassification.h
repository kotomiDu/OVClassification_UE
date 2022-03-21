/*
"Copyright 2019 Intel Corporation.

The source code, information and material ("Material") contained herein is owned by Intel Corporation or its
suppliers or licensors, and title to such Material remains with Intel Corporation or its suppliers or licensors.
The Material contains proprietary information of Intel or its suppliers and licensors. The Material is
protected by worldwide copyright laws and treaty provisions. No part of the Material may be used, copied,
reproduced, modified, published, uploaded, posted, transmitted, distributed or disclosed in any way without Intel's
prior express written permission. No license under any patent, copyright or other intellectual property rights in
the Material is granted to or conferred upon you, either expressly, by implication, inducement, estoppel or otherwise.
Any license under such intellectual property rights must be express and approved by Intel in writing.


Include supplier trademarks or logos as supplier requires Intel to use, preceded by an asterisk. An asterisked footnote
can be added as follows: *Third Party trademarks are the property of their respective owners.

Unless otherwise agreed by Intel in writing, you may not remove or alter this notice or any other notice
embedded in Materials by Intel or Intel's suppliers or licensors in any way."
*/


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "OpenVinoClassification.generated.h"

/** Delegate for the event fired when classification completes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClassificationComplete, const FString&, result);

/** 
 * @class UOpenVinoClassification
 * @brief This class is interface of the plugin towards UE's Blueprints 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENVINOMODULE_API UOpenVinoClassification : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenVinoClassification();

public:
	/**
	 * @brief Initializes OpenVino
	 * @param xmlFilePath
	 * @param binFilePath
	 * @param labelsFilePath
	 * @return message saying that plugin has been initialized or not
	 */
	UFUNCTION(BlueprintCallable)
		FString Initialize(FString xmlFilePath, FString binFilePath, FString labelsFilePath);

	/**
	 * @brief starts classification process, will fire an event once classification has completed
	 * @param filePath image file path to be analysed
	 * @return message saying that classification has started
	 */
	UFUNCTION(BlueprintCallable)
		FString BeginClassifyImageFromPath(FString filePath);

public:
	/**
	 * @brief This Blueprint event will be fired once classification has completed
	 * @param classification result
	 */
	UPROPERTY(BlueprintAssignable)
		FClassificationComplete OnClassificationComplete;

private:
	/**
	 * @brief Returns last error from OpenVino, logging it first to UE's log system
	 * @return Last error message
	 */
	FString
		GetAndLogLastError();
};
