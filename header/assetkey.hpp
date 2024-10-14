#ifndef __ASSETKEYS__
#define __ASSETKEYS__

namespace textures
{
	enum ID
	{
	    loading,
	    gremlins,
	    magnetic,
	    super_cars,
	    guyAndGirl,
	    ronAndNancy,
	    credits_original,
	    credits_additionnal,
	    pseudo,
	    game,
		cars,
		spritesheet,
		track,
		shadows,
        roadUp,
        roadDown,
        office,
        garage,
        darkgarage,
        ronAndNancyFont,
        supercarsfont,
        garageFont,
        goldenFont,
        whitecar,
        bluecar,
        redcar,
		win,
		podium,
		loose,
		end
	};
}

namespace sounds
{
	enum ID
	{
		applause,
		bouncingWheel,
		bump,
		gameOver,
		hornCountdown,
		tyresLong,
		tyresShort,
		tyresWater,
		floppy,
		cashDrawer,
		whatAreYouDoing
	};
}

namespace json
{
	enum ID
	{
		config,
		language
	};
}

#endif // __ASSETKEYS__
