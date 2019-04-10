#pragma once

namespace GEX {

	enum class TextureID {	
		Character,
		City1,
		Block,
		Key,
		Boy,
		Girl,
		Police,
		RedCarToRight,
		WhiteCarToRight,
		TruckToRight,
		RedCarToLeft,
		WhiteCarToLeft,
		TruckToLeft,
		BusToLeft,
		Bunker,
		SignPost,
		TitleScreen,
		IntroScreen,
		ScoreScreen,
	};

	enum class FontID {
		Main
	};

	enum class MusicID {			// Scoped enum class is made for specific identifiers in music Ids
		MenuTheme,
		MissionTheme
	};

	enum class SoundEffectID {		// Scoped enum class is made for specific identifiers in sound effect Ids
		CharacterDead,
		KnockBunker,
		OpenBunker,
		GetKey,
		GetSignpost
	};
}