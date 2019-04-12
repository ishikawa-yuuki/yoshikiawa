#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"
#include "tkEngine/graphics/preRender/tkLightCulling.h"
#include "tkEngine/graphics/preRender/shadow/tkDirectionShadowMap.h"
#include "tkEngine/graphics/preRender/tkGBufferRender.h"
#include "tkEngine/graphics/preRender/shadow/tkOminiDirectionShadowMap.h"

namespace tkEngine{
	
	/// <summary>
	/// �v�������_�����O�B
	/// </summary>
	class CPreRender : Noncopyable{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CPreRender();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CPreRender();
		
		/// <summary>
		/// �֐��B
		/// </summary>
		void Release();
		
		/// <summary>
		/// �쐬�B
		/// </summary>
		/// <param name="config"></param>
		void Create( const SGraphicsConfig& config );
		
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="rc"></param>
		void Render(CRenderContext& rc);
		/// <summary>
		/// �X�V�B
		/// </summary>
		void Update();
		
		/// <summary>
		/// �w�����V���h�E�}�b�v���擾�B
		/// </summary>
		/// <returns></returns>
		CDirectionShadowMap& GetDirectionShadowMap()
		{
			return m_directionShadowMap;
		}
		/// <summary>
		/// �S���ʃV���h�E�}�b�v���擾�B
		/// </summary>
		/// <returns></returns>
		COminiDirectionShadowMap& GetOminiDirectionShadowMap()
		{
			return m_ominiDirectionShadowMap;
		}
		
		/// <summary>
		/// G-Buffer���擾�B
		/// </summary>
		/// <returns></returns>
		CGBufferRender& GetGBufferRender()
		{
			return m_gbufferRender;
		}
	private:
		SGraphicsConfig		m_config;				//�R���t�B�O�B
		CLightCulling		m_lightCulling;			//���C�g�J�����O�B
		CDirectionShadowMap	m_directionShadowMap;	//�w�����V���h�E�}�b�v�B
		COminiDirectionShadowMap m_ominiDirectionShadowMap;	//�S���ʃV���h�E�}�b�v�B
		CGBufferRender		m_gbufferRender;		//G-Buffer�B
	};
}
#endif //_TKPRERENDER_H_