

# OVClassification_UE
AI classification demo in Unreal Engine based on Intel OpenVINO (Real-time CPU inference)

## IDE Configuration
* Unreal Engine 4.27
* Visual Studio 2019
* OpenVINO 2021.4.2 LST version

## Fast build for `OVClassification.exe`
* Right click `OVClassification.uproject`, click `generate visual studio project file`, then `OVClassification.sln` is appeared

* Open `OVClassification.sln` project, select `Development Editor` mode , then build project 
  - All related libraries will be copied to Folder `Binaries\Win64`

* Open `OVClassification.uproject`, go to menu `File-> Project Launcher -> Windows(64-bit)`

* Choose `folder\for\Release project`, waiting for the compiling result

* Go to `folder\for\Release project`, run `Level1.exe -WINDOWED` 

* Enjoy Your Demo! ^_^

  ![Result](doc/result.png)

## Clarification
> This project is a modified version based on [ Intel OpenVINO™ Toolkit Unreal* Integration project](https://www.intel.com/content/www/us/en/developer/articles/technical/openvino-toolkit-unreal-integration.html) which is not runnable.

Here is the details of modification.
1. Upgrade project to UE4.27 version 
2. Upgrade OpenVINO version from `2019.2` to `2021.4.2`
3. Upgrade classifcation IR model version to `2021.4.2`
4. Upgrade inference api in OpenVINOWapper project
5. Add `TopResult` function in OpenVINOWapper project

## Build self-ego OpenVINOWapper for your AI projects.
> We recommended you don't create the project from scratch, but based on the current OpenVINOWrapper project under [Thirdparty Folder](https://github.com/kotomiDu/OVClassification_UE/tree/main/Plugins/OpenVinoPlugin/Source/ThirdParty/OpenVinoWrapper)
1. Download and set `OpenVINO library` as system environment path, Details in [OpenVINO Guide](#OpenVINO-Guide)
2. Go to `Thirdparty Folder`
3. use command line `cmake . ` , this is used to generete `OpenVinoWrapper.sln` and copy `openvino related library` to `Thirdparty Folder`
4. Open sln project, now you can write inference code for your AI task. Please refer OpenVINO inference samples [here](https://github.com/openvinotoolkit/open_model_zoo/tree/releases/2021/4/demos)
5. Build the project. New `OpenVINOWrapper.dll` and `OpenVINOWrapper.lib` will be generated in folder `Release`, please move them into folder `bin`.
6. Refer code in `OpenVinoModule` and write your own code to connect `OpenVINOWrapper` with `Unreal Engine`.


## OpenVINO Guide
1. Download [OpenVINO 2021.4.2 runtime](https://www.intel.com/content/www/us/en/developer/tools/openvino-toolkit/download.html)
2. Double click and install w_openvino****.exe, it will be installed under `C:\Program Files (x86)\Intel\openvino_2021.4.752\` as default path
3. Go to folder `OpenVINO_folder\bin` and open command window (make sure it has python environment).
4. Run `setupvars.bat` to setup your openvino environment in the current command window.