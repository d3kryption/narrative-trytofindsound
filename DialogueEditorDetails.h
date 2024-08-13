FReply TryToFindSoundOnSelected();
void TryToFindSound(UDialogueNode& node);
void TryToFindSoundOnNodes(const UDialogueNode& node, TSet<const UDialogueNode*>& VisitedNodes);
FReply TryToFindSoundChildren();
FString CleanString(const FString& InString, const int maxCharacters, const FString& AlphaCharReplacement);
void AddTryToFindSoundButton(IDetailLayoutBuilder& DetailLayout);
