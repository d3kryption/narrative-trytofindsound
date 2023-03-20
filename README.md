# Narrative - Try to find sound button
This is a mod for Narrative (by Reubs) that adds a button to the dialogue node details panel that when clicked, will get the text of the selected node, strips any characters to make it file path accessable (?, ., !, -, _), then tries to find the file simularly named within /Game/Sounds.

## Why?

I use an AI generator and/or name my sound files with a specific format. As long as you stick to whatever format, this plugin will remove the entire searching part and will find the file instantly.

## Example
In these two examples you can see the before and after. The before being manually searching for files and the after is simply clicking the button. 

Before:
![narrative_mod_before](https://user-images.githubusercontent.com/48034534/226448774-d0b469e7-c09d-4cf7-b29b-8a8497361e41.gif)

After - as you can see its super quick:
![narrative_mod_after](https://user-images.githubusercontent.com/48034534/226448814-375f04ab-6e7f-4396-afc3-c3ce27ad668b.gif)


## ⚠️ Warning
This is not really a warning. If you've never touched C++ before don't worry. The aim in this guide is to guide you step by step to do it. Its a good mod and lack of knowledge shouldn't be a barrier.

Even if you add this mod and it breaks your Narrative, just redownload it and it'll all be gone. I'm always happy for you to contact me if you need help.

## 🧐 Features

- Customisable to your naming convention
- Quick - it contains a few checks to try and speed up the search
- If you have Narrative working, this mod will work for you. 
- The button hides if the dialogue already has been populated (you can remove this if you don't want this aspect)

## Limitations
- You need to own Narrative. If you don't this is useless to you.
- C++ - it requires you to edit the C++. Its dead easy however!
- I'm not a C++ programmer. I'm still learning. If you spot anything wrong please update / let me know :D
- Its not perfect. Sometimes it might not find a file (if it doesn't match) or you might not have named a file correctly so it won't work 100% but 95% is better than none right?
- When you click the button and it populates, it won't hide the button until you click off and back on. Never figured out how to solve that lol

## How it works


## 🛠️ Installation Steps - development

I cannot distrobute Narrative as its a licenced product created by Reubs, but with his permission, I have posted the modifications only here so you can make the changes you need.

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


3) In the file `DialogueEditorDetails-PLAYER.cpp` on this repo, copy all the lines - there is quite a few don't worry. It just copies the NPC code above but modified for the player.

Under the if statement or code you pasted in step 2, there should be roughly 5 brackets.

Paste the code in between the 3rd ending bracket and the fourth. Making sure there are two ending brackets below, and 3 above your code.

NOTE: If you removed the if statement above, you will need to do it in this section of code too. Just look for `if(!PlayerNode->DialogueSound)`
Remove this if statemnt, the opening bracket under it, then the bracket under the `AddTryToFindSoundButton(DetailLayout);`

If done correctly, the code should look like so WITH IF STATEMENT:
![image](https://user-images.githubusercontent.com/48034534/226450377-cbbfd79e-c7f7-4ed6-9bf8-bb2a5500d36b.png)

WITHOUT IF STATEMENT:
![image](https://user-images.githubusercontent.com/48034534/226451108-73d8bf7f-d7b5-4ab5-b381-ba9b0b403ef2.png)

## Customisation steps

As stated above, this mod is specific to using xVAVoiceSynth exports so you need to modify it to make it work for you. But I've tried to make it as easy as possible.

There is normally, 2 methods that you will need to edit.

### SplitFilename
The export convention for xVaVoiceSynth by default is:

```
ai_name_codec_text
```

E.g.

```
duke_nukem_hifi_You_stole_from_the_wrong_person__Time_to_die
```

This method splits on `hifi_` and keeps the text.

If you begin any of your sound files with a naming convention, modify this to split on it so only the text exists.

e.g.

```
duke_nukem_hifi_You_stole_from_the_wrong_person__Time_to_die
```

will become

```
You_stole_from_the_wrong_person__Time_to_die
```

If you don't need to split on anything, you can remove this method entirely.

Delete the method from `DialogueEditorDetails.cpp` and `DialogueEditorDetails.h`.

Then delete the method call from  `DialogueEditorDetails.cpp` in the method `TryToFindSound` around line 244.

 `soundName = SplitFilename(*soundName);` - delete this
 
 
