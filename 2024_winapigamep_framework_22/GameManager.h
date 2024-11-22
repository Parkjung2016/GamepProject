#pragma once
class GameManager
{
	DECLARE_SINGLE(GameManager);

public:
	void SetEditorMode(bool _bIsEditorMode) { m_bEditorMode = _bIsEditorMode; }
	bool GetEditorMode() const { return m_bEditorMode; }
private:
	bool m_bEditorMode;


};

