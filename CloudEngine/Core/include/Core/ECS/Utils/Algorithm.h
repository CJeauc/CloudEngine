#pragma once

#include "Core/stdafx.h"

namespace Core
{
		namespace Utils
		{
			template <typename T>
			void DepthFirstSearch(T p_vertex,
			                                 std::vector<int>& p_vertexState,
			                                 const std::vector<std::vector<bool>>& p_edges,
			                                 std::vector<T>& p_output)
			{
				p_vertexState[p_vertex] = 1; // visited

				for (int i = 0; i < p_vertexState.size(); ++i)
				{
					if (p_edges[i][p_vertex] == true && p_vertexState[i] == 0)
						DepthFirstSearch<T>(i, p_vertexState, p_edges, p_output);
				}

				p_vertexState[p_vertex] = 2; // done
				p_output.push_back(p_vertex);
			}
		}
}
