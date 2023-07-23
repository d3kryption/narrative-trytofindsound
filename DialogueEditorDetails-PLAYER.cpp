// added in the player node check
else if (UDialogueNode_Player* PlayerNode = Cast<UDialogueNode_Player>(EditedObjects[0].Get()))
{
	if (!PlayerNode->OwningDialogue)
	{
		return;
	}

	if (UDialogueBlueprint* DialogueBP = Cast<UDialogueBlueprint>(PlayerNode->OwningDialogue->GetOuter()))
	{
		if (UDialogue * DialogueCDO = Cast<UDialogue>(DialogueBP->GeneratedClass->GetDefaultObject()))
		{
			AddTryToFindSoundButton(DetailLayout);
		}
	}
}
