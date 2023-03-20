# Narrative - Try to find sound button
This is a mod for Narrative (by Reubs) that adds a button to the dialogue node details panel that when clicked, will get the text of the selected node, strips any characters to make it file path accessable (?, ., !, -, _), then tries to find the file simularly named within /Game/Sounds.

## Why?

I use an AI generator and/or name my sound files with a specific format. As long as you stick to whatever format, this plugin will remove the entire searching part and will find the file instantly.

## Example
In these two examples you can see the before and after. The before being manually searching for files and the after is simply clicking the button. 

## Warning
This is not really a warning. If you've never touched C++ before don't worry. The aim in this guide is to guide you step by step to do it. Its a good mod and lack of knowledge shouldn't be a barrier.

Even if you add this mod and it breaks your Narrative, just redownload it and it'll all be gone.

## 🧐 Features

- Customisable to your naming convention
- Quick - it contains a few checks to try and speed up the search
- If you have Narrative working, this mod will work for you. 

## Limitations
- You need to own Narrative. If you don't this is useless to you.
- C++ - it requires you to edit the C++. Its dead easy however!
- I'm not a C++ programmer. I'm still learning. If you spot anything wrong please update / let me know :D
- Its not perfect. Sometimes it might not find a file (if it doesn't match) or you might not have named a file correctly so it won't work 100% but 95% is better than none right?

## 🛠️ Installation Steps - development

I cannot distrobute Narrative as its a licenced product created by Reubs, but with his permission, I have posted the modifications only here so you can make the changes you need.

File 1 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.h`

1) Open the file `DialogueEditorDetails.h` from this repo and copy the 4 lines from the file `DialogueEditorDetails.h` into your Narrative `DialogueEditorDetails.h` file.

File 2 - `Source/NarrativeDialogueEditor/Private/DialogueEditorDetails.cpp`

1) Open the file `DialogueEditorDetails-Methods.cpp` from this repo and copy the 4 methods.

Open the Narrative file `DialogueEditorDetails.cpp` and paste the 4 methods at the very bottom. Just above the line 
```cpp
#undef LOCTEXT_NAMESPACE
```
