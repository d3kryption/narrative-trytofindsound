#include "Sound/SoundBase.h" 
#include "EngineUtils.h"
#include "DialogueEditorSettings.h"

void FDialogueEditorDetails::AddTryToFindSoundButton(IDetailLayoutBuilder& DetailLayout)
{
	IDetailCategoryBuilder& MacrosCategory = DetailLayout.EditCategory("Macros");
	FText MacrosGroupLabel(LOCTEXT("MacrosGroup", "Macros"));

	// add quick find sound
	MacrosCategory.AddCustomRow(MacrosGroupLabel)
			.ValueContent()
	[
			SNew(SButton)
					.ButtonStyle(FAppStyle::Get(), "RoundButton")
					.OnClicked(this, &FDialogueEditorDetails::TryToFindSoundOnSelected)
			[
					SNew(STextBlock)
							.Font(IDetailLayoutBuilder::GetDetailFontBold())
							.Text(LOCTEXT("TryToFindSound", "Try to find sound"))
			]
	];

	// add quick find sound children
	MacrosCategory.AddCustomRow(MacrosGroupLabel)
			.ValueContent()
	[
			SNew(SButton)
					.ButtonStyle(FAppStyle::Get(), "RoundButton")
					.OnClicked(this, &FDialogueEditorDetails::TryToFindSoundChildren)
			[
					SNew(STextBlock)
							.Font(IDetailLayoutBuilder::GetDetailFontBold())
							.Text(LOCTEXT("TryToFindSoundChildren", "Try to find sound on children"))
			]
	];
}

// Call TryToFindSound on selected node
FReply FDialogueEditorDetails::TryToFindSoundOnSelected()
{
	// array to store all selected objects & get them
	TArray<TWeakObjectPtr<UObject>> EditedObjects;
	LayoutBuilder->GetObjectsBeingCustomized(EditedObjects);

	// if array has at least 1 item
	if (EditedObjects.IsValidIndex(0))
	{
		UDialogueNode* node = Cast<UDialogueNode>(EditedObjects[0].Get());
		TryToFindSound(*node);
	}
	return FReply::Handled();
}

// Loop over all connected nodes and call TryToFindSound
FReply FDialogueEditorDetails::TryToFindSoundChildren()
{
	// array to store all selected objects & get them
	TArray<TWeakObjectPtr<UObject>> EditedObjects;
	LayoutBuilder->GetObjectsBeingCustomized(EditedObjects);

	// if array has at least 1 item
	if (EditedObjects.IsValidIndex(0))
	{
        if (UDialogueNode* node = Cast<UDialogueNode>(EditedObjects[0].Get()))
        {
        	// Create a set to track visited nodes
        	TSet<const UDialogueNode*> VisitedNodes;
        	
        	TryToFindSoundOnNodes(*node, VisitedNodes);
        }
	}
    return FReply::Handled();
}

// Loop over all connected nodes and call TryToFindSound
void FDialogueEditorDetails::TryToFindSoundOnNodes(const UDialogueNode& node, TSet<const UDialogueNode*>& VisitedNodes)
{
	// Check if this node has already been visited
	if (VisitedNodes.Contains(&node))
	{
		return;  // Avoid infinite loop
	}

	// Mark this node as visited
	VisitedNodes.Add(&node);
	
	for (UDialogueNode* NPCReply : node.NPCReplies)
	{
		TryToFindSound(*NPCReply);
		TryToFindSoundOnNodes(*NPCReply, VisitedNodes);
	}

	// Loop over PlayerReplies and call this function recursively
	for (UDialogueNode* PlayerReply : node.PlayerReplies)
	{
		TryToFindSound(*PlayerReply);
		TryToFindSoundOnNodes(*PlayerReply, VisitedNodes);
	}
}

