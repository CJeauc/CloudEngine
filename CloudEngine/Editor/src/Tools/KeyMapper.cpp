#include <stdafx.h>
#include <KeyMapper.h>

using namespace QtEditor;

int QtEditor::KeyMapper::ToEngineInput(int p_qtKey)
{
	switch (p_qtKey)
	{
	case 16777248:
		return 340;
		break;

	default:
		return p_qtKey;
		break;
	}
}
