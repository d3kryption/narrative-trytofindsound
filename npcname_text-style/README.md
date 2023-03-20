# Intro
This section is for users whos style fits the below:

```
/Game/Sounds/aivoice/text
```

e.g.

```
/Game/Sounds/GeneralButtlicker/You_stole_from_the_wrong_person_Time_to_die
```

It will assume that all non normal characters / numbers have been replaced. [A-Z] [a-z] [0-9] and [_]. No commas, no spaces, only characters, numbers and underscores for spaces.

The exact folder path is required to make this work. - you can have sub folders however.

```
/Game/Sounds/GeneralButtlicker/Stage1/Mission1/Objective/You_stole_from_the_wrong_person_Time_to_die
```

_should_ be okay.

## 🛠️ Installation Steps

I cannot distrobute Narrative as its a licenced product created by Reubs, but with his permission, I have posted the modifications only here so you can make the changes you need.

### File 1 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.h`

1) Open the file `DialogueEditorDetails.h` from this repo and copy the 3 lines from the file `DialogueEditorDetails.h` into your Narrative `DialogueEditorDetails.h` file. 

paste it above the final bracket and semicolon.


### File 2 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.cpp`

1) Open the file `DialogueEditorDetails-Methods.cpp` from this repo and copy the 3 methods.

Open the Narrative file `DialogueEditorDetails.cpp` and paste the 3 methods at the very bottom. Just above the line 
```cpp
#undef LOCTEXT_NAMESPACE
```


2) In the file `DialogueEditorDetails-NPC.cpp` on this repo, copy the 3 lines.

Open the Narrative file `DialogueEditorDetails.cpp` and find the method `FDialogueEditorDetails::CustomizeDetails`.

This method is used to customise the details panel to add buttons etc...

Scroll to the bottom of this function (around line 129 as per the time of writing) you will see it adds a button with the text being `.Text(this, &FDialogueEditorDetails::GetSpeakerText)`.

Under this line, paste the if statement. 

![image](https://user-images.githubusercontent.com/48034534/226450701-d4c386e2-3b92-45db-9b13-8d805eac0e8c.png)

NOTE: If you want the button to be visible 100% of the time and not hidden when you already have dialogue, then remove the if statement and the brackets. Just add the below line instead.

```cpp
AddTryToFindSoundButton(DetailLayout);
```

![image](https://user-images.githubusercontent.com/48034534/226450768-5b25a5db-3101-48a9-862b-b578e3954bfe.png)


3) In the file `DialogueEditorDetails-PLAYER.cpp` on this repo, copy all the lines - there is quite a few don't worry. It just copies the NPC code above but modified for the player.

Under the if statement or code you pasted in step 2, there should be roughly 5 brackets.

Paste the code in between the 3rd ending bracket and the fourth. Making sure there are two ending brackets below, and 3 above your code.

NOTE: If you removed the if statement above, you will need to do it in this section of code too. Just look for `if(!PlayerNode->DialogueSound)`
Remove this if statemnt, the opening bracket under it, then the bracket under the `AddTryToFindSoundButton(DetailLayout);`

Just above it.
