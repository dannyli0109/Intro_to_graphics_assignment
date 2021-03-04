#include "Utilities.h"

std::string LoadFileAsString(std::string filename)
{
	std::stringstream fileSoFar;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string thisLine;
			std::getline(file, thisLine);
			fileSoFar << thisLine << std::endl;
		}
		return fileSoFar.str();
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
		return "";
	}
}

//void OnWindowSizeChange(GLFWwindow* window, int newWidth, int newHeight, FrameBuffer* frameBuffer)
//{
//	glViewport(0, 0, newWidth, newHeight);
//	frameBuffer->Create(newWidth, newHeight);
//}

std::vector<std::string> Split(const std::string& s, std::string delimiter)
{
	std::vector<std::string> res;
	auto start = 0U;
	auto end = s.find(delimiter);
	while (end != std::string::npos)
	{
		res.push_back(s.substr(start, end - start));
		start = end + delimiter.length();
		end = s.find(delimiter, start);
	}
	res.push_back(s.substr(start, end));

	return res;
}


void ParseObj(
	std::string filename,
	std::vector<glm::vec3>& verts, std::vector<unsigned short>& vertIndices,
	std::vector<glm::vec2>& uvs, std::vector<unsigned short>& uvIndices,
	std::vector<glm::vec3>& normals, std::vector<unsigned short>& normalIndices,
	bool flipUV
)
{
	std::stringstream fileSoFar;
	std::ifstream file(filename);
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string thisLine;
			std::getline(file, thisLine);
			if (thisLine.substr(0, 2) == "v ") {
				std::istringstream v(thisLine.substr(2));
				float x, y, z;
				v >> x;
				v >> y;
				v >> z;
				verts.push_back({ x, y, z });
			}
			else if (thisLine.substr(0, 2) == "f ")
			{
				std::istringstream v(thisLine.substr(2));
				unsigned short newIndex;
				std::vector<std::string> face = Split(thisLine.substr(2), " ");
				std::vector<unsigned short> vis;
				std::vector<unsigned short> tis;
				std::vector<unsigned short> nis;
				for (int i = 0; i < face.size(); i++)
				{
					std::vector<std::string> elements = Split(face[i], "/");
					if (elements.size() > 0)
					{
						unsigned short vertIndex;
						std::istringstream vi(elements[0]);
						if (vi.str() != "")
						{
							vi >> vertIndex;
							vis.push_back(vertIndex - 1);
						}
					}

					if (elements.size() > 1)
					{
						unsigned short textureIndex;
						std::istringstream ti(elements[1]);
						if (ti.str() != "")
						{
							ti >> textureIndex;
							tis.push_back(textureIndex - 1);
						}
					}

					if (elements.size() > 2)
					{
						unsigned short normalIndex;
						std::istringstream ni(elements[2]);
						if (ni.str() != "")
						{
							ni >> normalIndex;
							nis.push_back(normalIndex - 1);
						}
					}
				}

				if (vis.size() >= 3)
				{
					vertIndices.push_back(vis[0]);
					vertIndices.push_back(vis[1]);
					vertIndices.push_back(vis[2]);
					for (int i = 3; i < vis.size(); i++)
					{
						vertIndices.push_back(vis[i - 3]);
						vertIndices.push_back(vis[i - 1]);
						vertIndices.push_back(vis[i]);
					}
				}

				if (tis.size() >= 3)
				{
					uvIndices.push_back(tis[0]);
					uvIndices.push_back(tis[1]);
					uvIndices.push_back(tis[2]);
					for (int i = 3; i < tis.size(); i++)
					{
						uvIndices.push_back(tis[i - 3]);
						uvIndices.push_back(tis[i - 1]);
						uvIndices.push_back(tis[i]);
					}
				}

				if (nis.size() >= 3)
				{
					normalIndices.push_back(nis[0]);
					normalIndices.push_back(nis[1]);
					normalIndices.push_back(nis[2]);
					for (int i = 3; i < nis.size(); i++)
					{
						normalIndices.push_back(nis[i - 3]);
						normalIndices.push_back(nis[i - 1]);
						normalIndices.push_back(nis[i]);
					}
				}

			}
			else if (thisLine.substr(0, 2) == "vt")
			{
				std::istringstream vt(thisLine.substr(2));
				float u, v;
				vt >> u;
				vt >> v;
				uvs.push_back({ u, flipUV ? (1.0f - v) : v });
			}
			else if (thisLine.substr(0, 2) == "vn")
			{
				std::istringstream vn(thisLine.substr(2));
				float x, y, z;
				vn >> x;
				vn >> y;
				vn >> z;
				normals.push_back({ x, y, z });
			}
		}
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
	}
}

bool VectorOfStringGetter(void* vec, int idx, const char** out_text)
{
	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	*out_text = vector.at(idx).c_str();
	return true;
}

