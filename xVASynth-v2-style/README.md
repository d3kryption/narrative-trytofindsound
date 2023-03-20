# Intro
This section is for users who use xVaSynth-V2 and use its default exporting style. If you do not use it, I highly recommend going to the other styles as it will most likely not work for you.

The code in here assumes you have your sounds setup like such:

```
/Game/Sounds/aivoice/ai_codec_text
```

e.g.

```
/Game/Sounds/GeneralButtlicker/duke_nukem_hifi_You_stole_from_the_wrong_person__Time_to_die
```

The initial AI naming part isn't required but the `hifi_` is required as it splits on this in the code.

## 🛠️ Installation Steps

I cannot distribute Narrative as it's a licenced product created by Reubs, but with his permission, I have posted the modifications only here so you can make the changes you need.

### File 1 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.h`

1) Open the file `DialogueEditorDetails.h` from this repo and copy the 4 lines from the file `DialogueEditorDetails.h` into your Narrative `DialogueEditorDetails.h` file. 

paste it above the final bracket and semicolon.

![image](https://user-images.githubusercontent.com/48034534/226450601-b8ac6327-c727-4bf4-a424-02aa51edb600.png)


### File 2 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.cpp`

1) Open the file `DialogueEditorDetails-Methods.cpp` from this repo and copy the 4 methods.

Open the Narrative file `DialogueEditorDetails.cpp` and paste the 4 methods at the very bottom. Just above the line 
```cpp
#undef LOCTEXT_NAMESPACE
```

![image](https://user-images.githubusercontent.com/48034534/226450506-afa2abe7-cfb8-4d49-b40d-f0bffaf11f6f.png)


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


3) In the file `DialogueEditorDetails-PLAYER.cpp` on this repo, copy all the lines - there are quite a few don't worry. It just copies the NPC code above but is modified for the player.

Under the if statement or code you pasted in step 2, there should be roughly 5 brackets.

Paste the code in between the 3rd ending bracket and the fourth. Making sure there are two ending brackets below, and 3 above your code.

NOTE: If you removed the if statement above, you will need to do it in this section of code too. Just look for `if(!PlayerNode->DialogueSound)`
Remove this if statement, the opening bracket under it, then the bracket under the `AddTryToFindSoundButton(DetailLayout);`

If done correctly, the code should look like so WITH IF STATEMENT:
![image](https://user-images.githubusercontent.com/48034534/226450377-cbbfd79e-c7f7-4ed6-9bf8-bb2a5500d36b.png)

WITHOUT IF STATEMENT:
![image](https://user-images.githubusercontent.com/48034534/226451108-73d8bf7f-d7b5-4ab5-b381-ba9b0b403ef2.png)

Just above it.
