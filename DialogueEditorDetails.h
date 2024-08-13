FReply TryToFindSoundOnSelected();
void TryToFindSound(UDialogueNode& node);
void TryToFindSoundOnNodes(const UDialogueNode& node);
FReply TryToFindSoundChildren();
FString CleanString(const FString& InString, const int maxCharacters, const FString& AlphaCharReplacement);
void AddTryToFindSoundButton(IDetailLayoutBuilder& DetailLayout);
