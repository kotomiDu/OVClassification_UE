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


#include "OpenVinoClassification.h"

#include "FOpenVinoModule.h"
#include "HAL/FileManager.h"
#include "Async/Async.h"

#include "ThirdParty\OpenVinoWrapper\OpenVinoWrapper.h"

#include <string>
#include <vector>

using namespace std;

/*
 * @brief Tests if file passed exists, and logs error if it doesn't
 * @param filePath to be tested
 * @return true if file exists, false if it doesn't
 */
static
bool TestFileExists(FString filePath)
{
	if (IFileManager::Get().FileExists(*filePath))
		return true;

	UE_LOG(LogTemp, Error, TEXT("Could not find file: %s"), *filePath);

	return false;
}

// Sets default values for this component's properties
UOpenVinoClassification::UOpenVinoClassification()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

/**
 * @brief Initializes OpenVino
 * @param xmlFilePath
 * @param binFilePath
 * @param labelsFilePath
 * @return message saying that plugin has been initialized or not
 */
FString 
UOpenVinoClassification::Initialize(
	FString xmlFilePath, 
	FString binFilePath, 
	FString labelsFilePath)
{
	// First, test if files passed exist, it is better to catch it early:
	if (!TestFileExists(xmlFilePath) ||
		!TestFileExists(binFilePath) ||
		!TestFileExists(labelsFilePath))
		return TEXT("One or more files passed to Initialize don't exit");

	auto ret = ::OpenVino_Initialize(
		TCHAR_TO_ANSI(*xmlFilePath),
		TCHAR_TO_ANSI(*binFilePath),
		TCHAR_TO_ANSI(*labelsFilePath));

	if (!ret)
	{
		// If initialization fails, log the error message:
		auto message = GetAndLogLastError();

		return TEXT("OpenVino has failed to initialize: ") + message;
	}

	return TEXT("OpenVino has been initialized.");
}

/**
 * @brief starts classification process, will fire an event once classification has completed
 * @param filePath image file path to be analysed
 * @return message saying that classification has started
 */
FString 
UOpenVinoClassification::BeginClassifyImageFromPath(FString filePath)
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [=]()
		{
			FString result;

			if (!TestFileExists(filePath))
			{
				result = TEXT("File Path has not been passed!");
			}
			else
			{
				// This is the buffer for result, with arbitrary size 1024: 
				vector<char> message(1024, '\0');

				auto ret = OpenVino_Infer_FromPath(
					TCHAR_TO_ANSI(*filePath),
					message.data(),
					message.size());

				if (!ret)
					result = GetAndLogLastError();
				else
					result = FString(message.data());
			}

			// Broadcast event when classification has completed
			this->OnClassificationComplete.Broadcast(result);
		});

	return TEXT("Starting Classification...");
}

/**
 * @brief Returns last error from OpenVino, logging it first to UE's log system
 * @return Last error message
 */
FString
UOpenVinoClassification::GetAndLogLastError()
{
	FString lastError;

	{
		// Pass in string buffer with arbitrary size (256):
		vector<char> buffer(256, '\0');
		auto ret = OpenVino_GetLastError(buffer.data(), buffer.size());

		if (ret)
			lastError = FString(buffer.data());
		else
			lastError = TEXT("Failed to read OpenVino_GetLastError");
	}

	UE_LOG(LogTemp, Error, TEXT("OpenVino_GetLastError: %s"), *lastError);

	return lastError;
}