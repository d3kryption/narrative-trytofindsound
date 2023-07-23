# Narrative - Try to find sound button
This is a mod for Narrative 3 (by Reubs) that adds a button to the dialogue node details panel that when clicked, will get the text of the selected node, and strips any non alphanum character, then tries to find the file similarly named within your specfied sounds folder. Default is: `/Game/Sounds`.

## Why?

I regularly make big dialogues for my games. It is bloody annoying to have to find all the sounds to match the nodes lol 

So this button is a 1 click macro to do it.

It might not sound much but when you are looking at 50+ nodes you need to add sounds to, this button is fantastic.

## Example
In these two examples, you can see the before and after. The before is manually searching for files and the after is simply clicking the button. 

YouTube - before and after:
https://youtu.be/Szz77n-nG4M

Before:
![narrative_mod_before](https://user-images.githubusercontent.com/48034534/226448774-d0b469e7-c09d-4cf7-b29b-8a8497361e41.gif)

After - as you can see it's super quick in comparison:
![narrative_mod_after](https://user-images.githubusercontent.com/48034534/226448814-375f04ab-6e7f-4396-afc3-c3ce27ad668b.gif)


## ⚠️ Warning
 If you've never touched C++ before don't worry. This guide aims to guide you step by step to do it. It's a good mod and lack of knowledge shouldn't be a barrier.

Even if you add this mod and it breaks your Narrative, just redownload it and it'll all be gone. I'm always happy for you to contact me if you need help.

But. And sorry there always has to be a but. If you have made changes yourself to the Narrative code or the Narrative UI BACK IT UP. If this goes badly wrong. You can lose all your changes when you redownload it. INCLUDING THE UI.

Back it up. Please.

## 🧐 Features

- Customisable to your naming convention - pick your style or make your own to match your standards
- Quick - it contains a few checks to try and speed up the search
- If you have Narrative working, this mod will work for you and you will love it.
- Customisable settings. Edit -> Project Settings -> Narrative Dialogue - Editor:
	- Pick your folder location to search
	- Sound search pattern
	- Max text length to search
	- What it replaces with
	- What the player folder is called

## Limitations
- You need to own Narrative. If you don't this is useless to you - sorry but...how did you get here lol
- C++ - it requires you to edit the C++. It's dead easy, however. I try to make the process super easy!
- I'm not a C++ programmer. I'm still learning. If you spot anything wrong please update/let me know :D
- It's not perfect. Sometimes it might not find a file (if it doesn't match via some logic flaw) or you might not have named a file correctly so it won't work 100% but 95% is better than none right?
- When Narrative releases an update, sadly you will have to reapply this. It only takes 5 minutes once you've done it a few times.

## Bugs
- I haven't yet figured out how to render the button in the same place on both NPC and Player dialogue nodes

## How it works - top level
1) When the user clicks the button it checks to make sure you only have a single node selected
2) It then sets some bits up, but mainly checks if the node is a type of NPC or Player
3) It cleans up the speaker ID and text (replacing / removing chars, trimming etc...)
4) It then loops through all assets in your path making sure to only check SOUND files
5) It checks that the path contains the sound folder location and if the sound file name contains the stripped down text
6) If it only finds a single sound file, it applies it to the dialogue. If it finds multiple or none, it errors (output log)

## 🛠️ Installation Steps
I cannot distribute Narrative as it's a licenced product created by Reubs, but with his permission, I have posted the modifications only here so you can make the changes you need.

### File 1 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.h`

1) Open the file `DialogueEditorDetails.h` from this repo and copy the 4lines from the file `DialogueEditorDetails.h` into your Narrative `DialogueEditorDetails.h` file. 

Paste it inside the class `FDialogueEditorDetails` near the bottom.

![image](https://user-images.githubusercontent.com/48034534/226450601-b8ac6327-c727-4bf4-a424-02aa51edb600.png)


### File 2 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.cpp`

1) Open the file `DialogueEditorDetails-Methods.cpp` from this repo and copy the includes from the top.

2) Open the Narrative file `DialogueEditorDetails.cpp` and paste the includes at the very top just below the other includes.

3) Open the file `DialogueEditorDetails-Methods.cpp` again from this repo and copy the methods below the includes.

4) Open the Narrative file `DialogueEditorDetails.cpp` and paste the methods at the very bottom. Just above the line 
```cpp
#undef LOCTEXT_NAMESPACE
```

![image](https://user-images.githubusercontent.com/48034534/226450506-afa2abe7-cfb8-4d49-b40d-f0bffaf11f6f.png)


2) In the file `DialogueEditorDetails-NPC.cpp` on this repo, copy the lines.

Open the Narrative file `DialogueEditorDetails.cpp` and find the method `FDialogueEditorDetails::CustomizeDetails`.

This method is used to customise the details panel to add buttons etc...

Scroll to the bottom of this function (around line 150 as per the time of writing) you will see it adds a button with the text being `.Text(this, &FDialogueEditorDetails::GetSpeakerText)`.

Then there are two square braces. Paste it under this line.

![image](https://user-images.githubusercontent.com/48034534/226450768-5b25a5db-3101-48a9-862b-b578e3954bfe.png)


3) In the file `DialogueEditorDetails-PLAYER.cpp` on this repo, copy all the lines - there are quite a few don't worry. It just copies the NPC code above but is modified for the player.

Under the if statement or code you pasted in step 2, there should be roughly 5 brackets.

Paste the code in between the 3rd ending bracket and the fourth. Making sure there are two ending brackets below, and 3 above your code.

If done correctly, the code should look like so:

![image](https://user-images.githubusercontent.com/48034534/226451108-73d8bf7f-d7b5-4ab5-b381-ba9b0b403ef2.png)

### File 3 - `Source/NarrativeDialogueEditor/Private/DialogueEditorSettings.h`

1) Open the file `DialogueEditorSettings.h` from this repo and copy the lines.

2) Open the Narrative file `DialogueEditorSettings.h` and paste the lines from this repo above the `UPROPERTY` for the `bEnableWarnings` variable.

### File 4 - `Source/NarrativeDialogueEditor/Private/DialogueEditorSettings.cpp`

1) Open the file `DialogueEditorSettings.cpp` from this repo and copy the lines.

2) Open the Narrative file `DialogueEditorSettings.cpp` and paste the lines from this repo below the `DefaultDialogueClass` line.
