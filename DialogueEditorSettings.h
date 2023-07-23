/**
This is the folder that Narrative will search to find your sounds
*/
UPROPERTY(EditAnywhere, config, Category = "Sounds", noclear, meta = (MetaClass = "Sounds"))
FString SoundFolderLocation;

/**
This is the pattern that will be used when searching for your sound.
The default is: {SpeakerID}_{Text}
Available tags are:
{SpeakerID} - the ID of the speaker, spaces replaced via the AlphaCharReplacement
{Text} - the text of the node. Spaces are replaced via the AlphaCharReplacement then the max text length is applied
*/
UPROPERTY(EditAnywhere, config, Category = "Sounds", noclear, meta = (MetaClass = "Sounds"))
FString SoundSearchPattern;

/**
When adding the text from the dialogue node, this is the max length AFTER the space replacement it will try to use in the fuzzy search
*/
UPROPERTY(EditAnywhere, config, Category = "Sounds/Text", noclear, meta = (MetaClass = "Sounds/Text"))
int MaxTextLength;

/**
This is what spaces will be replaced by.
*/
UPROPERTY(EditAnywhere, config, Category = "Sounds/Text", noclear, meta = (MetaClass = "Sounds/Text"))
FString AlphaCharReplacement;

/**
This is the name of the folder your players voices are stored in
*/
UPROPERTY(EditAnywhere, config, Category = "Sounds/Text", noclear, meta = (MetaClass = "Sounds/Text"))
FString PlayerVoiceFolderName;
