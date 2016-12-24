#include "Shader.h"
#include "../GameGlobal.h"
#include <iostream>

Shader::Shader(std::string sourceFile)
{
	HRESULT hr;
	ID3DXBuffer* error = NULL;
	hr = D3DXCreateEffectFromFileA(GameGlobal::GetCurrentDevice(), sourceFile.c_str(), 0, 0, 0, 0, &pShader ,&error);
	if(FAILED(hr))
	{
		if(error)
		{
			std :: cout << (char*)error ->GetBufferPointer();
		}
		else
		{
			std::cout <<"cant find shader";
		}
	}
}


Shader::~Shader(void)
{
	if(pShader)
	{
		pShader ->Release();
		pShader = NULL;
	}
}
