#include "Rendering/stdafx.h"
#include "Rendering/Resource/Cube.h"

using namespace Rendering;

Cube::Cube()
{
	m_positions = std::vector<CloudMath::Vector3f>{

					//Front Face
					CloudMath::Vector3f(-0.5f, 0.5f, 0.5f),	    //Front Top Left	    0
					CloudMath::Vector3f(0.5f, 0.5f, 0.5f),		//Front Top Right	    1
					CloudMath::Vector3f(-0.5f, -0.5f, 0.5f),	//Front Bottom Left	    2
					CloudMath::Vector3f(0.5f, -0.5f, 0.5f),		//Front Bottom Right	3

					//Right Face
					CloudMath::Vector3f(0.5f, 0.5f, 0.5f),		//Right Top Left		4	
					CloudMath::Vector3f(0.5f, 0.5f, -0.5f),		//Right Top Right		5
					CloudMath::Vector3f(0.5f, -0.5f, 0.5f),	    //Right Bottom Left		6
					CloudMath::Vector3f(0.5f, -0.5f, -0.5f),	//Right Bottom Right	7

					//Left Face
					CloudMath::Vector3f(-0.5f, 0.5f, -0.5f),	//Left Top Left			8         
					CloudMath::Vector3f(-0.5f, 0.5f, 0.5f),		//Left Top Right		9
					CloudMath::Vector3f(-0.5f, -0.5f, -0.5f),	//Left Bottom Left		10
					CloudMath::Vector3f(-0.5f, -0.5f, 0.5f),	//Left Bottom Right		11

					//Back Face
					CloudMath::Vector3f(-0.5f, 0.5f, -0.5f),	//Back Top Left			12				
					CloudMath::Vector3f(0.5f, 0.5f, -0.5f),		//Back Top Right		13
					CloudMath::Vector3f(-0.5f, -0.5f, -0.5f),	//Back Bottom Left		14
					CloudMath::Vector3f(0.5f, -0.5f, -0.5f),	//Back Bottom Right		15

					//Top Face
					CloudMath::Vector3f(-0.5f, 0.5f, -0.5f),	//Top Top Left			16	  			
					CloudMath::Vector3f(0.5f, 0.5f, -0.5f),		//Top Top Right			17
					CloudMath::Vector3f(-0.5f, 0.5f, 0.5f),		//Top Bottom Left		18
					CloudMath::Vector3f(0.5f, 0.5f, 0.5f),		//Top Bottom Right		19

					//Bottom Face
					CloudMath::Vector3f(-0.5f, -0.5f, 0.5f),	//Bottom Top Left		20	   		
					CloudMath::Vector3f(0.5f, -0.5f, 0.5f),		//Bottom Top Right		21
					CloudMath::Vector3f(-0.5f, -0.5f, -0.5f),	//Bottom Bottom Left	22
					CloudMath::Vector3f(0.5f, -0.5f, -0.5f),	//Bottom Bottom Right	23
	};

	m_normals = std::vector<CloudMath::Vector3f>{
					//Front
					CloudMath::Vector3f(0.0f, 0.0f, 1.0f),
					CloudMath::Vector3f(0.0f, 0.0f, 1.0f),
					CloudMath::Vector3f(0.0f, 0.0f, 1.0f),
					CloudMath::Vector3f(0.0f, 0.0f, 1.0f),

					//Right
					CloudMath::Vector3f(1.0f, 0.0f, 0.0f),
					CloudMath::Vector3f(1.0f, 0.0f, 0.0f),
					CloudMath::Vector3f(1.0f, 0.0f, 0.0f),
					CloudMath::Vector3f(1.0f, 0.0f, 0.0f),

					//Left
					CloudMath::Vector3f(-1.0f, 0.0f, 0.0f),
					CloudMath::Vector3f(-1.0f, 0.0f, 0.0f),
					CloudMath::Vector3f(-1.0f, 0.0f, 0.0f),
					CloudMath::Vector3f(-1.0f, 0.0f, 0.0f),

					//Back
					CloudMath::Vector3f(0.0f, 0.0f, -1.0f),
					CloudMath::Vector3f(0.0f, 0.0f, -1.0f),
					CloudMath::Vector3f(0.0f, 0.0f, -1.0f),
					CloudMath::Vector3f(0.0f, 0.0f, -1.0f),

					//Top
					CloudMath::Vector3f(0.0f, 1.0f, 0.0f),
					CloudMath::Vector3f(0.0f, 1.0f, 0.0f),
					CloudMath::Vector3f(0.0f, 1.0f, 0.0f),
					CloudMath::Vector3f(0.0f, 1.0f, 0.0f),

					//Bottom
					CloudMath::Vector3f(0.0f, -1.0f, 0.0f),
					CloudMath::Vector3f(0.0f, -1.0f, 0.0f),
					CloudMath::Vector3f(0.0f, -1.0f, 0.0f),
					CloudMath::Vector3f(0.0f, -1.0f, 0.0f)
	};

	m_UV = std::vector<CloudMath::Vector2f>{

					//Front Face
					CloudMath::Vector2f(0.0f, 1.0f),	//Front Top Left
					CloudMath::Vector2f(1.0f, 1.0f),	//Front Top Right
					CloudMath::Vector2f(0.0f, 0.0f),	//Front Bottom Left
					CloudMath::Vector2f(1.0f, 0.0f),	//Front Bottom Right
						
					//Right Face
					CloudMath::Vector2f(0.0f, 1.0f),	//Right Top Left
					CloudMath::Vector2f(1.0f, 1.0f),	//Right Top Right
					CloudMath::Vector2f(0.0f, 0.0f),	//Right Bottom Left
					CloudMath::Vector2f(1.0f, 0.0f),	//Right Bottom Right

					//Left Face
					CloudMath::Vector2f(0.0f, 1.0f),	//Left Top Left
					CloudMath::Vector2f(1.0f, 1.0f),	//Left Top Right
					CloudMath::Vector2f(0.0f, 0.0f),	//Left Bottom Left
					CloudMath::Vector2f(1.0f, 0.0f),	//Left Bottom Right

					//Back Face
					CloudMath::Vector2f(1.0f, 1.0f),	//Back Top Left
					CloudMath::Vector2f(0.0f, 1.0f),	//Back Top Right
					CloudMath::Vector2f(1.0f, 0.0f),	//Back Bottom Left
					CloudMath::Vector2f(0.0f, 0.0f),	//Back Bottom Right

					//Top Face
					CloudMath::Vector2f(0.0f, 1.0f),	//Top Top Left
					CloudMath::Vector2f(1.0f, 1.0f),	//Top Top Right
					CloudMath::Vector2f(0.0f, 0.0f),	//Top Bottom Left
					CloudMath::Vector2f(1.0f, 0.0f),	//Top Bottom Right

					//Bottom Face
					CloudMath::Vector2f(0.0f, 1.0f),	//Bottom Top Left
					CloudMath::Vector2f(1.0f, 1.0f),	//Bottom Top Right
					CloudMath::Vector2f(0.0f, 0.0f),	//Bottom Bottom Left
					CloudMath::Vector2f(1.0f, 0.0f)		//Bottom Bottom Right
	};

	m_indices = std::vector<unsigned int>{
			//Front
			0, 2, 3,
			0, 3, 1,

			//Right
			4, 6, 7,
			4, 7, 5,

			//Left
			8, 10, 11,
			8, 11, 9,

			//Back
			12, 15, 14,
			12, 13, 15,

			//Top
			16, 18, 19,
			16, 19, 17,

			//Bottom
			20, 22, 23,
			20, 23, 21
		};

	Finalize();

	/*m_positions.clear();
	m_UV.clear();
	m_normals.clear();
	m_indices.clear();*/
}
