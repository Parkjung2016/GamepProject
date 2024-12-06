#include "pch.h"
#include "EffectManager.h"

#include "Effect.h"
#include "Scene.h"
#include "SceneManager.h"

void EffectManager::SpawnEffect(Vec2 _vSpawnPos, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fEffectDuration)
{
	Effect* pEffect = new Effect;
	pEffect->SetPos(_vSpawnPos);
	pEffect->SetEffectAnimation(_vLT, _vSliceSize, _vStep, _frameCount, .05f);
	pEffect->SetSize({ 16,16 });
	pEffect->SetDurationTime(_fEffectDuration);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pEffect, LAYER::EFFECT);

}

Effect* EffectManager::SpawnEffect(Vec2 _vOffset, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount,
	Object* _parentObject)
{
	Effect* pEffect = new Effect;
	pEffect->SetOffset(_vOffset);
	pEffect->SetEffectAnimation(_vLT, _vSliceSize, _vStep, _frameCount, .15f);
	pEffect->SetSize({ 16,16 });
	pEffect->SetParent(_parentObject);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pEffect, LAYER::EFFECT);
	return pEffect;
}
