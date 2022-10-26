# Name Validator Plugin

Unreal Engine 5 validation plugin that allows you to create validation tests without writing code.

## Installation

Drag the NameValidatorPlugin into the Plugins folder of the Unreal Engine project.

## Usage

**To create validation tests:** 

Click on ``Edit->Project Settings`` and then under the section ``Game`` click on ``Name Validation Settings``. To add a test click on the plus sign next to ``0 Array elements`` and click on the arrow before Index[0] to open the dropdown. Now you can select the class of the asset type and fill in the Expected Prefix like this: ``Asset Type: Blueprint; Expected Prefix: BP_``.

**To validate the assets:**

When you have filled in the validation tests in the settings, go to the asset(s) you want to validate and select them. After you selected them right click them and click on ``Asset Actions->Validate Assets``. This should open a window with the results.

## License
[MIT](https://choosealicense.com/licenses/mit/)
