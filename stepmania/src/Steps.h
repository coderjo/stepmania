/* Steps - Holds note information for a Song.  A Song may have one or more Notes. */

#ifndef STEPS_H
#define STEPS_H

#include "GameConstantsAndTypes.h"
#include "PlayerNumber.h"
#include "Grade.h"
class NoteData;
class Profile;

class Steps
{
public:
	Steps();
	~Steps();

	// initializers
	void AutogenFrom( const Steps *parent, StepsType ntTo );
	void CopyFrom( Steps* pSource, StepsType ntTo );
	void CreateBlank( StepsType ntTo );

	void Compress() const;
	void Decompress() const;
	void DeAutogen();	/* If this Steps is autogenerated, make it a real Steps. */

	// Use a special value of difficulty
	bool IsAnEdit() const { return m_Difficulty == DIFFICULTY_EDIT; }
	bool WasLoadedFromProfile() const { return m_LoadedFromProfile != PROFILE_SLOT_INVALID; }
	ProfileSlot GetLoadedFromProfileSlot() const { return m_LoadedFromProfile; }
	unsigned GetHash() const { return Real()->m_uHash; }
	CString GetDescription() const { return Real()->m_sDescription; }
	Difficulty GetDifficulty() const { return Real()->m_Difficulty; }
	ProfileSlot GetLoadedFromProfile() const { return m_LoadedFromProfile; }
	int GetMeter() const { return Real()->m_iMeter; }
	const RadarValues& GetRadarValues() const { return Real()->m_RadarValues; }

	void SetDescription(CString desc);
	void SetDifficulty(Difficulty d);
	void SetLoadedFromProfile( ProfileSlot slot ) { m_LoadedFromProfile = slot; }
	void SetMeter(int meter);
	void SetRadarValue(int r, float val);
	bool IsAutogen() const;	// Was created by autogen?
	float PredictMeter() const;
	
	StepsType	m_StepsType;

	void		GetNoteData( NoteData* pNoteDataOut ) const;
	void		SetNoteData( const NoteData* pNewNoteData );
	void		SetSMNoteData( const CString &notes_comp, const CString &attacks_comp );
	void		GetSMNoteData( CString &notes_comp_out, CString &attacks_comp_out ) const;

	void TidyUpData();

protected:
	/* If this Steps is autogenerated, this will point to the autogen
	 * source.  If this is true, notes_comp will always be NULL. */
	const Steps *parent;

	/* We can have one or both of these; if we have both, they're always identical.
	 * Call Compress() to force us to only have notes_comp; otherwise, creation of 
	 * these is transparent. */
	mutable NoteData *notes;
	struct CompressedNoteData
	{
		CString notes, attacks;
	};
	mutable CompressedNoteData *notes_comp;

	const Steps *Real() const;

	/* These values are pulled from the autogen source first, if there is one. */
	ProfileSlot		m_LoadedFromProfile;	// PROFILE_SLOT_INVALID if wasn't loaded from a profile
	unsigned		m_uHash;			// only used if m_Difficulty == DIFFICULTY_EDIT
	CString			m_sDescription;		// Step author, edit name, or something meaningful
	Difficulty		m_Difficulty;		// difficulty classification
	int				m_iMeter;			// difficulty rating from MIN_METER to MAX_METER
	RadarValues		m_RadarValues;
};

#endif

/*
 * (c) 2001-2004 Chris Danford, Glenn Maynard
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
