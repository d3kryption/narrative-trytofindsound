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
                    .OnClicked(this, &FDialogueEditorDetails::TryToFindSound)
            [
                    SNew(STextBlock)
                            .Font(IDetailLayoutBuilder::GetDetailFontBold())
                            .Text(LOCTEXT("TryToFindSound", "Try to find sound"))
            ]
    ];
}

// try to find the sound based on path containing the speaker and the sound file name containing first 25 chars of text
FReply FDialogueEditorDetails::TryToFindSound()
{
    // array to store all selected objects & get them
    TArray<TWeakObjectPtr<UObject>> EditedObjects;
    LayoutBuilder->GetObjectsBeingCustomized(EditedObjects);

    // if array has at least 1 item
    if (EditedObjects.IsValidIndex(0))
    {
        // get the speaker ID
        FString speakerID = "";
        FString cleanSpeakerID = "";

        // get the text
        FString cleanSpeakerText = "";

        // check if we have NPC or Player node as they have different members
        if (UDialogueNode_NPC* nodeNPC = Cast<UDialogueNode_NPC>(EditedObjects[0].Get()))
        {
            speakerID = *nodeNPC->SpeakerID.ToString();
            cleanSpeakerText = *nodeNPC->Text.ToString();
        }
        else if (UDialogueNode_Player* nodePlayer = Cast<UDialogueNode_Player>(EditedObjects[0].Get()))
        {
            speakerID = "Player";
            cleanSpeakerText = *nodePlayer->Text.ToString();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("No NPC or player node, no idea what you are"));
            return FReply::Handled();
        }

        // clean up the speaker id
        cleanSpeakerID = CleanString(speakerID, 0);

        // log out the speaker id, text and the cleaned id
//        UE_LOG(LogTemp, Log, TEXT("Speaker ID: %s and cleaned ID: %s"), *speakerID, *cleanSpeakerID);

        // clean up text
        cleanSpeakerText = CleanString(cleanSpeakerText, 25);

//        UE_LOG(LogTemp, Log, TEXT("CLEANED TEXT %s"), *cleanSpeakerText);

        // get all assets at the specified path
        TArray<UObject*> SoundAssets;
        EngineUtils::FindOrLoadAssetsByPath(FString("/Game/Sounds"), SoundAssets, EngineUtils::ATL_Regular);

        // Create an array of USoundBase objects that match the file name
        TArray<UObject*> MatchingSounds;

        // loop through all found assets
        for (auto asset : SoundAssets)
        {
            // see if it can be cast to SoundBase and its path
            USoundBase* sound = Cast<USoundBase>(asset);
            FString SoundPath = asset->GetPathName();

//            UE_LOG(LogTemp, Log, TEXT("Path: %s and speakerID: %s"), *SoundPath, *cleanSpeakerID);

            if (sound != nullptr && SoundPath.Contains(*cleanSpeakerID))
            {
                // store the sound name
                FString soundName = *sound->GetName();

                // clean sound name
                soundName = CleanString(soundName, 25);

//                UE_LOG(LogTemp, Log, TEXT("SOUND: %s, IN DIR: %s"), *soundName, *SoundPath);

		        if (soundName == cleanSpeakerText) {
		            MatchingSounds.Add(asset);
		        }
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
            if (UDialogueNode_NPC* nodeNPC = Cast<UDialogueNode_NPC>(EditedObjects[0].Get()))
            {
                nodeNPC->DialogueSound = sound;
            }
            else if (UDialogueNode_Player* nodePlayer = Cast<UDialogueNode_Player>(EditedObjects[0].Get()))
            {
                nodePlayer->DialogueSound = sound;
            }
        }

        // Clear the array
        MatchingSounds.Empty();
    }

    return FReply::Handled();
}

// clean the string removing all alpha num characters
FString FDialogueEditorDetails::CleanString(const FString& InString, const int maxCharacters)
{
    FString CleanedString = "";

    for (int32 i = 0; i < InString.Len(); i++)
    {
        const TCHAR Char = InString[i];
        if (FChar::IsAlnum(Char))
        {
            CleanedString.AppendChar(Char);
        }

        // if we have max characters and we hit the limit
        if (maxCharacters > 0 && CleanedString.Len() == maxCharacters)
            break;
    }

    CleanedString.ToLowerInline();
    return CleanedString;
}