// try to find the sound based on path containing the speaker and the sound file name containing first 25 chars of text
void FDialogueEditorDetails::TryToFindSound(UDialogueNode& node)
{
    // load editors default settings 
    const UDialogueEditorSettings* DialogueSettings = GetDefault<UDialogueEditorSettings>();

    // get the speaker ID
    FString speakerID = "";
    FString cleanSpeakerID = "";

    // get the text
    FString cleanSpeakerText = "";

	// arrays to store found sounds and matched sounds
    TArray<UObject*> SoundAssets;
    TArray<UObject*> MatchingSounds;

	// replacement dialogue settings
    FString soundFolderLocation = DialogueSettings->SoundFolderLocation;
	FString searchPattern = DialogueSettings->SoundSearchPattern;

    // check if we have NPC or Player node as they have different members
    if (const UDialogueNode_NPC* nodeNPC = Cast<UDialogueNode_NPC>(&node))
    {
        speakerID = *nodeNPC->SpeakerID.ToString();
        cleanSpeakerText = *nodeNPC->Line.Text.ToString();
    }
    else if (const UDialogueNode_Player* nodePlayer = Cast<UDialogueNode_Player>(&node))
    {
        speakerID = DialogueSettings->PlayerVoiceFolderName;
        cleanSpeakerText = *nodePlayer->Line.Text.ToString();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No NPC or player node, no idea what you are"));
        return;
    }

    // clean up the speaker id
    cleanSpeakerID = CleanString(speakerID, 0, DialogueSettings->AlphaCharReplacement);

    UE_LOG(LogTemp, Log, TEXT("Speaker ID: %s"), *speakerID);
    UE_LOG(LogTemp, Log, TEXT("Cleaned Speaker ID: %s"), *cleanSpeakerID);

    // clean up text
    cleanSpeakerText = CleanString(cleanSpeakerText, DialogueSettings->MaxTextLength, DialogueSettings->AlphaCharReplacement);

    UE_LOG(LogTemp, Log, TEXT("Cleaned Text: '%s'"), *cleanSpeakerText);

	if (cleanSpeakerText.Len() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Text is empty. error?"));
		return;
	}

	// replace sound folder location with anything that needs to be replaced 
    soundFolderLocation.ReplaceInline(TEXT("{SpeakerID}"), *speakerID);

    UE_LOG(LogTemp, Log, TEXT("Sound path: %s"), *soundFolderLocation);

    // get all assets at the specified path
    EngineUtils::FindOrLoadAssetsByPath(soundFolderLocation, SoundAssets, EngineUtils::ATL_Regular);

    // replace search pattern's tags
	searchPattern.ReplaceInline(TEXT("{SpeakerID}"), *cleanSpeakerID);
	searchPattern.ReplaceInline(TEXT("{Text}"), *cleanSpeakerText);

    // loop through all found assets
    for (auto asset : SoundAssets)
    {
        // see if it can be cast to SoundBase and its path
        USoundBase* sound = Cast<USoundBase>(asset);

		// can we cast it?
		if (sound == nullptr)
			continue;

		// cast succesful, get details
        FString soundName = *sound->GetName(); // myvoice.wav
        FString soundPath = asset->GetPathName() + "/"; // /game/content/voice/

        // clean sound name
        soundName = CleanString(soundName, 0, DialogueSettings->AlphaCharReplacement);

		bool soundPathContainsFolder = soundPath.Contains(*soundFolderLocation);
		bool soundNameContainsSearchPattern = soundName.Contains(*searchPattern);

        UE_LOG(LogTemp, Log, TEXT("Path: '%s'"), *soundPath, *cleanSpeakerID);
        UE_LOG(LogTemp, Log, TEXT("SoundFolderLocation: '%s'"), *soundFolderLocation);
        UE_LOG(LogTemp, Log, TEXT("ContainsFolder: '%d'"), soundPathContainsFolder);

        UE_LOG(LogTemp, Log, TEXT("SoundName: '%s'"), *soundName);
        UE_LOG(LogTemp, Log, TEXT("SearchPattern: '%s'"), *searchPattern);
        UE_LOG(LogTemp, Log, TEXT("Contains search pattern: '%d'"), soundNameContainsSearchPattern);

		// check if the path contains the search pattern
        if (soundPathContainsFolder && soundNameContainsSearchPattern)
        {
            UE_LOG(LogTemp, Log, TEXT("FOUND SOUND: %s, IN DIR: %s"), *soundName, *soundPath);

	        MatchingSounds.Add(asset);
        }
    }

    // no audio was found
    if (MatchingSounds.Num() == 0) {
        UE_LOG(LogTemp, Error, TEXT("No audio found: %s"), *cleanSpeakerText);
    }
    // more than 1 audio meets the criteria
    else if (MatchingSounds.Num() > 1) {
        UE_LOG(LogTemp, Error, TEXT("%d results returned with name: %s"), MatchingSounds.Num(), *cleanSpeakerText);
    }
    // perfect
    else
    {
        USoundBase* sound = Cast<USoundBase>(MatchingSounds[0]);

        // check if we have NPC or Player node
        if (UDialogueNode_NPC* nodeNPC = Cast<UDialogueNode_NPC>(&node))
        {
            nodeNPC->Line.DialogueSound = sound;
        }
        else if (UDialogueNode_Player* nodePlayer = Cast<UDialogueNode_Player>(&node))
        {
            nodePlayer->Line.DialogueSound = sound;
        }
    }

    // Clear the array
    MatchingSounds.Empty();
}

// clean the string removing all alpha num characters
FString FDialogueEditorDetails::CleanString(const FString& InString, const int maxCharacters, const FString& AlphaCharReplacement)
{
    FString CleanedString = "";

    for (int32 i = 0; i < InString.Len(); i++)
    {
        const TCHAR Char = InString[i];

        if (FChar::IsAlnum(Char))
        {
            CleanedString.AppendChar(Char);
        }
		else
			CleanedString.Append(AlphaCharReplacement);

        // if we have max characters and we hit the limit
        if (maxCharacters > 0 && CleanedString.Len() == maxCharacters)
            break;
    }

    CleanedString.ToLowerInline();
    return CleanedString;
}
