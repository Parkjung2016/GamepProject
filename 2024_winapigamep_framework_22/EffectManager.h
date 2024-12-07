#pragma once

class Object;
class Effect;
class EffectManager
{
	DECLARE_SINGLE(EffectManager)
public:
	void SpawnEffect(Vec2 _vSpawnPos, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fEffectDuration);
	Effect* SpawnEffect(Vec2 _vSpawnPos, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, Object* _parentObject);

};

