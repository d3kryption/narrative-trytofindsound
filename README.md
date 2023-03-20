# Narrative - Try to find sound button
This is a mod for Narrative (by Reubs) that adds a button to the dialogue node details panel that when clicked, will get the text of the selected node, strips any characters to make it file path accessable (?, ., !, -, _), then tries to find the file simularly named within /Game/Sounds.

## Why?

I regualrly make big dialogues for my games. Its bloody annoying to have to find all the sounds to match the nodes lol 

So this button is a 1 click macro to do it.

It might not sound much but when you are looking at 50+ nodes you need to add sounds to, this button is fantastic.

## Example
In these two examples you can see the before and after. The before being manually searching for files and the after is simply clicking the button. 

Before:
![narrative_mod_before](https://user-images.githubusercontent.com/48034534/226448774-d0b469e7-c09d-4cf7-b29b-8a8497361e41.gif)

After - as you can see its super quick:
![narrative_mod_after](https://user-images.githubusercontent.com/48034534/226448814-375f04ab-6e7f-4396-afc3-c3ce27ad668b.gif)


## ⚠️ Warning
This is not really a warning. If you've never touched C++ before don't worry. The aim in this guide is to guide you step by step to do it. Its a good mod and lack of knowledge shouldn't be a barrier.

Even if you add this mod and it breaks your Narrative, just redownload it and it'll all be gone. I'm always happy for you to contact me if you need help.

But. And sorry there always has to be a but. If you have made changes yourself to the Narrative code or the Narrative UI BACK IT UP. If this goes badly wrong. You can loose all your changes when you redownload it. INCLUDING THE UI.

Back it up. Please.

## 🧐 Features

- Customisable to your naming convention - pick your style
- Quick - it contains a few checks to try and speed up the search
- If you have Narrative working, this mod will work for you and you will love it.
- The button hides if the dialogue already has been populated (you can remove this if you don't want this aspect, I show this during installation)

## Limitations
- You need to own Narrative. If you don't this is useless to you - sorry but...how did you get here lol
- C++ - it requires you to edit the C++. Its dead easy however. I try to make the process super easy!
- I'm not a C++ programmer. I'm still learning. If you spot anything wrong please update / let me know :D
- Its not perfect. Sometimes it might not find a file (if it doesn't match via some logic flaw) or you might not have named a file correctly so it won't work 100% but 95% is better than none right?
- When you click the button and it populates, it won't hide the button until you click off and back on. Never figured out how to solve that lol
- When Narrative releases an update, sadly you will have to reapply this. It only takes 5 minutes once you've done it a few times.

## How it works - top level


## 🛠️ Installation Steps

I cannot distrobute Narrative as its a licenced product created by Reubs, but with his permission, I have posted the modifications only here so you can make the changes you need.

Now you need to pick your "style".

A style in this guide, is refered to as how you orginises your files.

If you stick every single sound from your entire game into `/Game/Sounds/` - please change it :P 

If you can't find your style in here and you can logically explain it, I can try and help set you up but you'll need to explain it. 

`I randomly pick what I replace each character with and I change between naming it the npcs name and text to random guids that have nothing to do with the text` - sorry I can't help :P

### Style 1 - xVASynth v2
If you use xVASynth v2 and use its default exporting style:
```
/Game/Sounds/aivoice/ai_codec_text
```

e.g.

```
/Game/Sounds/GeneralButtlicker/duke_nukem_hifi_You_stole_from_the_wrong_person__Time_to_die
```

Then pick this style. Download this repo and go into the `xVASynth-v2-style` folder and follow the steps in the README.md (open in notepad or anything)

### Style 2 - NPCName/text
If you create a folder per NPC and set the sounds filename to be a stripped version of the text, this style is for you.
```
/Game/Sounds/aivoice/text
```

e.g.

```
/Game/Sounds/GeneralButtlicker/You_stole_from_the_wrong_person_Time_to_die
```

Then pick this style. Download this repo and go into the `npcname_text-style` folder and follow the steps in the README.md (open in notepad or anything)


### Help with new style

If the styles above don't work for your needs and you can logically explain your orginisation then download the style that looks as close to yours then modify it.

### SplitFilename
The export convention for xVASynth by default is:

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

If all your sounds start with something, maybe the speaker ID, maybe some emotion type, anything, and you can split on it, try to adapt this method and its call.
 
 
### CleanString
This method takes the text from your node and cleans it up removing anything that won't work in a file path. E.g. spaces.

It also has an optional parameter of maxCharacters. In order to restrict how much it has to query, while it builds up the cleaned string, it will return the max length. Typically, having a huge file names is a bad thing as it will cause issues cross OSs. You can set this max length to anything you want to suit your project. 25 is typically a good balance between dialogue.

This will entirely depend on how you name your files. In my case, I built it using xVASynth and tried to cater for thats random underscore additions lol

```
Hello and welcome to this years Mortal Kombat tournament! We hope you enjoy. At least we hope you do?
```

Would become:

```
Hello_and_welcome_to_this_years_Mortal_Kombat_tournament__We_hope_you_enjoy__At_least_we_hope_you_do_
```
or with max length of 25:

```
Hello_and_welcome_to_thi
```

But its just as easy to edit to remove all non [a-z] characters and replace spaces with underscores.

### Speaker ID path
One of the steps this mod takes to help speed up and return accurate dialogue, is it uses the Speaker ID of your node (Player is used for Player nodes)
and checks if the path of the sound contains the speaker id (stripped of spaces and such).

For example
A path of:

```
/Game/Sounds/hello_and_welcome_to_my_game.wav
```

would not work.

It would have to have the Speaker id in the folder structure:

```
/Game/Sounds/SPEAKER_ID/hello_and_welcome_to_my_game.wav
```
```
/Game/Sounds/Player/hello_and_welcome_to_my_game.wav
```

If you do not want this feature, you can modify the line:

```cpp
if (sound != nullptr && SoundPath.Contains(*cleanSpeakerID))
```

To instead be:

```cpp
if (sound != nullptr)
```

and remove the line:

```cpp
FString SoundPath = asset->GetPathName();
```

Just above it.
